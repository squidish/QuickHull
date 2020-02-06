/*
 *  compare.h
 *  ClassConvex2da
 *
 *  Created by Williams on 5/31/13.
 *
 */

#ifndef compare_H
#define	compare_H

#include "Point.h"

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
		
#endif
