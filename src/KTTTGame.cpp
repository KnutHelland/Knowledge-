/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

#include <cstdlib>
#include <QGraphicsScene>
#include <QPen>
#include <iostream>
#include <QList>
#include <QColor>

#include "TTTCell.h"
#include "KTTTGame.h"
#include "AutoScalingView.h"
#include "KDocument.h"

KTTTGame::KTTTGame(KDocument *document) : m_turn(1) {
    if (!document->isLoaded()) {
	return;
    }
    m_document = document;

    // Need some colors for the drawing.
    QList<QColor> colors;
    colors << QColor(Qt::blue) << QColor(Qt::red) << QColor(Qt::green);

    // Some calculations
    int cellsPerCat = (TTT_COLS * TTT_ROWS) / (m_document->m_categories.size());
    QList<int> categoryCounter;
    for (int i = 0; i < m_document->m_categories.size(); i++) {
    	categoryCounter.append(cellsPerCat+1);
    }

    // Setup view
    m_view = new AutoScalingView();
    m_view->setMinimumSize(400, 400);


    // Setup scene
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1, 1);
    m_view->setScene(m_scene);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHints(QPainter::Antialiasing);


    // Draw simple TTT cells. (want the margins to be 1 cell width)
    qreal cellWidth = TTT_WIDTH / (TTT_COLS + 2);
    qreal cellHeight = TTT_HEIGHT / (TTT_ROWS + 2);


    // Inserting cells
    for (int i = 1; i < (TTT_COLS+1); i++) {
    	for (int j = 1; j < (TTT_ROWS+1); j++) {
	    int column = i-1;
	    int row = j-1;

    	    int category = 1;
    	    while (true) {
    	    	category = (((qreal)qrand() / RAND_MAX) * (m_document->m_categories.size()));
		// std::cout << category << std::endl;
    	    	if (categoryCounter[category] > 0) {
    	    	    categoryCounter[category] = categoryCounter[category] - 1;
    	    	    break;
    	    	}
    	    }
	    
    	    TTTCell *cell = new TTTCell(m_document->m_categories[category], m_document, colors[category], this, column, row);
	    
    	    cell->scale(cellWidth, cellHeight);

    	    cell->setPos((qreal)i * cellWidth, (qreal)j * cellHeight);
    	    m_scene->addItem(cell);

	    m_cells[column][row] = cell;
    	}
    }
}



/**
 * action arg arg arg arg
 *
 * check 3 4 (check column 3 row 4 with team 1)
 * undo check 3 4
 */
void KTTTGame::runCommand(QString command) {
    QStringList args = command.split(" ");
    
    if (args[0].toLower() == "check") {
	int column = args[1].toInt();
	int row = args[2].toInt();

	m_cells[column][row]->setChecked(m_turn);

	if (m_turn == 2) {
	    m_turn = 1;
	} else {
	    m_turn++;
	}
    }

    if (args[0].toLower() == "undo" && args[1].toLower() == "check") {
	int column = args[2].toInt();
	int row = args[3].toInt();

	m_cells[column][row]->setChecked(0);
    }
}
