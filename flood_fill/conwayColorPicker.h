#ifndef conwayColorPicker_H
#define conwayColorPicker_H

#include <stdint.h>
#include <map>
#include <utility>
#include "colorPicker.h"

/**
 * conwayColorPicker: a functor that determines the color that should be used
 * given an x and a y coordinate using Game-of-Life-esque rules given in nextColor()
 *
 */
class conwayColorPicker : public colorPicker
{
  public:
    /**
     * Constructs a new conwayColorPicker.
     *
     */
    conwayColorPicker();

    /**
     * Picks the color for pixel (x, y).
     *
     * @param x The x coordinate to pick a color for.
     * @param y The y coordinat to pick a color for.
     * @return The color chosen for (x, y).
     */
    virtual HSLAPixel operator()(int x, int y);

  private:
    HSLAPixel nextColor(int neighbourCount);

    typedef std::map<std::pair<int, int>, HSLAPixel> PNGmap;
    size_t iter;
    PNGmap prev;
};

#endif