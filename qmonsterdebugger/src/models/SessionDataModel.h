#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include "stream/StreamFwd.h"

namespace monster {
class SessionProxy {
public:
    enum Roles { Session = Qt::UserRole + 1 };

    class Session* session{};
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

    QHash<int,QByteArray> roleNames() const override;

private:
    QList<SessionProxy> m_sessions;
};

}
#endif // CONNECTIONMODEL_H
