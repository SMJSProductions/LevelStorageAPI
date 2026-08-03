#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>

using namespace geode::prelude;

class $modify(LSEditorPauseLayer, EditorPauseLayer) {

    static void onModify(auto& self) {
        (void) self.setHookPriorityPre("EditorPauseLayer::saveLevel", Priority::Last);
    }

    void saveLevel();
};