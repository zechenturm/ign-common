/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>

#include "test_config.h"
#include "ignition/common/ColladaLoader.hh"
#include "ignition/common/Mesh.hh"

using namespace ignition;

/////////////////////////////////////////////////
// Test centering a submesh.
TEST(MeshTest, LocaleMesFail)
{
  common::ColladaLoader loader;
  loader.Load(
      std::string(PROJECT_SOURCE_PATH) + "/test/data/drill/meshes/drill.dae");
}
