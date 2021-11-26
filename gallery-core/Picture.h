#ifndef PICTURE_H
#define PICTURE_H
#include <QString>
#include <QUrl>
#include "gallery-core_global.h"

class GALLERYCORE_EXPORT Picture
{
public:
    //Constructors
    Picture(const QString& filePath = "");
    Picture(const QUrl& fileUrl);

    //Getters
    int id() const;
    int albumId() const;
    QUrl fileUrl() const;

    //Setters
    void setId(int id);
    void setAlbumId(int albumId);
    void setFileUrl(const QUrl& fileUrl);

private:
    int mId;
    int mAlbumId;
    QUrl mFileUrl;

};

#endif // PICTURE_H
