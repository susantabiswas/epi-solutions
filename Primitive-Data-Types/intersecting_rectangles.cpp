/*
    Problem:
        Given information about two axis parallel rectangles, find whether these two rectangles intersect or not.
        If they intersect, then give information about the shared area.

    Input Rectangle data:
        Coordinate of the lower left end, height and length of the rectangle.
    
    Output:
        (intersection?, lower end point of shared rectangular area, length, height)
        if intersection is there: 1 else 0
        Others: real nos. if intersection is there, else -1
*/

#include<iostream>
#include<vector>
using namespace std;

struct rectangle{
    // lower end point, length and height
    int x, y, length, height;
};

// for creating a rectangle object
rectangle createRectangle(int x, int y, int length, int height){
    rectangle rect;
    rect.x = x;
    rect.y = y;
    rect.length = length;
    rect.height = height;
    return rect;
}

// checks if the two rectangles intersect or not
// Output:
// (intersection, x, y, length, height)
vector<int> doesRectanglesIntersect(rectangle& r1, rectangle& r2){
    // see whether the two rectangles intersect
    // If two rectangles share area then some part of their length and width will be common
    bool intersect = (r1.x <= r2.x + r2.length) && (r2.x <= r1.x + r1.length) &&
                        (r1.y <= r2.y + r2.height) && (r2.y <= r1.y + r1.height);

    if (intersect){
        return vector<int>{
            1, max(r1.x, r2.x), max(r1.y, r2.y),
            min(r1.x + r1.length, r2.x + r2.length) - max(r1.x, r2.x),
            min(r1.y + r1.height, r2.y + r2.height) - max(r1.y, r2.y)};
    }

    return vector<int>{0, -1, -1, -1, -1};
}


int main(int argc, char const *argv[])
{
    rectangle r1 = createRectangle(76, 9, 12, 14);
    rectangle r2 = createRectangle(20, 1, 62, 60);

    vector<int> result = doesRectanglesIntersect(r1, r2);

    vector<int>::iterator it;
    for(it = result.begin(); it!=result.end(); it++)
        cout << *it << " ";

    return 0;
}
