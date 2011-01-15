/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <iostream>
#include <QtCore>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QFont>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "TTTCell.h"
#include "KDocument.h"



TTTCell::TTTCell(KDocument* document, QString* category) : QGraphicsObject() {
    m_document = document;
    m_category = category;
}


void TTTCell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->type() == QEvent::GraphicsSceneMouseDoubleClick) {
	// Open the question
	std::cout << "Gonna open" << std::endl;
    }
}


void TTTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::blue);
    painter->fillRect(QRectF(0.1, 0.1, 0.9, 0.9), Qt::blue);
}



