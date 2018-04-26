#ifndef QTDCHATMEMBERSTATUS_H
#define QTDCHATMEMBERSTATUS_H

#include <QObject>
#include <QDateTime>
#include "common/qabstracttdobject.h"

/**
 * @brief The QTdChatMemberStatus class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_chat_member_status.html
 */
class QTdChatMemberStatus : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdChatMemberStatus(QObject *parent = nullptr);
};

/**
 * @brief The QTdChatMemberStatusAdmin class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_administrator.html
 */
class QTdChatMemberStatusAdmin : public QTdChatMemberStatus
{
    Q_OBJECT
    Q_PROPERTY(bool canBeEdited READ canBeEdited NOTIFY statusChanged)
    Q_PROPERTY(bool canChangeInfo READ canChangeInfo NOTIFY statusChanged)
    Q_PROPERTY(bool canPostMessages READ canPostMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canEditMessages READ canEditMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canDeleteMessages READ canDeleteMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canInviteUsers READ canInviteUsers NOTIFY statusChanged)
    Q_PROPERTY(bool canRestrictMembers READ canRestrictMembers NOTIFY statusChanged)
    Q_PROPERTY(bool canPinMessages READ canPinMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canPromoteMembers READ canPromoteMembers NOTIFY statusChanged)
public:
    explicit QTdChatMemberStatusAdmin(QObject *parent = Q_NULLPTR);

    bool canBeEdited() const;

    bool canChangeInfo() const;

    bool canPostMessages() const;

    bool canEditMessages() const;

    bool canDeleteMessages() const;

    bool canInviteUsers() const;

    bool canRestrictMembers() const;

    bool canPinMessages() const;

    bool canPromoteMembers() const;

    void unmarshalJson(const QJsonObject &json);

signals:
    void statusChanged();
private:
    bool m_canBeEdited;
    bool m_canChangeInfo;
    bool m_canPostMessages;
    bool m_canEditMessages;
    bool m_canDeleteMessages;
    bool m_canInviteUsers;
    bool m_canRestrictMembers;
    bool m_canPinMessages;
    bool m_canPromoteMembers;
};

/**
 * @brief The QTdChatMemberStatusBanned class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_banned.html
 */
class QTdChatMemberStatusBanned : public QTdChatMemberStatus
{
    Q_OBJECT
    Q_PROPERTY(QDateTime bannedUntilDate READ qmlBannedUntilDate NOTIFY statusChanged)
public:
    explicit QTdChatMemberStatusBanned(QObject *parent = Q_NULLPTR);

    QDateTime qmlBannedUntilDate() const;
    qint32 bannedUntilDate() const;
    void unmarshalJson(const QJsonObject &json);
signals:
    void statusChanged();
private:
    qint32 m_bannedTil;
};

/**
 * @brief The QTdChatMemberStatusCreator class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_creator.html
 */
class QTdChatMemberStatusCreator : public QTdChatMemberStatus
{
    Q_OBJECT
    Q_PROPERTY(bool isMember READ isMember NOTIFY statusChanged)
public:
    explicit QTdChatMemberStatusCreator(QObject *parent = Q_NULLPTR);
    bool isMember() const;
    void unmarshalJson(const QJsonObject &json);
signals:
    void statusChanged();
private:
    bool m_isMember;
};

/**
 * @brief The QTdChatMemberStatusLeft class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_left.html
 */
class QTdChatMemberStatusLeft : public QTdChatMemberStatus
{
    Q_OBJECT
public:
    explicit QTdChatMemberStatusLeft(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdChatMemberStatusMember class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_member.html
 */
class QTdChatMemberStatusMember : public QTdChatMemberStatus
{
    Q_OBJECT
public:
    explicit QTdChatMemberStatusMember(QObject *parent = Q_NULLPTR);
};

/**
 * @brief The QTdChatMemberStatusRestricted class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_member_status_restricted.html
 */
class QTdChatMemberStatusRestricted : public QTdChatMemberStatus
{
    Q_OBJECT
    Q_PROPERTY(bool isMember READ isMember NOTIFY statusChanged)
    Q_PROPERTY(QDateTime restrictedUntil READ qmlRestrictedUntil NOTIFY statusChanged)
    Q_PROPERTY(bool canSendMessages READ canSendMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canSendMediaMessages READ canSendMediaMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canSendOtherMessages READ canSendOtherMessages NOTIFY statusChanged)
    Q_PROPERTY(bool canAddWebPagePreviews READ canAddWebPagePreviews NOTIFY statusChanged)
public:
    explicit QTdChatMemberStatusRestricted(QObject *parent = Q_NULLPTR);
    void unmarshalJson(const QJsonObject &json);
    bool isMember() const;
    QDateTime qmlRestrictedUntil() const;
    qint32 restrictedUntil() const;
    bool canSendMessages() const;
    bool canSendMediaMessages() const;
    bool canSendOtherMessages() const;
    bool canAddWebPagePreviews() const;

signals:
    void statusChanged();

private:
    bool m_isMember;
    qint32 m_restrictedUntil;
    bool m_canSendMessages;
    bool m_canSendMediaMessages;
    bool m_canSendOtherMessages;
    bool m_canAddWebPagePreviews;
};

#endif // QTDCHATMEMBERSTATUS_H
