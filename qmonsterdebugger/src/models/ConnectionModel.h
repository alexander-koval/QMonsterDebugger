#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

namespace monster {
class Session;
using SessionPtr = QSharedPointer<Session>;

class ConnectionItem : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
public:
    enum Roles { Name = Qt::UserRole + 1 };

    explicit ConnectionItem() : QObject(), _name() {}

    explicit ConnectionItem(const ConnectionItem& other) : QObject () {
        _name = other._name;
        emit nameChanged(_name);
    }

    void operator= (const ConnectionItem& other) {
        _name = other._name;
        emit nameChanged(_name);
    }

    const QString& getName() const { return _name; }

    void setName(const QString& name) {
        _name = name;
        emit nameChanged(_name);
    }

signals:
    void nameChanged(QString& name);

private:
    QString _name;
};

class ConnectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using Base = QAbstractListModel;

    explicit ConnectionModel();

    QVariant data(const QModelIndex& index, int role) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    int rowCount(const QModelIndex& index = QModelIndex()) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::EditRole) const override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int,QByteArray> roleNames() const override { return m_roles; }

private:
    QList<ConnectionItem> m_items;
    QHash<int, QByteArray> m_roles;
};

}
#endif // CONNECTIONMODEL_H
