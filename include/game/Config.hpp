#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

namespace game {

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

        void load(const std::string &filename);

        const std::unordered_map<std::string, std::vector<std::string>>& getTextureCategory(const std::string& category) const;
        const std::unordered_map<std::string, std::vector<std::string>>& getSoundEffectCategory(const std::string& category) const;

        const std::vector<std::string>& getTexturePaths(const std::string& category, const std::string& subcategory) const;
        const std::vector<std::string>& getSoundEffectPaths(const std::string& category, const std::string& subcategory) const;
        const std::vector<std::string>& getSoundtrackPaths() const;
    private:
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> _textures;
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> _soundEffects;
        std::vector<std::string> _soundTracks;

        void loadIntoMap(const std::string& folder, std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>>& dst);
};

} /* namespace game */
