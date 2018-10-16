#include "SessionDataModel.h"
#include "stream/sessions/Session.h"

namespace monster {

SessionDataModel::SessionDataModel()
    : Base()
    , m_sessions() {

}

QVariant SessionDataModel::data(const QModelIndex &index, int role) const
{
    if (role > Qt::UserRole &&
            index.isValid() &&
            index.row() >= 0 &&
            index.row() < m_sessions.count()) {
        const SessionProxy& data = m_sessions.at(index.row());
        QVariant value;
        switch (role) {
            case SessionProxy::Roles::Session: {
                value.setValue(data.session);
                break;
            }
        }
        return value;
    }
    return QVariant();
}

bool SessionDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role > Qt::UserRole &&
            index.row() >= 0 &&
            index.row() < m_sessions.count()) {
        SessionProxy& data = m_sessions[index.row()];
        switch (role) {
        case SessionProxy::Roles::Session: {
            data.session = value.value<Session*>();
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
    return index.isValid() ? 0 : m_sessions.count();
}

QVariant SessionDataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role > Qt::UserRole && orientation == Qt::Horizontal) {
        switch (role) {
        case SessionProxy::Session: return tr("Session");
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
        m_sessions.insert(row, SessionProxy());
    }
    endInsertRows();
    return true;
}

bool SessionDataModel::removeRows(int row, int count, const QModelIndex&)
{
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_sessions.removeAt(row);
    }
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> SessionDataModel::roleNames() const {
    static QHash<int, QByteArray> roles = { {SessionProxy::Session, "session"} };
    return roles;
}

}
