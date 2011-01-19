/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <QGraphicsScene>
#include <QPen>
#include <iostream>

#include "TTTCell.h"
#include "KTTTGame.h"
#include "AutoScalingView.h"
#include "KDocument.h"

#define TTT_COLS 7
#define TTT_ROWS 7


KTTTGame::KTTTGame(KDocument *document) {
    if (!document->isLoaded()) {
	return;
    }

    m_view = new AutoScalingView();
    m_view->setMinimumSize(400, 400);


    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1, 1);
    m_view->setScene(m_scene);


    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHints(QPainter::Antialiasing);

    // Draw simple TTT cells. (want the margins to be 1 cell width)
    qreal cellWidth = 1.0 / (TTT_COLS + 2);
    qreal cellHeight = 1.0 / (TTT_ROWS + 2);

    // Columns
    for (int i = 2; i < (TTT_COLS+1); i++) {
	m_scene->addLine((qreal)i * cellWidth, cellWidth, (qreal)i * cellWidth, 1-cellWidth);
    }

    // Rows
    for (int i = 2; i < (TTT_ROWS+1); i++) {
	m_scene->addLine(cellHeight, (qreal)i * cellHeight, 1-cellHeight, (qreal)i * cellHeight);
    }


    // Inserting cells
    for (int i = 1; i < (TTT_COLS+1); i++) {
	for (int j = 1; j < (TTT_ROWS+1); j++) {
	    TTTCell *cell = new TTTCell(new KDocument(), new QString());

	    cell->scale(cellWidth, cellHeight);

	    cell->setPos((qreal)i * cellWidth, (qreal)j * cellHeight);
	    m_scene->addItem(cell);
	}

    }


}



