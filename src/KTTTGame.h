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


#define TTT_COLS 6
#define TTT_ROWS 6
#define TTT_WIDTH 1.0
#define TTT_HEIGHT 1.0
#define TTT_TARGET 4    // How long to win?

class TTTCell;
class QStringList;
class QGraphicsScene;
class QWidget;
class KDocument;


class KTTTGame : public KGame {
    Q_OBJECT;
    Q_PROPERTY(int turn READ turn WRITE setTurn);

public:
    KTTTGame(KDocument *);
    ~KTTTGame() {
	delete m_view;
	delete m_scene;
    }


    virtual QWidget * widget() { return static_cast<QWidget *>(m_view); }
    virtual QPixmap * pixmap() { return 0; }
    virtual QString title() { return "Tic Tac Toe"; }
    virtual void runCommand(QString command);

    virtual QString description() { 
	return "A knowledge duell on a classic tic tac toe game.";
    }

    void undo();
    
    void setTurn(int);
    int turn() { return m_turn; }
    void nextTurn() { setTurn(turn() + 1); }


protected:
    TTTCell *m_cells[TTT_COLS][TTT_ROWS];

    AutoScalingView *m_view;
    QGraphicsScene *m_scene;
    
    int m_turn;

    KDocument *m_document;
    QStringList *m_commandHistory;
};


#endif
