/*
    Problem:
        Given information about two axis parallel rectangles, find whether these two rectangles intersect or not.
        If they intersect, then give information about the shared area.

    Input Rectangle data:
        Coordinate of the lower left end, height and length of the rectangle.

    Output:
        (interection?, lower end point of shared rectangular area, length, height)
        if intersection is there: 1 else 0
        Others: real nos. if intersection is there, else -1    
*/

#include<iostream>
using namespace std;

struct rectangle{
    // lower end point, length and height
    int x, y, length, height;
};

// for creating a rectangle object
rectangle* createRectangle(int x, int y, int length, int height){
    rectangle* rect = new rectangle;
    rect->x = x;
    rect->y = y;
    rect->length = length;
    rect->height = height;
    return rect;
}

// checks if the two rectangles intersect or not
bool doesRectanglesIntersect(rectangle r1, rectangle r2){
    
}

int main(int argc, char const *argv[])
{
    rectangle r1 = createRectangle();
    rectangle r2 = createRectangle();

    cout << doesRectanglesIntersect(r1, r2) << endl;
    return 0;
}
