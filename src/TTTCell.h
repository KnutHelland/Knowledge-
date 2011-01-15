/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef TTTCELL_H
#define TTTCELL_H

#include <QGraphicsObject>
#include <QRect>

class KDocument;
class QString;
class QEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneMouseEvent;


class TTTCell : public QGraphicsObject {
    Q_OBJECT;

public:
    TTTCell(KDocument*, QString* category);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

     virtual QRectF boundingRect() const {
	 return QRectF(0, 0, 1, 1);
     }
     void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget*);


protected:
    KDocument *m_document;
    QString *m_category;
};

#endif
