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
#include <QPen>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QFont>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QMessageBox>

#include "TTTCell.h"
#include "KTTTGame.h"
#include "KDocument.h"



TTTCell::TTTCell(QString category, KDocument *document, QColor color, KTTTGame *game, int column, int row) :
    QGraphicsObject(),
    m_category(category),
    m_document(document),
    m_color(color),
    m_game(game),
    m_column(column),
    m_row(row),
    m_checked(0) {
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
	if (m.exec() == QMessageBox::Yes) {

	    QString command("check ");
	    command += QString::number(m_column) + " " + QString::number(m_row);
	    m_game->runCommand(command);

	}
    }
}


void TTTCell::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (m_checked == 0) {

	painter->setPen(m_color);
	painter->fillRect(QRectF(0.1, 0.1, 0.9, 0.9), m_color);

    } else if (m_checked == 1) {

	painter->setPen(QPen(QBrush(QColor("blue")), 0.1));
	painter->drawEllipse(QRectF(0.2, 0.2, 0.7, 0.7));

    } else {
	
	painter->setPen(QPen(QBrush(QColor("red")), 0.1));
	painter->drawLine(QPointF(0.15, 0.15), QPointF(0.85, 0.85));
	painter->drawLine(QPointF(0.15, 0.85), QPointF(0.85, 0.15));

    }
}



