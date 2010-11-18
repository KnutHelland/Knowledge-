/**
 * This is a part of Knowledge!
 * All rights reserved to Knut Helland.
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @copyright Knut Helland 2010
 */


#include "KDocument.h"

#include <QString>



KDocument::KDocument() {

}



bool KDocument::loadKxml(QString filename) {
    return true;
}




QVariant setting(QString name) {
    return m_settings.value(name);
}



void setSetting(QString name, QVariant value) {
    m_settings.set(name, value);
}
