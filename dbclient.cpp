#include "dbclient.h"


DbClient::DbClient(QObject *parent) : QObject(parent)
{
    QString dataPath = "";

#ifdef Q_OS_MAC
    dataPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.qtimer";

    if (!QDir(dataPath).exists()) {
        QDir().mkdir(dataPath);
    }
#elif Q_OS_ANDROID
    dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dataPath + "/qtimer.sqlite");

    if (!db.open()) {
          qDebug() << db.lastError().text();
          return;
    }

    QSqlQuery query;
    QString str = "CREATE TABLE IF NOT EXISTS tasks ("
                    "id integer PRIMARY KEY AUTOINCREMENT,"
                    "name VARCHAR(255),"
                    "seconds integer"
                ");";
    insertPrepare = QSqlQuery(db);
    updatePrepare = QSqlQuery(db);
    deletePrepare = QSqlQuery(db);

    if (!query.exec(str)) {
        qDebug() << db.lastError().text();
        return;
    }
    if (!insertPrepare.prepare("insert into tasks (name, seconds) values (:name, :seconds)")) {
        qDebug() << db.lastError().text();
        return;
    }
    if (!updatePrepare.prepare("update tasks set name = :name, seconds = :seconds where id = :id")) {
        qDebug() << db.lastError().text();
        return;
    }
    if (!deletePrepare.prepare("delete from tasks where id = :id")) {
        qDebug() << db.lastError().text();
        return;
    }
}

DbClient::~DbClient()
{
    db.close();
}

Task DbClient::insert(const QString &name, const long &seconds)
{
    insertPrepare.bindValue(":name", name);
    insertPrepare.bindValue(":seconds", QVariant::fromValue(seconds));

    if (!insertPrepare.exec()) {
        qDebug() << db.lastError().text();
        return Task();
    }

    QVariant id = insertPrepare.lastInsertId();
    Task task;
    task.id = id.toUInt();
    task.seconds = seconds;
    task.name = name;

    return task;
}

Task DbClient::update(const Task &task)
{
    updatePrepare.bindValue(":id", QVariant::fromValue(task.id));
    updatePrepare.bindValue(":seconds", QVariant::fromValue(task.seconds));
    updatePrepare.bindValue(":name", task.name);

    if (!updatePrepare.exec()) {
        qDebug() << db.lastError().text();
    }

    return task;
}

QVector<Task> DbClient::getAll()
{
    QSqlQuery query;
    QString sql = "select id, seconds, name from tasks";

    if (!query.exec(sql)) {
        qDebug() << db.lastError().text();
        return QVector<Task>();
    }

    QVector<Task> tasks;

    while (query.next()) {
        Task task;
        task.id = query.value("id").toLongLong();
        task.seconds = query.value("seconds").toLongLong();
        task.name = query.value("name").toString();

        tasks.append(task);
    }

    return tasks;
}

void DbClient::remove(const long id)
{
    deletePrepare.bindValue(":id", QVariant::fromValue(id));

    if (!deletePrepare.exec()) {
        qDebug() << db.lastError().text();
    }
}
