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

class KMainWindow : public QMainWindow {
    Q_OBJECT;

public:
    KMainWindow();

protected:
    KGame *m_game;
    KDocument *m_document;

public slots:
    void action_open();
};


#endif
