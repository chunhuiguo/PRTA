#include<vector>

#include "Task.h"

using namespace std;

#ifndef   RESOURCE_H 
#define   RESOURCE_H 


class Resource
{
public:
	Resource();
	virtual ~Resource();
	Resource(int period, double allocationTime, int index);

	void assign(Task* task);
	void assign(Task* task, double harmonicity);
	bool checkHarmonicUtilizationBound(Task* task, double harmonicity);
	bool checkUtilizationBound(Task* task);
	double calculateUtilizationBoundDifference(Task* task);
	void markFull();
	void clearAssignedTasks();

	double calculateUtilizationRate();	

	int getPeriod();
	double getCapacity();
	double getAllocationTime();
	int getIndex();
	vector<Task*> getAssignedTasks();
	int getAssignedTaskNumber();
	vector<int> getAssignedTaskHarmonicPeriods();

private:
	double calculateUtilizationBound(Task* task);
	//double calculateHarmonicUtilization(Task* task);
	//vector<double> calculateHarmonicity(Task* task);
	//double DCT(Task * task);

private:
	int period;
	double allocationTime;
	double capacity;
	int index;
	bool full;

	vector<Task*> assignedTasks;
	int assignedTaskNumber;
	int assignedMinTaskPeriod;
	double assignedTaskUtilization;
	double assignedTaskHarmonicUtilization;
	vector<int> assignedTaskHarmonicPeriods;
};

#endif