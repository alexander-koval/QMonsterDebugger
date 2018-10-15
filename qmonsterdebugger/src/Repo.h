#ifndef REPO_H
#define REPO_H

#include <QQmlApplicationEngine>

namespace monster {

class SessionDataModel;

class Repo
{
public:
    static QQmlApplicationEngine* engine();

    static void engine(QQmlApplicationEngine* engine);

    static SessionDataModel* connectionModel();

    static void connectionModel(SessionDataModel* model);

private:
    static QQmlApplicationEngine* _engine;
    static SessionDataModel* _connectionModel;
};

}

#endif // REPO_H
