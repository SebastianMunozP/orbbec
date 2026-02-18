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

#include "point_cloud_generator.hpp"

#include <stdexcept>

namespace orbbec {

std::vector<std::uint8_t> PointCloudGenerator::generatePointCloud(ViamOBDevice& device,
                                                                  std::shared_ptr<ob::FrameSet> frameset,
                                                                  bool apply_depth_filters) {
    // TODO: Migrate implementation from orbbec.cpp get_point_cloud()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("PointCloudGenerator::generatePointCloud not yet implemented");
}

std::vector<std::uint8_t> PointCloudGenerator::rgbPointsToPCD(std::shared_ptr<ob::Frame> frame, float scale) {
    // TODO: Migrate implementation from orbbec.cpp RGBPointsToPCD()
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("PointCloudGenerator::rgbPointsToPCD not yet implemented");
}

void PointCloudGenerator::dumpPCDToFile(const std::vector<std::uint8_t>& pcd_data, const std::string& serial_number) {
    // TODO: Implement PCD file dumping for debugging
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("PointCloudGenerator::dumpPCDToFile not yet implemented");
}

std::shared_ptr<ob::Frame> PointCloudGenerator::applyDepthFilters(std::shared_ptr<ob::Frame> depth,
                                                                  const std::vector<std::shared_ptr<ob::Filter>>& filters) {
    // TODO: Implement depth filter application
    // This is a stub that will be implemented in Phase 2
    throw std::runtime_error("PointCloudGenerator::applyDepthFilters not yet implemented");
}

}  // namespace orbbec
