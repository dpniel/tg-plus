#ifndef QTDAUTHCODE_H
#define QTDAUTHCODE_H

#include <QObject>
#include "common/qabstracttdobject.h"
#include "common/qtdint.h"

/**
 * @brief The QTdAuthCode class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_authentication_code_type.html
 */
class QTdAuthCode : public QAbstractTdObject
{
    Q_OBJECT
public:
    explicit QTdAuthCode(QObject *parent = nullptr);
};

/**
 * @brief The QTdAuthCodeTelegramMessage class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_telegram_message.html
 */
class QTdAuthCodeTelegramMessage : public QTdAuthCode
{
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
public:
    explicit QTdAuthCodeTelegramMessage(QObject *parent = 0);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;
signals:
    void lengthChanged();

private:
    QTdInt32 m_length;
};

/**
 * @brief The QTdAuthCodeSms class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_sms.html
 */
class QTdAuthCodeSms : public QTdAuthCode {
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
public:
    explicit QTdAuthCodeSms (QObject * parent = Q_NULLPTR);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;
signals:
    void lengthChanged();

private:
    QTdInt32 m_length;
};

/**
 * @brief The QTdAuthCodeCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_call.html
 */
class QTdAuthCodeCall : public QTdAuthCode {
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
public:
    explicit QTdAuthCodeCall (QObject * parent = Q_NULLPTR);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;
signals:
    void lengthChanged();

private:
    QTdInt32 m_length;
};

/**
 * @brief The QTdAuthCodeFlashCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_flash_call.html
 */
class QTdAuthCodeFlashCall : public QTdAuthCode {
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern NOTIFY patternChanged)
public:
    explicit QTdAuthCodeFlashCall (QObject * parent = Q_NULLPTR);

    QString pattern() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;
signals:
    void patternChanged();
private:
    QString m_pattern;
};

/**
 * @brief The QTdAuthCodeInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_info.html
 */
class QTdAuthCodeInfo : public QAbstractTdObject {
    Q_OBJECT
    Q_PROPERTY(QString timeout READ qmlTimeout NOTIFY infoChanged)
    Q_PROPERTY(QTdAuthCode *type READ type NOTIFY infoChanged)
    Q_PROPERTY(QTdAuthCode *nextType READ nextType NOTIFY infoChanged)
public:
    explicit QTdAuthCodeInfo (QObject * parent = Q_NULLPTR);

    QString qmlTimeout() const;
    qint32 timeout() const;

    QTdAuthCode *type() const;
    QTdAuthCode *nextType() const;

    void unmarshalJson(const QJsonObject &json) Q_DECL_FINAL;

    static QTdAuthCode *create(const QJsonObject &json, QObject *parent);

signals:
    void infoChanged();

private:
    QTdInt32 m_timeout;
    QTdAuthCode *m_type;
    QTdAuthCode *m_nextType;
};


#endif // QTDAUTHCODE_H
