#ifndef SKEtCHIFY_H
#define SKEtCHIFY_H

#include <string>

void sketchify(std::string inputFile, std::string outputFile, int hue, double noise_reduction);
void sketchify(PNG & image, std::string outputFile, int hue, double noise_reduction);

#endif
