#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace game {

enum class Category {
    Texture,
    SoundEffect,
    Soundtrack,
    Unknown
};

enum class SubCategory {
    Bird,
    Pipe,
    Floor,
    Jump,
    Hit,
    Background,
    Unknown
};

class BaseEntityConfig {
    public:
        virtual ~BaseEntityConfig() = default;

        float getVelocity() const;

        const std::vector<std::string>& getTexturePaths(const std::string& subCetegory) const;
        const std::unordered_map<std::string, std::vector<std::string>>& getTextureCategory(const std::string& cetegory) const;
    protected:
        float _velocity = 0.0f;
        std::unordered_map<std::string, std::vector<std::string>> textures;
};

class PipeConfig : public BaseEntityConfig {
    public:
        float getSpacing() const;
    private:
        float _spacing;
};

class BirdConfig : public BaseEntityConfig {
    public:
        float getJumpForce() const;
    private:
        float _jumpForce;
};

/**
 * @class Config
 * @brief Stores paths for textures, sound effects, and soundtracks.
 */
class Config {
    public:
        Config();
        ~Config();
        Config(const Config &other);
        Config& operator=(const Config &other);

        void loadAssets(const std::string& rootFolder);
        void loadConfig(const std::string& configFile);

        const std::vector<std::string>& getSoundtrackPaths() const;
        const std::vector<std::string>& getSoundEffectPaths(const std::string& category) const;
    private:
        BirdConfig birdConfig;
        PipeConfig pipeConfig;
        BaseEntityConfig floorConfig;

        std::vector<std::string> _soundTracks;
        std::unordered_map<std::string, std::string> _soundEffects;
        void loadIntoMap(const std::string& folder, std::unordered_map<std::string, std::vector<std::string>& dst);

        const std::string& categoryToString(Category category) const;
        const std::string& subCetegotyToString(SubCategory subCategory) const;
};

} /* namespace game */
