#include <iostream>
#include <string>
#include <fstream>      // std::ifstream
#include "cs221util/PNG.h"
#include "block_chain/chain.h"
#include "block_chain/block.h"
#include "basic_effect/lab_intro.h"
#include "sketchification/sketchify.h"


using namespace std;
using namespace cs221util;


string chooseImage()
{
    bool proceed = false;
    string path;

    while(!proceed) {
        cout << "Enter path of image you would like to process: ";
        cin >> path;
        ifstream test(path, ifstream::in); 
        if (path == "quit") {
            return "";
        } else if (!test)
        {
            //not a dir or file
            cout << "The file doesn't exist" << endl;
        } else if (path.find(".png") == std::string::npos) {
            //not a file
            cout << "Not a PNG file" << endl;
        } else {
            proceed = true;
        }
    }
    return path;
}

int getNumericInput(int max) {
    int input;
    bool proceed = false;

    while (!proceed) {
        cin >> input;
        if (input > max || input < 0) {
            cout << "Invalid option" << endl;
        } else if (input == 0) {
            return 0;
        } else {
            proceed = true;
        }
    }
    return input;
}

PNG processImage(PNG & image) {
    Chain c;
    cout << "=====================================" << endl
    << "choose manipulation type: " << endl
    << "1. basic effects" << endl
    << "2: sketchification " << endl
    << "3. block-chain effects" << endl
    << "0. quit " << endl;

    switch(getNumericInput(3)) {
        case 1:
            cout << "\t=================================" << endl
            << "\t1. grayscale" << endl
            << "\t2: spotlight " << endl
            << "\t3. monochrome" << endl
            << "\t4. dichrome" << endl
            << "\t0. quit " << endl;
            switch (getNumericInput(4)) {
                case 1:
                    cout << "\t\t==============grayscale==============" << endl
                    << "\t\tEnter strength of effect (0.0 - 1.0): ";
                        double strength;
                        cin >> strength;
                    return grayscale(image, strength);
                case 2:
                    cout << "\t\t==============spotlight==============" << endl
                    << "\t\tEnter radius of effect (pixel): ";
                        int radius;
                        cin >> radius;
                    cout << "\t\tEnter x-coordinate of center (pixel): ";
                        int centerX;
                        cin >> centerX;
                    cout << "\t\tEnter y-coordinate of center (pixel): ";
                        int centerY;
                        cin >> centerY;
                    return createSpotlight(image, centerX, centerY, radius);
                case 3:
                    cout << "\t\t==============monochrome==============" << endl
                    << "\t\tEnter a hue (0 - 360): ";
                        double hue;
                        cin >> hue;
                    return monochromatize(image, hue);
                case 4:
                    cout << "\t\t==============dichrome==============" << endl
                    << "\t\tEnter a hue (0 - 360): ";
                        double hue1;
                        cin >> hue1;
                    cout << "\t\tEnter another hue (0 - 360): ";
                        double hue2;
                        cin >> hue2;
                    return dichromatize(image, hue1, hue2);
                default:
                    return image;
            }
        case 2:
            cout << "\t==============sketchify===============" << endl
            << "\t1Enter a hue (0 - 360): ";
                double hue;
                cin >> hue;
            cout << "\tEnter noise reduction level (0.0 - 1.0): ";
                double noise;
                cin >> noise;
            sketchify(image, "result.png", hue, noise);
            return image;
        case 3:
            cout << "\t=============block-chain==============" << endl
            << "\t1Enter column number (1 - " << image.width()/2 << "): ";
                int col;
                cin >> col;
            cout << "\t=================================" << endl
                << "\t1. mirror" << endl
                << "\t2: rotate " << endl;
            c = Chain(image, col);
            switch(getNumericInput(2)) {
                case 1:
                    c.mirror();
                    return c.render(col);
                case 2:
                    cout << "\t\t==============rotate==============" << endl
                    << "\t\tEnter frequency of rotation: ";
                        int frequency;
                        cin >> frequency;
                    c.rotate(frequency);
                    return c.render(col);
                default:
                    return image;
            }
        default:
            return image;
    }
}

bool promptYN(string message) {
    while (true) {
        cout << message;
        char input;
        cin >> input;
        if (input == 'y') return true;
        else if (input == 'n') return false;

        cout << "\nInvalid input" << endl;
    }
}

int main() {
    while (true) {
        string path = chooseImage();
        if (path == "") return 0;
        PNG pngin;
        pngin.readFromFile(path);
        
        while (true) {
            PNG result = processImage(pngin);
            if (result == pngin) {
                if (promptYN("Would you like to choose a different image? (y/n) ")) break;
                else if (promptYN("Would you like to quit? (y/n) ")) return 0;
            } else {
                result.writeToFile("result.png");
                if (promptYN("The result is saved as result.png. Would you like to process it further? (y/n) ")) {
                    pngin = result;
                    continue;
                } else if (promptYN("Would you like to choose a different image? (y/n) ")) {
                    continue;
                }
                else if (promptYN("Would you like to quit? (y/n) ")) return 0;
            }
        }
    }
}
