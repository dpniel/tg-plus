#ifndef QTDUSERTYPE_H
#define QTDUSERTYPE_H

#include "common/qabstracttdobject.h"

class QTdUserType : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdUserType(QObject *parent = Q_NULLPTR);
};

class QTdUserTypeBot : public QTdUserType
{
    Q_OBJECT
    Q_PROPERTY(bool canJoinGroups READ canJoinGroups NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool canReadAllGroupMessages READ canReadAllGroupMessages NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool isInline READ isInline NOTIFY userTypeDataChanged)
    Q_PROPERTY(QString inlineQueryPlaceholder READ placeholder NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool needLocation READ needLocation NOTIFY userTypeDataChanged)
public:
    explicit QTdUserTypeBot(QObject *parent = Q_NULLPTR);
    bool canJoinGroups() const;
    bool canReadAllGroupMessages() const;
    bool isInline() const;
    QString placeholder() const;
    bool needLocation() const;

    void unmarshalJson(const QJsonObject &json)  Q_DECL_FINAL;
signals:
    void userTypeDataChanged();
private:
    bool m_canJoinGroups;
    bool m_canReadAllGroupMessages;
    bool m_isInline;
    QString m_inlineQueryPlaceholder;
    bool m_needLocation;
};

class QTdUserTypeDeleted : public QTdUserType
{
    Q_OBJECT
public:
    explicit QTdUserTypeDeleted(QObject *parent = Q_NULLPTR);
};

class QTdUserTypeRegular : public QTdUserType
{
    Q_OBJECT
public:
    explicit QTdUserTypeRegular(QObject *parent = Q_NULLPTR);
};

class QTdUserTypeUnknown : public QTdUserType
{
    Q_OBJECT
public:
    explicit QTdUserTypeUnknown(QObject *parent = Q_NULLPTR);
};
#endif // QTDUSERTYPE_H
