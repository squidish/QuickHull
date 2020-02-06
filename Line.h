/*
 *  Line.h
 *  ClassConvex2da
 *
 *  Created by Williams on 5/17/13.
 *
 */

#ifndef Line_H
#define	Line_H

//#include "compare.h"
#include "Object.h"
#include "Facet.h"
#include<limits>

// Class to represent Points.
class Line : public Object, public Facet  {
	
public:
	
	//default
	Line() : ndim(1), AntiClock(0) {
		Ptr1 = new Point();
		Ptr2 = new Point();
		Ptr3 = NULL;
	} 
	
	Line( const Point& Pt1_, const Point& Pt2_) : ndim(1)  {
		  Ptr1 = new Point(Pt1_);
		  Ptr2 = new Point(Pt2_);
		  if (Pt1_ < Pt2_) {
			  AntiClock=1;
		  } else {
			  AntiClock=0;
		  }
		  Ptr3=NULL;
	} 
	
	// constructor can only take in members
	Line(const Line & L1) : ndim(1)  {
		if (L1.Ptr3 == NULL) {
		    Ptr1 = new Point(*(L1.Ptr1));
		    Ptr2 = new Point(*(L1.Ptr2));
		    Ptr3=NULL;
		} else {
			Ptr1 = new Point(*(L1.Ptr1));
		    Ptr2 = new Point(*(L1.Ptr2));
			Ptr3 = new Point(*(L1.Ptr3));
		}
		if (*Ptr1 < *Ptr2) {
			AntiClock=1;
		} else {
			AntiClock=0;
		}
	} 
	
	Line& operator=(const Line& L1)  {
		
		if(&L1 == this) {
			return *this;
		}
		if (L1.Ptr3 == NULL) {
		    Ptr1 = new Point(*(L1.Ptr1));
		    Ptr2 = new Point(*(L1.Ptr2));
		    Ptr3=NULL;
		} else {
			Ptr1 = new Point(*(L1.Ptr1));
		    Ptr2 = new Point(*(L1.Ptr2));
		    Ptr3 = new Point(*(L1.Ptr3));
		}
		AntiClock = L1.AntiClock;
	    return *this;

	}
		
	virtual ~Line() {
		delete Ptr1;
		delete Ptr2;
		if (Ptr3 != NULL) {
			delete Ptr3;
		}
	}
	
	virtual Facet* clone() const {
		return new Line(*this);	
	}
	
	virtual void reversedir() { 
	    swap(Ptr1,Ptr2);
		return;
	}
	
	virtual bool isanti() {
		return AntiClock;
	}
	
	virtual void splitleft() {
		
		if (Ptr3 != NULL) {
		  delete Ptr2;
		  Ptr2 = new Point(*Ptr3);
		  delete Ptr3;
		  Ptr3=NULL;
		}
		return;
	}
	
	virtual void splitright() {
		
		if (Ptr3 != NULL) {
			delete Ptr1;
			Ptr1 = new Point(*Ptr3);
			delete Ptr3;
			Ptr3=NULL;
		}
		return;
	}
	
	virtual void splitcent() {
		return;
	}
	
	virtual int dimension() {return 1; }
	
	double orientln(const Point &Pto) const {
		// going outside
		double d;
		//going forward
			d = Ptr1 -> plorient(*Ptr2,Pto);
		return d;
	} 
	
	virtual void splitset(const vector<Point>& Pt, vector<Point>& lft, vector<Point>& rght)  const {

		lft.clear();
		rght.clear();
		double det;
		//double eta = -0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		
		// define points
		for (int i=0; i < Pt.size(); i++) {
		       det = this -> orientln(Pt[i]);
		    if ( det > eta && Pt[i] != *Ptr1 && Pt[i] != *Ptr2  ) {
		       lft.push_back(Pt[i]);
		    } else if (Pt[i] != *Ptr1 && Pt[i] != *Ptr2  ) {
		       rght.push_back(Pt[i]);
		    }
		 }
		
		return;
	}
	
	int furthest(const vector<Point>& Pt_) {
		double furthest=0;
		double current;
	   int i=0;
		if (Ptr3==NULL) {
		   for (int k=0; k < Pt_.size(); k++) {
		    	//find the point
		    	current = Ptr1 -> pldist(*Ptr2,Pt_[k]);
			   if (current > furthest ) { 
			    	furthest = current;
			     	i = k;
			   }
		    } 			
		Ptr3 = new Point(Pt_[i]);
		} else { 
			cout << "Facet already allocated point" << endl;
			return -1;
		}
		return i;
    }
	
	
	virtual bool orient23(const Point &Pt)  const {
		
		double det;
		double eta = numeric_limits<double>::epsilon();
		det = Ptr1 -> plorient(*Ptr3,Pt);
		return det > eta;
	}

	virtual bool orient31(const Point &Pt)  const {
		
		double det;
		double eta = numeric_limits<double>::epsilon();
		det = Ptr3 -> plorient(*Ptr2,Pt);
		return det > eta;
	}
	
	virtual bool orient34(const Point &Pt)  const {
		
		return 0;
	}
	
	virtual bool pointcompare(const Point &Pt)  const {
		
			return (Pt == *Ptr1 || Pt == *Ptr2)   ;
	}
	
	virtual void print()
	{
		cout << "Line:" << endl;
		Ptr1 -> print();
		Ptr2 -> print();
		if (Ptr3 != NULL) {
			Ptr3 -> print();
		}
	}  
	
private:
	
	//alter to use map ptr to Pt1
	int ndim;
	Point* Ptr1;
	Point* Ptr2;
	Point* Ptr3;
	bool AntiClock;	
}; 

#endif

