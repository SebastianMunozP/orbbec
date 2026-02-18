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

#pragma once

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <viam/sdk/common/proto_value.hpp>
#include <viam/sdk/config/resource.hpp>

#include "orbbec.hpp"

namespace orbbec {

// Handles configuration parsing and validation
// Extracted from orbbec.cpp lines 898-1012, 1026-1035, 1691-1721
class ConfigurationParser {
   public:
    // Parse Viam SDK ResourceConfig to native ObResourceConfig
    // Migrated from configure() in orbbec.cpp lines 1691-1721
    static std::unique_ptr<ObResourceConfig> parseConfig(const viam::sdk::ResourceConfig& cfg);

    // Model-specific validation methods
    // Migrated from validateAstra2() in orbbec.cpp lines 1014-1016
    static std::vector<std::string> validateAstra2Config(const viam::sdk::ResourceConfig& cfg);

    // Migrated from validateGemini335Le() in orbbec.cpp lines 1018-1024
    static std::vector<std::string> validateGemini335LeConfig(const viam::sdk::ResourceConfig& cfg);

    // Migrated from validateOrbbecModel() in orbbec.cpp lines 954-1012
    static std::vector<std::string> validateOrbbecModelConfig(const viam::sdk::ResourceConfig& cfg, const OrbbecModelConfig& modelConfig);

   private:
    // Validate individual sensor configuration
    // Migrated from validate_sensor() in orbbec.cpp lines 898-952
    static void validateSensor(const std::pair<std::string, viam::sdk::ProtoValue>& sensor_pair, const OrbbecModelConfig& modelConfig);

    // Extract serial number from configuration
    // Migrated from getSerialNumber() in orbbec.cpp lines 1026-1035
    static std::string getSerialNumber(const viam::sdk::ResourceConfig& cfg);

    // Parse device resolution and format settings from attributes
    static std::pair<std::optional<DeviceResolution>, std::optional<DeviceFormat>> parseDeviceSettings(const viam::sdk::ProtoStruct& attrs);
};

}  // namespace orbbec
