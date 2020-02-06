/*
 *  Object.h
 *  ClassConvex2da
 *
 *  Created by Williams on 6/5/13.
 *
 */

#ifndef Object_H
#define	Object_H


class Object {
	
public:
	
	Object() {}
	virtual ~Object() {}
	virtual int dimension()=0;
	
private:
	
};

#endif