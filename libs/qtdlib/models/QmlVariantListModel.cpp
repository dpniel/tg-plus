#include "QmlVariantListModel.h"

QmlVariantListModel::QmlVariantListModel(QObject *parent) : QAbstractListModel(parent),
    m_count(0)
{
}

QHash<int, QByteArray> QmlVariantListModel::rolenames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(Qt::UserRole, QByteArrayLiteral("qtVariant"));
    return roles;
}

QVariant QmlVariantListModel::data(const QModelIndex &index, int role) const
{
    QVariant value;
    const int row = index.row();
    if (row >= 0 && row < count() && role == Qt::UserRole) {
        value = m_values.value(row);
    }
    return value;
}

bool QmlVariantListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool dataSet = false;
    const int row = index.row();
    if (row >=0 && row < count()) {
        m_values.replace(row, value);
        QModelIndex item = QAbstractListModel::index(row, 0, QModelIndex());
        emit dataChanged(item, item, QVector<int>(1, role));
        dataSet = true;
    }
    return dataSet;
}

int QmlVariantListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_values.count();
}

void QmlVariantListModel::append(const QVariant &value)
{
    const int rows = count();
    beginInsertRows(QModelIndex(), rows, rows);
    m_values.append(value);
    endInsertRows();
    countPossiblyChanged();
}

void QmlVariantListModel::appendList(const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    const int rows = count();
    beginInsertRows(QModelIndex(), rows, rows + values.count() - 1);
    m_values.append(values);
    endInsertRows();
    countPossiblyChanged();
}

int QmlVariantListModel::count() const
{
    return rowCount();
}

void QmlVariantListModel::clear()
{
    if (m_values.isEmpty()) {
        return;
    }
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_values.clear();
    endRemoveRows();
    countPossiblyChanged();
}

QVariant QmlVariantListModel::get(int index)
{
    QVariant value;
    if (index >= 0 && index < m_values.size()) {
        value = m_values.value(index);
    }
    return value;
}

bool QmlVariantListModel::isEmpty() const
{
    return m_values.isEmpty();
}

void QmlVariantListModel::insert(int index, const QVariant &value)
{
    beginInsertRows(QModelIndex(), index, index);
    m_values.insert(index, value);
    endInsertRows();
    countPossiblyChanged();
}

void QmlVariantListModel::insertList(int index, const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), index, (index + values.count()) - 1);
    int offset = 0;
    for(auto value : values) {
        m_values.insert(index + offset, value);
        ++offset;
    }
    endInsertRows();
    countPossiblyChanged();
}

QVariantList QmlVariantListModel::list() const
{
    return m_values;
}

void QmlVariantListModel::move(int index, int to)
{
    if (index == to) {
        // well that's not clever
        return;
    }
    beginMoveRows(QModelIndex(), index, index, QModelIndex(), (index < to ? to + 1 : to));
    m_values.move(index,to);
    endMoveRows();
    countPossiblyChanged();
}

void QmlVariantListModel::prepend(const QVariant &value)
{
    beginInsertColumns(QModelIndex(), 0, 0);
    m_values.prepend(value);
    endInsertRows();
    countPossiblyChanged();
}

void QmlVariantListModel::prependList(const QVariantList &values)
{
    if (values.isEmpty()) {
        return;
    }
    beginInsertRows(QModelIndex(), 0, values.count() - 1);
    int offset = 0;
    for (auto value : values) {
        m_values.insert(offset, value);
    }
    endInsertRows();
    countPossiblyChanged();
}

void QmlVariantListModel::replace(int index, const QVariant &value)
{
    if (index >= 0 && index < count()) {
        m_values.replace(index, value);
        QModelIndex item = QAbstractListModel::index(index, 0, QModelIndex());
        emit dataChanged(item, item, QVector<int>(1, Qt::UserRole));
    }
}

void QmlVariantListModel::remove(int index)
{
    if (index >= 0 && index < count()) {
        beginRemoveColumns(QModelIndex(), index, index);
        m_values.removeAt(index);
        endRemoveRows();
        countPossiblyChanged();
    }
}

void QmlVariantListModel::countPossiblyChanged()
{
    if (m_count != count()) {
        m_count = count();
        emit countChanged();
    }
}

