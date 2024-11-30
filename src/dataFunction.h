#ifndef DATA_H
#define DATA_H

#define INFINITE 99999999

#include <math.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Data {
   public:
	Data(int, char *);
	~Data();

	void readData();
	void printMatrixDist();
	inline int getDimension() { return dimension; };
	inline double getDistance(int i, int j) { return distMatrix[i][j]; };
	inline vector<vector<double>> getMatrixCost() { return distMatrix; }
	inline double getXCoord(int i) { return xCoord[i]; }
	inline double getYCoord(int i) { return yCoord[i]; }
	inline bool getExplicitCoord() { return explicitCoord; };

	string getInstanceName();  // Get instance's name

   private:
	string instaceName;
	int nbOfPar;

	int dimension;

	vector<vector<double>> distMatrix;
	double *xCoord, *yCoord;

	// Computing Distances
	static double CalcDistEuc(double *, double *, int, int);
	static double CalcDistAtt(double *, double *, int, int);
	static double CalcDistGeo(double *, double *, int, int);
	static void CalcLatLong(double *, double *, int, double *, double *);

	bool explicitCoord;
};

#endif
