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
#include <string>
#include <vector>

#include <libobsensor/ObSensor.hpp>

#include "orbbec.hpp"

namespace orbbec {

// Handles point cloud generation and PCD file format conversion
// Extracted from orbbec.cpp lines 334-396 and get_point_cloud() logic
class PointCloudGenerator {
   public:
    // Generate point cloud from frameset with optional depth filtering
    // Combines logic from get_point_cloud() in orbbec.cpp lines 1580-1683
    static std::vector<std::uint8_t> generatePointCloud(ViamOBDevice& device,
                                                        std::shared_ptr<ob::FrameSet> frameset,
                                                        bool apply_depth_filters);

    // Convert RGB points to PCD format
    // Migrated from RGBPointsToPCD() in orbbec.cpp lines 334-396
    static std::vector<std::uint8_t> rgbPointsToPCD(std::shared_ptr<ob::Frame> frame, float scale);

    // Dump PCD data to file for debugging
    static void dumpPCDToFile(const std::vector<std::uint8_t>& pcd_data, const std::string& serial_number);

   private:
    // Apply post-process depth filters to depth frame
    static std::shared_ptr<ob::Frame> applyDepthFilters(std::shared_ptr<ob::Frame> depth,
                                                        const std::vector<std::shared_ptr<ob::Filter>>& filters);
};

}  // namespace orbbec
