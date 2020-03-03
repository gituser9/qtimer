#ifndef TASKMODEL_H
#define TASKMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QHash>

#include "task.h"
#include "dbclient.h"


class TaskModel : public QAbstractListModel
{
    Q_OBJECT
public:

    TaskModel(QObject *parent = nullptr);

    enum TaskRoles {
        IdRole = Qt::UserRole + 1,
        SecondsRole,
        NameRole
    };

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void update(const long id, const long seconds, const QString &name);
    Q_INVOKABLE void create();
    Q_INVOKABLE void remove(const long id);

private:
    DbClient *dbClient;
    QVector<Task> tasks;

signals:

};

#endif // TASKMODEL_H
