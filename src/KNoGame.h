/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KNOGAME_H
#define KNOGAME_H

#include <QString>

#include "AutoScalingView.h"
#include "KGame.h"

class QGraphicsScene;
class QWidget;

class KNoGame : public KGame {
    Q_OBJECT;

public:
    KNoGame(KDocument *);
    ~KNoGame();

    virtual QWidget * widget() { return static_cast<QWidget *>(m_view); }
    virtual QPixmap * pixmap() { return 0; }
    virtual QString title() { return "No game loaded"; }

    virtual QString description() { 
	return "Open a kxml file for playing";
    }


protected:
    AutoScalingView *m_view;
    QGraphicsScene *m_scene;
    
    KDocument *m_document;
};


#endif
