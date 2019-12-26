/*
 * Texture.h
 *
 *
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "math/geometry.h"
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

namespace rt
{

class Texture
{

  public:
	Texture(){};

	~Texture(){};

	void setParameters(std::string _location);
	Vec3f getRGB(float u, float v);

  private:
	std::string location;
	cv::Mat image;
};

} //namespace rt

#endif /* TEXTURE_H_ */
