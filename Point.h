/*
 *  Point.h
 *  ClassConvex2da
 *
 *  Created by Williams on 5/17/13.
 *
 */

#ifndef Point_H
#define	Point_H

#include <iostream>
#include <math.h>
#include<vector>
#include<iomanip>
#include<fstream>
#include "Object.h"
#include "ThreeDDet.h"
#include<limits>

using namespace std;

// Class to represent Points.
class Point : public Object {
	
public:
	// Constructor uses default arguments to allow calling with zero, one,
	// or two values.
	Point(double x = 0.0, double y = 0.0, double z=0.0) : xval(x), yval(y), zval(z)  {
	}
	
	//copy constructor
	Point(const Point &P_) : xval(P_.xval), yval(P_.yval), zval(P_.zval)    {
	}
	
	virtual int dimension() {return 0; }
	
	//equality
	bool operator ==(const Point &p) const {
		return zval == p.zval && yval == p.yval &&  xval == p.xval;
	}
	
	//inequality
	bool operator !=(const Point &p) const {
		return zval != p.zval || yval != p.yval ||  xval != p.xval;
	}
	
	//comparision
	bool operator <(const Point &p) const {
		return zval < p.zval || (zval == p.zval && yval < p.yval)  
		|| (zval == p.zval && yval < p.yval) || (zval == p.zval && yval == p.yval && xval < p.xval);
	}
	
	bool operator >(const Point &p) const {
		return zval > p.zval || (zval == p.zval && yval > p.yval)  
		|| (zval == p.zval && yval > p.yval) || (zval == p.zval && yval == p.yval && xval > p.xval);
	}
	
	friend bool zls (Point p1, Point p2);
	friend bool yls (Point p1, Point p2);
	friend bool xls (Point p1, Point p2);

	double dist(const Point &p) const {
		double xd = xval - p.xval;
		double yd = yval - p.yval;
		double zd = zval - p.zval;
		return sqrt(xd*xd + yd*yd + zd*zd);
	}
	
	double dot(const Point &p1) {
		return xval*p1.xval + yval*p1.yval + zval*p1.zval;
	}
	
	double abs() {
		return sqrt(xval*xval+yval*yval+zval*zval);
	}
	
	double pldist(const Point &Pt2, const Point &Pto) const {
		double v;
		double r;
		Point Pt1o;
		Pt1o = *this- Pto;
		Point Pt21;
		Pt21 = Pt2 - *this;
		Point Ptc;
		Ptc = Pt21.cross(Pt1o);
		v = Ptc.abs();
		r = Pt21.abs();
		return fabs(v)/r;
	} 
	
	double plorient(const Point &Pt2, const Point &Pt3) const {
		double det;
		det = xval*Pt2.yval+Pt2.xval*Pt3.yval + Pt3.xval*yval - Pt3.xval*Pt2.yval - Pt2.xval*yval - xval*Pt3.yval;
		return det;
	}
	
	bool allToLeft(const Point &Pt2, vector<Point>& VecPts  )  const {
		double eta = numeric_limits<double>::epsilon();
		if (this -> operator== (Pt2)) {
			//never part of hull
			return 0;
		} else {	
			double lst=0;
			int k=0;
			while ( k< VecPts.size() && lst >= eta  ) {
				lst = this -> plorient(Pt2,VecPts[k]);
				k++;
		    }
			return lst >= eta;		
	    }
	}
	
	double volorient(const Point &Pt1, const Point &Pt2, const Point &Pt3) const  {
		double one = 1.0;
		double det;
		double t1; double t2; double t3; double t4;
		t1 = xval*ThreeDDet(Pt1.yval,Pt2.yval,Pt3.yval,
							Pt1.zval,Pt2.zval,Pt3.zval,
							one,one,one); 
		t2 = (Pt1.xval)*ThreeDDet(yval,Pt2.yval,Pt3.yval,
								  zval,Pt2.zval,Pt3.zval,
								  one,one,one);
		t3 = (Pt2.xval)*ThreeDDet(yval,Pt1.yval,Pt3.yval,
								  zval,Pt1.zval,Pt3.zval,
								  one,one,one);
		t4 = (Pt3.xval)*ThreeDDet(yval,Pt1.yval,Pt2.yval,
								  zval,Pt1.zval,Pt2.zval,
								  one,one,one);
		det = t1-t2+t3-t4;
		return det;
	}
	
	double voldist(const Point &Pt2, const Point &Pt3,const Point &Pto ) const {
		double distence;
		Point Pt21;
		Pt21 = Pt2-*this;
		Point Pt31; 
		Pt31 = Pt3-*this;
		Point Norm = Pt31.cross(Pt21);
		double dNorm = Norm.abs();
		Point Pt01 =  Pto-*this;
		double dPt0 = Pt01.abs();
        distence = Pt01.dot(Norm)/dNorm; 
		return fabs(distence);
	}
	
	bool areclock(const Point &Pt2, const Point &Pt3) {
	    double det;
		//double eta = -0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		det = this -> plorient(Pt2,Pt3);
		return det > eta;
	}
	
	void reverse() {
		xval = -xval;
		yval = -yval;
		zval = -zval;
	}
		
	Point operator+(const Point &p1) const
	{
		return Point(xval + p1.xval, yval + p1.yval, zval + p1.zval);
	}
	
	Point operator-(const Point &p1) const
	{
		return Point(xval - p1.xval, yval - p1.yval,zval - p1.zval);
	}
	
	Point cross(const Point &p1) const 
	{
		double x =  yval*p1.zval-zval*p1.yval;
		double y =  xval*p1.zval-zval*p1.xval;
		double z =  xval*p1.yval-yval*p1.xval;
		return Point(x,-y,z);
	}
	
	void output(ofstream* file , const int& n) const
	{
        if (n == 2) {
			*file << setprecision(8) << xval <<  "," << yval << endl;
		} else {
			*file << setprecision(8) << xval <<  "," << yval << "," << zval << endl;
		}
	}
	
	void print() const
	{
		cout  << "(" << xval << "," << yval << "," << zval <<  ")" << endl;
	}
	
//protected:
private:
	
	double xval, yval, zval;
	
};

#endif

