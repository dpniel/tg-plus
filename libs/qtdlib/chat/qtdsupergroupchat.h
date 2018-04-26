#ifndef QTDSUPERGROUPCHAT_H
#define QTDSUPERGROUPCHAT_H

#include <QObject>
#include "qtdchat.h"
#include "qtdchatmemberstatus.h"

class QTdSuperGroupChat : public QTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY superGroupChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY superGroupChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY superGroupChanged)
    Q_PROPERTY(QTdChatMemberStatus* status READ status NOTIFY superGroupChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY superGroupChanged)
    Q_PROPERTY(bool anyoneCanInvite READ anyoneCanInvite NOTIFY superGroupChanged)
    Q_PROPERTY(bool signMessages READ signMessages NOTIFY superGroupChanged)
    Q_PROPERTY(bool isChannel READ isChannel NOTIFY superGroupChanged)
    Q_PROPERTY(bool isVerified READ isVerified NOTIFY superGroupChanged)
    Q_PROPERTY(QString restrictionReason READ restrictionReason NOTIFY superGroupChanged)
public:
    explicit QTdSuperGroupChat(QObject *parent = nullptr);

    QString qmlSuperGroupId() const;
    qint32 superGroupId() const;
    QString userName() const;
    QDateTime qmlDate() const;
    qint32 date() const;
    QTdChatMemberStatus* status() const;
    QString qmlMemberCount() const;
    qint32 memberCount() const;
    bool anyoneCanInvite() const;
    bool signMessages() const;
    bool isChannel() const;
    bool isVerified() const;
    QString restrictionReason() const;
signals:
    void superGroupChanged();

private slots:
    void getSuperGroupData();
    void updateSuperGroup(const QJsonObject &json);
private:
    QTdInt32 m_sgId;
    QString m_username;
    qint32 m_date;
    QTdChatMemberStatus *m_status;
    QTdInt32 m_memberCount;
    bool m_canInvite;
    bool m_signMessages;
    bool m_isChannel;
    bool m_isVerified;
    QString m_restrictionReason;
};

#endif // QTDSUPERGROUPCHAT_H
