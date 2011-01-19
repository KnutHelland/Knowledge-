/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <iostream>

#include "KNoGame.h"
#include "AutoScalingView.h"
#include "KDocument.h"



KNoGame::KNoGame(KDocument *) {
    m_view = new AutoScalingView();
    m_view->setMinimumSize(400, 400);

    m_scene = new QGraphicsScene();
    m_scene->setSceneRect(0, 0, 1, 1);
    m_view->setScene(m_scene);

    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHints(QPainter::Antialiasing);

    m_scene->addRect(0, 0, 1, 1, Qt::NoPen, QBrush(Qt::darkGray));
    QGraphicsTextItem *t = m_scene->addText("Open a knowledge database file to play", QFont("Sans-serif", 12, QFont::Bold));
    t->setDefaultTextColor(Qt::white);
    t->setPos(0.1, 0.3);
    t->scale(0.002, 0.002);
}

