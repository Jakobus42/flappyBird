#pragma once

#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

namespace game {

class Config {
    public:
        struct BirdConfig {
            float velocity;
            float jumpForce;
            std::map<std::string, std::vector<std::string>> textures;
        };

        struct PipeConfig {
            float velocity;
            float spacing;
            std::map<std::string, std::vector<std::string>> textures;
        };

        struct FloorConfig {
            float velocity;
            std::map<std::string, std::vector<std::string>> textures;
        };

        struct BackgroundConfig {
            float velocity;
            std::map<std::string, std::vector<std::string>> textures;
        };

        void loadFromFile(const std::string &filename);

        const BirdConfig& getBirdConfig() const;
        const PipeConfig& getPipeConfig() const;
        const FloorConfig& getFloorConfig() const;
        const BackgroundConfig& getBackgroundConfig() const;

    private:
        BirdConfig _birdConfig;
        PipeConfig _pipeConfig;
        FloorConfig _floorConfig;
        BackgroundConfig _backgroundConfig;

        void loadTextureConfig(const nlohmann::json& json, std::map<std::string, std::vector<std::string>>& textures);
};

} // namespace game