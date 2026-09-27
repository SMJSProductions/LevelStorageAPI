#include "EditLevelLayer.hpp"
#include "GJGameLevel.hpp"

bool LSEditLevelLayer::init(GJGameLevel* level) {
    static_cast<LSGJGameLevel*>(level)->extractFromString();

    return EditLevelLayer::init(level);
}