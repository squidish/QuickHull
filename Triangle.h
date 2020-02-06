/*
 *  Triangle.h
 *  ClassConvex2da
 *
 *  Created by Williams on 6/6/13.
 *
 */

#ifndef Triangle_H
#define	Triangle_H

#include "Facet.h"
#include<algorithm>
#include "Object.h"


// Class to represent Points.
class Triangle : public Object, public Facet  {
	
public:
	
	//default
	Triangle() : ndim(2)  {
		Ptr1 = new Point();
		Ptr2 = new Point();
		Ptr3 = new Point();
		Ptr4 =NULL;
		
	} 
	
	Triangle( const Point& Pt1_, const Point& Pt2_,const Point& Pt3_) : ndim(2)  {
		Ptr1 = new Point(Pt1_);
		Ptr2 = new Point(Pt2_);
		Ptr3 = new Point(Pt3_);
		if (Ptr1 -> plorient(*Ptr2,*Ptr3) > numeric_limits<double>::epsilon()) {
		    Anticlock =1;
		} else {
			Anticlock =0;
		}
		Ptr4 =NULL;
	} 
	
	Triangle(const Triangle& T1) : ndim(1)  {
		if (T1.Ptr4 == NULL) {
		    Ptr1 = new Point(*(T1.Ptr1));
		    Ptr2 = new Point(*(T1.Ptr2));
		    Ptr3 = new Point(*(T1.Ptr3));
			Ptr4 =NULL;
		} else {
			Ptr1 = new Point(*(T1.Ptr1));
		    Ptr2 = new Point(*(T1.Ptr2));
			Ptr3 = new Point(*(T1.Ptr3));
			Ptr4 = new Point(*(T1.Ptr4));
		}
		if (Ptr1 -> plorient(*Ptr2,*Ptr3) > numeric_limits<double>::epsilon()) {
			Anticlock =1;
		} else {
			Anticlock =0;
		}
	} 
	
	Triangle& operator=(const Triangle& T1) {
		
		if(&T1 == this) {
			return *this;
		}
		if (T1.Ptr3 == NULL) {
		    Ptr1 = new Point(*(T1.Ptr1));
		    Ptr2 = new Point(*(T1.Ptr2));
			Ptr3 = new Point(*(T1.Ptr3));
			Ptr4 =NULL;
		    
		} else {
			Ptr1 = new Point(*(T1.Ptr1));
		    Ptr2 = new Point(*(T1.Ptr2));
		    Ptr3 = new Point(*(T1.Ptr3));
			Ptr4 = new Point(*(T1.Ptr3));
		}
		ndim= T1.ndim;
		Anticlock = T1.Anticlock;
		
	    return *this;
	}
	
	
	virtual ~Triangle() {
		delete Ptr1;
		delete Ptr2;
		delete Ptr3;
		if (Ptr4 != NULL) {
			delete Ptr4;
		}
	}
	
	virtual Facet* clone() const {
		return new Triangle(*this);	
	}
	
	virtual int dimension() {return 2;}
	
	virtual void reversedir() { 
	    swap(Ptr2,Ptr3);
		return;
	}
	
	virtual bool isanti() {
		return Anticlock;
	}
	
	double orienttri(const Point &Pto) const {
		// going outside
		double d;
		//going forward
		d = Ptr1 -> volorient(*Ptr2,*Ptr3,Pto);
		return d;
	} 
	
	
	virtual void splitset(const vector<Point>& Pt, vector<Point>& lft, vector<Point>& rght) const {
	
		lft.clear();
		rght.clear();
		double det;
		//double eta = -0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		
		// define points
		for (int i=0; i < Pt.size(); i++) {
			det = this -> orienttri(Pt[i]);
		    if ( det > eta && Pt[i] != *Ptr1 && Pt[i] != *Ptr2 && Pt[i] != *Ptr3 ) {
				lft.push_back(Pt[i]);
		    } else if (Pt[i] != *Ptr1 && Pt[i] != *Ptr2  && Pt[i] != *Ptr3  ) {
				rght.push_back(Pt[i]);
		    }
		}
		return;
	}
	
	int furthest(const vector<Point>& Pt_) {
		double furthest=0;
		double current;
		int i=0;
		if (Ptr4==NULL) {
			for (int k=0; k < Pt_.size(); k++) {
		    	//find the point
		    	current = Ptr1 -> voldist(*Ptr2,*Ptr3,Pt_[k]);
				if (current > furthest ) { 
			    	furthest = current;
			     	i = k;
				}
				//cout << "furthest   "   << i << " " << furthest << endl;
		    } 
			Ptr4 = new Point(Pt_[i]);
		} else { 
			cout << "Facet already allocated point" << endl;
		   return -1;
		}
		return i;
    }
	
	
	virtual bool orient23(const Point &Pt)  const {
		
		double det;
		//double eta = 0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		det = Ptr1 -> volorient(*Ptr2,*Ptr4,Pt);
		return det > eta;
	}
	
	virtual bool orient31(const Point &Pt)  const {
		
		double det;
		//double eta = 0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		det = Ptr2 -> volorient(*Ptr3,*Ptr4,Pt);
		return det > eta;
	}
	
	virtual bool orient34(const Point &Pt)  const {
		
		double det;
		//double eta = 0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		det = Ptr3 -> volorient(*Ptr1,*Ptr4,Pt);
		return det > eta;
	}
	
	virtual void splitleft() {
		
		if (Ptr4 != NULL) {
			delete Ptr3;
			Ptr3 = new Point(*Ptr4);
			delete Ptr4;
			Ptr4=NULL;
		}
		return;
	}
	
	virtual void splitright() {
		if (Ptr4 != NULL) {
	        swap(Ptr1,Ptr2);
			swap(Ptr2,Ptr3);
			delete Ptr3;
			Ptr3 = new Point(*Ptr4);
			delete Ptr4;
			Ptr4=NULL;
		}
		return;
	}
	
	virtual void splitcent() {
		if (Ptr4 != NULL) {
			swap(Ptr1,Ptr3);
			swap(Ptr2,Ptr3);
			delete Ptr3;
			Ptr3 = new Point(*Ptr4);
			delete Ptr4;
			Ptr4=NULL;
		}
		return;
	}
	
	
	virtual bool pointcompare(const Point &Pt)  const {
		
		return (Pt == *Ptr1 || Pt == *Ptr2 || Pt == *Ptr3)   ;
	}
	
	// Print the Point on the stream. 
	virtual void print()
	{
		cout << "Triangle:" << endl;
		Ptr1 -> print();
		Ptr2 -> print();
		Ptr3 -> print();
		if (Ptr4 != NULL) {
			Ptr4 -> print();
		}
	}  
	
private:
	
	int ndim;
	Point* Ptr1;
	Point* Ptr2;
	Point* Ptr3;
	Point* Ptr4;
	bool Anticlock;
};
#endif
