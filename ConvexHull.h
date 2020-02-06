/*
 *  TwoDimHull.h
 *  ClassConvex2da
 *
 *  Created by Williams on 5/18/13.
 *
 */

#ifndef ConvexHull_H
#define	ConvexHull_H

#include "Line.h"
//#include "compare.h"
#include <vector>
//#include "Facet.h"
#include "Triangle.h"
#include <limits>

class ConvexHull {
	
	public:
	
	ConvexHull() : EnclosePoints(0) {}
	
	ConvexHull(const int &ndim_) : EnclosePoints(0), ndim(ndim_) {}

	void wrap(vector<Point> Pt);

	void Enclose(vector<Point>& Pt,Facet *Fac); 

	void PrintPoints() const;
	
	void outputpoints(ofstream* file) const;
	
    private:
	
	int ndim;
	bool EnclosePoints;
	vector<Point> vertex;
};


#endif

