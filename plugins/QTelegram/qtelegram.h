#ifndef QTELEGRAM_H
#define QTELEGRAM_H

#include <QObject>

class QTelegram: public QObject {
    Q_OBJECT

public:
    QTelegram();
    ~QTelegram() = default;

    Q_INVOKABLE void speak();
};

#endif
