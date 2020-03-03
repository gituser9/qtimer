#ifndef TASK_H
#define TASK_H

#include <QString>
#include <QObject>


struct Task {
    long id;
    long seconds;
    QString name;

    Task() {
        id = 0;
        seconds = 0;
        name = "";
    }

    Task& operator=(const Task &task) {
        this->id = task.id;
        this->name = task.name;
        this->seconds = task.seconds;

        return *this;
    }

    bool operator==(const Task &right) {
        return this->id == right.id
                && this->seconds == right.seconds
                && this->name == right.name;
    }
};


#endif // TASK_H
