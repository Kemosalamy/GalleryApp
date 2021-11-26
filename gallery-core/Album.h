#ifndef ALBUM_H
#define ALBUM_H

#include "gallery-core_global.h"
#include <QString>

class GALLERYCORE_EXPORT Album
{
public:
    //Constructor
    explicit Album(const QString& name = "");

    //Getters
    int id() const;
    QString name() const;

    //Setters
    void setId(const int id);
    void setName(const QString& name);

private:
    int mId;
    QString mName;

};

#endif // ALBUM_H
