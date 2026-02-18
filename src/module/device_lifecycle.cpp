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

#include "device_lifecycle.hpp"

#include <stdexcept>

namespace orbbec {

DeviceLifecycleManager::DeviceLifecycleManager(DeviceRegistry& registry) : registry_(registry) {}

void DeviceLifecycleManager::configureDevice(const std::string& serial,
                                             const OrbbecModelConfig& modelConfig,
                                             const std::optional<DeviceResolution>& resolution,
                                             const std::optional<DeviceFormat>& format) {
    // TODO: Migrate implementation from orbbec.cpp configureDevice()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::configureDevice not yet implemented");
}

void DeviceLifecycleManager::startDevice(const std::string& serial, const OrbbecModelConfig& modelConfig) {
    // TODO: Migrate implementation from orbbec.cpp startDevice()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::startDevice not yet implemented");
}

void DeviceLifecycleManager::stopDevice(const std::string& serial, const std::string& resourceName) {
    // TODO: Migrate implementation from orbbec.cpp stopDevice()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::stopDevice not yet implemented");
}

void DeviceLifecycleManager::applyExperimentalConfig(const std::string& serial, const viam::sdk::ProtoStruct& config) {
    // TODO: Migrate implementation from orbbec.cpp applyExperimentalConfig()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::applyExperimentalConfig not yet implemented");
}

void DeviceLifecycleManager::enableGlobalTimestamp(const std::string& serial) {
    // TODO: Implement global timestamp enabling
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::enableGlobalTimestamp not yet implemented");
}

void DeviceLifecycleManager::setMultiDeviceSyncMode(const std::string& serial, OBMultiDeviceSyncMode mode) {
    // TODO: Implement multi-device sync mode setting
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::setMultiDeviceSyncMode not yet implemented");
}

void DeviceLifecycleManager::initializeDeviceComponents(ViamOBDevice& device) {
    // TODO: Migrate component initialization logic
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::initializeDeviceComponents not yet implemented");
}

std::shared_ptr<ob::Config> DeviceLifecycleManager::createPipelineConfig(ViamOBDevice& device,
                                                                         const OrbbecModelConfig& modelConfig,
                                                                         const std::optional<DeviceResolution>& resolution,
                                                                         const std::optional<DeviceFormat>& format) {
    // TODO: Migrate pipeline config creation logic
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("DeviceLifecycleManager::createPipelineConfig not yet implemented");
}

}  // namespace orbbec
