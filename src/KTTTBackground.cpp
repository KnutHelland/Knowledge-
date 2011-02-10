/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

#include <iostream>

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QFont>
#include <QColor>
#include <QString>

#include "KTTTBackground.h"
#include "KTTTGame.h"
#include "KDocument.h"


void KTTTBackground::paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) {
    qreal scale = 0.005;
    painter->scale(scale, scale);

    // Draw simple TTT cells. (want the margins to be 1 cell width)
    qreal cellWidth = TTT_WIDTH / (TTT_COLS + 6) / scale;
    qreal cellHeight = TTT_HEIGHT / (TTT_ROWS + 2) / scale;

    painter->setPen(QColor("black"));

    QFont f("Arial");
    f.setPointSize(8);
    painter->setFont(f);

    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Draw letters horizontally
    for (int i = 0; i < TTT_COLS; i++) {
	int x = cellWidth * (i+1.5);
	int y = 0.8 * cellHeight;

	painter->drawText(x, y, QString(alphabet[i]));
    }

    // Draw numbers vertically
    for (int i = 0; i < TTT_ROWS; i++) {
	int x = 0.7 * cellWidth;
	int y = cellHeight * (i+1.7);

	painter->drawText(x, y, QString::number(i));
    }

    // List categories
    QList<QString> *cats = &m_game->m_document->m_categories;
    for (int i = 0; i < cats->size(); i++) {
	painter->setFont(QFont("Arial", 6));
	painter->setPen(m_game->m_colors[i]);
	painter->drawText(0.65/scale, 8 * (i+5.7), cats->at(i));
    }


    // Whos turn?
    
}
