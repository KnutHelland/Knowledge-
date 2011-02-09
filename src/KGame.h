/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KGAME_H
#define KGAME_H

#include <QObject>

class QWidget;
class KDocument;
class QPixmap;
class QString;

class KGame : public QObject {
    Q_OBJECT;

public:
    virtual QWidget * widget() = 0;
    virtual QPixmap * pixmap() = 0;
    virtual QString title() = 0;
    virtual QString description() = 0;
};

#endif
