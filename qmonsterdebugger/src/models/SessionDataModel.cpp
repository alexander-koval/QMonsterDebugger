#include "SessionDataModel.h"
#include "stream/sessions/Session.h"

namespace monster {

SessionDataModel::SessionDataModel()
    : Base()
    , m_clients()
    , m_roles() {
    m_roles[SessionData::Roles::Name] = "name";
}

QVariant SessionDataModel::data(const QModelIndex &index, int role) const
{
    if (role > Qt::UserRole &&
            index.isValid() &&
            index.row() >= 0 &&
            index.row() < m_clients.count()) {
        const SessionData& data = m_clients.at(index.row());
        switch (role) {
            case SessionData::Roles::Name: return data.name;
        }
    }
    return QVariant();
}

bool SessionDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role > Qt::UserRole &&
            index.row() >= 0 &&
            index.row() < m_clients.count()) {
        SessionData& data = m_clients[index.row()];
        switch (role) {
        case SessionData::Roles::Name: {
            data.name = value.toString();
            break;
        }
        default: Q_ASSERT(false);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int SessionDataModel::rowCount(const QModelIndex &index) const {
    return index.isValid() ? 0 : m_clients.count();
}

QVariant SessionDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role > Qt::UserRole && orientation == Qt::Horizontal) {
        switch (role) {
        case SessionData::Name: return tr("Name");
        default: Q_ASSERT(false);
        }
    }
    return section + 1;
}

Qt::ItemFlags SessionDataModel::flags(const QModelIndex &index) const
{
    return Base::flags(index);
}

bool SessionDataModel::insertRows(int row, int count, const QModelIndex&)
{
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index){
        m_clients.insert(row, SessionData());
    }
    endInsertRows();
    return true;
}

bool SessionDataModel::removeRows(int row, int count, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_clients.removeAt(row);
    }
    endRemoveRows();
    return true;
}

}
