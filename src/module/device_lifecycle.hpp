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

#include <libobsensor/ObSensor.hpp>
#include <viam/sdk/common/proto_value.hpp>

#include "device_registry.hpp"
#include "orbbec.hpp"

namespace orbbec {

// Manages device lifecycle: configuration, startup, and shutdown
// Extracted from monolithic orbbec.cpp to separate device management concerns
class DeviceLifecycleManager {
   public:
    explicit DeviceLifecycleManager(DeviceRegistry& registry);

    // Configure device with stream profiles, alignment, and filters
    // Migrated from configureDevice() in orbbec.cpp lines 707-832
    void configureDevice(const std::string& serial,
                         const OrbbecModelConfig& modelConfig,
                         const std::optional<DeviceResolution>& resolution = std::nullopt,
                         const std::optional<DeviceFormat>& format = std::nullopt);

    // Start device streaming with frame callback
    // Migrated from startDevice() in orbbec.cpp lines 834-865
    void startDevice(const std::string& serial, const OrbbecModelConfig& modelConfig);

    // Stop device streaming and cleanup
    // Migrated from stopDevice() in orbbec.cpp lines 867-893
    void stopDevice(const std::string& serial, const std::string& resourceName);

    // Apply experimental configuration (device properties, filters)
    // Migrated from applyExperimentalConfig() in orbbec.cpp lines 1037-1061
    void applyExperimentalConfig(const std::string& serial, const viam::sdk::ProtoStruct& config);

    // Enable global timestamp if supported by device
    void enableGlobalTimestamp(const std::string& serial);

    // Set multi-device sync mode (standalone, free-run, etc.)
    void setMultiDeviceSyncMode(const std::string& serial, OBMultiDeviceSyncMode mode);

   private:
    DeviceRegistry& registry_;

    // Initialize device components (pipeline, filters, alignment)
    void initializeDeviceComponents(ViamOBDevice& device);

    // Create pipeline configuration with alignment mode
    std::shared_ptr<ob::Config> createPipelineConfig(ViamOBDevice& device,
                                                     const OrbbecModelConfig& modelConfig,
                                                     const std::optional<DeviceResolution>& resolution,
                                                     const std::optional<DeviceFormat>& format);
};

}  // namespace orbbec
