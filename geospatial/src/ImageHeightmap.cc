/*
 * Copyright (C) 2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include "ignition/common/Console.hh"
#include "ignition/common/geospatial/ImageHeightmap.hh"

using namespace ignition;
using namespace common;

//////////////////////////////////////////////////
ImageHeightmap::ImageHeightmap()
{
}

//////////////////////////////////////////////////
int ImageHeightmap::Load(const std::string &_filename)
{
  if (this->img.Load(_filename) != 0)
  {
    ignerr << "Unable to load image file as a terrain [" << _filename << "]\n";
    return -1;
  }

  return 0;
}

//////////////////////////////////////////////////
void ImageHeightmap::FillHeightMap(int _subSampling,
    unsigned int _vertSize, const ignition::math::Vector3d &_size,
    const ignition::math::Vector3d &_scale, bool _flipY,
    std::vector<float> &_heights) const
{
  // Resize the vector to match the size of the vertices.
  _heights.resize(_vertSize * _vertSize);

  int imgHeight = this->Height();
  int imgWidth = this->Width();

  IGN_ASSERT(imgWidth == imgHeight, "Heightmap image must be square");

  // Bytes per row
  unsigned int pitch = this->img.Pitch();

  // Get the image format so we can arrange our heightmap
  // Currently supported: 8-bit and 16-bit.
  auto imgFormat = this->img.PixelFormat();

  unsigned char *data = nullptr;
  unsigned int count;
  this->img.Data(&data, count);

  if (imgFormat == ignition::common::Image::PixelFormatType::L_INT8 ||
    imgFormat == ignition::common::Image::PixelFormatType::RGB_INT8 ||
    imgFormat == ignition::common::Image::PixelFormatType::RGBA_INT8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BAYER_BGGR8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BAYER_GBRG8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BAYER_GRBG8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BAYER_GRBG8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BAYER_RGGB8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BGR_INT8 ||
    imgFormat == ignition::common::Image::PixelFormatType::BGRA_INT8)
  {
    this->FillHeights<unsigned char>(data, imgHeight, imgWidth, pitch,
        _subSampling, _vertSize, _size, _scale, _flipY, _heights);
  }
  else if (imgFormat == ignition::common::Image::PixelFormatType::BGR_INT16 ||
    imgFormat == ignition::common::Image::PixelFormatType::L_INT16 ||
    imgFormat == ignition::common::Image::PixelFormatType::RGB_FLOAT16 ||
    imgFormat == ignition::common::Image::PixelFormatType::RGB_INT16 ||
    imgFormat == ignition::common::Image::PixelFormatType::R_FLOAT16)
  {
    uint16_t *dataShort = reinterpret_cast<uint16_t *>(data);
    this->FillHeights<uint16_t>(dataShort, imgHeight, imgWidth, pitch,
        _subSampling, _vertSize, _size, _scale, _flipY, _heights);
  }
  else
  {
    ignerr << "Unsupported image format, "
      "heightmap will not be loaded" << std::endl;
    return;
  }
  delete [] data;
}

//////////////////////////////////////////////////
std::string ImageHeightmap::Filename() const
{
  return this->img.Filename();
}

//////////////////////////////////////////////////
unsigned int ImageHeightmap::Height() const
{
  return this->img.Height();
}

//////////////////////////////////////////////////
unsigned int ImageHeightmap::Width() const
{
  return this->img.Width();
}

//////////////////////////////////////////////////
float ImageHeightmap::MaxElevation() const
{
  return this->img.MaxColor().R();
}
