/*
 * Texture.cpp
 *
 *
 */

#include "Texture.h"

namespace rt
{

void Texture::setParameters(std::string _location)
{
    image = cv::imread(_location, 1);
    location = _location;
};

Vec3f Texture::getRGB(float u, float v)
{
    int i = (u)*image.rows;
    int j = (1 - v) * image.cols - 0.001;
    if (i < 0)
        i = 0;
    if (j < 0)
        j = 0;
    if (i > image.rows - 1)
        i = image.rows - 1;
    if (j > image.cols - 1)
        j = image.cols - 1;

    cv::Vec3b col = image.at<cv::Vec3b>(i, j);
    float r = col[2] / 255.0;
    float g = col[1] / 255.0;
    float b = col[0] / 255.0;
    return Vec3f(r, g, b);
};

} //namespace rt
