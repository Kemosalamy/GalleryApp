QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = desktop-gallery
TEMPLATE = app

SOURCES += \
    AlbumListWidget.cpp \
    AlbumWidget.cpp \
    GalleryWidget.cpp \
    PictureDelegate.cpp \
    PictureWidget.cpp \
    ThumbnailProxyModel.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    AlbumListWidget.h \
    AlbumWidget.h \
    GalleryWidget.h \
    MainWindow.h \
    PictureDelegate.h \
    PictureWidget.h \
    ThumbnailProxyModel.h

FORMS += \
    AlbumListWidget.ui \
    AlbumWidget.ui \
    GalleryWidget.ui \
    MainWindow.ui \
    PictureWidget.ui


INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core

RESOURCES += \
    resource.qrc
