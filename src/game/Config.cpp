#include "../../include/game/Config.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>
#include <filesystem>

namespace fs = std::filesystem;

namespace game {

/**
 * @brief Constructs a new Config object.
 */
Config::Config() {}

/**
 * @brief Destroys the Config object.
 */
Config::~Config() {}

/**
 * @brief Copy constructor.
 * @param other The other Config object to copy.
 */
Config::Config(const Config &other)
    : _textures(other._textures), _soundEffects(other._soundEffects), _soundTracks(other._soundTracks) {}

/**
 * @brief Copy assignment operator.
 * @param other The other Config object to assign from.
 * @return A reference to the assigned Config object.
 */
Config& Config::operator=(const Config &other) {
    if (this != &other) {
        _textures = other._textures;
        _soundEffects = other._soundEffects;
        _soundTracks = other._soundTracks;
    }
    return *this;
}

void Config::loadIntoMap(const std::string& folder, std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>>& dst ) {
    if (!fs::exists(folder)) {
        throw std::runtime_error("Cant find " + folder);
    }
    for (const auto& entry : fs::recursive_directory_iterator(folder)) {
        if (fs::is_regular_file(entry)) {
            std::string fullPath = entry.path().string();
            std::string category = entry.path().parent_path().parent_path().filename().string();  
            std::string subcategory = entry.path().parent_path().filename().string();
            dst[category][subcategory].push_back(fullPath);
        }
    }
}

/**
 * @brief Recursively load all textures and sounds from a directory structure.
 * @param rootFolder The base folder to start scanning (e.g., "assets").
 */
void Config::loadAssets(const std::string &rootFolder) {
    if (!fs::exists(rootFolder)) {
        throw std::runtime_error("Root folder does not exist: " + rootFolder);
    }
    loadIntoMap(rootFolder + "/textures", _textures);
    loadIntoMap(rootFolder + "/audio/soundEffects", _soundEffects);
    std::string soundtrackFolder = rootFolder + "/audio/soundtracks";
    if (fs::exists(soundtrackFolder)) {
        for (const auto& entry : fs::directory_iterator(soundtrackFolder)) {
            if (fs::is_regular_file(entry)) {
                _soundTracks.push_back(entry.path().string());
            }
        }
    }
}

void loadConfig(const std::string& configFile) {
    
}

const std::unordered_map<std::string, std::vector<std::string>>& Config::getTextureCategory(const std::string& category) const {
    auto it = _textures.find(category);
    if (it != _textures.end()) {
        return it->second;
    }
    throw std::runtime_error("Can't find " + category);
}

const std::unordered_map<std::string, std::vector<std::string>>& Config::getSoundEffectCategory(const std::string& category) const {
    auto it = _soundEffects.find(category);
    if (it != _soundEffects.end()) {
        return it->second;
    }
    throw std::runtime_error("Can't find " + category);
}

/**
 * @brief Gets the texture paths for a specific category and subcategory (e.g., "BIRD", "BIRD1").
 * @param category The texture category (e.g., "BIRD").
 * @param subcategory The subcategory (e.g., "BIRD1").
 * @return A vector of file paths for the textures.
 */
const std::vector<std::string>& Config::getTexturePaths(const std::string& category, const std::string& subcategory) const {
    auto categoryIt = _textures.find(category);
    if (categoryIt != _textures.end()) {
        auto subcategoryIt = categoryIt->second.find(subcategory);
        if (subcategoryIt != categoryIt->second.end()) {
            return subcategoryIt->second;
        }
    }
    throw std::runtime_error("Can't find " + category + " " + subcategory);
}

/**
 * @brief Gets the sound effect paths for a specific category and subcategory (e.g., "actions", "flap").
 * @param category The sound effect category (e.g., "actions").
 * @param subcategory The subcategory (e.g., "flap").
 * @return A vector of file paths for the sound effects.
 */
const std::vector<std::string>& Config::getSoundEffectPaths(const std::string& category, const std::string& subcategory) const {
    auto categoryIt = _soundEffects.find(category);
    if (categoryIt != _soundEffects.end()) {
        auto subcategoryIt = categoryIt->second.find(subcategory);
        if (subcategoryIt != categoryIt->second.end()) {
            return subcategoryIt->second;
        }
    }
    throw std::runtime_error("Can't find " + category + " " + subcategory);
}

/**
 * @brief Gets the list of soundtrack paths.
 * @return A vector of file paths for the soundtracks.
 */
const std::vector<std::string>& Config::getSoundtrackPaths() const {
    return _soundTracks;
}

} /* namespace game */
