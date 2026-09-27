#include "LevelInfoLayer.hpp"
#include "GJGameLevel.hpp"

bool LSLevelInfoLayer::init(GJGameLevel* level, bool challenge) {
    bool hasLevel = !level->m_levelString.empty();

    if (hasLevel) {
        static_cast<LSGJGameLevel*>(level)->extractFromString();
    }

    if (!LevelInfoLayer::init(level, challenge)) return false;

    if (hasLevel) {
        for (const auto& callback : m_fields->m_waitForLevelCallbacks) {
            callback();
        }
    }

    return true;
}

void LSLevelInfoLayer::levelDownloadFinished(GJGameLevel* level) {
    static_cast<LSGJGameLevel*>(level)->extractFromString();

    LevelInfoLayer::levelDownloadFinished(level);

    for (const auto& callback : m_fields->m_waitForLevelCallbacks) {
        callback();
    }
}

void LSLevelInfoLayer::addCallback(std::function<void()>&& callback) {
    m_fields->m_waitForLevelCallbacks.push_back(std::move(callback));
}