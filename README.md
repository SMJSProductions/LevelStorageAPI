# Level Storage API

An easy to use way to store information within a level without using objects!

It is stored per mod in JSON that is stored in the level data.

All of these must be called after the class init has been called.

**The `Mod*` param is defaulted to `Mod::get()` so you are accessing your own save container. You can access another mod's save container by passing in their `Mod*`.**

### Getting Saved Values

**The layer param must be `LevelInfoLayer`, `EditLevelLayer`, `PlayLayer`, `LevelEditorLayer`, or `EditorUI`.**

To get a saved value:

```cpp
template<class T>
T alpha::level_storage::getSavedValue(CCLayer* layer, ZStringView key, Mod* mod);
```

To get all saved values:

```cpp
matjson::Value& getSaveContainer(CCLayer* layer, Mod* mod);
```

### Setting Saved Values

To set a value:
```cpp
void setSavedValue(LevelEditorLayer* layer, ZStringView str, const matjson::Value& value, Mod* mod);
```

## Get and Save Example:

```cpp
class $modify(MyLevelEditorLayer, LevelEditorLayer) {
    bool init(GJGameLevel* level, bool noUI) {
        if (!LevelEditorLayer::init(level, noUI)) return false;

        int openedCount = alpha::level_storage::getSavedValue<int>(this, "opened-count");
        alpha::level_storage::setSavedValue(this, "opened-count", openedCount + 1);

        return true;
    }
};
```

### Getting Saved Values on LevelInfoLayer

Since levels are downloaded and the data is with that downloaded level, you can't simply have the information ready in init, so this API provides a way to do so. The callback runs whenever the level string is available. So if the level is already downloaded, it will run in init. If it is not downloaded it will run when it is downloaded.

**Note that this can be called multiple times, as it runs every time the level is downloaded, such as after a refresh, so be sure to handle any cleanup neatly.**

```cpp
void waitForLevel(LevelInfoLayer* layer, std::function<void()>&& callback);
```

## LevelInfoLayer Get Example:

```cpp
class $modify(MyLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        alpha::level_storage::waitForLevel(this, [this] {
            int openedCount = alpha::level_storage::getSavedValue<int>(this, "opened-count");
            log::info("opened count: {}", openedCount);
        });

        return true;
    }
};
```

### Extra Info

Internally, this mod uses the Guidelines string to add data. This is carefully set up such that there is no crashes even in vanilla without the mod.

## Previous Owner

This mod is an official continuation of the Level Storage API mod from [Alphalaneous](https://linktr.ee/Alphalaneous). [SMJS](https://github.com/SMJSProductions) now maintains the mod.