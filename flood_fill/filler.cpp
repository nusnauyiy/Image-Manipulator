/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. 
 *
 */
#include "filler.h"
#include <vector>
#include <algorithm>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

/**
 * STRIPE is given as an example
*/
animation filler::fillStripeDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{
    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Stack>(img, x, y, scp, tolerance, frameFreq);
}
animation filler::fillStripeBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int stripeSpacing, double tolerance, int frameFreq)
{

    stripeColorPicker scp = stripeColorPicker(fillColor, stripeSpacing);
    return fill<Queue>(img, x, y, scp, tolerance, frameFreq);
}



/**
 * @todo your turn!
 */

animation filler::fillBorderDFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, *(img.getPixel(x,y)));
    return fill<Stack>(img, x, y, bcp, tolerance, frameFreq);
}

/* Given implementation of a DFS conwa fill. */
animation filler::fillConwayDFS(PNG& img, int x, int y, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Stack>(img, x, y, ccp, tolerance, frameFreq);
}
animation filler::fillGridBFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Queue>(img, x, y, gcp, tolerance, frameFreq);
}
animation filler::fillGridDFS(PNG& img, int x, int y, HSLAPixel fillColor,
                                int spacing, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     */
    gridColorPicker gcp = gridColorPicker(fillColor, spacing);
    return fill<Stack>(img, x, y, gcp, tolerance, frameFreq);
}

animation filler::fillBorderBFS(PNG& img, int x, int y,
                                    HSLAPixel borderColor, double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! You should replace the following line with a
     */
    borderColorPicker bcp = borderColorPicker(borderColor, img, tolerance, *(img.getPixel(x,y)));
    return fill<Queue>(img, x, y, bcp, tolerance, frameFreq);
}

/* Given implementation of a BFS conwa fill. */
animation filler::fillConwayBFS(PNG& img, int x, int y, double tolerance, int frameFreq)
{    /**
     * @todo Your code here! You should replace the following line with a
     */
    conwayColorPicker ccp = conwayColorPicker();
    return fill<Queue>(img, x, y, ccp, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill(PNG& img, int x, int y, colorPicker& fillColor,
                       double tolerance, int frameFreq)
{
    /**
     * @todo Your code here! 
     * NOTE: this'll be a long one!
     */
    HSLAPixel center = * img.getPixel(x,y);
    //img.getPixel(x,y)->l = 0;

    OrderingStructure<vector<int>> t;
    animation a = animation();
    //a.addFrame(img);
    //img.getPixel(x,y)->l = 1;
    //a.addFrame(img);
    //return a;
    vector<vector<bool>> processed;
    for (unsigned int i = 0; i < img.width(); i++) {
        vector<bool> temp;
        for (unsigned int j = 0; j < img.height(); j++) {
            temp.push_back(false);
        }
        processed.push_back(temp);
    }


    const vector<vector<int>> neighbors = {{0, 1},{1, 0}, {0, -1}, {-1, 0}};

    vector<int> p = {x, y};
    t.add(p);
    
    int processed_count  = 1;
    processed[x][y] = true;
            if (processed_count % frameFreq == 0) {
                    a.addFrame(img);
                    //cout << "added a frame" << endl;
                }

    while (!t.isEmpty()) {
        
        vector<int> top = t.remove();
        /*
        if (processed[top[0]][top[1]]) {
                        //cout << "is processed" << endl;
                        continue;
                    }*/

        HSLAPixel pxl = fillColor(top[0], top[1]);
        HSLAPixel * pxl_p = img.getPixel(top[0], top[1]);
        pxl_p->h = pxl.h;
        pxl_p->s = pxl.s;
        pxl_p->l = pxl.l;
        pxl_p->a = pxl.a;
        //cout << "added a frame" << endl;
        //a.addFrame(img);
        
                    

        //check each neighbor...
        for (vector<int> n: neighbors) {
            //coordinate of neighbor
            int x_coord = top[0] + n[0];
            int y_coord = top[1] + n[1];

            //check is neighbor is in range of image
            if (x_coord < 0 || (unsigned int) x_coord >= img.width() ||
                y_coord < 0 || (unsigned int) y_coord >= img.height()) {
                    //cout << "not in range" << endl;
                    continue;   //skip this "neighbor"
                }
            //check if neighbor is outside tolerance
            HSLAPixel * px = img.getPixel(x_coord, y_coord);
            if (px->dist(center) > tolerance) {
                //cout << "not in border" << endl;
                continue;   //skip this neighbor
            }
            //check if the neighbor is processed
            if (processed[x_coord][y_coord]) continue;

            //if we're still here...
            //cout << x_coord << " " << y_coord << endl;
            vector<int> neighbor = {x_coord, y_coord};
            t.add(neighbor);
            //img.getPixel()
            //fillColor(x_coord, y_coord);
            processed_count ++;
            processed[x_coord][y_coord] = true;
            if (processed_count % frameFreq == 0) {
                    a.addFrame(img);
                    //cout << "added a frame" << endl;
                }

            
            //cout << processed.size() << endl;
        }
        
    }
    a.addFrame(img);
    return a;
} 

    /** FOR ABOVE fill
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a QUEUE, for a depth-first-search, that
     * structure is a STACK.
     * To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure. 
     *
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are 
     *              within (or equal to) tolerance distance from the center, 
     *              to the ordering structure.
     *        2.    use the colorPicker to set the new color of the point.
     *        3.    mark the point as processed.
     *        4.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        For this assignment, each pixel p has 4 neighbors, consisting of 
     *        the 4 pixels who share an edge or corner with p. (We leave it to
     *        you to describe those 4 pixel locations, relative to the location
     *        of p.)
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! 
     *
     *        The order you should put
     *        neighboring pixels **ONTO** the ordering structure (queue or stack) 
     *        is as follows: 
     *          >>> South (y + 1), East (x + 1), North (y - 1), West (x -1) <<<
     *
     *        If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.  
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and 
     *        it will be the one we test against.
     */