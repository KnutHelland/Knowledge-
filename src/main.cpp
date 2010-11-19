/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */

#include <QApplication>

#include "KDocument.h"

int main(int args, char** argc) {

    QApplication app(args, argc);

    KDocument doc;
    doc.loadKxml("../example.kxml");
    doc.saveKxml("output.kxml");

    app.exec();

    return 0;
}
