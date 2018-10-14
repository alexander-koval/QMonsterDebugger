#include "ConnectionModel.h"
#include "stream/sessions/session.h"

namespace monster {

ConnectionModel::ConnectionModel()
    : Base()
    , m_items()
    , m_roles() {
    m_roles[ConnectionItem::Roles::Name] = "name";
}

QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{
    if (role > Qt::UserRole &&
            index.isValid() &&
            index.row() >= 0 &&
            index.row() < m_items.count()) {
        const ConnectionItem& item = m_items.at(index.row());
        switch (role) {
            case ConnectionItem::Roles::Name: return item.getName();
        }
    }
    return QVariant();
}

bool ConnectionModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role > Qt::UserRole &&
            index.row() >= 0 &&
            index.row() < m_items.count()) {
        ConnectionItem& item = m_items[index.row()];
        switch (role) {
        case ConnectionItem::Roles::Name: {
            item.setName(value.toString());
            break;
        }
        default: Q_ASSERT(false);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int ConnectionModel::rowCount(const QModelIndex &index) const {
    return index.isValid() ? 0 : m_items.count();
}

QVariant ConnectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role > Qt::UserRole && orientation == Qt::Horizontal) {
        switch (role) {
        case ConnectionItem::Name: return tr("Name");
        default: Q_ASSERT(false);
        }
    }
    return section + 1;
}

Qt::ItemFlags ConnectionModel::flags(const QModelIndex &index) const
{
    return Base::flags(index);
}

bool ConnectionModel::insertRows(int row, int count, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index){
        m_items.insert(row, ConnectionItem());
    }
    endInsertRows();
    return true;
}

bool ConnectionModel::removeRows(int row, int count, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_items.removeAt(row);
    }
    endRemoveRows();
    return true;
}

}
