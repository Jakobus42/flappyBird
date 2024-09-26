#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace game {

enum class TextureCategory {
    Bird,
    Pipe,
    Background,
    Floor,
    Unknown
};

enum class SoundEffect {
    Die,
    Hit,
    Point,
    Wing,
    Unknown
};

class BaseEntityConfig {
    public:
        virtual ~BaseEntityConfig() = default;

        float getVelocity() const;

        const std::vector<std::string>& getTexturePaths(const TextureCategory& category) const;
        const std::unordered_map<TextureCategory, std::vector<std::string>>& getTextureCategory(const TextureCategory& category) const;
    protected:
        float _velocity = 0.0f;
        std::unordered_map<TextureCategory, std::vector<std::string>> _textures;
};

class PipeConfig : public BaseEntityConfig {
    public:
        float getSpacing() const;
    private:
        float _spacing = 0.0f;
};

class BirdConfig : public BaseEntityConfig {
    public:
        float getJumpForce() const;
    private:
        float _jumpForce = 0.0f;  
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
        const std::vector<std::string>& getSoundEffectPaths(const SoundEffect& effect) const;
    private:
        BirdConfig birdConfig;
        PipeConfig pipeConfig;
        BaseEntityConfig floorConfig;

        std::vector<std::string> _soundTracks;
        std::unordered_map<SoundEffect, std::string> _soundEffects;

        const std::string& categoryToString(TextureCategory category) const;
};

} /* namespace game */
