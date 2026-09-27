#include "../include/LevelStorageAPI.hpp"
#include "GJGameLevel.hpp"
#include "Geode/loader/Log.hpp"
#include "LevelInfoLayer.hpp"
#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace alpha::level_storage {

    LSGJGameLevel* levelForLayer(CCLayer* layer) {
        if (auto gameLayer = typeinfo_cast<GJBaseGameLayer*>(layer)) {
            return static_cast<LSGJGameLevel*>(gameLayer->m_level);
        } else if (auto editorUI = typeinfo_cast<EditorUI*>(layer)) {
            return static_cast<LSGJGameLevel*>(editorUI->m_editorLayer->m_level);
        } else if (auto infoLayer = typeinfo_cast<LevelInfoLayer*>(layer)) {
            return static_cast<LSGJGameLevel*>(infoLayer->m_level);
        } else if (auto editLevelLayer = typeinfo_cast<EditLevelLayer*>(layer)) {
            return static_cast<LSGJGameLevel*>(editLevelLayer->m_level);
        }
        return nullptr;
    }

    matjson::Value& getSavedValueInternal(CCLayer* layer, geode::ZStringView str, geode::Mod* mod) {
        auto lsLevel = levelForLayer(layer);
        if (!lsLevel) return LSGJGameLevel::getEmptyData();
        return lsLevel->getDataContainer(mod)[str];
    }

    matjson::Value& getSaveContainer(CCLayer* layer, geode::Mod* mod) {
        auto lsLevel = levelForLayer(layer);
        if (!lsLevel) return LSGJGameLevel::getEmptyData();
        return lsLevel->getDataContainer(mod);
    }

    void setSavedValue(LevelEditorLayer* layer, geode::ZStringView str, const matjson::Value& value, geode::Mod* mod) {
        auto lsLevel = levelForLayer(layer);
        if (!lsLevel) return;
        lsLevel->getDataContainer(mod)[str] = value;
    }

    void clearSavedValue(LevelEditorLayer* layer, geode::ZStringView str, geode::Mod* mod) {
        auto lsLevel = levelForLayer(layer);
        if (!lsLevel) return;
        lsLevel->getDataContainer(mod)[str].clear();
    }

    void waitForLevel(LevelInfoLayer* layer, std::function<void()>&& callback) {
        static_cast<LSLevelInfoLayer*>(layer)->addCallback(std::move(callback));
    }
}