#include "authmanager.h"
#include <QDebug>
#include <qtdlib/client/qtdclient.h>
#include <qtdlib/auth/qtdauthencryptionkeyresponse.h>
#include <qtdlib/auth/qtdauthparametersresponse.h>
#include <qtdlib/auth/qtdauthphonenumberresponse.h>
#include <qtdlib/auth/qtdauthcoderesponse.h>

AuthState::AuthState(QObject *parent) : QObject(parent),
    m_state(Invalid),
    m_params(0)
{
    connect(QTdClient::instance(),
            &QTdClient::authStateChanged,
            this,
            &AuthState::handleAuthStateChanged);

    // Manually run the update now as the client may already be initialized
    // so we want the *current* state to set us up correctly.
    if (QTdClient::instance()->authState()) {
        handleAuthStateChanged(QTdClient::instance()->authState());
    }
}

AuthState::State AuthState::state() const
{
    return m_state;
}

QTdAuthState *AuthState::type() const
{
    return QTdClient::instance()->authState();
}

AuthParams *AuthState::params() const
{
    return m_params;
}

void AuthState::setParams(AuthParams *params)
{
    if (m_params == params)
        return;

    m_params = params;
    emit paramsChanged(m_params);
}

void AuthState::sendParams()
{
    if (!m_params) {
        qWarning() << "Missing auth params. aborting...";
        return;
    }

    if (m_state != WaitTdParams) {
        qWarning() << "TDLib isn't waiting for this so not sending!";
        return;
    }
    auto *resp = new QTdAuthParametersResponse;
    resp->setParameters(m_params);
    QTdClient::instance()->send(resp);
}

void AuthState::setEncryptionKey(const QString &key)
{
    if (m_state != WaitEncryptionKey) {
        qWarning() << "TDLib isn't waiting for the encryption key";
        return;
    }
    auto *resp = new QTdAuthEncryptionKeyResponse;
    resp->setKey(key);
    QTdClient::instance()->send(resp);
}

void AuthState::sendPhoneNumber(const QString &number)
{
    if (m_state != WaitPhoneNumber) {
        qWarning() << "TDLib isn't waiting for the phone number";
        return;
    }
    auto *resp = new QTdAuthPhoneNumberResponse;
    resp->setPhoneNumber(number);
    QTdClient::instance()->send(resp);
}

void AuthState::sendCode(const QString &code)
{
    if (m_state != WaitCode) {
        qWarning() << "TDLib isn't waiting for a code";
        return;
    }
    auto *resp = new QTdAuthCodeResponse;
    resp->setCode(code);
    QTdClient::instance()->send(resp);
}

void AuthState::handleAuthStateChanged(QTdAuthState *state)
{
    switch (state->type()) {
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS:
    {
        m_state = WaitTdParams;
        emit waitingForTdParams();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY:
    {
        m_state = WaitEncryptionKey;
        emit waitingForEncryptionKey();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PHONE_NUMBER:
    {
        m_state = WaitPhoneNumber;
        emit waitingForPhoneNumber();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_CODE:
    {
        m_state = WaitCode;
        emit waitingForCode();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PASSWORD:
    {
        m_state = WaitPassword;
        emit waitingForPassword();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_READY:
    {
        m_state = Ready;
        emit ready();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_LOGGING_OUT:
    {
        m_state = LoggingOut;
        emit loggingOut();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSING:
    {
        m_state = Closing;
        emit closing();
        break;
    }
    case QTdAuthState::Type::AUTHORIZATION_STATE_CLOSED:
    {
        m_state = Closed;
        emit closed();
        break;
    }
    default:
        return;
    }
    emit stateChanged(m_state);
}
