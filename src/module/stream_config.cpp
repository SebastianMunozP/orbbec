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

#include "stream_config.hpp"

#include <stdexcept>

namespace orbbec {

std::shared_ptr<ob::Config> StreamConfigManager::createHwD2CAlignConfig(std::shared_ptr<ob::Pipeline> pipe,
                                                                        const std::optional<DeviceResolution>& deviceRes,
                                                                        const std::optional<DeviceFormat>& deviceFormat,
                                                                        const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp createHwD2CAlignConfig()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::createHwD2CAlignConfig not yet implemented");
}

std::shared_ptr<ob::Config> StreamConfigManager::createSwD2CAlignConfig(std::shared_ptr<ob::Pipeline> pipe,
                                                                        const std::optional<DeviceResolution>& deviceRes,
                                                                        const std::optional<DeviceFormat>& deviceFormat,
                                                                        const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp createSwD2CAlignConfig()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::createSwD2CAlignConfig not yet implemented");
}

bool StreamConfigManager::checkIfSupportHWD2CAlign(std::shared_ptr<ob::Pipeline> pipe,
                                                   std::shared_ptr<ob::StreamProfile> colorProfile,
                                                   std::shared_ptr<ob::StreamProfile> depthProfile) {
    // TODO: Migrate implementation from orbbec.cpp checkIfSupportHWD2CAlign()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::checkIfSupportHWD2CAlign not yet implemented");
}

std::pair<std::shared_ptr<ob::StreamProfile>, std::shared_ptr<ob::StreamProfile>> StreamConfigManager::findMatchingProfiles(
    std::shared_ptr<ob::Pipeline> pipe,
    const std::optional<DeviceResolution>& deviceRes,
    const std::optional<DeviceFormat>& deviceFormat,
    const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp findMatchingProfiles()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::findMatchingProfiles not yet implemented");
}

bool StreamConfigManager::profileMatchesSpec(std::shared_ptr<ob::VideoStreamProfile> vsp,
                                             const std::optional<DeviceResolution>& deviceRes,
                                             const std::optional<DeviceFormat>& deviceFormat,
                                             const OrbbecModelConfig& modelConfig,
                                             bool isColor) {
    // TODO: Migrate implementation from orbbec.cpp profileMatchesSpec()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::profileMatchesSpec not yet implemented");
}

std::string StreamConfigManager::buildProfileErrorMsg(bool isColor,
                                                      const std::optional<DeviceResolution>& deviceRes,
                                                      const std::optional<DeviceFormat>& deviceFormat) {
    // TODO: Migrate implementation from orbbec.cpp buildProfileErrorMsg()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("StreamConfigManager::buildProfileErrorMsg not yet implemented");
}

}  // namespace orbbec
