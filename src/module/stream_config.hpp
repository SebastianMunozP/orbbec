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

#include <libobsensor/ObSensor.hpp>

#include "orbbec.hpp"

namespace orbbec {

// Manages stream profile selection and depth-to-color alignment configuration
// Extracted from orbbec.cpp lines 424-651
class StreamConfigManager {
   public:
    // Create hardware depth-to-color alignment configuration
    // Migrated from createHwD2CAlignConfig() in orbbec.cpp lines 583-651
    static std::shared_ptr<ob::Config> createHwD2CAlignConfig(std::shared_ptr<ob::Pipeline> pipe,
                                                              const std::optional<DeviceResolution>& deviceRes,
                                                              const std::optional<DeviceFormat>& deviceFormat,
                                                              const OrbbecModelConfig& modelConfig);

    // Create software depth-to-color alignment configuration
    // Migrated from createSwD2CAlignConfig() in orbbec.cpp lines 546-580
    static std::shared_ptr<ob::Config> createSwD2CAlignConfig(std::shared_ptr<ob::Pipeline> pipe,
                                                              const std::optional<DeviceResolution>& deviceRes,
                                                              const std::optional<DeviceFormat>& deviceFormat,
                                                              const OrbbecModelConfig& modelConfig);

    // Check if stream profiles support hardware depth-to-color alignment
    // Migrated from checkIfSupportHWD2CAlign() in orbbec.cpp lines 426-452
    static bool checkIfSupportHWD2CAlign(std::shared_ptr<ob::Pipeline> pipe,
                                         std::shared_ptr<ob::StreamProfile> colorProfile,
                                         std::shared_ptr<ob::StreamProfile> depthProfile);

    // Find matching color and depth stream profiles
    // Migrated from findMatchingProfiles() in orbbec.cpp lines 489-526
    static std::pair<std::shared_ptr<ob::StreamProfile>, std::shared_ptr<ob::StreamProfile>> findMatchingProfiles(
        std::shared_ptr<ob::Pipeline> pipe,
        const std::optional<DeviceResolution>& deviceRes,
        const std::optional<DeviceFormat>& deviceFormat,
        const OrbbecModelConfig& modelConfig);

   private:
    // Check if video stream profile matches resolution/format specification
    // Migrated from profileMatchesSpec() in orbbec.cpp lines 455-486
    static bool profileMatchesSpec(std::shared_ptr<ob::VideoStreamProfile> vsp,
                                   const std::optional<DeviceResolution>& deviceRes,
                                   const std::optional<DeviceFormat>& deviceFormat,
                                   const OrbbecModelConfig& modelConfig,
                                   bool isColor);

    // Build error message for missing profiles
    // Migrated from buildProfileErrorMsg() in orbbec.cpp lines 529-543
    static std::string buildProfileErrorMsg(bool isColor,
                                            const std::optional<DeviceResolution>& deviceRes,
                                            const std::optional<DeviceFormat>& deviceFormat);
};

}  // namespace orbbec
