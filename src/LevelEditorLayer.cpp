#include "LevelEditorLayer.hpp"
#include "GJGameLevel.hpp"

bool LSLevelEditorLayer::init(GJGameLevel* level, bool noUI) {
    static_cast<LSGJGameLevel*>(level)->extractFromString();

    return LevelEditorLayer::init(level, noUI);
}