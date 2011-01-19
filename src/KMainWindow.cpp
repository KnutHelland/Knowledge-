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

#include "KMainWindow.h"
#include "KTTTGame.h"
#include "KDocument.h"


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


    m_game = new KTTTGame();
    setCentralWidget(m_game->widget());
}


void KMainWindow::action_open() {
    QFileDialog dialog(this, "Open file", "", "Knowledge file (*.kxml)");
    dialog.setFileMode(QFileDialog::ExistingFile);

    if (dialog.exec()) {
	QString filename = dialog.selectedFiles()[0];

	m_document = new KDocument();
	if (!m_document->loadKxml(filename)) {
	    QMessageBox(QMessageBox::Critical, "Could not load", "Could not load the selected file. Bad format.", QMessageBox::Ok, this).exec();
	}
    }
}
