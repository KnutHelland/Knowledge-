/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KTTTBACKGROUND_H
#define KTTTBACKGROUND_H

#include <QGraphicsItem>

class KTTTGame;

class KTTTBackground : public QGraphicsItem {
public:
    KTTTBackground(KTTTGame *g) : m_game(g) {}

    virtual QRectF boundingRect() const {
	return QRectF(0, 0, 1, 1);
    }
    void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget*);

protected:
    KTTTGame *m_game;

};

#endif
