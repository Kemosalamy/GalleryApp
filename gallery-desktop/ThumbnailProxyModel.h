#ifndef THUMBNAILPROXYMODEL_H
#define THUMBNAILPROXYMODEL_H

#include <QWidget>
#include <QIdentityProxyModel>
#include <QHash>
#include <QPixmap>
#include <PictureModel.h>

class ThumbnailProxyModel : public QIdentityProxyModel
{
    Q_OBJECT

public:
    ThumbnailProxyModel(QObject* parent = 0);
    ThumbnailProxyModel();
    ~ThumbnailProxyModel();
    QVariant data(const QModelIndex& index, int role) const override;
    void setSourceModel(QAbstractItemModel* sourceModel) override;
    PictureModel* pictureModel() const;


private:
    QHash<QString,QPixmap*> mThumbnails;

    void generateThumbnails(const QModelIndex& startIndex, int count);
    void reloadThumbnails();


};

#endif // THUMBNAILPROXYMODEL_H
