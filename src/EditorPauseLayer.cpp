#include "EditorPauseLayer.hpp"
#include "GJGameLevel.hpp"
#include <Geode/utils/base64.hpp>

void LSEditorPauseLayer::saveLevel() {
    std::string str = "";
    if (!m_editorLayer->m_levelSettings->m_guidelineString.empty()) {
        auto split = utils::string::split(m_editorLayer->m_levelSettings->m_guidelineString, "~|");
        if (split.size() > 0 && !split[0].empty() && split[0][0] != '|') {
            str = split[0];
        }
    }

    auto& data = static_cast<LSGJGameLevel*>(m_editorLayer->m_level)->getData();

    auto extraSeparator = "";

    if (str.size() != 0 && str[str.size()-1] != '~') {
        extraSeparator = "~";
    }

    m_editorLayer->m_levelSettings->m_guidelineString = fmt::format("{}{}|{}~0.1~", str, extraSeparator, base64::encode(data.dump(0)));

    EditorPauseLayer::saveLevel();
}
