#include "tracemodel.h"
#include <QFontMetrics>
#include <QStyleOptionComboBox>
#include <QApplication>

namespace monster {

TraceModel::TraceModel(QObject* parent /*= nullptr*/)
    : QAbstractTableModel(parent)
    , m_items() {

}

Qt::ItemFlags TraceModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags theFlags = QAbstractTableModel::flags(index);
    if (index.isValid()) {
        theFlags |= Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    return theFlags;
}

QVariant TraceModel::data(const QModelIndex &index, int role) const {
    if (role != Qt::DisplayRole)
            return QVariant();
    if (index.isValid() && index.row() >= 0 &&
            index.row() < m_items.count() &&
            index.column() >= 0 && index.column() < TraceItem::Count)  {
        const TraceItem& item = m_items.at(index.row());
            switch (index.column()) {
            case TraceItem::Line: return item.line;
            case TraceItem::Time: return item.time;
            case TraceItem::Target: return item.target;
            case TraceItem::Message: return item.message;
            case TraceItem::Label: return item.label;
            case TraceItem::Person: return item.person;
            case TraceItem::Memory: return item.memory;
            default: Q_ASSERT(false);
        }
    }
    return QVariant();
}

QVariant TraceModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
            return QVariant();
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case TraceItem::Line: return tr("#");
        case TraceItem::Time: return tr("Time");
        case TraceItem::Target: return tr("Target");
        case TraceItem::Message: return tr("Message");
        case TraceItem::Label: return tr("Label");
        case TraceItem::Person: return tr("Person");
        case TraceItem::Memory: return tr("Memory");
        default: Q_ASSERT(false);
        }
    }
    return section + 1;
}

int TraceModel::rowCount(const QModelIndex &index) const {
    return index.isValid() ? 0 : m_items.count();
}

int TraceModel::columnCount(const QModelIndex &index) const {
    return index.isValid() ? 0 : TraceItem::Count;
}

bool TraceModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::DisplayRole &&
            index.row() >= 0 && index.row() < m_items.count() &&
            index.column() >= 0 && index.column() < TraceItem::Count) {
        TraceItem& item = m_items[index.row()];
        switch (index.column()) {
        case TraceItem::Line: {
            bool ok;
            quint64 line = value.toULongLong(&ok);
            if (!ok) { return false; }
            item.line = line;
            break;
        }
        case TraceItem::Time: item.time = value.toString(); break;
        case TraceItem::Target: item.target = value.toString(); break;
        case TraceItem::Message: item.message = value.toString(); break;
        case TraceItem::Label: item.label = value.toString(); break;
        case TraceItem::Person: item.person = value.toString(); break;
        case TraceItem::Memory: item.memory = value.toString(); break;
        default: Q_ASSERT(false);
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool TraceModel::setHeaderData(int, Qt::Orientation, const QVariant&, int) {
    return false;
}

bool TraceModel::insertRows(int row, int count, const QModelIndex&) {
    beginInsertRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_items.insert(row, TraceItem());
    }
    endInsertRows();
    return true;
}

bool TraceModel::removeRows(int row, int count, const QModelIndex&) {
    beginRemoveRows(QModelIndex(), row, row + count - 1);
    for (int index = 0; index < count; ++index) {
        m_items.removeAt(row);
    }
    endRemoveRows();
    return true;
}

}
