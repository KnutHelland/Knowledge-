/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KDOCUMENT_H
#define KDOCUMENT_H

#include <QObject>
#include <QHash>
#include <QList>
#include <QString>
#include <QVariant>

#include "KQuestion.h"



class KDocument : public QObject {
    Q_OBJECT;
    Q_PROPERTY(QString isLoaded READ isLoaded);
    Q_PROPERTY(QString title READ title WRITE setTitle);
    Q_PROPERTY(QString author READ author WRITE setAuthor);
    Q_PROPERTY(QString description READ description WRITE setDescription);
    Q_PROPERTY(QString language READ language WRITE setLanguage);

public:
    KDocument();

    bool isLoaded() { return m_isLoaded; };

    bool loadKxml(QString filename);
    bool saveKxml(QString filename);

    QVariant setting(QString name);
    void setSetting(QString name, QVariant value);

    QString title() { return m_title; }
    void setTitle(QString title) { m_title = title; }

    QString author() { return m_author; }
    void setAuthor(QString author) { m_author = author; }

    QString description() { return m_description; }
    void setDescription(QString description) { m_description = description; }

    QString language() { return m_language; }
    void setLanguage(QString language) { m_language = language; }

    QList<QString> m_categories;
    QList<KQuestion> m_questions;


protected:
    bool m_isLoaded;

    QHash<QString, QVariant> m_settings;

    QString m_title;
    QString m_author;
    QString m_description;
    QString m_language;
};


#endif
