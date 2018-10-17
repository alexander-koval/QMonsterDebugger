#ifndef TRACEMODEL_H
#define TRACEMODEL_H

#include <QAbstractListModel>
#include "TraceItem.h"

namespace monster {

class TraceModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit TraceModel(QObject* parent = nullptr);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &index = QModelIndex()) const override;

    int columnCount(const QModelIndex &index = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::DisplayRole) override;

    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::DisplayRole) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int, QByteArray> roleNames() const override { return m_roles; }

private:
    QList<TraceItem> m_items;
    QHash<int, QByteArray> m_roles;
};

using TraceModelPtr = QSharedPointer<TraceModel>;

}
#endif // TRACEMODEL_H
