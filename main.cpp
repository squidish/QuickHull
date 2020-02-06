#include <iostream>
#include<fstream>
#include<iomanip>
#include <vector>
#include "ConvexHull.h"

int main (int argc, char * const argv[]) {
    
	ofstream outfile;
	ifstream infile;
	string inputfilename;
	double pta, ptb; double ptc;
	Point p1;
	vector<Point> InputPoints;
	int npts; int nd;
	cout << "Number of dimensions?" << endl;
	cin >> nd;
	cout << "Generate how many points?" << endl;
	cin >> npts;
	//outfile.open("/Users/Williams/Software/C/Tasks/Task2/IO/input.txt");
	 outfile.open("HullInput.txt");
	 for (int i=0; i < npts;  i++) {
		if(nd ==2) {
		  	pta = ((double) rand() / (RAND_MAX))*10.0;	
			ptb = ((double) rand() / (RAND_MAX))*10.0;
			Point p1(pta,ptb);
			p1.output(&outfile,2);
			InputPoints.push_back(p1);
		} else {
			pta = ((double) rand() / (RAND_MAX))*10.0;	
			ptb = ((double) rand() / (RAND_MAX))*10.0;
			ptc = ((double) rand() / (RAND_MAX))*10.0;
			Point p1(pta,ptb,ptc);
			p1.output(&outfile,3);
			InputPoints.push_back(p1);
		}
	  }
	  outfile.close();
	 //construct hull
	 ConvexHull test_new(nd);
	 test_new.wrap(InputPoints);
	 //output file
	 //outfile.open("/Users/Williams/Software/C/Tasks/Task2/IO/output.txt");
	 outfile.open("HullOutput.txt");
     test_new.outputpoints(&outfile);
	 outfile.close();
     return 0;
}



