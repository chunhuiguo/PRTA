#include <iostream>
#include <time.h>
#include <windows.h>

#include "Random.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



Random::Random()
{		
}

Random::~Random()
{
}

int Random::nextInt(int min, int max)
{
	mySRand();

	return rand() % (max - min + 1) + min;
}

vector<int> Random::nextInts(int number, int min, int max)
{
	mySRand();

	vector<int> ints;
	int num = 0;
	for (int i = 0; i < number; i++)
	{
		num = rand() % (max - min + 1) + min;
		ints.push_back(num);

		//ints.push_back(rand() % (max - min + 1) + min);
	}	

	return ints;
}

double Random::nextDouble()
{
	mySRand();

	return rand() / (double)(RAND_MAX);
}

vector<double> Random::nextDoubles(int number)
{
	mySRand();

	vector<double> doubles;
	double num = 0.0;
	for (int i = 0; i < number; i++)
	{
		num = rand() / (double)(RAND_MAX);
		doubles.push_back(num);

		//doubles.push_back(nextDouble(min, max));
	}		

	return doubles;
}

double Random::nextDouble(double min, double max)
{
	mySRand();

	double num = 0.0;
	while (1)
	{
		num = (rand() / (double)(RAND_MAX)) * (max - min) + min;

		if (num != min)
			break;
	}

	return num;
}

vector<double> Random::nextDoubles(int number, double min, double max)
{
	mySRand();

	vector<double> doubles;
	double num = 0.0;
	for (int i = 0; i < number; i++)
	{
		num = (rand() / (double)(RAND_MAX)) * (max - min) + min;

		if (num == min)
		{
			i--;
			continue;
		}

		doubles.push_back(num);

		//doubles.push_back(nextDouble(min, max));
	}	

	return doubles;
}


void Random::mySRand()
{
	time_t timer1, timer2;

	Sleep(1500);
	timer1 = time(NULL);
	Sleep(1500);
	timer2 = time(NULL);

	srand((unsigned)timer1 * timer2);
}