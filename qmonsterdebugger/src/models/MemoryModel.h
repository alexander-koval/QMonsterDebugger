#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QAbstractListModel>

namespace monster {

struct MonitorItem {
    enum Roles { MEMORY = Qt::UserRole + 1, FPS, FPS_MOVIE };

    int64_t memory{};
    int64_t fps{};
    int64_t fpsMovie{};
};

class MemoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using Base = QAbstractListModel;

    explicit MemoryModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    int rowCount(const QModelIndex& index = QModelIndex()) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int,QByteArray> roleNames() const override;

private:
    QList<MonitorItem> m_items;

};

}


#endif // MEMORYMODEL_H
