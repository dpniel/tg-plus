#include "qtdthread.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QDebug>
#include <QCoreApplication>

QTdWorker::QTdWorker(QObject *parent) : QObject(parent),
    m_tdlib(QTdHandle::instance())
{
}

QTdWorker::~QTdWorker()
{
    m_tdlib.clear();
}

void QTdWorker::run()
{
    // enter the tdlib event loop
    forever {
        const QByteArray rcv = QByteArray(td_json_client_receive(m_tdlib->handle(), 1));
        if (!rcv.isEmpty()) {
            const QJsonObject json = QJsonDocument::fromJson(rcv).object();
            if (!json.isEmpty()) {
                emit recv(json);
                // if this is an authorizationStateClosed we should exit the event loop and destroy
                // the client.
                if (json["@type"] == "updateAuthorizationState" ) {
                    const QJsonObject state = json["authorization_state"].toObject();
                    if (state["type"] == "authorizationStateClosed") {
                        qDebug() << "Closing connection";
                        break;
                    }
                }
            }
        }
    }
}
