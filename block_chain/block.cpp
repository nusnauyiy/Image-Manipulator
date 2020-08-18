#include "block.h"
#include <iostream>

using namespace std;

//int width() const: Returns the width of the current block.
int Block::width() const {
    return data.size();
}

//int height() const: Returns the height of the current block.
int Block::height() const {
    return data[0].size();
}

//void build(PNG & im, int column, int width): 
//From im, grabs the vertical strip of pixels whose 
//upper left corner is at position (column,0), and whose width is "width".
void Block::build(PNG & img, int column, int width) {
    if (column + width > img.width()) {
        width = img.width() - column;
    }

    for (int i = 0; i < width; i++) {
        vector<HSLAPixel> arr(img.height());
        data.push_back(arr);
        for (int j = 0; j < img.height(); j++) {
            //cout << "line 28" << endl;
            data[i][j] = * img.getPixel(i + column, j);
            //cout << "line 30" << endl;
        }
    }
}

/** 
    * Renders the given block onto img with its upper
    * left corner at (x, 0)
    */
void Block::render(PNG & im, int column) const {
    for (int i = 0; i < width() && (column + i) < im.width(); i++) {
        for (int j = 0; j < height() && j < im.height(); j++) {
            (*im.getPixel(column + i, j)) = data[i][j];
        }
    }
}

/**
    * Creates a "pastel" version of the block by halving
    * the saturation and doubling the luminesence of each pixel.
    */
void Block::pastel() {
    for (int i = 0; i < width(); i++) {
        for (int j = 0; j < height(); j++) {
            data[i][j].s /= 2;
            data[i][j].l *= 2;
            if(data[i][j].l > 1) data[i][j].l = 1;
        }
    }
}

