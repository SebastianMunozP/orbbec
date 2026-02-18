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
#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include <libobsensor/ObSensor.hpp>

#include "orbbec.hpp"

namespace orbbec {

// Consolidated per-device state structure
// Replaces 4 separate global maps with a single unified state container
struct DeviceState {
    std::string serial_number;
    std::string resource_name;                      // Replaces serial_by_resource map
    std::unique_ptr<ViamOBDevice> device;           // Replaces devices_by_serial map
    std::shared_ptr<ob::FrameSet> latest_frameset;  // Replaces frame_set_by_serial map
    ObResourceConfig config;                        // Replaces config_by_serial map
};

// Thread-safe singleton managing all device state
// Eliminates global variables and reduces from 4 mutexes to 1
//
// Note: This class is designed for future template-based testing.
// Templates will be added in Phase 2 to enable dependency injection
// and testing without real hardware.
class DeviceRegistry {
   public:
    // Get singleton instance
    static DeviceRegistry& instance();

    // Device management
    void registerDevice(const std::string& serial, std::shared_ptr<ob::Device> device);
    void unregisterDevice(const std::string& serial);
    bool hasDevice(const std::string& serial) const;

    // Resource mapping (replaces serial_by_resource global map)
    void bindResourceToSerial(const std::string& resource, const std::string& serial);
    void unbindResource(const std::string& resource);
    std::optional<std::string> getSerialForResource(const std::string& resource);

    // Thread-safe device access with RAII lock
    // Returns locked access to device, automatically releases on destruction
    struct DeviceLock {
        std::unique_lock<std::mutex> lock;
        ViamOBDevice* device;

        // Explicit constructor
        DeviceLock(std::unique_lock<std::mutex> l, ViamOBDevice* d) : lock(std::move(l)), device(d) {}

        // Allow move
        DeviceLock(DeviceLock&&) = default;
        DeviceLock& operator=(DeviceLock&&) = default;

        // Prevent copy
        DeviceLock(const DeviceLock&) = delete;
        DeviceLock& operator=(const DeviceLock&) = delete;
    };
    DeviceLock getDevice(const std::string& serial);

    // Frame management (replaces frame_set_by_serial global map)
    void updateFrameSet(const std::string& serial, std::shared_ptr<ob::FrameSet> frameset);
    std::shared_ptr<ob::FrameSet> getFrameSet(const std::string& serial);

    // Config management (replaces config_by_serial global map)
    void updateConfig(const std::string& serial, const ObResourceConfig& config);
    ObResourceConfig getConfig(const std::string& serial);

    // Query operations
    std::vector<std::string> getAllSerials() const;

   private:
    // Singleton pattern - private constructor/destructor
    DeviceRegistry() = default;
    ~DeviceRegistry() = default;
    DeviceRegistry(const DeviceRegistry&) = delete;
    DeviceRegistry& operator=(const DeviceRegistry&) = delete;

    // Single mutex for all state (replaces 4 separate mutexes)
    mutable std::mutex state_mutex_;

    // Consolidated device state (replaces 4 separate global maps)
    std::unordered_map<std::string, DeviceState> device_states_;
};

}  // namespace orbbec
