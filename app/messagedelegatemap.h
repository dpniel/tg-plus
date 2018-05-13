#ifndef MESSAGEDELEGATEMAP_H
#define MESSAGEDELEGATEMAP_H

#include <QObject>
#include <QHash>

class MessageDelegateMap : public QObject
{
    Q_OBJECT
public:
    explicit MessageDelegateMap(QObject *parent = Q_NULLPTR);

    Q_INVOKABLE QString findComponent(const int &type);

private:
    QHash<int, QString> m_delegates;
    QString m_default;
};

#endif // MESSAGEDELEGATEMAP_H
