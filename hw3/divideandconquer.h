#ifndef DIVIDEANDCONQUER_H_INCLUDED
#define DIVIDEANDCONQUER_H_INCLUDED

#include <vector>
#include "convexhull.h"

int dc_compare_by_x(const void *vp1, const void *vp2);

std::vector<Point>* dc(std::vector<Point> &arr);

void show_vect(std::vector<Point> &arr);
#endif // DIVIDEANDCONQUER_H_INCLUDED
