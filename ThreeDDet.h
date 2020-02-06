/*
 *  ThreeDDet.h
 *  ClassConvex2da
 *
 *  Created by Williams on 6/6/13.
 *
 */

#ifndef ThreeDDet_H
#define ThreeDDet_H

inline double ThreeDDet(const double &a1,const double &a2,const double &a3,
				 const double &b1,const double &b2,const double &b3,
				 const double &c1,const double &c2,const double &c3) {
	double det = a1*b2*c3+a2*b3*c1+a3*b1*c2-a3*b2*c1-a2*b1*c3-a1*b3*c2;
	return det;
}




#endif
