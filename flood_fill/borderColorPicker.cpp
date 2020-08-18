#include "borderColorPicker.h"
#include <vector>

using namespace std;

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{   color = fillColor;
   im = img;
   tol = tolerance;
   ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y) {
   if (x < 3 || x >= im.width() - 3 ||
      y < 3 || y >= im.width() - 3) {
         return color;
      }
   
   vector<vector<int>> border{{0, 3},{3, 0},{0, -3},{-3, 0},
                              {-2, -2},{-2, -1},{-2, 0},{-2, 1},{-2, 2},
                              {-1, -2},{-1, -1},{-1, 0},{-1, 1},{-1, 2},
                              {0, -2},{0, -1},{0, 1},{0, 2},
                              {1, -2},{1, -1},{1, 0},{1, 1},{1, 2},
                              {2, -2},{2, -1},{2, 0},{2, 1},{2, 2}
                           };

   for (vector<int> c: border) {
      int x_coord = c[0] + x;
      int y_coord = c[1] + y;
      HSLAPixel * neighbor = im.getPixel(x_coord,y_coord);
      if (ctr.dist(*neighbor) > tol) {
         return color;
      }
   }
	return ctr;
}
