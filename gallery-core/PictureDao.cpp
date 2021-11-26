#include "PictureDao.h"
#include <QDebug>

PictureDao::PictureDao(QSqlDatabase& database) : mDatabase(database) {

}

void PictureDao::init() const{
    if(!mDatabase.tables().contains("pictures")){
        QSqlQuery query(mDatabase);
        query.prepare("CREATE TABLE pictures(id INTEGER PRIMARY KEY AUTOINCREMENT, album_id INTEGER, url TEXT)");
        query.exec();
    }
}


void PictureDao::addPictureInAlbum(int albumId, Picture &picture) const{
    QSqlQuery query(mDatabase);
    qDebug() << "inserting into database";
    query.prepare("INSERT INTO pictures(album_id,url) VALUES(:album_id,:url)");
    query.bindValue(":album_id",albumId);
    query.bindValue(":url",picture.fileUrl());
    query.exec();
    picture.setId(query.lastInsertId().toInt());
    picture.setAlbumId(albumId);
}

void PictureDao::removePicture(int id) const{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE id=:id");
    query.bindValue(":id",id);
    query.exec();
}

void PictureDao::removePicturesForAlbum(int albumId) const{
    QSqlQuery query(mDatabase);
    query.prepare("DELETE FROM pictures WHERE album_id=:album_id");
    query.bindValue(":album_id",albumId);
    query.exec();
}


std::unique_ptr<std::vector<std::unique_ptr<Picture>>> PictureDao::picturesForAlbum(int albumId) const{
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM pictures WHERE album_id = :album_id");
    query.bindValue(":album_id",albumId);
    query.exec();
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> list(new std::vector<std::unique_ptr<Picture>>);

    while(query.next()){
        std::unique_ptr<Picture> pic(new Picture());
        pic->setId(query.value("id").toInt());
        pic->setFileUrl(query.value("url").toUrl());
        pic->setAlbumId(albumId);
        list->push_back(std::move(pic));
    }

    return list;

}













