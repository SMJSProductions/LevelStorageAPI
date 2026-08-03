#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>

using namespace geode::prelude;

class $modify(LSLevelInfoLayer, LevelInfoLayer) {

    static void onModify(auto& self) {
        (void) self.setHookPriorityPost("LevelInfoLayer::init", Priority::Last);
    }

    struct Fields {
        std::vector<std::function<void()>> m_waitForLevelCallbacks;
    };

    bool init(GJGameLevel* level, bool challenge);
    void levelDownloadFinished(GJGameLevel* level);

    void addCallback(std::function<void()>&& callback);
};