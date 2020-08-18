#include "conwayColorPicker.h"
#include <math.h>

using std::pair;
using std::map;

conwayColorPicker::conwayColorPicker() : iter(0)
{
}
/**
 *  The function below returns either a black or a white HSLA pixels.
 *  The logic for determining whether a pixel is black or white is abstracted
 *  away in nextColor() which is given to you.
 * 
 *  However, nextColor() requires the number of WHITE pixels (representing dead cells)
 *  so your job here to figure out how to do an 8 point search around a pixel, eg
 *      NW  | North| NE
 *      West| (x,y)| East
 *      SW  | South| SE 
 *  All pixels around an initial (x,y) pixel
 * 
 *  HINT: in this filler, you will have to exploit and update the PNGmap field accordingly.
 *          it will also be useful if you look up the documentation for a C++ Map
 * 
 */
HSLAPixel conwayColorPicker::operator()(int x, int y)
{
    //PNGmap::iterator stored;
    //vector<PNGmap::iterator> neighbours;
    HSLAPixel deadCell = HSLAPixel(0, 0, 1, 1);

    vector<pair<int, int>> n {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                        {0, 1}, {1, 1}, {1, 0}, {1, -1}};
    int dead_count = 0;
    for (pair<int, int> p: n) {
        pair<int, int> coord (x + p.first, y + p.second);

        auto lookup = prev.find(coord);
        if (lookup == prev.end()) continue;
        if (lookup->second == deadCell) {
            dead_count ++;
        }
    }
    HSLAPixel next = nextColor(dead_count);
    prev[{x, y}] = next;

    return next;
}


/**
 * GIVEN FUNCTION
 * 
 * for those interested, I did my best to mimic Conway's Game of Life in a colourpicker,
 * constrained to the 8 pixels and the propogating nature of a fill. See
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 * 
 * John Horton Conway, am active mathematician in the fields of number theory, 
 * combinatorial game theory and coding theory, died recently of COVID 19 complications.
*/
HSLAPixel conwayColorPicker::nextColor(int deadNeighbourCount)
{
    // extra variables for readability
    HSLAPixel alive = HSLAPixel(0, 0, 0, 1); // black means alive, true to the game
    HSLAPixel dead = HSLAPixel(0, 0, 1, 1);  // white means alive, true to the game

    HSLAPixel ret = dead;

    if (deadNeighbourCount == 2) 
    {
        return alive;
    }

    if (deadNeighbourCount > 2)
    { // possibility of death by population if more than 3 neighbours
        if (iter % deadNeighbourCount == 0)
        { // chance to be alive decreases with deadNeighbourCount
            ret = alive;
        }
        else
        {
            ret = dead;
        }
    }
    iter++;
    return ret;
}