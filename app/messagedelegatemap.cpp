#include "messagedelegatemap.h"
#include <qtdlib/common/qabstracttdobject.h>


MessageDelegateMap::MessageDelegateMap(QObject *parent) : QObject(parent)
{
    m_delegates.insert(QTdObject::MESSAGE_TEXT, QStringLiteral("qrc:///delegates/MessageTextItem.qml"));
    m_default = QStringLiteral("qrc:///delegates/NotImplementedYet.qml");
}

QString MessageDelegateMap::findComponent(const int &type) {
    return m_delegates.value(type, m_default);
}
