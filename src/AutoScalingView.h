/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

#ifndef AUTOSCALINGVIEW_H
#define AUTOSCALINGVIEW_H

#include <QGraphicsView>
#include <QResizeEvent>


class AutoScalingView : public QGraphicsView {
private:
    qreal m_prevScaleW;
    qreal m_prevScaleH;

public:
    AutoScalingView() : QGraphicsView(), m_prevScaleW(1), m_prevScaleH(1) {};

    virtual void resizeEvent(QResizeEvent *e) {
	scale(1/m_prevScaleW, 1/m_prevScaleH);
	scale(e->size().width(), e->size().height());

	m_prevScaleW = e->size().width();
	m_prevScaleH = e->size().height();
    }
};

#endif
