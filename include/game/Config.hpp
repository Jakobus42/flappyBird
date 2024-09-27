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

    struct SoundEffectConfig {
        std::map<std::string, std::string> soundEffects;

        uint8_t volume;
    };

    struct MusicConfig {
        std::map<std::string, std::string> music;

        uint8_t volume;
    };

    void loadFromFile(const std::string& filename);

    const BirdConfig& getBirdConfig() const;
    const PipeConfig& getPipeConfig() const;
    const FloorConfig& getFloorConfig() const;
    const BackgroundConfig& getBackgroundConfig() const;
    const GeneralConfig& getGeneralConfig() const;
    const SoundEffectConfig& getSoundEffectConfig() const;
    const MusicConfig& getMusicConfig() const;

   private:
    BirdConfig _birdConfig;
    PipeConfig _pipeConfig;
    FloorConfig _floorConfig;
    GeneralConfig _generalConfig;
    BackgroundConfig _backgroundConfig;
    SoundEffectConfig _soundeffectConfig;
    MusicConfig _musicConfig;

    void loadTextureConfig(const nlohmann::json& json,
                           std::map<std::string, std::vector<std::string>>& textures);
};

}  // namespace game