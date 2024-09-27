#pragma once

#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace game {

class Config {
   public:
   struct GeneralConfig {
        uint32_t fps;
   };
    struct BirdConfig {
        float velocity;
        float jumpForce;


        std::map<std::string, std::vector<std::string>> textures;
    };

    struct PipeConfig {
        float velocity;
        float spacing;
        float gap;
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

    void loadFromFile(const std::string& filename);

    const BirdConfig& getBirdConfig() const;
    const PipeConfig& getPipeConfig() const;
    const FloorConfig& getFloorConfig() const;
    const BackgroundConfig& getBackgroundConfig() const;
    const GeneralConfig& getGeneralConfig() const;


    const std::map<std::string, std::string>& getMusicConfig() const;
    const std::map<std::string, std::string>& getSoundEffectConfig() const;
   private:
    BirdConfig _birdConfig;
    PipeConfig _pipeConfig;
    FloorConfig _floorConfig;
    GeneralConfig _generalConfig;
    BackgroundConfig _backgroundConfig;
    std::map<std::string, std::string> _soundEffectConfig;
    std::map<std::string, std::string> _musicConfig;

    void loadTextureConfig(const nlohmann::json& json,
                           std::map<std::string, std::vector<std::string>>& textures);
};

}  // namespace game