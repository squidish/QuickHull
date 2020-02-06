/*
 *  TwoDimHull.h
 *  ClassConvex2da
 *
 *  Created by Williams on 5/18/13.
 *
 */

#include "ConvexHull.h"

bool  xls(Point p1, Point p2)  {
        return p1.xval < p2.xval || (p1.xval == p2.xval && p1.yval < p2.yval) 
        || (p1.xval == p2.xval && p1.yval == p2.yval && p1.zval < p2.zval);
}

bool  yls(Point p1, Point p2)  {
return p1.yval < p2.yval || (p1.yval == p2.yval && p1.zval < p2.zval) 
       || (p1.yval == p2.yval && p1.zval == p2.zval && p1.xval < p2.xval);
}

bool  zls(Point p1, Point p2)  {
                return p1.zval < p2.zval || (p1.zval == p2.zval && p1.xval < p2.xval) 
                || (p1.zval == p2.zval && p1.xval == p2.xval && p1.yval < p2.yval);
}
                


	void ConvexHull::wrap(vector<Point> Pt)  {	
		//check this is a 2d or 3d Hull
		if ( ndim > 3) {
	 		cout << ndim << "d Hull not supported." << endl;
			return;
			
		} else if  ( ndim < 2) {
		  	cout << ndim << "d Hull not supported. Don't be silly." << endl;
		} else {
			
			if (EnclosePoints == 1) {
				cout << "Hull already encloses points. Create new hull." << endl;
				return;
			}
		}
		Point Pmin;Point Pmax; Point Ppnt;
		Facet *Initial;
		Facet *RevInitial;
		if (ndim ==2) {
		  //vector
		   vector <Point>::iterator Min;
		   vector <Point>::iterator Max;
		   Min = min_element(Pt.begin(), Pt.end(),xls);
		   // iterator to vector element:
		   Pmin = *Min;
		   Pt.erase(Min);
		   // iterator to vector element:
		   Max = max_element(Pt.begin(), Pt.end(),xls);
		   Pmax = *Max;
		   Pt.erase(Max);
		   //starting points
		   cout << "Initial Starting Points" << endl;
		   cout << "Line" << endl;
		   Pmin.print();
		   Pmax.print();
		   Initial = new Line(Pmin,Pmax);
		   RevInitial = new Line(Pmax,Pmin);
		} else {
			vector <Point>::iterator Min;
			vector <Point>::iterator Max;
			int k;
			double xdist; double ydist; double zdist;
			Min = min_element(Pt.begin(), Pt.end(),xls);
			Max = max_element(Pt.begin(), Pt.end(),xls);
			xdist = Min -> dist(*Max);
			Pmin = *Min; Pmax = *Max;
			//ydist
			Min = min_element(Pt.begin(), Pt.end(),yls);
			Max = max_element(Pt.begin(), Pt.end(),yls);
			ydist = Min -> dist(*Max);
			if (ydist >= xdist )  {
			  Pmin = *Min; Pmax = *Max;
			}
			//cout << "ydist" << ydist << endl;
			Min = min_element(Pt.begin(), Pt.end(),zls);
			Max = max_element(Pt.begin(), Pt.end(),zls);
			zdist = Min -> dist(*Max);
			if (zdist >= xdist && zdist >= ydist)  {
				Pmin = *Min; Pmax = *Max;
			}
			//cout << "zdist" << zdist << endl;
			Line Base(Pmin,Pmax);
			//Find the furthest point from initial line
			k = Base.furthest(Pt);
			Ppnt = Pt[k];
			cout << "Initial Starting Points" << endl;
			cout << "Triangle" << endl;
			Pmin.print();
			Pmax.print();
			Ppnt.print();
			if ( Pmin.areclock(Pmax,Ppnt)) { 
			     Initial = new Triangle(Pmin,Pmax,Ppnt);
				 RevInitial = new Triangle(Ppnt,Pmax,Pmin);
			} else {
				Initial = new Triangle(Ppnt,Pmax,Pmin);
				RevInitial = new Triangle(Pmin,Pmax,Ppnt);
			}
		}
		vector<Point> lft;
		vector<Point> rght;
		Initial -> splitset(Pt,lft,rght);
		vertex.push_back(Pmax);
		Enclose(lft,Initial);
		vertex.push_back(Pmin);
		Enclose(rght,RevInitial);
	    if (ndim==3) {
		  vertex.push_back(Ppnt);
		}
		delete Initial;
		delete RevInitial;
		cout << "Points Enclosed Successfully" << endl;
		EnclosePoints =1;
		return;
	}
	
	void ConvexHull::Enclose(vector<Point>& Pt,Facet *Fac) {

		Point Pta;
		int NotIn;
		vector<Point> lft;
		vector<Point> rght;
		vector<Point> opp;
		lft.clear();
		rght.clear();
		opp.clear();
		NotIn = Fac -> furthest(Pt);
		bool det;
		bool det2;
		bool det3;
		//double eta = 0.00000000001;
		double eta = numeric_limits<double>::epsilon();
		
		for (int i=0; i < Pt.size(); i++) {
			det = Fac -> orient23(Pt[i]);
			det2 = Fac -> orient31(Pt[i]);
			det3 = Fac -> orient34(Pt[i]);
			if ( det && ! Fac -> pointcompare(Pt[i]) ) {
				lft.push_back(Pt[i]);
			} else if (det2 && ! Fac -> pointcompare(Pt[i]) )  {
				rght.push_back(Pt[i]);
			} else if (det3 && ! Fac -> pointcompare(Pt[i])) {
				opp.push_back(Pt[i]);
			}
		}
				
		Facet *Next = Fac -> clone();
		Facet *RevNext = Fac -> clone();
		Facet *OppNext = Fac -> clone();

		if (lft.size() > 0 ) {
		   Next -> splitleft();
		   Enclose(lft,Next);
		}
		vertex.push_back(Pt[NotIn]);
		if (rght.size() > 0 ) {
		    RevNext -> splitright();
		   Enclose(rght,RevNext);
		}
		if (opp.size() > 0 ) {
			OppNext -> splitcent();
			Enclose(opp,OppNext);
	    }
		delete Next;
		delete RevNext;
		delete OppNext;	
		return;
	}	
	
	void ConvexHull::PrintPoints() const {
		for (int i=0; i < vertex.size(); i++ ) {
		    vertex[i].print();
		}	
	}
	
	void ConvexHull::outputpoints(ofstream* file) const {
		for (int i=0; i < vertex.size(); i++ ) {
		    vertex[i].output(file,ndim);
		}
	}
	



