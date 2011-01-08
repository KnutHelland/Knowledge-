/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KTTTGAME_H
#define KTTTGAME_H

#include <QString>

#include "KGame.h"
#include "AutoScalingView.h"

class QGraphicsScene;
class QWidget;



class KTTTGame : public KGame {
public:
    KTTTGame();

    virtual QWidget * widget() { return static_cast<QWidget *>(m_view); }
    virtual QPixmap * pixmap() { return 0; }
    virtual QString title() { return "Tic Tac Toe"; }

    virtual QString description() { 
	return "A knowledge duell on a classic tic tac toe game.";
    }

    virtual void load(KDocument *);

protected:
    AutoScalingView *m_view;
    QGraphicsScene *m_scene;
    
    KDocument *m_document;
};


#endif
