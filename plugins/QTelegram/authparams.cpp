#include "authparams.h"
#include <QCoreApplication>
#include <QStandardPaths>

AuthParams::AuthParams(QObject *parent) : QAbstractTdObject(parent),
    m_useTestDC(false),
    m_useFileDatabase(true),
    m_useChatInfoDatabase(true),
    m_useMessageDatabase(true),
    m_useSecretChats(true),
    m_useStorageOptimizer(true)
{
    m_systemLanguageCode = QStringLiteral("en");
    m_deviceModel = QStringLiteral("Ubuntu Phone");
    m_systemVersion = QStringLiteral("xenial");
    m_applicationVersion = QCoreApplication::applicationVersion();
    m_databaseDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/database");
    m_filesDirectory = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation).append("/files");
}

bool AuthParams::useTestDC() const
{
    return m_useTestDC;
}

bool AuthParams::useFileDatabase() const
{
    return m_useFileDatabase;
}

bool AuthParams::useChatInfoDatabase() const
{
    return m_useChatInfoDatabase;
}

bool AuthParams::useMessageDatabase() const
{
    return m_useMessageDatabase;
}

bool AuthParams::useSecretChats() const
{
    return m_useSecretChats;
}

bool AuthParams::useStorageOptimizer() const
{
    return m_useStorageOptimizer;
}

qint32 AuthParams::apiID() const
{
    return m_apiID;
}

QString AuthParams::apiHash() const
{
    return m_apiHash;
}

QString AuthParams::systemLanguageCode() const
{
    return m_systemLanguageCode;
}

QString AuthParams::deviceModel() const
{
    return m_deviceModel;
}

QString AuthParams::systemVersion() const
{
    return m_systemVersion;
}

QString AuthParams::applicationVersion() const
{
    return m_applicationVersion;
}

QString AuthParams::databaseDirectory() const
{
    return m_databaseDirectory;
}

QString AuthParams::filesDirectory() const
{
    return m_filesDirectory;
}

QJsonObject AuthParams::marshalJson()
{
    return QJsonObject{
        {"use_test_dc", m_useTestDC },
        {"use_file_database", m_useFileDatabase},
        { "use_chat_info_database", m_useChatInfoDatabase },
        { "use_message_database", m_useMessageDatabase },
        { "use_secret_chats", m_useSecretChats },
        { "api_id", m_apiID },
        { "api_hash", m_apiHash },
        { "system_language_code", "en" },
        { "device_model", m_deviceModel },
        { "system_version", m_systemVersion },
        { "application_version", m_applicationVersion },
        { "enable_storage_optimizer", m_useStorageOptimizer },
        { "database_directory", m_databaseDirectory },
        { "files_directory", m_filesDirectory },
    };
}

void AuthParams::setUseTestDC(bool useTestDC)
{
    if (m_useTestDC == useTestDC)
        return;

    m_useTestDC = useTestDC;
    emit useTstDCChanged(m_useTestDC);
}

void AuthParams::setUseFileDatabase(bool useFileDatabase)
{
    if (m_useFileDatabase == useFileDatabase)
        return;

    m_useFileDatabase = useFileDatabase;
    emit useFileDatabaseChanged(m_useFileDatabase);
}

void AuthParams::setUseChatInfoDatabase(bool useChatInfoDatabase)
{
    if (m_useChatInfoDatabase == useChatInfoDatabase)
        return;

    m_useChatInfoDatabase = useChatInfoDatabase;
    emit useChatInfoDatabaseChanged(m_useChatInfoDatabase);
}

void AuthParams::setUseMessageDatabase(bool useMessageDatabase)
{
    if (m_useMessageDatabase == useMessageDatabase)
        return;

    m_useMessageDatabase = useMessageDatabase;
    emit useMessageDatabaseChanged(m_useMessageDatabase);
}

void AuthParams::setUseSecretChats(bool useSecretChats)
{
    if (m_useSecretChats == useSecretChats)
        return;

    m_useSecretChats = useSecretChats;
    emit useSecretChatsChanged(m_useSecretChats);
}

void AuthParams::setUseStorageOptimizer(bool useStorageOptimizer)
{
    if (m_useStorageOptimizer == useStorageOptimizer)
        return;

    m_useStorageOptimizer = useStorageOptimizer;
    emit useStorageOptimizerChanged(m_useStorageOptimizer);
}

void AuthParams::setApiID(qint32 apiID)
{
    if (m_apiID == apiID)
        return;

    m_apiID = apiID;
    emit apiIDChanged(m_apiID);
}

void AuthParams::setApiHash(QString apiHash)
{
    if (m_apiHash == apiHash)
        return;

    m_apiHash = apiHash;
    emit apiHashChanged(m_apiHash);
}

void AuthParams::setSystemLanguageCode(QString systemLanguageCode)
{
    if (m_systemLanguageCode == systemLanguageCode)
        return;

    m_systemLanguageCode = systemLanguageCode;
    emit systemLanguageCodeChanged(m_systemLanguageCode);
}

void AuthParams::setDeviceModel(QString deviceModel)
{
    if (m_deviceModel == deviceModel)
        return;

    m_deviceModel = deviceModel;
    emit deviceModelChanged(m_deviceModel);
}

void AuthParams::setSystemVersion(QString systemVersion)
{
    if (m_systemVersion == systemVersion)
        return;

    m_systemVersion = systemVersion;
    emit systemVersionChanged(m_systemVersion);
}

void AuthParams::setApplicationVersion(QString applicationVersion)
{
    if (m_applicationVersion == applicationVersion)
        return;

    m_applicationVersion = applicationVersion;
    emit applicationVersionChanged(m_applicationVersion);
}

void AuthParams::setDatabaseDirectory(QString databaseDirectory)
{
    if (m_databaseDirectory == databaseDirectory)
        return;

    m_databaseDirectory = databaseDirectory;
    emit databaseDirectoryChanged(m_databaseDirectory);
}

void AuthParams::setFilesDirectory(QString filesDirectory)
{
    if (m_filesDirectory == filesDirectory)
        return;

    m_filesDirectory = filesDirectory;
    emit filesDirectoryChanged(m_filesDirectory);
}
