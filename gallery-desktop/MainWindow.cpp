#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow),
mGalleryWidget(new GalleryWidget(this)),
mPictureWidget(new PictureWidget(this)),
mStackedWidget(new QStackedWidget(this)){

    ui->setupUi(this);

    //Initiate the AlbumModel, pass onto QItemSelectionModel and Widgets
    AlbumModel* albumModel = new AlbumModel(this);
    QItemSelectionModel* albumSelectionModel =
                                new QItemSelectionModel(albumModel, this);
    mGalleryWidget->setAlbumModel(albumModel);
    mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);


    //Initiate the PictureModel, pass onto QItemSelectionModel and Widgets
    PictureModel* pictureModel = new PictureModel(*albumModel, this);
    ThumbnailProxyModel* thumbnailModel = new ThumbnailProxyModel(this);
    thumbnailModel->setSourceModel(pictureModel);
    QItemSelectionModel* pictureSelectionModel =
                                new QItemSelectionModel(thumbnailModel, this);
    mGalleryWidget->setPictureModel(thumbnailModel);
    mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
    mPictureWidget->setModel(thumbnailModel);
    mPictureWidget->setSelectionModel(pictureSelectionModel);

    //Adding both onto stacked widget and then displaying gallery
    mStackedWidget->addWidget(mGalleryWidget);
    mStackedWidget->addWidget(mPictureWidget);
    displayGallery();
    setCentralWidget(mStackedWidget);

    connect(mGalleryWidget, &GalleryWidget::pictureActivated, this, &MainWindow::displayPicture);
    connect(mPictureWidget, &PictureWidget::backToGallery, this, &MainWindow::displayGallery);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayGallery(){
    mStackedWidget->setCurrentWidget(mGalleryWidget);
}


void MainWindow::displayPicture(const QModelIndex&){
    mStackedWidget->setCurrentWidget(mPictureWidget);
}

