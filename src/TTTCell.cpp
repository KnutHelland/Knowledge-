/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <cstdlib>
#include <iostream>

#include <QtCore>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QFont>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QMessageBox>

#include "TTTCell.h"
#include "KDocument.h"



TTTCell::TTTCell(QString category, KDocument *document, QColor color) :
    QGraphicsObject(),
    m_category(category),
    m_document(document),
    m_color(color) {
}


void TTTCell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->type() == QEvent::GraphicsSceneMouseDoubleClick) {

	// Get a random question from correct category.
	int categoryNumber;
	KQuestion *question;
	while(true) {
	    categoryNumber = ((qreal)qrand() / RAND_MAX) * m_document->m_questions.size();
	    if (m_document->m_questions[categoryNumber].category() == m_category) {
		question = &m_document->m_questions[categoryNumber];
		break;
	    }
	}

	QMessageBox m;
	m.setWindowTitle(m_category);
	m.setText(question->text() + "\n\nRett svar?");
	m.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	m.exec();
    }
}


void TTTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(m_color);
    painter->fillRect(QRectF(0.1, 0.1, 0.9, 0.9), m_color);
}



