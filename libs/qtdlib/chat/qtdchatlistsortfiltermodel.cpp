#include "qtdchatlistsortfiltermodel.h"
#include <QDebug>
#include "client/qtdclient.h"
#include "models/QmlObjectListModel.h"
#include "qtdbasicgroupchat.h"
#include "qtdsupergroupchat.h"

QTdChatListSortFilterModel::QTdChatListSortFilterModel(QObject *parent) : QSortFilterProxyModel(parent),
    m_chatList(0), m_chatFilters(CurrentChats)
{
}

QTdChatListModel *QTdChatListSortFilterModel::model() const
{
    return m_chatList;
}

void QTdChatListSortFilterModel::setModel(QTdChatListModel *model)
{
    m_chatList = model;
    setSourceModel(static_cast<QAbstractItemModel*>(m_chatList->model()));
    connect(model, &QTdChatListModel::chatStatusChanged, [=](){invalidateFilter();});
    emit modelChanged();
    setSortRole(static_cast<QQmlObjectListModel<QTdChat>*>(m_chatList->model())->roleForName("lastMessage"));
    setFilterRole(static_cast<QQmlObjectListModel<QTdChat>*>(m_chatList->model())->roleForName("chatType"));
    setDynamicSortFilter(true);
    sort(0, Qt::DescendingOrder);
}

int QTdChatListSortFilterModel::chatFilters() const
{
    return m_chatFilters;
}

void QTdChatListSortFilterModel::setChatFilters(int chatFilters)
{
    if (m_chatFilters == chatFilters)
        return;

    m_chatFilters = chatFilters;
    emit chatFiltersChanged(m_chatFilters);
    invalidateFilter();
}

bool QTdChatListSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    // First check for Everything flag as we just want to
    // show well... everything! even if other flags are set
    if (m_chatFilters & ChatFilters::Everything) {
        return true;
    }

    // Ok so the filters want something a little more fine grained.
    // So first we need to get rid of the chats with status banned or left
    QQmlObjectListModel<QTdChat> *model = static_cast<QQmlObjectListModel<QTdChat>*>(sourceModel());
    QTdChat *chat = model->at(source_row);
    if (chat) {
        switch(chat->chatType()->type()) {
        case QTdChatType::Type::CHAT_TYPE_BASIC_GROUP:
        {
            QTdBasicGroupChat *gc = static_cast<QTdBasicGroupChat*>(chat);
            if (!gc->status()) {
                return true;
            }
            switch(gc->status()->type()) {
            case QTdChatMemberStatus::Type::CHAT_MEMBER_STATUS_LEFT:
            case QTdChatMemberStatus::Type::CHAT_MEMBER_STATUS_BANNED:
                return false;
            default:
                break;
            }
            break;
        }
        case QTdChatType::Type::CHAT_TYPE_SUPERGROUP:
        {
            QTdSuperGroupChat *gc = static_cast<QTdSuperGroupChat*>(chat);
            if (!gc->status()) {
                return true;
            }
            switch(gc->status()->type()) {
            case QTdChatMemberStatus::Type::CHAT_MEMBER_STATUS_LEFT:
            case QTdChatMemberStatus::Type::CHAT_MEMBER_STATUS_BANNED:
                return false;
            default:
                break;
            }
            break;
        }
        default:
            break;
        }
    }

    // If current chats is defined we are just going to show all the remaining chats
    // after the filtering above has been applied. Otherwise filter on a per chat
    // basis filtering on the remaining filters.
    bool allow = false;
    if (m_chatFilters & ChatFilters::CurrentChats) {
        allow = true;
    } else if (m_chatFilters & ChatFilters::PrivateChats) {
        allow = chat->chatType()->type() == QTdChatType::Type::CHAT_TYPE_PRIVATE;
    } else if (m_chatFilters & ChatFilters::SecretChats) {
        allow = chat->chatType()->type() == QTdChatType::Type::CHAT_TYPE_SECRET;
    } else if (m_chatFilters & ChatFilters::SuperGroups) {
        allow = chat->chatType()->type() == QTdChatType::Type::CHAT_TYPE_SUPERGROUP;
    } else if (m_chatFilters & ChatFilters::BasicGroups) {
        allow = chat->chatType()->type() == QTdChatType::Type::CHAT_TYPE_BASIC_GROUP;
    }

    // Finally if PinnedChats is set then only allow pinned chats
    // This allows us to only show pinned chats for each type above
    if (m_chatFilters & ChatFilters::PinnedChats) {
        allow = chat->isPinned();
    }

    return allow;
}

bool QTdChatListSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    /**
     * TDlib suggests to user QTdChat::order() for ordering of the chat list but this seems to be
     * broken right now as evverything apart from supergroups/channels all have an order of 0 which
     * is means undetermined :-/
     *
     * So instead we do the following
     */
    QQmlObjectListModel<QTdChat> *model = static_cast<QQmlObjectListModel<QTdChat>*>(sourceModel());
    QTdChat *left = model->at(source_left.row());
    QTdChat *right = model->at(source_right.row());
    /**
     * If the message under evaluation i.e source_left hasn't received the lastMessage
     * yet. Then retain it's original ordering we received from tdlib.
     */
    if (!left->lastMessage()) {
        return sortOrder() == Qt::AscendingOrder;
    }

    /**
     * If it's a pinned chat we always want this at the top
     * but also retain the original order for multiple pinned chats
     */
    if (left->isPinned()) {
        return false;
    }

    if (right->isPinned()) {
        return true;
    }
    /**
     * And finally just order by the last message date
     */
    return left->lastMessage()->date() < right->lastMessage()->date();
}
