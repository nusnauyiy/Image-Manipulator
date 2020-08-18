#include <cstdlib>
#include <cmath>
#include <iostream>
#include "../cs221util/PNG.h"
#include "../cs221util/HSLAPixel.h"

using namespace cs221util;
using namespace std;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double hue) {
    HSLAPixel* pixel = new HSLAPixel(hue, 0.5, 0.5);
    return pixel;
}

// Returns a score determining if the pixel is an edge
// requires 1 <= x < width - 1; 1 <= y < height - 1
double edgeScore(PNG* im, unsigned x, unsigned y) {
    double score = 0;
       
    // calculate score based on the luminance of the curret pixel
    // and the 8 neighboring pixels around it
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (i == 0 && j == 0) {
                score += 8 * (im->getPixel(x,y)->l);
            } else {
                score -= im->getPixel(x+i, y+j)->l;
            }
        }
    }

    return score;

}

void sketchify(std::string inputFile, std::string outputFile, int hue, double noise_reduction) {
    // Load in.png
    PNG* original = new PNG();
    //cout << "Reached line 46" << endl;
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    
    //cout << "Reached line 50" << endl;
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    hue = (hue > 0)?hue:0;
    hue = (hue < 360)?hue:360;
    HSLAPixel* myPixel = myFavoriteColor(hue);

    // Go over the whole image, and if a pixel is likely to be an edge,
    // color it my favorite color in the output
    for (unsigned y = 1; y < height - 1; y++) {
        for (unsigned x = 1; x < width - 1; x++) {
            //cout << "Reached line 61" << endl;
            // calculate how "edge-like" a pixel is
            double score = edgeScore(original, x, y);

            HSLAPixel* currOutPixel = (*output).getPixel(x, y);
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            noise_reduction = (noise_reduction > 0.1)?noise_reduction:0.1;
            noise_reduction = (noise_reduction < 0.8)?noise_reduction:0.8;
            if (score > noise_reduction) {
                //currOutPixel = myPixel;
                currOutPixel->a = myPixel->a;
                currOutPixel->h = myPixel->h;
                currOutPixel->s = myPixel->s;
                currOutPixel->l = myPixel->l;
            }
            //cout << "Reached line 71" << endl;
        }
    }




    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}

void sketchify(PNG & original, std::string outputFile, int hue, double noise_reduction) {
    // Load in.png

    unsigned width = original.width();
    unsigned height = original.height();
    
    //cout << "Reached line 50" << endl;
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    hue = (hue > 0)?hue:0;
    hue = (hue < 360)?hue:360;
    HSLAPixel* myPixel = myFavoriteColor(hue);

    // Go over the whole image, and if a pixel is likely to be an edge,
    // color it my favorite color in the output
    for (unsigned y = 1; y < height - 1; y++) {
        for (unsigned x = 1; x < width - 1; x++) {
            //cout << "Reached line 61" << endl;
            // calculate how "edge-like" a pixel is
            double score = edgeScore(&original, x, y);

            HSLAPixel* currOutPixel = (*output).getPixel(x, y);
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            noise_reduction = (noise_reduction > 0.1)?noise_reduction:0.1;
            noise_reduction = (noise_reduction < 0.8)?noise_reduction:0.8;
            if (score > noise_reduction) {
                //currOutPixel = myPixel;
                currOutPixel->a = myPixel->a;
                currOutPixel->h = myPixel->h;
                currOutPixel->s = myPixel->s;
                currOutPixel->l = myPixel->l;
            }
            //cout << "Reached line 71" << endl;
        }
    }




    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
}

