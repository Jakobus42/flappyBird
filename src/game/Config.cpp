#include "../../include/game/Config.hpp"
#include <iostream>

#include <fstream>

using json = nlohmann::json;

namespace game {

void Config::loadTextureConfig(const json& jsonObject,
                               std::map<std::string, std::vector<std::string>>& textures) {
    for (auto& [key, value] : jsonObject.items()) {
        std::vector<std::string> textureConfig;
        for (const auto& texture : value) {
            textureConfig.push_back(texture);
        }
        textures[key] = textureConfig;
    }
}

void Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    json configJson;
    file >> configJson;

    _generalConfig.fps = configJson["generalConfig"]["fps"];
    _musicConfig.volume = configJson["musicConfig"]["volume"];
    _soundeffectConfig.volume = configJson["soundEffectConfig"]["volume"];
    for (auto& [key, value] : configJson["soundEffectConfig"].items()) {
        if (!value.is_number()) {
            _soundeffectConfig.soundEffects[key] = value[0];
        }
    }
    for (auto& [key, value] : configJson["musicConfig"].items()) {
        if (!value.is_number()) {
            _musicConfig.music[key] = value[0];
        }
    }
    _birdConfig.velocity = configJson["birdConfig"]["velocity"];
    _birdConfig.jumpForce = configJson["birdConfig"]["jumpForce"];
    loadTextureConfig(configJson["birdConfig"]["textures"], _birdConfig.textures);

    _pipeConfig.velocity = configJson["pipeConfig"]["velocity"];
    _pipeConfig.spacing = configJson["pipeConfig"]["spacing"];
    _pipeConfig.gap = configJson["pipeConfig"]["gap"];
    loadTextureConfig(configJson["pipeConfig"]["textures"], _pipeConfig.textures);

    _floorConfig.velocity = configJson["floorConfig"]["velocity"];
    loadTextureConfig(configJson["floorConfig"]["textures"], _floorConfig.textures);

    _backgroundConfig.velocity = configJson["backgroundConfig"]["velocity"];
    loadTextureConfig(configJson["backgroundConfig"]["textures"], _backgroundConfig.textures);
}

const Config::BirdConfig& Config::getBirdConfig() const { return _birdConfig; }

const Config::PipeConfig& Config::getPipeConfig() const { return _pipeConfig; }

const Config::FloorConfig& Config::getFloorConfig() const { return _floorConfig; }

const Config::BackgroundConfig& Config::getBackgroundConfig() const { return _backgroundConfig; }

const Config::GeneralConfig& Config::getGeneralConfig() const { return _generalConfig; }

const Config::SoundEffectConfig& Config::getSoundEffectConfig() const { return _soundeffectConfig; }

const Config::MusicConfig& Config::getMusicConfig() const { return _musicConfig; }

}  // namespace game
