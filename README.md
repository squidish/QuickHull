# QuickHull


Implements the QuickHull algorithm to find the Convex Hull enclosing a set of points

## Convex Hull 

The convex hull of a set of points is defined as the smallest convex polygon, that encloses all of the points in the set. Convex means that the polygon has no corner that is bent inwards. There are several different algoithms to produce one given a set of points. This code uses the QuickHull algorithm see: https://en.wikipedia.org/wiki/Quickhull as it is relatively simple but scales well. 

## Depedencies and Make Instructions

g++ complier required, standard C++ libraries only

`cd QuickHull` 
`make`

Then run the file ./QuickHull.exe

## Input 

Points are input in the file HullInput.txt. They can be 2D in the format 

x y

or 3D in the file format

x y z

You do not have to use all the points or all the dimensions input. Number of dimensions and number of points used can be specified at the prompts 'Number of dimensions?' and 'Generate how many points? respectively.

## Output

In 2D mode the output is a set of lines. This is a set of points in order

l1a  
l1b  
l2a 
l2b  
...

where lxa is the (x,y) coordinates of the origin of the line and lxb is the (x,y) coordinates of its end point. 

In 3D mode the output is a set of facets. This is a set of points in order 

f1a   
f1b   
f1c   
f2a   
f2b   
f2c   


