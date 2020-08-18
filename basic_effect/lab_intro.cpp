#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#include "../cs221util/PNG.h"
#include "../cs221util/HSLAPixel.h"
#include "lab_intro.h"

using namespace cs221util;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image, double strength) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel->s = pixel->s * (1 - strength);
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 * @param radius the distance until the image parts that does not have lumosity
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY, int radius) {

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      double distance = sqrt((centerX - x) * (centerX - x) + (centerY - y) * (centerY - y));
      
      HSLAPixel *pixel = image.getPixel(x, y);
      if (distance > radius) {
        pixel->l = 0;
      } else {
        pixel->l = pixel->l - distance * (1.0 / (double)radius); 
        if (pixel->l < 0) pixel->l = 0;
      }
    }
  }
  return image;
}

/**
 * Returns a image transformed to one colors
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param hue color transformed to
 * @return The monochromatic image.
**/
PNG monochromatize(PNG image, double hue) {
  hue = (hue > 0)?hue:0;
  hue = (hue < 360)?hue:360;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      image.getPixel(x, y)->h = hue;
    }
  }
}


/**
 * Returns a image transformed to two colors, base on whichever color each picel is closer to
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param hue1 first color
 * @param hue2 second color
 * @return The dichromatic image.
**/
PNG dichromatize(PNG image, double hue1, double hue2) {

  hue1 = (hue1 > 0)?hue1:0;
  hue1 = (hue1 < 360)?hue1:360;
  hue2 = (hue2 > 0)?hue2:0;
  hue2 = (hue2 < 360)?hue2:360;

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      
      double distanceToHue1 = min(min(abs(pixel->h - hue1), abs(pixel->h - hue1 + 360)), abs(pixel->h - hue1 - 360));
      double distanceToHue2 = min(min(abs(pixel->h - hue2), abs(pixel->h - hue2 + 360)), abs(pixel->h - hue2 - 360));
      if (distanceToHue1 > distanceToHue2) {
        pixel -> h = hue2;
      } else {
        pixel -> h = hue1;
      }
    }
  }
  return image;
}


/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is greater than 0.5 (50%), then the pixel at the same location on
* the first image has its luminance increased by 0.2 * luminance of the first pixel.
*
* @param firstImage  The first of the two PNGs.
* @param secondImage The second of the two PNGs.
* @param startX      x coordinate on first image the water mark should appear
* @param startY      y coordinate on first image the water mark should appear
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage, int startX, int startY) {

  for (unsigned x = 0; x < secondImage.width(); x++) {
    for (unsigned y = 0; y < secondImage.height(); y++) {
        if (secondImage.getPixel(x, y) -> l > 0.5 && 
          (x + startX < firstImage.width() && y + startY < firstImage.height())) {
          firstImage.getPixel(x + startX, y + startY) -> l += (0.2 * secondImage.getPixel(x, y) -> l) ;
        }
    }
  }
  return firstImage;
}

