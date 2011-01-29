/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#include <QStringList>
#include <QByteArray>
#include <QBuffer>
#include <QVariant>
#include <QFile>

#include <QDomDocument>
#include <QDomElement>
#include <QDomText>
#include <QDomNodeList>

#include <iostream>

#include "KDocument.h"





KDocument::KDocument() {
    m_isLoaded = false;
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
	for (uint j = 0; j < questions.length(); j++) {
	    
	    QDomElement question = questions.at(j).toElement();
	    KQuestion q;

	    q.setCategory(category.attribute("name"));

	    // Text
	    QDomElement text = question.elementsByTagName("text").at(0).toElement();
	    q.setText(text.text());

	    // Id
	    if (question.hasAttribute("id")) {
		q.setId(question.attribute("id").toInt());
	    }
	    
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
		QByteArray ba = QByteArray::fromBase64(image.text().toUtf8());
		QPixmap p;
		p.loadFromData(ba, "PNG");
		q.setImage(p);
	    }

	    // Answers
	    QDomNodeList answers = question.elementsByTagName("answer");
	    for (uint k = 0; k < answers.length(); k++) {
		QDomElement answer = answers.at(k).toElement();
		
		if (answer.attribute("correct") != 0) {
		    q.m_answers.prepend(answer.text());
		} else {
		    q.m_answers.append(answer.text());
		}
	    }

	    m_questions.append(q);
	}
    }

    /*
     * Settings
     */
    QDomNodeList settings = document.elementsByTagName("setting");
    for (uint i = 0; i < settings.length(); i++) {
	
	QDomElement setting = settings.at(i).toElement();
	m_settings.insert(
	    setting.attribute("name"),
	    QVariant(setting.text())
	);

    }

    m_isLoaded = true;
    return true;
}



bool KDocument::saveKxml(QString filename) {
    QDomDocument document("kxml");

    QDomElement root = document.createElement("kxml");
    document.appendChild(root);

    /*
     * <meta>
     */
    {
    	QDomElement meta = document.createElement("meta");
    	root.appendChild(meta);

    	QDomElement title = document.createElement("title");
    	title.appendChild(document.createTextNode(m_title));
    	meta.appendChild(title);

    	QDomElement author = document.createElement("author");
    	author.appendChild(document.createTextNode(m_author));
    	meta.appendChild(author);

    	QDomElement description = document.createElement("description");
    	description.appendChild(document.createTextNode(m_description));
    	meta.appendChild(description);

    	QDomElement language = document.createElement("language");
    	language.appendChild(document.createTextNode(m_language));
    	meta.appendChild(language);
    }


    /*
     * <questions>
     */
    {
    	QDomElement questions = document.createElement("questions");
    	root.appendChild(questions);

    	for (int i = 0; i < m_categories.size(); i++) {
	    
    	    QDomElement category = document.createElement("category");
    	    category.setAttribute("name", m_categories.at(i));
    	    questions.appendChild(category);

    	    for (int j = 0; j < m_questions.size(); j++) {
    		if (m_questions.at(j).category() == m_categories.at(i)) {
    		    const KQuestion *q = &m_questions.at(j);

    		    QDomElement question = document.createElement("question");
    		    category.appendChild(question);

    		    if (q->type() == KQuestion::Manual) {
    		    	question.setAttribute("type", "manual");
    		    } else {
    		    	question.setAttribute("type", "alternatives");
    		    }

    		    if (q->level() == KQuestion::Easy) {
    		    	question.setAttribute("level", "easy");
    		    } else if (q->level() == KQuestion::Medium) {
    		    	question.setAttribute("level", "medium");
    		    } else {
    		    	question.setAttribute("level", "hard");
    		    }
		    
		    if (q->id() > 0) {
			question.setAttribute("id", q->id());
		    }

    		    // Text
    		    QDomElement text = document.createElement("text");
    		    text.appendChild(document.createTextNode(q->text()));
    		    question.appendChild(text);

		    if (!q->image().isNull()) {
			// Image
			QByteArray ba;
			QBuffer buffer(&ba);
			buffer.open(QIODevice::WriteOnly);
			q->image().save(&buffer, "PNG");
		    		    
			QDomElement image = document.createElement("image");
			image.appendChild(document.createTextNode(ba.toBase64()));
			question.appendChild(image);
		    }

    		    // Answers
    		    for (int k = 0; k < q->m_answers.length(); k++) {
			
    		    	QDomElement answer = document.createElement("answer");
    		    	answer.appendChild(document.createTextNode(q->m_answers[k]));
			
    		    	if (k == 0) {
    		    	    answer.setAttribute("correct", "correct");
    		    	}

    		    	question.appendChild(answer);

    		    }
    		}
    	    }
    	}
    }


    /*
     * <settings>
     */
    {
    	QDomElement settings = document.createElement("settings");
    	root.appendChild(settings);

    	QList<QString> names = m_settings.keys();
	
    	for (int i = 0; i < names.size(); i++) {
	    
    	    QDomElement setting = document.createElement("setting");
	    setting.setAttribute("name", names.at(i));
	    setting.appendChild(document.createTextNode( m_settings.value(names.at(i)).toString() ));
    	    settings.appendChild(setting);

    	}
    }
    

    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(document.toByteArray());
    file.close();

    return true;
}




QVariant KDocument::setting(QString name) {
    return m_settings.value(name);
}



void KDocument::setSetting(QString name, QVariant value) {
    m_settings.insert(name, value);
}
