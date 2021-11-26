#include "AlbumWidget.h"
#include "ui_AlbumWidget.h"
#include <QDebug>

AlbumWidget::AlbumWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumWidget),
    mAlbumModel(nullptr),
    mAlbumSelectionModel(nullptr),
    mPictureModel(nullptr),
    mPictureSelectionModel(nullptr){
        ui->setupUi(this);
        clearUi();

        ui->thumbnailsListView->setSpacing(5);
        ui->thumbnailsListView->setResizeMode(QListView::Adjust);
        ui->thumbnailsListView->setFlow(QListView::LeftToRight);
        ui->thumbnailsListView->setWrapping(true);
        ui->thumbnailsListView->setItemDelegate(
                    new PictureDelegate(this));

        connect(ui->thumbnailsListView, &QListView::doubleClicked,
        this, &AlbumWidget::pictureActivated);

        connect(ui->removeAlbumButton, &QPushButton::clicked,
        this, &AlbumWidget::deleteAlbum);

        connect(ui->editAlbumButton, &QPushButton::clicked,
        this, &AlbumWidget::editAlbum);

        connect(ui->addPictureButton, &QPushButton::clicked,
        this, &AlbumWidget::addPictures);

}
AlbumWidget::~AlbumWidget()
{
    delete ui;
}

void AlbumWidget::setAlbumModel(AlbumModel *albumModel){
    mAlbumModel = albumModel;
    connect(mAlbumModel,&QAbstractItemModel::dataChanged, [this] (const QModelIndex &topleft){
        if(topleft == mAlbumSelectionModel->currentIndex()){

            loadAlbum(topleft);
        }
    });
}

void AlbumWidget::setAlbumSelectionModel(QItemSelectionModel* albumSelectionModel){
    mAlbumSelectionModel = albumSelectionModel;
    connect(mAlbumSelectionModel,&QItemSelectionModel::selectionChanged,
        [this] (const QItemSelection& selected) {
            if(selected.isEmpty()){
                clearUi();
                return;
            }

            loadAlbum(selected.indexes().first());
        }
    );

}

void AlbumWidget::setPictureModel(ThumbnailProxyModel* pictureModel){
    mPictureModel = pictureModel;
    ui->thumbnailsListView->setModel(mPictureModel);
}

void AlbumWidget::setPictureSelectionModel(QItemSelectionModel* selectionModel){
    ui->thumbnailsListView->setSelectionModel(selectionModel);
}

void AlbumWidget::clearUi(){
    ui->albumName->setText("");
    ui->removeAlbumButton->setVisible(false);
    ui->editAlbumButton->setVisible(false);
    ui->addPictureButton->setVisible(false);
}

void AlbumWidget::loadAlbum(const QModelIndex& albumIndex){
    mPictureModel->pictureModel()->setAlbumId(mAlbumModel->data(albumIndex,
                                                                AlbumModel::idRole).toInt());
    ui->albumName->setText(mAlbumModel->data(albumIndex, Qt::DisplayRole).toString());
    ui->removeAlbumButton->setVisible(true);
    ui->editAlbumButton->setVisible(true);
    ui->addPictureButton->setVisible(true);
}

void AlbumWidget::addPictures(){
QStringList filenames = QFileDialog::getOpenFileNames(this,"Add pictures",
                                    QDir::homePath(), "Picture files (*.jpg *.png)");

    if (!filenames.isEmpty()){
        QModelIndex lastModelIndex;
        for (auto filename : filenames) {
            Picture picture(filename);
            lastModelIndex = mPictureModel->pictureModel()
                                            ->addPicture(picture);
        }

        lastModelIndex = mPictureModel->index(lastModelIndex.row(), 0);
        ui->thumbnailsListView->setCurrentIndex(lastModelIndex);
    }
}

void AlbumWidget::editAlbum(){
    if (mAlbumSelectionModel->selectedIndexes().isEmpty()) return;

    QModelIndex currentAlbumIndex = mAlbumSelectionModel->selectedIndexes().first();
    QString oldAlbumName = mAlbumModel->data(currentAlbumIndex,
                                        AlbumModel::Roles::NameRole).toString();

    bool ok;
    QString newName = QInputDialog::getText(this,
                                    "Album's name",
                                "Change Album name",
                                    QLineEdit::Normal,
                                            oldAlbumName,
                                                    &ok);

    if (ok && !newName.isEmpty()) {
        mAlbumModel->setData(currentAlbumIndex,
                    newName, AlbumModel::Roles::NameRole);
    }
}


void AlbumWidget::deleteAlbum(){
    if (mAlbumSelectionModel->selectedIndexes().isEmpty()) return;

    int row = mAlbumSelectionModel->currentIndex().row();
    mAlbumModel->removeRow(row);

    QModelIndex previousModelIndex = mAlbumModel->index(row - 1, 0);

    if(previousModelIndex.isValid()) {
        mAlbumSelectionModel->setCurrentIndex(previousModelIndex,
                                              QItemSelectionModel::SelectCurrent);

        return;
    }


    QModelIndex nextModelIndex = mAlbumModel->index(row, 0);

    if(nextModelIndex.isValid()) {
        mAlbumSelectionModel->setCurrentIndex(nextModelIndex,
                                              QItemSelectionModel::SelectCurrent);

        return;
    }
}
