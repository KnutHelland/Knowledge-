/**
 * This is a part of Knowledge!
 * All rights reserved to Knut Helland.
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @copyright Knut Helland 2010
 */


#include "KDocument.h"

#include <QFile>

#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QDomNodeList>



KDocument::KDocument() {

}



/**
 * Parse a kxml file and insert content into the document. Returns
 * true on success.
 */
bool KDocument::loadKxml(QString filename) {
    QFile file(filename);
    file->open(QUIDevice::ReadOnly);
    QDomDocument document("kxml");
    
    if (!document.setContent(file)) {
	return false;
    }

    /*
     * Meta information
     */
    QList meta() << "title" << "author" << "description" << "language";
    for (i = 0; i < meta.size(); i++) {
	
	setProperty(
	    meta.at(i),
	    document.elementsByTagName( meta.at(i) ).at(0).toElement().text()
	);

    }


    /*
     * Questions
     */


    return true;
}




QVariant setting(QString name) {
    return m_settings.value(name);
}



void setSetting(QString name, QVariant value) {
    m_settings.set(name, value);
}
