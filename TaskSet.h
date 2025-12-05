#include <vector>

#include "Task.h"

using namespace std;

#ifndef   TASKSET_H 
#define   TASKSET_H 


class ResourceSet;

class TaskSet
{
public:
	TaskSet();
	virtual ~TaskSet();	
	
	TaskSet(vector<Task*> tasks);
	TaskSet(int taskNumber, int minPeriod, int maxPeriod, ResourceSet * resourceSet);	
	TaskSet(int taskNumber, int maxPeriod, double harmonicity, ResourceSet * resourceSet);
	TaskSet(int taskNumber, int minPeriod, int maxPeriod, vector<double> utilizations, double harmonicity, ResourceSet * resourceSet);

	void markTaskAssigned(Task * task);
	void clearAssignedTasks();	

	int getTaskNumber();	
	int getMinPeriod();
	double getMaxUtilization();
	vector<Task*> getTasks();
	double getUtilization();
	vector<int> getUnassignedTaskIndex();	


private:	
	bool generateTaskSet(int taskNumber, int minPeriod, int maxPeriod, ResourceSet * resourceSet); 	
	bool generateTaskSet(int taskNumber, int maxPeriod, double harmonicity, ResourceSet * resourceSet); 
	bool generateTaskSet(int taskNumber, int minPeriod, int maxPeriod, vector<double> utilizations, double harmonicity, ResourceSet * resourceSet);

	double calculateMaxTaskUtilizationWithUtilizationBound(int minTaskPeriod, ResourceSet * resourceSet);

	void sort(vector<double>* utilizations, vector<int>* periods);

	void clear();	


private:
	vector<Task*> tasks;
	double utilization;
	int taskNumber;

	int minPeriod;
	int maxPeriod;
	double minUtilization;
	double maxUtilization;
	vector<int> unassignedTaskIndex;
	vector<int> assignedTaskIndex;
};

#endif 