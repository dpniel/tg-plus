#ifndef QTDHANDLE_H
#define QTDHANDLE_H

#include <QObject>
#include <QSharedPointer>
#include <td/telegram/td_json_client.h>

/**
 * @brief The Handle class
 *
 * Wraps the td_json_client handle so it can
 * be stored in a QSharedPointer allowing sharing
 * of the instance across threads
 */
class Handle
{
    void *m_handle;
public:
    explicit Handle(): m_handle(Q_NULLPTR) {
        m_handle = td_json_client_create();
    }

    void *handle() { return m_handle; }
};

/**
 * @brief The QTdHandle class
 *
 * Holds a static QSharedPointer<Handle> instance
 *
 * Access to the underlying handle can be done with
 *
 * QTdHandle::instance()->handle()
 */
class QTdHandle
{
public:
    static QSharedPointer<Handle> instance();
};

#endif // QTDHANDLE_H
