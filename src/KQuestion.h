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

class KQuestion : public QObject {
    Q_OBJECT;

    Q_PROPERTY(QString text READ text WRITE setText);
    Q_PROPERTY(Type type READ type WRITE setType);
    Q_PROPERTY(Level level READ level WRITE setLevel);

    Q_PROPERTY(QPixmap image READ image WRITE setImage);

    
public:
    enum Type {Manual, Alternatives};
    enum Level {Easy, Medium, Hard};

    QString text() { return m_text; }
    void setText(QString text) { m_text = text; }
    
    Type type() { return m_type; }
    void setType(Type type) { m_type = type; }
    
    Level level() { return m_level; }
    void setLevel(Level level) { m_level = level; }

    QPixmap image() { return m_image; }
    void setImage(QPixmap image) { m_image = image; }

protected:
    QString m_text;
    Type m_type;
    Level m_level;
    QPixmap m_image;
}


#endif
