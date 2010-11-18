/**
 * This is a part of Knowledge!
 * All rights reserved to Knut Helland.
 *
 * @author Knut Helland <knutoh@gmail.com>
 * @copyright Knut Helland 2010
 */


#ifndef KDOCUMENT_H
#define KDOCUMENT_H

class QString;
class QVariant;

class KDocument {
public:
    KDocument();

    bool loadKxml(QString filename);

    QVariant setting(QString name);
    void setSetting(QString name, QVariant value);

protected:
    QHashMap<QString, QVariant> m_settings;
};


#endif
