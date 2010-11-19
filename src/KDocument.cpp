/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include "KDocument.h"

#include <QStringList>
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
    file.open(QIODevice::ReadOnly);
    QDomDocument document("kxml");
    
    if (!document.setContent(&file)) {
	return false;
    }

    /*
     * Meta information
     */
    QStringList meta;
    meta << "title" << "author" << "description" << "language";
    for (int i = 0; i < meta.size(); i++) {
	
	setProperty(
	    meta.at(i).toUtf8(),
	    document.elementsByTagName( meta.at(i) ).at(0).toElement().text()
	);

    }


    /*
     * Questions
     */


    return true;
}




QVariant KDocument::setting(QString name) {
    return m_settings.value(name);
}



void KDocument::setSetting(QString name, QVariant value) {
    m_settings.insert(name, value);
}
