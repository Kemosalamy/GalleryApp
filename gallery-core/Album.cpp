#include "Album.h"

Album::Album(const QString& name) : mId(-1),mName(name)
{
}


int Album::id() const{
    return mId;
}

QString Album::name() const{
    return mName;
}

void Album::setId(const int id){
    mId = id;
}

void Album::setName(const QString &name){
    mName = name;
}

