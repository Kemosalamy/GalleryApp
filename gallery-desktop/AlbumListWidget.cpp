#include "AlbumListWidget.h"
#include "ui_AlbumListWidget.h"
#include <QInputDialog>


AlbumListWidget::AlbumListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlbumListWidget),
    mAlbumModel(nullptr){

    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &AlbumListWidget::createAlbum);

}

AlbumListWidget::~AlbumListWidget(){
    delete ui;
}

void AlbumListWidget::setModel(AlbumModel *model){
    mAlbumModel = model;
    ui->listView->setModel(mAlbumModel);
}

void AlbumListWidget::setSelectionModel(QItemSelectionModel *selectionModel){
    ui->listView->setSelectionModel(selectionModel);
}

void AlbumListWidget::createAlbum(){
    if(!mAlbumModel) return;

    bool ok;
    QString albumName = QInputDialog::getText(this,
            "Create a new Album",
            "Choose an name",
            QLineEdit::Normal,
            "New album",
            &ok);

    if (ok && !albumName.isEmpty()){
        Album album(albumName);
        QModelIndex createdIndex = mAlbumModel->addAlbum(album);
        ui->listView->setCurrentIndex(createdIndex);
    }
}




