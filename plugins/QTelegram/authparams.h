#ifndef AUTHPARAMS_H
#define AUTHPARAMS_H

#include <QObject>
#include <qtdlib/common/qabstracttdobject.h>

class AuthParams : public QAbstractTdObject
{
    Q_OBJECT
    Q_PROPERTY(bool useTestDC READ useTestDC WRITE setUseTestDC NOTIFY useTstDCChanged)
    Q_PROPERTY(bool useFileDatabase READ useFileDatabase WRITE setUseFileDatabase NOTIFY useFileDatabaseChanged)
    Q_PROPERTY(bool useChatInfoDatabase READ useChatInfoDatabase WRITE setUseChatInfoDatabase NOTIFY useChatInfoDatabaseChanged)
    Q_PROPERTY(bool useMessageDatabase READ useMessageDatabase WRITE setUseMessageDatabase NOTIFY useMessageDatabaseChanged)
    Q_PROPERTY(bool useSecretChats READ useSecretChats WRITE setUseSecretChats NOTIFY useSecretChatsChanged)
    Q_PROPERTY(bool useStorageOptimizer READ useStorageOptimizer WRITE setUseStorageOptimizer NOTIFY useStorageOptimizerChanged)
    Q_PROPERTY(qint32 apiID READ apiID WRITE setApiID NOTIFY apiIDChanged)
    Q_PROPERTY(QString apiHash READ apiHash WRITE setApiHash NOTIFY apiHashChanged)
    Q_PROPERTY(QString systemLanguageCode READ systemLanguageCode WRITE setSystemLanguageCode NOTIFY systemLanguageCodeChanged)
    Q_PROPERTY(QString deviceModel READ deviceModel WRITE setDeviceModel NOTIFY deviceModelChanged)
    Q_PROPERTY(QString systemVersion READ systemVersion WRITE setSystemVersion NOTIFY systemVersionChanged)
    Q_PROPERTY(QString applicationVersion READ applicationVersion WRITE setApplicationVersion NOTIFY applicationVersionChanged)
    Q_PROPERTY(QString databaseDirectory READ databaseDirectory WRITE setDatabaseDirectory NOTIFY databaseDirectoryChanged)
    Q_PROPERTY(QString filesDirectory READ filesDirectory WRITE setFilesDirectory NOTIFY filesDirectoryChanged)

public:
    explicit AuthParams(QObject *parent = nullptr);

    bool useTestDC() const;
    bool useFileDatabase() const;
    bool useChatInfoDatabase() const;
    bool useMessageDatabase() const;
    bool useSecretChats() const;
    bool useStorageOptimizer() const;
    qint32 apiID() const;
    QString apiHash() const;
    QString systemLanguageCode() const;
    QString deviceModel() const;
    QString systemVersion() const;
    QString applicationVersion() const;
    QString databaseDirectory() const;
    QString filesDirectory() const;

    // QAbstractTdObject interface
public:
    QJsonObject marshalJson();

signals:
    void useTstDCChanged(bool useTestDC);
    void useFileDatabaseChanged(bool useFileDatabase);
    void useChatInfoDatabaseChanged(bool useChatInfoDatabase);
    void useMessageDatabaseChanged(bool useMessageDatabase);
    void useSecretChatsChanged(bool useSecretChats);
    void useStorageOptimizerChanged(bool useStorageOptimizer);
    void apiIDChanged(qint32 apiID);
    void apiHashChanged(QString apiHash);
    void systemLanguageCodeChanged(QString systemLanguageCode);
    void deviceModelChanged(QString deviceModel);
    void systemVersionChanged(QString systemVersion);
    void applicationVersionChanged(QString applicationVersion);
    void databaseDirectoryChanged(QString databaseDirectory);
    void filesDirectoryChanged(QString filesDirectory);

public slots:
    void setUseTestDC(bool useTestDC);
    void setUseFileDatabase(bool useFileDatabase);
    void setUseChatInfoDatabase(bool useChatInfoDatabase);
    void setUseMessageDatabase(bool useMessageDatabase);
    void setUseSecretChats(bool useSecretChats);
    void setUseStorageOptimizer(bool useStorageOptimizer);
    void setApiID(qint32 apiID);
    void setApiHash(QString apiHash);
    void setSystemLanguageCode(QString systemLanguageCode);
    void setDeviceModel(QString deviceModel);
    void setSystemVersion(QString systemVersion);
    void setApplicationVersion(QString applicationVersion);
    void setDatabaseDirectory(QString databaseDirectory);
    void setFilesDirectory(QString filesDirectory);
private:
    bool m_useTestDC;
    bool m_useFileDatabase;
    bool m_useChatInfoDatabase;
    bool m_useMessageDatabase;
    bool m_useSecretChats;
    bool m_useStorageOptimizer;
    qint32 m_apiID;
    QString m_apiHash;
    QString m_systemLanguageCode;
    QString m_deviceModel;
    QString m_systemVersion;
    QString m_applicationVersion;
    QString m_databaseDirectory;
    QString m_filesDirectory;
};

#endif // AUTHPARAMS_H
