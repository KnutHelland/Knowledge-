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

class QWidget;



class KTTTGame : public KGame {
public:
    KTTTGame();

    virtual QWidget * widget() { return m_widget; }
    virtual QPixmap * pixmap() { return 0; }
    virtual QString title() { return "Tic Tac Toe"; }

    virtual QString description() { 
	return "A knowledge duell on a classic tic tac toe game.";
    }

    virtual void load(KDocument *);

protected:
    QWidget *m_widget;
    KDocument *m_document;
};


#endif
