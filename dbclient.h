#ifndef DBCLIENT_H
#define DBCLIENT_H

#include <QObject>
#include <QList>
#include <QVariantList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QObject>
#include <QDebug>
#include <QVector>
#include <QStandardPaths>
#include <QDir>

#include <task.h>

class DbClient : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase db;
    QSqlQuery insertPrepare;
    QSqlQuery updatePrepare;
    QSqlQuery deletePrepare;

public:
    explicit DbClient(QObject *parent = nullptr);
    virtual ~DbClient();

    Task insert(const QString &name, const long &seconds);
    Task update(const Task &task);
    QVector<Task> getAll();
    void remove(const long id);
};

#endif // DBCLIENT_H
