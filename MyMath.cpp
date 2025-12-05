#include <math.h>
#include <vector>
#include <iostream>

#include "MyMath.h"
#include "Random.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



MyMath::MyMath()
{
}

MyMath::~MyMath()
{
}

vector<double> MyMath::unifast(int n, double u)
{
	vector<double> util;
	double sumU = u;
	double nextSumU = 0.0;
	Random rand;
	for (int i = 0; i< n - 1; i++)
	{
		nextSumU = sumU * pow(rand.nextDouble(), ((double)1 / (double)(n - i)));

		//avoid utilization be 0.0, except sumU is 0.0
		if (sumU!=0.0 && nextSumU==sumU)
		{
			i--;
			continue;
		}

		util.push_back(sumU - nextSumU);
		sumU = nextSumU;
	}
	util.push_back(sumU);
	return util;
}

int MyMath::GCD(int a, int b)
{
	for (;;)
	{
		if (a == 0) return b;
		b %= a;
		if (b == 0) return a;
		a %= b;
	}
}

int MyMath::LCM(int a, int b)
{
	int temp = GCD(a, b);

	if ((a / temp * b) > 0)
		return a / temp*b;
	else
		return 0;
}

double MyMath::average(vector<double> nums)
{
	double sum = 0.0;
	for (int i = 0; i < nums.size(); i++)
		sum = sum + nums[i];

	return sum / nums.size();
}

vector<double> MyMath::decomposeRandom(int n, double  u, double baseRatio, bool ratio)
{
	Random rand;
	vector<double> util;
	double base = 0.0;
	if (ratio)
		base = (u / n)*baseRatio;
	else
		base = baseRatio;	 	

	double sumU = 0.0;
	vector<double> randomUs;
	int size = 0;

	while (util.size() != n)
	{
		randomUs = rand.nextDoubles(n);
		size = util.size();

		for (int i = 0; i<n-size && randomUs.size()>i; i++)
		{
			if (randomUs[i] < base)
			{
				randomUs.erase(randomUs.begin() + i);
				i--;
				continue;
			}

			sumU = sumU + randomUs[i];
			util.push_back(randomUs[i]);
		}
	}

	int count = 0;
	double difference = 0.0;
	while (sumU != u)
	{
		// try to adjust 100 times
		if (count == 100)
		{
			util.clear();
			break;
		}

		difference = fabs(sumU - u) / n;

		if (sumU > u)
		{
			sumU = 0.0;
			for (int i = 0; i < n; i++)
			{
				if (util[i] - difference >= base)
					util[i] = util[i] - difference;

				sumU = sumU + util[i];
			}
		}
		else
		{
			sumU = 0.0;
			for (int i = 0; i < n; i++)
			{
				if (util[i] + difference <= 1.0)
					util[i] = util[i] + difference;

				sumU = sumU + util[i];
			}
		}
		count++;
		cout << "            resourceSet decomposition " << count << " adjustor done" << endl;
	}

	cout << "            resourceSet decomposition done" << endl;

	return util;
}
/*
vector<double> MyMath::decomposeRandom(int n, double  u)
{
	Random rand;
	vector<double> util;

	int groupNumber = (int)ceil(u);
	int groupRange = (int)ceil(n / u);
	vector<int> groups = rand.nextInts(groupNumber, 1, groupRange);
	
	while (sumVecotr(groups) != n)
	{
		int sum = sumVecotr(groups);
		int difference = abs(sum - n);
		
		vector<int> adjustors = rand.nextInts(difference, 0, 1);
		if (sum > n)
		{
			for (int i = 0; i < groupNumber && i < difference; i++)
			{
				if (groups[i] > adjustors[i])
					groups[i] = groups[i] - adjustors[i];
			}				
		}
		if (sum < n)
		{
			for (int i = 0; i < groupNumber && i < difference; i++)
				groups[i] = groups[i] + adjustors[i];
		}
		
	}

	double base = 0.0;
	double sumU = 0.0;
	double randomU = 0.0;
	for (int i = 0; i < groupNumber; i++)
	{
		if (i == groupNumber - 1)
			base = u - groupNumber + 1;
		else
			base = 1.0;

		sumU = 0.0;
		for (int j = 0; j < groups[i]; j++)
		{
			if (j == groups[i] - 1)
			{
				randomU = base - sumU;
			}
			else
			{
				randomU = rand.nextDouble(0.0, base / groups[i]) * base;
				sumU = sumU + randomU;
			}
			util.push_back(randomU);
		}
	}

	return util;
}
*/

vector<int> MyMath::harmonicNumbers(int num, double harmonicity, int min, int max)
{
	vector<int> harmonicNums;

	double harmonicNum = 0.0;
	int i = 1;
	while (1)
	{
		harmonicNum = (num*i) / harmonicity;		
			
		if (harmonicNum > (max+0.5))
			break;
		if (harmonicNum > (min - 0.5) && int(harmonicNum / num) == i)
		{
			if (harmonicNum - floor(harmonicNum) < 0.0000001)
				harmonicNums.push_back((int)floor(harmonicNum));
			else if (ceil(harmonicNum) - harmonicNum < 0.0000001)
				harmonicNums.push_back((int)ceil(harmonicNum));
		}

		i++;
	}	

	return harmonicNums;
}



int MyMath::sumVecotr(vector<int> ints)
{
	int sum = 0;
	for (int i = 0; i < ints.size(); i++)
		sum = sum + ints[i];

	return sum;
}