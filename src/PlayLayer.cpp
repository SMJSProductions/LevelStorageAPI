#include "PlayLayer.hpp"
#include "GJGameLevel.hpp"

bool LSPlayLayer::init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
    static_cast<LSGJGameLevel*>(level)->extractFromString();

    return PlayLayer::init(level, useReplay, dontCreateObjects);
}