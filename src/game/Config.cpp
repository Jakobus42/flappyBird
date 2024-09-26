#include "Config.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

namespace game {

    float BaseEntityConfig::getVelocity() const {
        return _velocity;
    }

    const std::vector<std::string>& BaseEntityConfig::getTexturePaths(const TextureCategory& category) const {
        static std::vector<std::string> empty;
        auto it = _textures.find(category);
        return (it != _textures.end()) ? it->second : empty;
    }

    const std::unordered_map<TextureCategory, std::vector<std::string>>& BaseEntityConfig::getTextureCategory(const TextureCategory& category) const {
        return _textures;
    }

    float PipeConfig::getSpacing() const {
        return _spacing;
    }

    float BirdConfig::getJumpForce() const {
        return _jumpForce;
    }

    const std::string& Config::categoryToString(TextureCategory category) const {
        static const std::unordered_map<TextureCategory, std::string> categoryToStr = {
            {TextureCategory::Bird, "Bird"},
            {TextureCategory::Pipe, "Pipe"},
            {TextureCategory::Background, "Background"},
            {TextureCategory::Floor, "Floor"},
            {TextureCategory::Unknown, "Unknown"}
        };

        auto it = categoryToStr.find(category);
        if (it != categoryToStr.end()) {
            return it->second;
        }
        static std::string unknown = "Unknown";
        return unknown;
    }

    Config::Config() {
    }

    Config::~Config() {
    }

    Config::Config(const Config &other) 
        : birdConfig(other.birdConfig), pipeConfig(other.pipeConfig), floorConfig(other.floorConfig),
          _soundTracks(other._soundTracks), _soundEffects(other._soundEffects) {
    }

    Config& Config::operator=(const Config &other) {
        if (this != &other) {
            birdConfig = other.birdConfig;
            pipeConfig = other.pipeConfig;
            floorConfig = other.floorConfig;
            _soundTracks = other._soundTracks;
            _soundEffects = other._soundEffects;
        }
        return *this;
    }

    void Config::loadAssets(const std::string& rootFolder) {
        if (!fs::exists(rootFolder)) {
            throw std::runtime_error("Root folder does not exist: " + rootFolder);
        }

        auto loadIntoMap = [](const std::string& folder, std::unordered_map<TextureCategory, std::vector<std::string>>& map) {
            if (!fs::exists(folder)) {
                return;
            }
            for (const auto& entry : fs::directory_iterator(folder)) {
                if (!fs::is_directory(entry)) {
                    
                }
                    TextureCategory category = TextureCategory::Unknown;
                    std::string categoryName = entry.path().filename().string();
                    if (categoryName == "Bird") category = TextureCategory::Bird;
                    else if (categoryName == "Pipe") category = TextureCategory::Pipe;
                    else if (categoryName == "Background") category = TextureCategory::Background;
                    else if (categoryName == "Floor") category = TextureCategory::Floor;

                    if (category != TextureCategory::Unknown) {
                        for (const auto& file : fs::directory_iterator(entry)) {
                            if (fs::is_regular_file(file)) {
                                map[category].push_back(file.path().string());
                            }
                        }
                    }
            }
        };

        loadIntoMap(rootFolder + "/textures", birdConfig._textures);
        loadIntoMap(rootFolder + "/textures", pipeConfig._textures);
        loadIntoMap(rootFolder + "/textures", floorConfig._textures);

        std::string soundEffectsFolder = rootFolder + "/audio/soundEffects";
        if (fs::exists(soundEffectsFolder)) {
            for (const auto& entry : fs::directory_iterator(soundEffectsFolder)) {
                if (fs::is_regular_file(entry)) {
                    std::string filename = entry.path().filename().string();
                    SoundEffect effect = SoundEffect::Unknown;

                    if (filename.find("die") != std::string::npos) {
                        effect = SoundEffect::Die;
                    } else if (filename.find("hit") != std::string::npos) {
                        effect = SoundEffect::Hit;
                    } else if (filename.find("point") != std::string::npos) {
                        effect = SoundEffect::Point;
                    } else if (filename.find("wing") != std::string::npos) {
                        effect = SoundEffect::Wing;
                    }

                    if (effect != SoundEffect::Unknown) {
                        _soundEffects[effect] = entry.path().string();
                    }
                }
            }
        }

        std::string soundtrackFolder = rootFolder + "/audio/soundtracks";
        if (fs::exists(soundtrackFolder)) {
            for (const auto& entry : fs::directory_iterator(soundtrackFolder)) {
                if (fs::is_regular_file(entry)) {
                    _soundTracks.push_back(entry.path().string());
                }
            }
        }
    }

    void Config::loadConfig(const std::string& configFile) {
    }

    const std::vector<std::string>& Config::getSoundtrackPaths() const {
        return _soundTracks;
    }

    const std::vector<std::string>& Config::getSoundEffectPaths(const SoundEffect& effect) const {
        static std::vector<std::string> empty;
        auto it = _soundEffects.find(effect);
        return (it != _soundEffects.end()) ? std::vector<std::string>{it->second} : empty;
    }

} // namespace game
