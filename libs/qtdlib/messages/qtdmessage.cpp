#include "qtdmessage.h"

QTdMessage::QTdMessage(QObject *parent) : QAbstractInt64Id(parent)
{
    setType(MESSAGE);
}
