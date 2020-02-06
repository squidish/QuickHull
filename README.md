# QuickHull


Implements the QuickHull algorithm to find the Convex Hull enclosing a set of points

## Convex Hull 

The convex hull of a set of points is defined as the smallest convex polygon, that encloses all of the points in the set. Convex means that the polygon has no corner that is bent inwards. There are several different algoithms to produce one given a set of points. This code uses the QuickHull algorithm see: https://en.wikipedia.org/wiki/Quickhull as it is relatively simple but scales well. 

## Depedencies and Make Instructions

g++ complier required, standard C++ libraries only

`cd QuickHull` 

`make`

## Input 

Points are input in the file HullInput.txt. 
