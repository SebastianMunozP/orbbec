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

#include "frame_processor.hpp"

#include <stdexcept>

namespace orbbec {

void FrameProcessor::validateColorFrame(std::shared_ptr<ob::Frame> color,
                                        const std::optional<DeviceFormat>& device_format_opt,
                                        const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp validateColorFrame()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::validateColorFrame not yet implemented");
}

void FrameProcessor::validateDepthFrame(std::shared_ptr<ob::Frame> depth,
                                        const std::optional<DeviceFormat>& device_format_opt,
                                        const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp validateDepthFrame()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::validateDepthFrame not yet implemented");
}

viam::sdk::Camera::raw_image FrameProcessor::encodeColorFrame(std::shared_ptr<ob::Frame> color) {
    // TODO: Migrate implementation from orbbec.cpp encodeColorFrame()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::encodeColorFrame not yet implemented");
}

std::vector<std::uint8_t> FrameProcessor::encodeDepthFrame(std::shared_ptr<ob::Frame> depth) {
    // TODO: Implement depth frame encoding
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::encodeDepthFrame not yet implemented");
}

uint64_t FrameProcessor::getBestTimestampUs(std::shared_ptr<ob::Frame> frame) {
    // TODO: Migrate implementation from orbbec.cpp getBestTimestampUs()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::getBestTimestampUs not yet implemented");
}

uint64_t FrameProcessor::getNowUs() {
    // TODO: Migrate implementation from orbbec.cpp getNowUs()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::getNowUs not yet implemented");
}

uint64_t FrameProcessor::timeSinceFrameUs(uint64_t nowUs, uint64_t frameTimeUs) {
    // TODO: Migrate implementation from orbbec.cpp timeSinceFrameUs()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::timeSinceFrameUs not yet implemented");
}

FrameProcessor::TimestampValidationResult FrameProcessor::validateFrameSetTimestamps(std::shared_ptr<ob::Frame> color,
                                                                                     std::shared_ptr<ob::Frame> depth,
                                                                                     uint64_t last_log_time_us,
                                                                                     uint64_t& updated_log_time_us) {
    // TODO: Implement timestamp validation with throttled logging
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("FrameProcessor::validateFrameSetTimestamps not yet implemented");
}

}  // namespace orbbec
