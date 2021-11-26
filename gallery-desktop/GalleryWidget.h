#ifndef GALLERYWIDGET_H
#define GALLERYWIDGET_H

#include <QWidget>
#include "ThumbnailProxyModel.h"
#include <QItemSelectionModel>
#include <AlbumModel.h>


namespace Ui {
class GalleryWidget;
}

class GalleryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GalleryWidget(QWidget *parent = 0);
    ~GalleryWidget();

    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);

    void setPictureModel(ThumbnailProxyModel* pictureModel);
    void setPictureSelectionModel(QItemSelectionModel* pictureSelectionModel);

signals:
    void pictureActivated(const QModelIndex& index);

private:
    Ui::GalleryWidget *ui;
};

#endif // GALLERYWIDGET_H

