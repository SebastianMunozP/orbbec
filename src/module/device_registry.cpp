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

#include "device_registry.hpp"

#include <iostream>
#include <optional>
#include <stdexcept>

#ifdef _WIN32
#include "orbbec_windows_registry.hpp"
#endif

namespace orbbec {

// Singleton instance accessor
DeviceRegistry& DeviceRegistry::instance() {
    static DeviceRegistry instance;
    return instance;
}

// Device management
void DeviceRegistry::registerDevice(const std::string& serial, std::shared_ptr<ob::Device> device) {
    std::cout << "[DeviceRegistry::registerDevice] Registering device " << serial << "\n";

#ifdef _WIN32
    // Setup Windows device registry for Orbbec cameras
    try {
        windows_registry::setupWindowsDeviceRegistry(device);
    } catch (const std::exception& e) {
        throw std::runtime_error("failed to setup windows device registry: " + std::string(e.what()));
    }
#endif

    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it == device_states_.end()) {
        // Create ViamOBDevice wrapper
        auto viam_device = std::make_unique<ViamOBDevice>();
        viam_device->serialNumber = serial;
        viam_device->device = device;
        viam_device->started = false;
        viam_device->applyEnabledPostProcessDepthFilters = false;
        viam_device->dumpPCLFiles = false;

        // Create DeviceState inline with all required fields
        // Config will be updated later via updateConfig()
        DeviceState state{
            serial,                                                   // serial_number
            "",                                                       // resource_name (empty initially)
            std::move(viam_device),                                   // device
            nullptr,                                                  // latest_frameset (null initially)
            ObResourceConfig(serial, "", std::nullopt, std::nullopt)  // config (default config)
        };

        device_states_.emplace(serial, std::move(state));
        std::cout << "[DeviceRegistry::registerDevice] Successfully registered device " << serial << "\n";
    } else {
        // Update existing device
        it->second.device->device = device;
        std::cout << "[DeviceRegistry::registerDevice] Updated existing device " << serial << "\n";
    }
}

void DeviceRegistry::unregisterDevice(const std::string& serial) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        std::cout << "[DeviceRegistry::unregisterDevice] Unregistering device " << serial << "\n";
        device_states_.erase(it);
    } else {
        std::cerr << "[DeviceRegistry::unregisterDevice] Device " << serial << " not found in registry\n";
    }
}

bool DeviceRegistry::hasDevice(const std::string& serial) const {
    std::lock_guard<std::mutex> lock(state_mutex_);
    return device_states_.find(serial) != device_states_.end();
}

// Resource mapping
void DeviceRegistry::bindResourceToSerial(const std::string& resource, const std::string& serial) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        // Unbind any previous resource binding for this serial
        if (!it->second.resource_name.empty() && it->second.resource_name != resource) {
            std::cerr << "[DeviceRegistry::bindResourceToSerial] Device " << serial << " already bound to resource "
                      << it->second.resource_name << ", rebinding to " << resource << "\n";
        }
        it->second.resource_name = resource;
        // Debug logging commented out to reduce verbosity
        // std::cout << "[DeviceRegistry::bindResourceToSerial] Bound resource " << resource << " to serial " << serial << "\n";
    } else {
        std::cerr << "[DeviceRegistry::bindResourceToSerial] Attempted to bind resource " << resource << " to non-existent device "
                  << serial << "\n";
    }
}

void DeviceRegistry::unbindResource(const std::string& resource) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    // Find device with this resource name and clear it
    for (auto& [serial, state] : device_states_) {
        if (state.resource_name == resource) {
            // Debug logging commented out to reduce verbosity
            // std::cout << "[DeviceRegistry::unbindResource] Unbinding resource " << resource << " from serial " << serial << "\n";
            state.resource_name.clear();
            break;
        }
    }
}

std::optional<std::string> DeviceRegistry::getSerialForResource(const std::string& resource) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    for (const auto& [serial, state] : device_states_) {
        if (state.resource_name == resource) {
            return serial;
        }
    }
    return std::nullopt;
}

// Thread-safe device access
DeviceRegistry::DeviceLock DeviceRegistry::getDevice(const std::string& serial) {
    std::unique_lock<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it == device_states_.end()) {
        return DeviceLock(std::move(lock), nullptr);
    }

    return DeviceLock(std::move(lock), it->second.device.get());
}

// Frame management
void DeviceRegistry::updateFrameSet(const std::string& serial, std::shared_ptr<ob::FrameSet> frameset) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        it->second.latest_frameset = frameset;
    }
}

std::shared_ptr<ob::FrameSet> DeviceRegistry::getFrameSet(const std::string& serial) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        return it->second.latest_frameset;
    }
    return nullptr;
}

// Config management
void DeviceRegistry::updateConfig(const std::string& serial, const ObResourceConfig& config) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        it->second.config = config;
        // Debug logging commented out to reduce verbosity
        // std::cout << "[DeviceRegistry::updateConfig] Updated config for device " << serial << ": " << config.to_string() << "\n";
    }
}

ObResourceConfig DeviceRegistry::getConfig(const std::string& serial) {
    std::lock_guard<std::mutex> lock(state_mutex_);

    auto it = device_states_.find(serial);
    if (it != device_states_.end()) {
        return it->second.config;
    }

    // Return empty config if not found
    throw std::runtime_error("Config not found for serial: " + serial);
}

// Query operations
std::vector<std::string> DeviceRegistry::getAllSerials() const {
    std::lock_guard<std::mutex> lock(state_mutex_);

    std::vector<std::string> serials;
    serials.reserve(device_states_.size());

    for (const auto& [serial, _] : device_states_) {
        serials.push_back(serial);
    }

    return serials;
}

}  // namespace orbbec
