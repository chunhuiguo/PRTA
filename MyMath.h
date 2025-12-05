#include <vector>

using namespace std;

#ifndef   MYMATH_H 
#define   MYMATH_H 


class MyMath
{
public:
	MyMath();
	~MyMath();

	vector<double> unifast(int n, double u);
	int GCD(int a, int b);
	int LCM(int a, int b);
	double average(vector<double> nums);
	vector<double> decomposeRandom(int n, double u, double baseRatio, bool ratio);

	vector<int> harmonicNumbers(int num, double harmonicity, int min, int max);

private:
	int sumVecotr(vector<int> ints);
};

#endif