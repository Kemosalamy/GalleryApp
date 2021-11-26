#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>
#include <QItemSelection>
#include <PictureModel.h>
#include <QItemSelectionModel>
#include "ThumbnailProxyModel.h"

namespace Ui {
class PictureWidget;
}

class PictureWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PictureWidget(QWidget *parent = nullptr);
    ~PictureWidget();
    void setModel(ThumbnailProxyModel* model);
    void setSelectionModel(QItemSelectionModel* selectionModel);

signals:
    void backToGallery();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void deletePicture();
    void loadPicture(const QItemSelection& selected);

private:
    Ui::PictureWidget *ui;
    ThumbnailProxyModel* mModel;
    QItemSelectionModel* mSelectionModel;
    QPixmap mPixmap;

    void updatePicturePixmap();
};

#endif // PICTUREWIDGET_H
