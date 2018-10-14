#ifndef REPO_H
#define REPO_H

#include <QQmlApplicationEngine>

namespace monster {

class ConnectionModel;

class Repo
{
public:
    static QQmlApplicationEngine* engine();

    static void engine(QQmlApplicationEngine* engine);

    static ConnectionModel* connectionModel();

    static void connectionModel(ConnectionModel* model);

private:
    static QQmlApplicationEngine* _engine;
    static ConnectionModel* _connectionModel;
};

}

#endif // REPO_H
