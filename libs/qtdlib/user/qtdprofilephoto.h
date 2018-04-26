#ifndef QTDPROFILEPHOTO_H
#define QTDPROFILEPHOTO_H

#include <QObject>

#include "common/qabstractint64id.h"
#include "files/qtdphoto.h"

class QTdProfilePhoto : public QTdPhoto
{
    Q_OBJECT
public:
    explicit QTdProfilePhoto(QObject *parent = nullptr);
};

#endif // QTDPROFILEPHOTO_H
