/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

//#include <QMenuBar>
//#include <QMenu>
#include <QToolBar>

#include "KMainWindow.h"


KMainWindow::KMainWindow() : QMainWindow() {
    setWindowTitle("Knowledge");

    // // Menu bar
    // QMenuBar *menu = new QMenuBar();
    // QMenu *file = menu->addMenu("&File");
    // file->addAction

    // Tool bar
    QToolBar *actions = new QToolBar("Actions", this);
    actions->setIconSize(QSize(32, 32));
    actions->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addToolBar(Qt::TopToolBarArea, actions);

    actions->addAction(QIcon::fromTheme("document-open"), "Open game", this, SLOT(action_open()));
    // m_saveAction = actions->addAction(QIcon::fromTheme("document-save"), "Save", this, SLOT(action_save()));
    // actions->addAction(QIcon::fromTheme("document-save-as"), "Save as", this, SLOT(action_saveAs()));
}
