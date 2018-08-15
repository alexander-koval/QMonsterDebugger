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

    Qt::ItemFlags flags(const QModelIndex& index) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    int rowCount(const QModelIndex &index = QModelIndex()) const;

    int columnCount(const QModelIndex &index = QModelIndex()) const;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::DisplayRole);

    bool setHeaderData(int section, Qt::Orientation orientation,
                       const QVariant &value, int role = Qt::DisplayRole);

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

private:
    QList<TraceItem> m_items;
};

}
#endif // TRACEMODEL_H
