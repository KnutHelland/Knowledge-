/**
 * This is a part of Knowledge!
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @license GNU GPL 3 or newer
 */


#ifndef KQUESTION_H
#define KQUESTION_H

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QList>

class KQuestion : public QObject {
    Q_OBJECT;

    Q_PROPERTY(QString text READ text WRITE setText);
    Q_PROPERTY(QString category READ category WRITE setCategory);
    Q_PROPERTY(Type type READ type WRITE setType);
    Q_PROPERTY(Level level READ level WRITE setLevel);

    Q_PROPERTY(QPixmap image READ image WRITE setImage);

    
public:
    enum Type {Manual, Alternatives};
    enum Level {Easy, Medium, Hard};


    KQuestion() : QObject() {}
    KQuestion(const KQuestion &q) : QObject() { m_text = q.text(); m_category = q.category(); m_type = q.type(); m_level = q.level(); m_image = q.image(); }

    QString text() const { return m_text; }
    void setText(QString text) { m_text = text; }
    
    QString category() const { return m_category; }
    void setCategory(QString category) { m_category = category; }
    
    Type type() const { return m_type; }
    void setType(Type type) { m_type = type; }
    
    Level level() const { return m_level; }
    void setLevel(Level level) { m_level = level; }

    QPixmap image() const { return m_image; }
    void setImage(QPixmap image) { m_image = image; }

    /**
     * The first answer is always the correct one.
     */
    QList<QString> m_answers;

protected:
    QString m_text, m_category;
    Type m_type;
    Level m_level;
    QPixmap m_image;
};


#endif
