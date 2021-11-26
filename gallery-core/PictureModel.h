#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include "gallery-core_global.h"
#include <memory>
#include <vector>
#include <QAbstractListModel>
#include "Picture.h"
#include "Album.h"
#include "AlbumModel.h"
#include "DatabaseManager.h"

class GALLERYCORE_EXPORT PictureModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PictureRole{
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };

    PictureModel(const AlbumModel& albumModel, QObject* parent = 0);
    QModelIndex addPicture(const Picture& picture);
    QVariant data(const QModelIndex& index, int role) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;
    void setAlbumId(int albumId);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    void clearAlbum();

public slots:
    void deletePicturesForAlbum();

private:
    void loadPictures(int albumId);
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& mDb;
    int mAlbumId;
    std::unique_ptr<std::vector<std::unique_ptr<Picture>>> mPictures;

};

#endif // PICTUREMODEL_H
