/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

//#include <QMenuBar>
//#include <QMenu>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>

#include "KMainWindow.h"
#include "KTTTGame.h"
#include "KNoGame.h"
#include "KDocument.h"


KMainWindow::KMainWindow() : QMainWindow(), m_document(0) {
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
    actions->addAction(QIcon::fromTheme("view-refresh"), "Restart game", this, SLOT(action_restart()));
    // m_saveAction = actions->addAction(QIcon::fromTheme("document-save"), "Save", this, SLOT(action_save()));
    // actions->addAction(QIcon::fromTheme("document-save-as"), "Save as", this, SLOT(action_saveAs()));


    m_game = new KNoGame(new KDocument());
    setCentralWidget(m_game->widget());
    // m_game = new KTTTGame(new KDocument());
    // setCentralWidget(m_game->widget());
}


void KMainWindow::action_open() {
    // Reset current game?
    if (m_document != 0 && m_document->isLoaded()) {
	if (QMessageBox(QMessageBox::Question, "Open game", "By opening a new game, the current game state will be lost. Do you want to continue?", QMessageBox::Yes | QMessageBox::No).exec() == QMessageBox::No) {
	    return;
	}
    }


    QFileDialog dialog(this, "Open file", "", "Knowledge file (*.kxml)");
    dialog.setFileMode(QFileDialog::ExistingFile);

    if (dialog.exec()) {
	QString filename = dialog.selectedFiles()[0];

	m_document = new KDocument();
	if (!m_document->loadKxml(filename)) {

	    QMessageBox(QMessageBox::Critical, "Could not load", "Could not load the selected file. Bad format.", QMessageBox::Ok, this).exec();

	} else {
	    
	    delete m_game;
	    m_game = new KTTTGame(m_document);
	    setCentralWidget(m_game->widget());

	}
    }
}



/**
 * Restart the game
 */
void KMainWindow::action_restart() {
    if (m_document == 0 || !m_document->isLoaded()) {
	return;
    }

    QMessageBox m(QMessageBox::Question, "Restart", "Do you really want to restart game? The current game will be lost.", QMessageBox::Yes | QMessageBox::No, this);
    if (m.exec() == QMessageBox::Yes) {
	
	delete m_game;
	m_game = new KTTTGame(m_document);
	setCentralWidget(m_game->widget());

    }
}
