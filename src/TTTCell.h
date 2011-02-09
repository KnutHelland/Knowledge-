/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef TTTCELL_H
#define TTTCELL_H

#include <QGraphicsObject>
#include <QColor>
#include <QRect>

class KDocument;
class QString;
class QEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QGraphicsSceneMouseEvent;
class KTTTGame;

class TTTCell : public QGraphicsObject {
    Q_OBJECT;
    Q_PROPERTY(int checked READ checked WRITE setChecked);

public:
    TTTCell(QString, KDocument *, QColor color, KTTTGame*, int, int);
    void mousePressEvent(QGraphicsSceneMouseEvent *);

    virtual QRectF boundingRect() const {
	return QRectF(0, 0, 1, 1);
    }
    void paint(QPainter*, const QStyleOptionGraphicsItem *, QWidget*);
    void setChecked(int value) { if (value < 3 && value >= 0) { m_checked = value; update(boundingRect()); } }
    int checked() { return m_checked; }


protected:
    QString m_category;
    KDocument *m_document;
    QColor m_color;
    KTTTGame *m_game;
    int m_column;
    int m_row;
    int m_checked;
};

#endif
