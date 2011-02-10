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
#include "KTTTBackground.h"
#include "AutoScalingView.h"
#include "KDocument.h"

KTTTGame::KTTTGame(KDocument *document) : m_turn(1), m_commandHistory(new QStringList) {
    if (!document->isLoaded()) {
	return;
    }
    m_document = document;

    // Need some colors for the drawing.
    m_colors << QColor(Qt::blue) << QColor(Qt::red) << QColor(Qt::green) << QColor(Qt::darkRed) << QColor(Qt::yellow);

    // Some calculations
    int cellsPerCat = (TTT_COLS * TTT_ROWS) / (m_document->m_categories.size());
    QList<int> categoryCounter;
    for (int i = 0; i < m_document->m_categories.size(); i++) {
    	categoryCounter.append(cellsPerCat+1);
    }

    // Setup view
    m_view = new AutoScalingView();
    m_view->setMinimumSize(400*1.5, 400);


    // Setup scene
    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1, 1);
    m_view->setScene(m_scene);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHints(QPainter::Antialiasing);

    // Appending background
    m_background = new KTTTBackground(this);
    m_scene->addItem(m_background);


    // Draw simple TTT cells. (want the margins to be 1 cell width)
    qreal cellWidth = TTT_WIDTH / (TTT_COLS + 6);
    qreal cellHeight = TTT_HEIGHT / (TTT_ROWS + 2);


    // Inserting cells
    for (int i = 1; i < (TTT_COLS+1); i++) {
    	for (int j = 1; j < (TTT_ROWS+1); j++) {
	    int column = i-1;
	    int row = j-1;

	    // Pick a random category
    	    int category = 1;
    	    while (true) {
    	    	category = (((qreal)qrand() / RAND_MAX) * (m_document->m_categories.size()));

    	    	if (categoryCounter[category] > 0) {
    	    	    categoryCounter[category] = categoryCounter[category] - 1;
    	    	    break;
    	    	}
    	    }
	    
    	    TTTCell *cell = new TTTCell(m_document->m_categories[category], m_document, m_colors[category], this, column, row);
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
	
	nextTurn();
	m_commandHistory->append(command);
    }

    if (args[0].toLower() == "undo" && args[1].toLower() == "check") {
	int column = args[2].toInt();
	int row = args[3].toInt();

	nextTurn();

	m_cells[column][row]->setChecked(0);
    }
}



void KTTTGame::undo() {
    if (m_commandHistory->size() > 0) {

	QString command("undo ");
	command += m_commandHistory->takeLast();
	runCommand(command);

    }
}



void KTTTGame::setTurn(int turn) {
    if (turn % 2 == 0) {
	m_turn = 2;
    } else {
	m_turn = 1;
    }

    // Change turn
    m_background->update(m_background->boundingRect());


    // Evaluate winner
    
    // Two teams
    for (int team = 1; team <= 2; team++) {
	
	// Horizontal
	for (int row = 0; row < TTT_ROWS; row++) {
	    int got = 0;

	    for (int col = 0; col < TTT_COLS; col++) {
		if (m_cells[col][row]->checked() == team) {
		    got++;

		    if (got >= TTT_TARGET) {
			std::cout << "Got horizontal winner team " << team << std::endl;
		    }
		} else {
		    got = 0;
		}
	    }
	}


	// Vertical
	for (int col = 0; col < TTT_COLS; col++) {
	    int got = 0;
	   
	    for (int row = 0; row < TTT_ROWS; row++) {
		if (m_cells[col][row]->checked() == team) {
		    got++;

		    if (got >= TTT_TARGET) {
			std::cout << "Got vertical winner team " << team << std::endl;
		    }
		} else {
		    got = 0;
		}
	    }
	}


	// Diagonals
	int diagonals = TTT_ROWS + TTT_COLS;

	// Direction backslash (\)
	// Start from bottom left corner.
	// i walks vertical, j walks diagonal from bottom
	for (int i = 0; i < diagonals; i++) {
	    int got = 0;
	    
	    for (int j = 0; j < diagonals; j++) {
		int col = i-j;
		int row = TTT_ROWS-j;

		if (col < 0 || col > (TTT_COLS-1) ||
		    row < 0 || row > (TTT_ROWS-1)) {
		    continue;
		}
		
		if (m_cells[col][row]->checked() == team) {
		    got++;

		    if (got >= TTT_TARGET) {
			std::cout << "Got a backslash diagonal winner team " << team << std::endl;
		    }
		} else {
		    got = 0;
		}
	    }
	}

	
	// Direction slash (/)
	// Start from top right corner
	// i walks vertical, j walks diagonal from top
	for (int i = 0; i < diagonals; i++) {
	    int got = 0;

	    for (int j = 0; j < diagonals; j++) {
		int col = (TTT_COLS-i)-j;
		int row = j;

		if (col < 0 || col > (TTT_COLS-1) ||
		    row < 0 || row > (TTT_ROWS-1)) {
		    continue;
		}
		
		if (m_cells[col][row]->checked() == team) {
		    got++;

		    if (got >= TTT_TARGET) {
			std::cout << "Got a slash diagonal winner team " << team << std::endl;
		    }
		} else {
		    got = 0;
		}
	    }
	}
    }    
}
