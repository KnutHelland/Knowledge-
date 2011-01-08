/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <QGraphicsScene>
#include <QPen>

#include "KTTTGame.h"
#include "AutoScalingView.h"


KTTTGame::KTTTGame() {
    m_view = new AutoScalingView();
    m_view->setMinimumSize(400, 400);


    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1, 1);
    m_view->setScene(m_scene);


    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHints(QPainter::Antialiasing);
}


void KTTTGame::load(KDocument *) {
    
}
