#include "qtdlinkstate.h"

QTdLinkState::QTdLinkState(QObject *parent) : QAbstractTdObject(parent)
{
}

QTdLinkStateIsContact::QTdLinkStateIsContact(QObject *parent) : QTdLinkState(parent)
{
    setType(LINK_STATE_IS_CONTACT);
}

QTdLinkStateKnowsPhoneNumber::QTdLinkStateKnowsPhoneNumber(QObject *parent) : QTdLinkState(parent)
{
    setType(LINK_STATE_KNOWS_PHONE_NUMBER);
}

QTdLinkStateNone::QTdLinkStateNone(QObject *parent) : QTdLinkState(parent)
{
    setType(LINK_STATE_NONE);
}
