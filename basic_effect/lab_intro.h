#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "../cs221util/PNG.h"
using namespace cs221util;

PNG grayscale(PNG image, double strength);  
PNG createSpotlight(PNG image, int centerX, int centerY, int radius);
PNG monochromatize(PNG image, double hue);
PNG dichromatize(PNG image, double hue1, double hue2);
PNG watermark(PNG firstImage, PNG secondImage, int startX, int startY);

#endif
