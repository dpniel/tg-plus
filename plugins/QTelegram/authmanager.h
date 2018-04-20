#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <auth/qtdauthstate.h>
#include "authparams.h"

class AuthState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QTdAuthState* type READ type NOTIFY stateChanged)
    Q_PROPERTY(AuthParams* params READ params WRITE setParams NOTIFY paramsChanged)
public:
    explicit AuthState(QObject *parent = nullptr);

    enum State {
        Invalid,
        WaitTdParams,
        WaitEncryptionKey,
        WaitPhoneNumber,
        WaitCode,
        WaitPassword,
        Ready,
        LoggingOut,
        Closing,
        Closed
    };
    Q_ENUM(State)
    State state() const;
    QTdAuthState *type() const;

    AuthParams* params() const;

public slots:
    void setParams(AuthParams* params);
    void sendParams();
    void setEncryptionKey(const QString &key);
    void sendPhoneNumber(const QString &number);
    void sendCode(const QString &code);

signals:
    void stateChanged(State state);
    void waitingForTdParams();
    void waitingForEncryptionKey();
    void waitingForPhoneNumber();
    void waitingForCode();
    void waitingForPassword();
    void ready();
    void loggingOut();
    void closing();
    void closed();

    void paramsChanged(AuthParams* params);

private slots:
    void handleAuthStateChanged(QTdAuthState *state);

private:
    State m_state;
    AuthParams* m_params;
};

#endif // AUTHMANAGER_H
