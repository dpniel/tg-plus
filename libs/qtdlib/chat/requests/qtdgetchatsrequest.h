#ifndef QTDGETCHATSREQUEST_H
#define QTDGETCHATSREQUEST_H

#include <QObject>

class QTdGetChatsRequest : public QObject
{
    Q_OBJECT
public:
    explicit QTdGetChatsRequest(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTDGETCHATSREQUEST_H