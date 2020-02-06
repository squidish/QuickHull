/*
 *  Facet.h
 *  ClassConvex2da
 *
 *  Created by Williams on 6/5/13.
 *
 */


#ifndef Facet_H
#define	Facet_H

#include<vector>
#include "Point.h"

class Facet {

public:

	Facet() {}
	virtual ~Facet() {}
	virtual Facet* clone() const=0;
	virtual void reversedir() =0;
	virtual bool isanti() =0;
	virtual void splitset(const vector<Point>& Pt, vector<Point>& lft, vector<Point>& rght)  const=0;
	virtual void splitleft()=0;
	virtual void splitright()=0;
	virtual void splitcent()=0;
	virtual void print()=0;
	virtual bool orient23(const Point &Pt)  const =0;
	virtual bool orient31(const Point &Pt)  const =0; 
	virtual bool orient34(const Point &Pt)  const =0;
	virtual bool pointcompare(const Point &Pt)  const =0;
	virtual int furthest(const vector<Point>& Pt_) =0; 

private:

};

#endif
