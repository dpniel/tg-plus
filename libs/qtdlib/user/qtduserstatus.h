#ifndef QTDUSERSTATUS_H
#define QTDUSERSTATUS_H

#include <QDateTime>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdUserStatus class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_user_status.html
 */
class QTdUserStatus : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdUserStatus(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdUserStatusEmpty class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_empty.html
 */
class QTdUserStatusEmpty : public QTdUserStatus
{
    Q_OBJECT
public:
    explicit QTdUserStatusEmpty(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdUserStateLastMonth class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_last_month.html
 */
class QTdUserStateLastMonth : public QTdUserStatus
{
    Q_OBJECT
public:
    explicit QTdUserStateLastMonth(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdUserStatusLastWeek class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_last_week.html
 */
class QTdUserStatusLastWeek : public QTdUserStatus
{
    Q_OBJECT
public:
    explicit QTdUserStatusLastWeek(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdUserStatusOffline class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_offline.html
 */
class QTdUserStatusOffline : public QTdUserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDateTime wasOnline READ wasOnline NOTIFY wasOnlineChanged)
public:
    explicit QTdUserStatusOffline(QObject *parent = Q_NULLPTR);
    QDateTime wasOnline() const;
    void unmarshalJson(const QJsonObject &json);
signals:
    void wasOnlineChanged(QDateTime wasOnline);
private:
    QDateTime m_wasOnline;
};

/**
 * @brief The QTdUserStatusOnline class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_online.html
 */
class QTdUserStatusOnline : public QTdUserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDateTime expires READ expires NOTIFY expiresChanged)
public:
    explicit QTdUserStatusOnline(QObject *parent = Q_NULLPTR);
    QDateTime expires() const;
    void unmarshalJson(const QJsonObject &json);
signals:
    void expiresChanged();
private:
    QDateTime m_expires;
};

/**
 * @brief The QTdUserStatusRecently class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_recently.html
 */
class QTdUserStatusRecently : public QTdUserStatus
{
    Q_OBJECT
public:
    explicit QTdUserStatusRecently(QObject *parent = Q_NULLPTR);
};

#endif // QTDUSERSTATUS_H
