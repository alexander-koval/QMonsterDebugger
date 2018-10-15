#include "Repo.h"
#include "models/SessionDataModel.h"

namespace monster {

QQmlApplicationEngine* Repo::_engine = nullptr;
SessionDataModel* Repo::_connectionModel = nullptr;

QQmlApplicationEngine *monster::Repo::engine() {
    return _engine;
}

void monster::Repo::engine(QQmlApplicationEngine *engine) {
    _engine = engine;
}

monster::SessionDataModel *monster::Repo::connectionModel() {
    return _connectionModel;
}

void monster::Repo::connectionModel(monster::SessionDataModel *model) {
    _connectionModel = model;
}

}
