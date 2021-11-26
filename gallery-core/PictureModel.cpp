#include "PictureModel.h"

PictureModel::PictureModel(const AlbumModel& albumModel, QObject* parent) :
    QAbstractListModel(parent), mDb(DatabaseManager::instance()), mAlbumId(-1),
    mPictures(new std::vector<std::unique_ptr<Picture>>){

    connect(&albumModel, &AlbumModel::rowsRemoved,
            this, &PictureModel::deletePicturesForAlbum);

}


void PictureModel::setAlbumId(int albumId){
    beginResetModel();
    mAlbumId = albumId;
    loadPictures(mAlbumId);
    endResetModel();
}


QVariant PictureModel::data(const QModelIndex &index, int role) const{
    if(!isIndexValid(index)) return QVariant();

    const Picture& picture = *(mPictures->at(index.row()));

    switch(role){
        case (PictureRole::FilePathRole):
            return picture.fileUrl().toLocalFile();
            break;
        case (Qt::DisplayRole):
            return picture.fileUrl().fileName();
            break;
        case (PictureRole::UrlRole):
            return picture.fileUrl();
            break;
    }

    return QVariant();
}

QModelIndex PictureModel::addPicture(const Picture& picture){
    int insert = rowCount();
    beginInsertRows(QModelIndex(), insert, insert);
    std::unique_ptr<Picture> pic(new Picture(picture));
    mDb.pictureDao.addPictureInAlbum(mAlbumId,*pic);
    mPictures->push_back(std::move(pic));
    endInsertRows();
    return index(insert, 0);
}



bool PictureModel::removeRows(int row, int count, const QModelIndex& parent){
    if (row < 0 || row >= rowCount() || count < 0 || (row + count) > rowCount()) return false;

    beginRemoveRows(parent, row, row + count - 1);

    for(int i=count-1;i>-1;i--){
        const Picture& picture = *(mPictures->at(row+i));
        mDb.pictureDao.removePicture(picture.id());
    }

    mPictures->erase(mPictures->begin()+ row, mPictures->begin() + row + count);

    endRemoveRows();


    return true;
}


QHash<int, QByteArray> PictureModel::roleNames() const{
    QHash<int, QByteArray> roles;
    roles[PictureRole::FilePathRole] = "filepath";
    return roles;
}


bool PictureModel::isIndexValid(const QModelIndex& index) const{
    if(index.row()>=rowCount() || !index.isValid()) return false;
    return true;
};

void PictureModel::clearAlbum(){
    setAlbumId(-1);

}


void PictureModel::deletePicturesForAlbum(){
    mDb.pictureDao.removePicturesForAlbum(mAlbumId);
    clearAlbum();
}

void PictureModel::loadPictures(int albumId){
    if (albumId <= 0) {
        mPictures.reset(new std::vector<std::unique_ptr<Picture>>());
        return;
    }
    mPictures = mDb.pictureDao.picturesForAlbum(albumId);
}
int PictureModel::rowCount(const QModelIndex& parent) const{
    return mPictures->size();
}
