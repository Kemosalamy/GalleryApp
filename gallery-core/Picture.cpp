#include "Picture.h"

//Constructors

Picture::Picture(const QString& filePath) :
    Picture::Picture(QUrl::fromLocalFile(filePath))
{

}

Picture::Picture(const QUrl& fileUrl)
    : mId(-1), mAlbumId(-1), mFileUrl(fileUrl)
{

}

//Getters

int Picture::id() const{
    return mId;
}

int Picture::albumId() const{
    return mAlbumId;
}

QUrl Picture::fileUrl() const{
    return mFileUrl;
}

//Setters

void Picture::setId(int id){
    mId = id;
}

void Picture::setAlbumId(int albumId){
    mAlbumId = albumId;
}

void Picture::setFileUrl(const QUrl& fileUrl){
    mFileUrl = fileUrl;
}

