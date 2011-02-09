/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QFont>
#include <QColor>
#include <QString>

#include "KTTTBackground.h"
#include "KTTTGame.h"



void KTTTBackground::paint(QPainter* painter, const QStyleOptionGraphicsItem *, QWidget *) {
    qreal scale = 0.1;
    painter->scale(scale, scale);

    // Draw simple TTT cells. (want the margins to be 1 cell width)
    qreal cellWidth = TTT_WIDTH / (TTT_COLS + 2) * scale;
    qreal cellHeight = TTT_HEIGHT / (TTT_ROWS + 2) * scale;

    painter->setPen(QColor("black"));

    QFont f("Arial");
    f.setPointSizeF(1.);
    painter->setFont(f);

    // Draw letters horizontally
    for (int i = 0; i < TTT_COLS; i++) {
	int x = cellWidth * (i+1);
	int y = 0.5 * cellHeight;

	painter->drawText(x, y, QString::number(i));
    }
}
