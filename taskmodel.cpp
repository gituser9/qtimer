#include "taskmodel.h"

TaskModel::TaskModel(QObject *parent) : QAbstractListModel(parent)
{
    dbClient = new DbClient(this);
    tasks = dbClient->getAll();
}


QVariant TaskModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    Task task = tasks[index.row()];

    switch (role) {
    case Qt::DisplayRole:
        return {};
    case IdRole:
        return QVariant::fromValue(task.id);
    case SecondsRole:
        return QVariant::fromValue(task.seconds);
    case NameRole:
        return QVariant::fromValue(task.name);
    default:
        return {};
    }
}

int TaskModel::rowCount(const QModelIndex&) const
{
    return tasks.size();
}

QHash<int, QByteArray> TaskModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole] = "id";
    roles[SecondsRole] = "seconds";
    roles[NameRole] = "name";

    return roles;
}

void TaskModel::update(const long id, const long seconds, const QString &name)
{
    for (Task &task : tasks) {
        if (task.id == id) {
            task.name = name;
            task.seconds = seconds;
            dbClient->update(task);

            this->beginResetModel();
            this->endResetModel();

            return;
        }
    }
}

void TaskModel::create()
{
    Task task = dbClient->insert("", 0);

    this->beginResetModel();
    tasks.append(task);
    this->endResetModel();
}

void TaskModel::remove(const long id)
{
    dbClient->remove(id);
    int index = -1;


    for (int i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            index = i;
            break;
        }
    }
    if (index < 0) {
        return;
    }

    this->beginResetModel();
    tasks.removeAt(index);
    this->endResetModel();
}

