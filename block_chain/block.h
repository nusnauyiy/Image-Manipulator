
#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include "../cs221util/PNG.h"
#include "../cs221util/HSLAPixel.h"
using namespace std;
using namespace cs221util;

class Block
{

public:
   /** 
    * Creates a block that is width pixels wide.
    * starting at (x, 0) on img.
    */
   void build(PNG &img, int x, int width);

   /** 
    * Renders the given block onto img with its upper
    * left corner at (x, 0)
    */
   void render(PNG &img, int x) const;

   /**
    * Creates a "pastel" version of the block by halving
    * the saturation and doubling the luminesence of each pixel.
    */
   void pastel();

   // Return the width and height of the block.
   int width() const;
   int height() const;

private:
   vector<vector<HSLAPixel>> data;
};
#endif
