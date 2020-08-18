#include "gridColorPicker.h"

gridColorPicker::gridColorPicker(HSLAPixel gridColor, int gridSpacing)
{
    color = gridColor;
    spacing = gridSpacing;
}

HSLAPixel gridColorPicker::operator()(int x, int y)
{
    /**
     * @todo your code here!
     * HINT: manipulate y = mx + b
     */
    int b = x - y;
    int c = x + y;
    if (b % spacing == 0 || c % spacing == 0) {
        return color;
    } else {
        return HSLAPixel(0,0,1,0);
    }
}
