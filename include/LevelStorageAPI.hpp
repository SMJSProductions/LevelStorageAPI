#pragma once

#include <Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h>
#include <Geode/binding/LevelInfoLayer.hpp>
#include <Geode/utils/ZStringView.hpp>
#include <matjson.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifdef LEVEL_STORAGE_API_EXPORTING
        #define LEVEL_STORAGE_API_DLL __declspec(dllexport)
    #else
        #define LEVEL_STORAGE_API_DLL __declspec(dllimport)
    #endif
#else
    #define LEVEL_STORAGE_API_DLL __attribute__((visibility("default")))
#endif

namespace alpha::level_storage {

    /// internal getSavedValue method used by the templated one
    LEVEL_STORAGE_API_DLL matjson::Value& getSavedValueInternal(cocos2d::CCLayer* layer, geode::ZStringView str, geode::Mod* mod = geode::Mod::get());

    /// get json container of saved values
    LEVEL_STORAGE_API_DLL matjson::Value& getSaveContainer(cocos2d::CCLayer* layer, geode::Mod* mod = geode::Mod::get());

    /// set a value with a key
    LEVEL_STORAGE_API_DLL void setSavedValue(LevelEditorLayer* layer, geode::ZStringView str, const matjson::Value& value, geode::Mod* mod = geode::Mod::get());

    /// clears a saved value with a key
    LEVEL_STORAGE_API_DLL void clearSavedValue(LevelEditorLayer* layer, geode::ZStringView str, geode::Mod* mod = geode::Mod::get());

    /// get a value by a key
    template<class T>
    T getSavedValue(cocos2d::CCLayer* layer, geode::ZStringView str, geode::Mod* mod = geode::Mod::get()) {
        return getSavedValueInternal(layer, str, mod).as<T>().unwrapOrDefault();
    }

    /// wait for a level to load on LevelInfoLayer
    LEVEL_STORAGE_API_DLL void waitForLevel(LevelInfoLayer* layer, std::function<void()>&& callback);
}