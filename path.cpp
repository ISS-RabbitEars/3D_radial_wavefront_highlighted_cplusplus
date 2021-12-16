#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#define PI 3.141592653589793238462643383

int main()
{
	int N=210;
	double theta,phi,delta=2*PI/(N-1);
    ofstream file;
	
	theta=3*PI/2;
	phi=0;
    file.open("path.dat");
	for(int i=0;i<N;i++)
	{
		phi=i*delta;
		file<<"<"<<cos(theta)*cos(phi)<<", "<<sin(theta)*cos(phi)<<", "<<sin(phi)<<">"<<endl;
	}
    file.close();
    
	return 0;
}

#undef PI

