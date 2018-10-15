#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>

namespace monster {
class Session;
using SessionPtr = QSharedPointer<Session>;

struct SessionData {
    enum Roles { Name = Qt::UserRole + 1, Trace };

    QString name;
};

class SessionDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using Base = QAbstractListModel;

    explicit SessionDataModel();

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
    QList<SessionData> m_clients;
    QHash<int, QByteArray> m_roles;
};

}
#endif // CONNECTIONMODEL_H
