QT -= gui
QT += core
QT += sql

TEMPLATE = lib
DEFINES += GALLERYCORE_LIBRARY

CONFIG += c++11

SOURCES += \
    Album.cpp \
    AlbumDao.cpp \
    AlbumModel.cpp \
    DatabaseManager.cpp \
    Picture.cpp \
    PictureDao.cpp \
    PictureModel.cpp

HEADERS += \
    AlbumDao.h \
    AlbumModel.h \
    DatabaseManager.h \
    Picture.h \
    PictureDao.h \
    PictureModel.h \
    gallery-core_global.h \
    Album.h

