#include "MemoryModel.h"

namespace monster {

MemoryModel::MemoryModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_items() {

}

QVariant MemoryModel::data(const QModelIndex &index, int role) const {
    QVariant result;
    if (role > Qt::UserRole &&
            index.isValid() &&
            index.row() >= 0 &&
            index.row() < m_items.count()) {
        const MonitorItem& item = m_items.at(index.row());
        switch (role) {
            case MonitorItem::MEMORY: return item.memory;
            case MonitorItem::FPS: return item.fps;
            case MonitorItem::FPS_MOVIE: return item.fpsMovie;
        }
    }
    return result;
}

bool MemoryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role > Qt::UserRole &&
            index.row() >= 0 &&
            index.row() < m_items.count()) {
        MonitorItem& item = m_items[index.row()];
        switch (role) {
        case MonitorItem::MEMORY: {
            item.memory = value.toLongLong();
            break;
        }
        case MonitorItem::FPS: {
            item.fps = value.toLongLong();
            break;
        }
        case MonitorItem::FPS_MOVIE: {
            item.fpsMovie = value.toLongLong();
            break;
        }
        default: Q_ASSERT(false);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int MemoryModel::rowCount(const QModelIndex &index) const {
    return index.isValid() ? 0 : m_items.count();
}

bool MemoryModel::insertRows(int row, int count, const QModelIndex&) {
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index){
        m_items.insert(row, MonitorItem());
    }
    endInsertRows();
    return true;
}

bool MemoryModel::removeRows(int row, int count, const QModelIndex&) {
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_items.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> MemoryModel::roleNames() const {
    static QHash<int, QByteArray> roles = {
        {MonitorItem::MEMORY, "memory"},
        {MonitorItem::FPS, "fps"},
        {MonitorItem::FPS_MOVIE, "fpsMovie"}
    };
    return roles;
}

}
