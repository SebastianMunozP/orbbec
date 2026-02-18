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

#include <cstdint>
#include <memory>
#include <optional>
#include <sstream>
#include <vector>

#include <libobsensor/ObSensor.hpp>
#include <viam/sdk/components/camera.hpp>

#include "orbbec.hpp"

namespace orbbec {

// Handles frame validation, encoding, and timestamp management
// Extracted from orbbec.cpp lines 199-330
class FrameProcessor {
   public:
    // Frame validation methods
    // Migrated from validateColorFrame() in orbbec.cpp lines 233-267
    static void validateColorFrame(std::shared_ptr<ob::Frame> color,
                                   const std::optional<DeviceFormat>& device_format_opt,
                                   const OrbbecModelConfig& modelConfig);

    // Migrated from validateDepthFrame() in orbbec.cpp lines 270-304
    static void validateDepthFrame(std::shared_ptr<ob::Frame> depth,
                                   const std::optional<DeviceFormat>& device_format_opt,
                                   const OrbbecModelConfig& modelConfig);

    // Frame encoding methods
    // Migrated from encodeColorFrame() in orbbec.cpp lines 307-330
    static viam::sdk::Camera::raw_image encodeColorFrame(std::shared_ptr<ob::Frame> color);

    // Encode depth frame to Viam depth format
    static std::vector<std::uint8_t> encodeDepthFrame(std::shared_ptr<ob::Frame> depth);

    // Timestamp utilities
    // Migrated from getBestTimestampUs() in orbbec.cpp lines 221-230
    static uint64_t getBestTimestampUs(std::shared_ptr<ob::Frame> frame);

    // Migrated from getNowUs() in orbbec.cpp lines 199-201
    static uint64_t getNowUs();

    // Migrated from timeSinceFrameUs() in orbbec.cpp lines 203-208
    static uint64_t timeSinceFrameUs(uint64_t nowUs, uint64_t frameTimeUs);

    // Timestamp validation with throttled logging
    struct TimestampValidationResult {
        uint64_t timestamp_us;
        bool timestamps_differ;
        uint64_t time_diff_us;
    };

    static TimestampValidationResult validateFrameSetTimestamps(std::shared_ptr<ob::Frame> color,
                                                                std::shared_ptr<ob::Frame> depth,
                                                                uint64_t last_log_time_us,
                                                                uint64_t& updated_log_time_us);

   private:
    // Helper: Format error messages
    // Migrated from formatError() in orbbec.cpp lines 214-218
    template <typename... Args>
    static std::string formatError(Args&&... args) {
        std::ostringstream buffer;
        (buffer << ... << args);
        return buffer.str();
    }
};

}  // namespace orbbec
