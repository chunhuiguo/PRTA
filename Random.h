#include <vector>

using namespace std;

#ifndef   RANDOM_H 
#define   RANDOM_H 


class Random
{
public:
	Random();
	~Random();

	int nextInt(int min, int max); // [min, max]
	vector<int> nextInts(int number, int min, int max); // each satisfy [min, max]
	double nextDouble(); // (0, 1]
	vector<double> nextDoubles(int number); // each satisfy (0, 1]
	double nextDouble(double min, double max); // (min, max]
	vector<double> nextDoubles(int number, double min, double max); // each satisfy (min, max]

private:
	void mySRand();
};

#endif