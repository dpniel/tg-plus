#ifndef QTDCHATLISTSORTFILTERMODEL_H
#define QTDCHATLISTSORTFILTERMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

/**
 * @brief The QTdChatListSortFilterModel class
 *
 * Sorts chat list in descending order based on QTdChat::order()
 *
 * Filters can be applied to show certain QTdChatType's
 */
class QTdChatListSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit QTdChatListSortFilterModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QTDCHATLISTSORTFILTERMODEL_H
