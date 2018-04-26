#ifndef QMLVARIANTLISTMODEL_H
#define QMLVARIANTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QVariant>

class QmlVariantListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    explicit QmlVariantListModel(QObject *parent = 0);

    QHash<int, QByteArray> rolenames() const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

signals:
    void countChanged();

public slots:
    void append(const QVariant &value);
    void appendList(const QVariantList &values);
    int count() const;
    void clear();
    QVariant get(int index);
    bool isEmpty() const;
    void insert(int index, const QVariant &value);
    void insertList(int index, const QVariantList &values);
    QVariantList list() const;
    void move(int index, int to);
    void prepend(const QVariant &value);
    void prependList(const QVariantList &values);
    void replace(int index, const QVariant &value);
    void remove(int index);

private:
    void countPossiblyChanged();

    QVariantList m_values;
    int m_count;
};

#endif // QMLVARIANTLISTMODEL_H
