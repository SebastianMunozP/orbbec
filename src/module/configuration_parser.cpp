// Copyright 2025 Viam Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "configuration_parser.hpp"

#include <stdexcept>

namespace orbbec {

std::unique_ptr<ObResourceConfig> ConfigurationParser::parseConfig(const viam::sdk::ResourceConfig& cfg) {
    // TODO: Migrate implementation from orbbec.cpp configure()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::parseConfig not yet implemented");
}

std::vector<std::string> ConfigurationParser::validateAstra2Config(const viam::sdk::ResourceConfig& cfg) {
    // TODO: Migrate implementation from orbbec.cpp validateAstra2()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::validateAstra2Config not yet implemented");
}

std::vector<std::string> ConfigurationParser::validateGemini335LeConfig(const viam::sdk::ResourceConfig& cfg) {
    // TODO: Migrate implementation from orbbec.cpp validateGemini335Le()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::validateGemini335LeConfig not yet implemented");
}

std::vector<std::string> ConfigurationParser::validateOrbbecModelConfig(const viam::sdk::ResourceConfig& cfg,
                                                                        const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp validateOrbbecModel()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::validateOrbbecModelConfig not yet implemented");
}

void ConfigurationParser::validateSensor(const std::pair<std::string, viam::sdk::ProtoValue>& sensor_pair,
                                         const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp validate_sensor()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::validateSensor not yet implemented");
}

std::string ConfigurationParser::getSerialNumber(const viam::sdk::ResourceConfig& cfg) {
    // TODO: Migrate implementation from orbbec.cpp getSerialNumber()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::getSerialNumber not yet implemented");
}

std::pair<std::optional<DeviceResolution>, std::optional<DeviceFormat>> ConfigurationParser::parseDeviceSettings(
    const viam::sdk::ProtoStruct& attrs) {
    // TODO: Implement device settings parsing
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("ConfigurationParser::parseDeviceSettings not yet implemented");
}

}  // namespace orbbec
