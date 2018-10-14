#include "Repo.h"
#include "models/ConnectionModel.h"

namespace monster {

QQmlApplicationEngine* Repo::_engine = nullptr;
ConnectionModel* Repo::_connectionModel = nullptr;

QQmlApplicationEngine *monster::Repo::engine() {
    return _engine;
}

void monster::Repo::engine(QQmlApplicationEngine *engine) {
    _engine = engine;
}

monster::ConnectionModel *monster::Repo::connectionModel() {
    return _connectionModel;
}

void monster::Repo::connectionModel(monster::ConnectionModel *model) {
    _connectionModel = model;
}

}
