#ifndef MEMORYMODEL_H
#define MEMORYMODEL_H

#include <QObject>
#include <QAbstractListModel>

class MemoryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using Base = QAbstractListModel;
    explicit MemoryModel(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MEMORYMODEL_H
