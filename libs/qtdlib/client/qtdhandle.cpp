#include "qtdhandle.h"
#include <QDebug>

static void deleteHandle(Handle *handle) {
    qWarning() << "Destroying handle";
    td_json_client_destroy(handle->handle());
    delete handle;
    handle = Q_NULLPTR;
}

static QWeakPointer<Handle> s_handle;
QSharedPointer<Handle> QTdHandle::instance()
{
    QSharedPointer<Handle> handle = s_handle.toStrongRef();
    if (handle.isNull()) {
        handle = QSharedPointer<Handle>(new Handle, deleteHandle);
        s_handle = handle;
    }
    return s_handle.toStrongRef();
}

Handle::Handle(): m_handle(Q_NULLPTR) {
    m_handle = td_json_client_create();
    td_set_log_verbosity_level(2);
}

void *Handle::handle() { return m_handle; }
