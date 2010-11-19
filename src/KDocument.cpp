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



typedef unsigned int uint;


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
     * Categories
     */
    QDomNodeList categories = document.elementsByTagName("category");
    for (uint i = 0; i < categories.length(); i++) {
	
	QDomElement category = categories.at(i).toElement();
	m_categories.append(category.attribute("name"));

	

	/*
	 * Questions
	 */
	QDomNodeList questions = document.elementsByTagName("question");
	for (uint i = 0; i < categories.length(); i++) {
	    
	    QDomElement question = questions.at(i).toElement();
	    KQuestion q();
	    
	    // Type
	    if (question.attribute("type") == "alternatives") {
		q.setType(KQuestion::Alternatives);
	    } else {
		q.setType(KQuestion::Manual);
	    }

	    // Level
	    if (question.attribute("level") == "easy") {
		q.setLevel(KQuestion::Easy);
	    } else if (question.attribute("level") == "medium") {
		q.setLevel(KQuestion::Medium);
	    } else {
		q.setLevel(KQuestion::Hard);
	    }

	    // Image
	    QDomNodeList images = question.elementsByTagName("image");
	    if (images.count() > 0) {
		QDomElement image = images.at(0).toElement();
		QByteArray ba = QByteArray::fromBase64(image.text());
		QPixmap p();
		p.loadFromData(ba, "PNG");
		q.setImage(p);
	    }

	    // Answers
	    QDomNodeList answers = question.elementsByTagName("answer");
	    if (images.count() > 0) {
		QDomElement answer = answers.at(0).toElement();
		
    return true;
}




QVariant KDocument::setting(QString name) {
    return m_settings.value(name);
}



void KDocument::setSetting(QString name, QVariant value) {
    m_settings.insert(name, value);
}
