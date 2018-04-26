#ifndef QTDBASICGROUPCHAT_H
#define QTDBASICGROUPCHAT_H

#include <QObject>
#include "qtdchat.h"
#include "qtdbasicgroupinfo.h"
#include "qtdchatmemberstatus.h"

class QTdBasicGroupChat : public QTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString groupId READ qmlGroupId NOTIFY groupChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY groupChanged)
    Q_PROPERTY(QTdChatMemberStatus* status READ status NOTIFY groupChanged)
    Q_PROPERTY(bool everyoneIsAdmin READ everyoneIsAdmin NOTIFY groupChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY groupChanged)
    Q_PROPERTY(QString upgradedToSuperGroupId READ qmlUpgradedToSuperGroupId NOTIFY groupChanged)
public:
    explicit QTdBasicGroupChat(QObject *parent = nullptr);

    QString qmlGroupId() const;
    qint32 groupId() const;
    QString qmlMemberCount() const;
    qint32 memberCount() const;
    QTdChatMemberStatus* status() const;
    bool everyoneIsAdmin() const;
    bool isActive() const;
    QString qmlUpgradedToSuperGroupId() const;
    qint32 upgradedToSuperGroupId() const;
signals:
    void groupChanged();

private slots:
    void requestGroupData();
    void updateGroupData(const QJsonObject &json);

private:
    QTdInt32 m_groupId;
    QTdInt32 m_memberCount;
    QTdChatMemberStatus *m_status;
    bool m_everyoneIsAdmin;
    bool m_isActive;
    QTdInt32 m_upgradedSGID;
};

#endif // QTDBASICGROUPCHAT_H
