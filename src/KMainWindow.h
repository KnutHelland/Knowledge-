/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include <QMainWindow>

class KGame;
class KDocument;
class QAction;

class KMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    KMainWindow();
    
    QAction *m_undoAction;

protected:
    KGame *m_game;
    KDocument *m_document;

public slots:
    void action_open();
    void action_restart();
    void action_undo();
};


#endif
