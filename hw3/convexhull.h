//Source:http://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
#ifndef CONVEXHULL_H_INCLUDED
#define CONVEXHULL_H_INCLUDED

// A C++ program to find convex hull of a set of points. Refer
// http://www.geeksforgeeks.org/orientation-3-ordered-points/
// for explanation of orientation()
#include <iostream>
//#include <stack>
#include <vector> //��vector���Nstack
#include <stdlib.h> //for qsort

struct Point
{
    int x, y;
};

//�ϥ�vector�N���쥻��stack
Point nextToTop(std::vector<Point> &S);

// A utility function to swap two points
void swap(Point &p1, Point &p2);

// A utility function to return square of distance
// between p1 and p2
int distSq(Point p1, Point p2);
int orientation(Point p, Point q, Point r);
int compare(const void *vp1, const void *vp2);

//�|��^ConvexHull�W���I
std::vector<Point>* convexHull(Point points[], int n);


#endif // CONVEXHULL_H_INCLUDED
