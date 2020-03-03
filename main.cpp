#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlEngine>

#include "dbclient.h"
#include "taskmodel.h"
#include "task.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

#if defined (Q_OS_LINUX)
    QQuickStyle::setStyle("Material");
#elif defined (Q_OS_WIN)
    QQuickStyle::setStyle("Universal");
#else
    QQuickStyle::setStyle("Material");
#endif


    qmlRegisterType<DbClient>("DbClient", 1, 0, "DbClient");
    qmlRegisterType<TaskModel>("TaskModel", 1, 0, "TaskModel");
//    qmlRegisterType<Task>("Task", 1, 0, "Task");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
