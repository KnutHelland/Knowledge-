/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

#include <QApplication>

#include "KDocument.h"
#include "KMainWindow.h"

int main(int args, char** argc) {

    QApplication app(args, argc);

    KMainWindow * window = new KMainWindow();
    window->showNormal();

    app.exec();

    return 0;
}
