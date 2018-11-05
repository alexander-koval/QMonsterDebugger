#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QAbstractListModel>

namespace monster {

struct MonitorItem {
    enum Roles { MEMORY = Qt::UserRole + 1, FPS, FPS_MOVIE };

    qlonglong memory{};
    qint32 fps{};
    qint32 fpsMovie{};
};

class MonitorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(qlonglong minMemory READ minMemory CONSTANT)
//    Q_PROPERTY(qlonglong minMemory READ minMemory WRITE setMinMemory NOTIFY minMemoryChanged)

public:
    using Base = QAbstractListModel;

    explicit MonitorModel(QObject *parent = nullptr);

    QVariant data(const QModelIndex& index, int role) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    int rowCount(const QModelIndex& index = QModelIndex()) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    QHash<int,QByteArray> roleNames() const override;

    qlonglong minMemory() const { return m_minMemory; }

//    void setMinMemory(qlonglong memory) {
//        m_minMemory = memory;
//        emit minMemoryChanged(m_minMemory);
//    }

//Q_SIGNALS:
//    void minMemoryChanged(qlonglong memory);

private:
    qlonglong m_minMemory;
    QList<MonitorItem> m_items;
};

}


#endif // MEMORYMODEL_H
