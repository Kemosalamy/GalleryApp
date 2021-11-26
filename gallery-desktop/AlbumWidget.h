#ifndef ALBUMWIDGET_H
#define ALBUMWIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <AlbumModel.h>
#include <PictureModel.h>
#include <QItemSelectionModel>
#include "ThumbnailProxyModel.h"
#include "PictureDelegate.h"
#include <QInputDialog>
#include <QFileDialog>

namespace Ui {
class AlbumWidget;
}

class AlbumWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumWidget(QWidget *parent = nullptr);
    ~AlbumWidget();
    void setAlbumModel(AlbumModel* albumModel);
    void setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel);
    void setPictureModel(ThumbnailProxyModel* pictureModel);
    void setPictureSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void pictureActivated(const QModelIndex& index);

private slots:
    void deleteAlbum();
    void editAlbum();
    void addPictures();

private:
    void clearUi();
    void loadAlbum(const QModelIndex& albumIndex);

    Ui::AlbumWidget *ui;
    AlbumModel* mAlbumModel;
    QItemSelectionModel* mAlbumSelectionModel;
    ThumbnailProxyModel* mPictureModel;
    QItemSelectionModel* mPictureSelectionModel;

};

#endif // ALBUMWIDGET_H


