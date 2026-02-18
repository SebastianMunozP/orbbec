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

#include <libobsensor/ObSensor.hpp>
#include <memory>
#include <string>

namespace orbbec {

// Abstract interfaces for Orbbec SDK types
// These enable testing without real hardware by allowing mock implementations

// Interface for ob::Device
class IDevice {
   public:
    virtual ~IDevice() = default;
    virtual std::shared_ptr<ob::DeviceInfo> getDeviceInfo() = 0;
    virtual std::shared_ptr<ob::DeviceList> querySensors() = 0;
    virtual void setIntProperty(OBPropertyID property_id, int32_t value) = 0;
    virtual int32_t getIntProperty(OBPropertyID property_id) = 0;
    virtual void setBoolProperty(OBPropertyID property_id, bool value) = 0;
    virtual bool getBoolProperty(OBPropertyID property_id) = 0;
    virtual bool isPropertySupported(OBPropertyID property_id, OBPermissionType permission) = 0;
    virtual OBMultiDeviceSyncMode getMultiDeviceSyncConfig() = 0;
    virtual void setMultiDeviceSyncConfig(OBMultiDeviceSyncMode mode) = 0;
};

// Interface for ob::Pipeline
class IPipeline {
   public:
    virtual ~IPipeline() = default;
    virtual void start(std::shared_ptr<ob::Config> config) = 0;
    virtual void start(std::shared_ptr<ob::Config> config, std::function<void(std::shared_ptr<ob::FrameSet>)> callback) = 0;
    virtual void stop() = 0;
    virtual std::shared_ptr<ob::Config> getConfig() = 0;
    virtual std::shared_ptr<ob::StreamProfileList> getStreamProfileList(OBSensorType sensorType) = 0;
    virtual void enableFrameSync() = 0;
    virtual std::shared_ptr<ob::CameraParamList> getCameraParamList() = 0;
};

// Interface for ob::Config
class IConfig {
   public:
    virtual ~IConfig() = default;
    virtual void enableStream(std::shared_ptr<ob::StreamProfile> profile) = 0;
    virtual void setAlignMode(OBAlignMode mode) = 0;
    virtual void setFrameAggregateOutputMode(OBFrameAggregateOutputMode mode) = 0;
};

// Interface for ob::FrameSet
class IFrameSet {
   public:
    virtual ~IFrameSet() = default;
    virtual std::shared_ptr<ob::Frame> getFrame(OBFrameType type) = 0;
    virtual uint32_t getCount() = 0;
};

// Interface for ob::Frame
class IFrame {
   public:
    virtual ~IFrame() = default;
    virtual OBFrameType getType() = 0;
    virtual OBFormat getFormat() = 0;
    virtual uint64_t getTimeStamp() = 0;
    virtual uint64_t getTimeStampUs() = 0;
    virtual uint64_t getSystemTimeStamp() = 0;
    virtual void* getData() = 0;
    virtual uint32_t getDataSize() = 0;
};

// Interface for ob::VideoFrame
class IVideoFrame : public IFrame {
   public:
    virtual ~IVideoFrame() = default;
    virtual uint32_t getWidth() = 0;
    virtual uint32_t getHeight() = 0;
    virtual uint32_t getPixelAvailableBitSize() = 0;
};

// Interface for ob::Filter
class IFilter {
   public:
    virtual ~IFilter() = default;
    virtual std::shared_ptr<ob::Frame> process(std::shared_ptr<ob::Frame> frame) = 0;
    virtual void enable(bool enable) = 0;
};

// Interface for ob::PointCloudFilter
class IPointCloudFilter : public IFilter {
   public:
    virtual ~IPointCloudFilter() = default;
    virtual void setCameraParam(ob::OBCameraParam param) = 0;
    virtual void setPositionDataScaled(float scale) = 0;
    virtual void setColorDataNormalization(bool enable) = 0;
};

// Interface for ob::Align
class IAlign : public IFilter {
   public:
    virtual ~IAlign() = default;
    // Inherits process() from IFilter
};

// Adapter classes that wrap real Orbbec SDK types
// These allow existing code to work with both real and mock implementations

template <typename T>
class RealDevice : public IDevice {
   public:
    explicit RealDevice(std::shared_ptr<T> device) : device_(device) {}

    std::shared_ptr<ob::DeviceInfo> getDeviceInfo() override {
        return device_->getDeviceInfo();
    }
    std::shared_ptr<ob::DeviceList> querySensors() override {
        return device_->querySensors();
    }
    void setIntProperty(OBPropertyID property_id, int32_t value) override {
        device_->setIntProperty(property_id, value);
    }
    int32_t getIntProperty(OBPropertyID property_id) override {
        return device_->getIntProperty(property_id);
    }
    void setBoolProperty(OBPropertyID property_id, bool value) override {
        device_->setBoolProperty(property_id, value);
    }
    bool getBoolProperty(OBPropertyID property_id) override {
        return device_->getBoolProperty(property_id);
    }
    bool isPropertySupported(OBPropertyID property_id, OBPermissionType permission) override {
        return device_->isPropertySupported(property_id, permission);
    }
    OBMultiDeviceSyncMode getMultiDeviceSyncConfig() override {
        return device_->getMultiDeviceSyncConfig();
    }
    void setMultiDeviceSyncConfig(OBMultiDeviceSyncMode mode) override {
        device_->setMultiDeviceSyncConfig(mode);
    }

    std::shared_ptr<T> getRealDevice() {
        return device_;
    }

   private:
    std::shared_ptr<T> device_;
};

template <typename T>
class RealPipeline : public IPipeline {
   public:
    explicit RealPipeline(std::shared_ptr<T> pipeline) : pipeline_(pipeline) {}

    void start(std::shared_ptr<ob::Config> config) override {
        pipeline_->start(config);
    }
    void start(std::shared_ptr<ob::Config> config, std::function<void(std::shared_ptr<ob::FrameSet>)> callback) override {
        pipeline_->start(config, callback);
    }
    void stop() override {
        pipeline_->stop();
    }
    std::shared_ptr<ob::Config> getConfig() override {
        return pipeline_->getConfig();
    }
    std::shared_ptr<ob::StreamProfileList> getStreamProfileList(OBSensorType sensorType) override {
        return pipeline_->getStreamProfileList(sensorType);
    }
    void enableFrameSync() override {
        pipeline_->enableFrameSync();
    }
    std::shared_ptr<ob::CameraParamList> getCameraParamList() override {
        return pipeline_->getCameraParamList();
    }

    std::shared_ptr<T> getRealPipeline() {
        return pipeline_;
    }

   private:
    std::shared_ptr<T> pipeline_;
};

}  // namespace orbbec
