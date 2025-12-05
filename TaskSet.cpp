#include <iostream>
#include <math.h>

#include "TaskSet.h"
#include "MyMath.h"
#include "Random.h"
#include "ResourceSet.h"

using namespace std;



TaskSet::TaskSet()
{
	taskNumber = 0;

	utilization = 0.0;
	minPeriod = 2147483647;
	maxPeriod = 0;
	minUtilization = 1.0;
	maxUtilization = 0.0;
}

TaskSet::~TaskSet()
{
	clear();
}


TaskSet::TaskSet(vector<Task*> tasks)
{
	this->tasks = tasks;
	taskNumber = tasks.size();
	minPeriod = 2147483647;
	maxPeriod = 0;
	minUtilization = 1.0;
	maxUtilization = 0.0;

	Task* task = NULL;
	for (int i = 0; i < taskNumber; i++)
	{
		unassignedTaskIndex.push_back(i);

		task = tasks[i];
		utilization = utilization + task->getUtilization();

		if (task->getPeriod() < minPeriod)
			minPeriod = task->getPeriod();
		if (task->getPeriod() > maxPeriod)
			maxPeriod = task->getPeriod();
		if (task->getUtilization() < minUtilization)
			minUtilization = task->getUtilization();
		if (task->getUtilization() > maxUtilization)
			maxUtilization = task->getUtilization();
	}
}

TaskSet::TaskSet(int taskNumber, int minPeriod, int maxPeriod, ResourceSet * resourceSet)
{
	this->taskNumber = 0;
	this->utilization = 0.0;
	this->minPeriod = maxPeriod;
	this->maxPeriod = 0;
	this->minUtilization = 1.0;
	this->maxUtilization = 0.0;
	
	if (generateTaskSet(taskNumber, minPeriod, maxPeriod, resourceSet))
	{
		this->taskNumber = taskNumber;

		Task * task = NULL;
		for (int i = 0; i < taskNumber; i++)
		{
			task = tasks[i];
			utilization = utilization + task->getUtilization();

			if (task->getPeriod() < this->minPeriod)
				this->minPeriod = task->getPeriod();
			if (task->getPeriod() > this->maxPeriod)
				this->maxPeriod = task->getPeriod();
			if (task->getUtilization() < this->minUtilization)
				this->minUtilization = task->getUtilization();
			if (task->getUtilization() > this->maxUtilization)
				this->maxUtilization = task->getUtilization();
		}
	}
}



TaskSet::TaskSet(int taskNumber, int maxPeriod, double harmonicity, ResourceSet * resourceSet)
{
	this->taskNumber = 0;
	this->utilization = 0.0;
	this->minPeriod = maxPeriod;
	this->maxPeriod = 0;
	this->minUtilization = 1.0;
	this->maxUtilization = 0.0;

	if (generateTaskSet(taskNumber, maxPeriod, harmonicity, resourceSet))
	{
		this->taskNumber = taskNumber;

		Task * task = NULL;
		for (int i = 0; i < taskNumber; i++)
		{
			task = tasks[i];
			utilization = utilization + task->getUtilization();

			if (task->getPeriod() < this->minPeriod)
				this->minPeriod = task->getPeriod();
			if (task->getPeriod() > this->maxPeriod)
				this->maxPeriod = task->getPeriod();
			if (task->getUtilization() < this->minUtilization)
				this->minUtilization = task->getUtilization();
			if (task->getUtilization() > this->maxUtilization)
				this->maxUtilization = task->getUtilization();
		}
	}
}

TaskSet::TaskSet(int taskNumber, int minPeriod, int maxPeriod, vector<double> utilizations, double harmonicity, ResourceSet * resourceSet)
{
	this->taskNumber = 0;
	this->utilization = 0.0;
	this->minPeriod = 2147483647;
	this->maxPeriod = 0;
	this->minUtilization = 1.0;
	this->maxUtilization = 0.0;

	if (generateTaskSet(taskNumber, minPeriod, maxPeriod, utilizations, harmonicity, resourceSet))
	{
		this->taskNumber = taskNumber;

		Task * task = NULL;
		for (int i = 0; i < taskNumber; i++)
		{
			task = tasks[i];
			utilization = utilization + task->getUtilization();

			if (task->getPeriod() < this->minPeriod)
				this->minPeriod = task->getPeriod();
			if (task->getPeriod() > this->maxPeriod)
				this->maxPeriod = task->getPeriod();
			if (task->getUtilization() < this->minUtilization)
				this->minUtilization = task->getUtilization();
			if (task->getUtilization() > this->maxUtilization)
				this->maxUtilization = task->getUtilization();
		}
	}
}

void TaskSet::markTaskAssigned(Task* task)
{
	int taskIndex = task->getIndex();
	assignedTaskIndex.push_back(taskIndex);

	vector<int>::iterator it;
	for (it = unassignedTaskIndex.begin(); it != unassignedTaskIndex.end(); it++)
	{
		if (*it == taskIndex)
		{
			unassignedTaskIndex.erase(it);
			break;
		}
	}

	task->markAssigned();
}

void TaskSet::clearAssignedTasks()
{
	assignedTaskIndex.clear();
	unassignedTaskIndex.clear();
	for (int i = 0; i < taskNumber; i++)
	{
		tasks[i]->clearAssignedTasks();
		unassignedTaskIndex.push_back(i);
	}
}

int TaskSet::getTaskNumber()
{
	return taskNumber;
}

int TaskSet::getMinPeriod()
{
	return minPeriod;
}

double TaskSet::getMaxUtilization()
{
	return maxUtilization;
}

vector<Task*> TaskSet::getTasks()
{
	return tasks;
}

double TaskSet::getUtilization()
{
	return utilization;
}

vector<int> TaskSet::getUnassignedTaskIndex()
{
	return unassignedTaskIndex;
}



bool TaskSet::generateTaskSet(int taskNumber, int minPeriod, int maxPeriod, ResourceSet * resourceSet)
{
	clear();	
	
	vector<int> periods;
	int minTaskPeriodCalculated = minPeriod >= resourceSet->getMaxPeriodFactor() ? minPeriod : (int)ceil(resourceSet->getMaxPeriodFactor());
	int minTaskPeriodActual = 2147483647;
	vector<double> utilizations;
	vector<double> utilizationsActual;
	double maxTaskUtilizationCalculated = 0.0;
	double maxTaskUtilizationActual = 0.0;

	int count = 100;// 1000;
	int i = 0;
	while (count > 0)
	{		
		Random rand;
		periods = rand.nextInts(taskNumber, minTaskPeriodCalculated, maxPeriod);
		minTaskPeriodActual = 2147483647;
		for (i = 0; i < taskNumber; i++)
		{
			if (periods[i] < minTaskPeriodActual)
				minTaskPeriodActual = periods[i];
		}
				
		maxTaskUtilizationCalculated = calculateMaxTaskUtilizationWithUtilizationBound(minTaskPeriodActual, resourceSet);

		maxTaskUtilizationActual = 0.0;
		while (utilizationsActual.size() != taskNumber)
		{
			utilizations = rand.nextDoubles(taskNumber, 0.0, maxTaskUtilizationCalculated);
			
			for (i = 0; i<taskNumber && utilizationsActual.size() != taskNumber; i++)
			{
				if (utilizations[i] >= 0.1)
				{
					utilizationsActual.push_back(utilizations[i]);

					if (utilizations[i] > maxTaskUtilizationActual)
						maxTaskUtilizationActual = utilizations[i];
				}				
			}			
		}	

		for (i = 0; i < taskNumber; i++)
		{
			if (!resourceSet->checkTask(minTaskPeriodActual, maxTaskUtilizationActual))
				break;
		}

		if (i == taskNumber)
		{
			sort(&utilizationsActual, &periods);

			for (int j = 0; j < taskNumber; j++)
			{
				tasks.push_back(new Task(periods[j], periods[j] * utilizationsActual[j], j));
				unassignedTaskIndex.push_back(i);
			}

			return true;
		}

		count--;
		cout << "        taskSet " << 100 - count << " try fail" << endl;
	}

	return false;
}



bool TaskSet::generateTaskSet(int taskNumber, int maxPeriod, double harmonicity, ResourceSet * resourceSet)
{
	clear();

	int fixedResourcePeriod = resourceSet->getResources()[0]->getPeriod();
	vector<int> periods;	
	int minTaskPeriodCalculated = (int)ceil(fixedResourcePeriod * (2 - resourceSet->getMinCapacity()));
	int minTaskPeriodActual = maxPeriod;
	vector<double> utilizations;
	vector<double> utilizationsActual;
	double maxTaskUtilizationCalculated = 0.0;
	double maxTaskUtilizationActual = 0.0;

	int count = 100;// 1000;
	int i = 0;
	Random rand;
	MyMath math;
	vector<int> periodBases;
	while (count > 0)
	{
		periodBases = math.harmonicNumbers(fixedResourcePeriod, harmonicity, minTaskPeriodCalculated, maxPeriod);
		if (periodBases.size() == 0)
			return false;

		vector<int> periodIndices = rand.nextInts(taskNumber, 0, periodBases.size() - 1);
		minTaskPeriodActual = maxPeriod;
		for (int i = 0; i < taskNumber; i++)
		{
			periods.push_back(periodBases[periodIndices[i]]);

			if (periods[i] < minTaskPeriodActual)
				minTaskPeriodActual = periods[i];
		}
		

		maxTaskUtilizationCalculated = calculateMaxTaskUtilizationWithUtilizationBound(minTaskPeriodActual, resourceSet);

		maxTaskUtilizationActual = 0.0;
		while (utilizationsActual.size() != taskNumber)
		{
			utilizations = rand.nextDoubles(taskNumber, 0.0, maxTaskUtilizationCalculated);

			for (i = 0; i<taskNumber && utilizationsActual.size() != taskNumber; i++)
			{
				if (utilizations[i] >= 0.1)
				{
					utilizationsActual.push_back(utilizations[i]);

					if (utilizations[i] > maxTaskUtilizationActual)
						maxTaskUtilizationActual = utilizations[i];
				}
			}
		}

		for (i = 0; i < taskNumber; i++)
		{
			if (!resourceSet->checkTask(minTaskPeriodActual, maxTaskUtilizationActual))
				break;
		}

		if (i == taskNumber)
		{
			sort(&utilizationsActual, &periods);

			for (int j = 0; j < taskNumber; j++)
			{
				tasks.push_back(new Task(periods[j], periods[j] * utilizationsActual[j], j));
				unassignedTaskIndex.push_back(i);
			}

			return true;
		}

		count--;
		cout << "        taskSet " << 100 - count << " try fail" << endl;
	}

	return false;
}

bool TaskSet::generateTaskSet(int taskNumber, int minPeriod, int maxPeriod, vector<double> utilizations, double harmonicity, ResourceSet * resourceSet)
{
	clear();

	int fixedResourcePeriod = resourceSet->getResources()[0]->getPeriod();
	vector<int> periods;
	int minTaskPeriodCalculatedFromResource = (int)ceil(fixedResourcePeriod * (2 - resourceSet->getMinCapacity()));
	int minTaskPeriodCalculated = minPeriod >= minTaskPeriodCalculatedFromResource ? minPeriod : minTaskPeriodCalculatedFromResource;
	int minTaskPeriodActual = 2147483647;	
	double maxTaskUtilizationActual = 0.0;

	int count = 100;// 1000;
	int i = 0;
	Random rand;
	MyMath math;
	vector<int> periodBases;
	while (count > 0)
	{
		periodBases = math.harmonicNumbers(fixedResourcePeriod, harmonicity, minTaskPeriodCalculated, maxPeriod);
		if (periodBases.size() == 0)
			return false;

		vector<int> periodIndices = rand.nextInts(taskNumber, 0, periodBases.size() - 1);
		minTaskPeriodActual = 2147483647;
		maxTaskUtilizationActual = 0.0;
		for (int i = 0; i < taskNumber; i++)
		{
			periods.push_back(periodBases[periodIndices[i]]);

			if (periods[i] < minTaskPeriodActual)
				minTaskPeriodActual = periods[i];
			if (utilizations[i] > maxTaskUtilizationActual)
				maxTaskUtilizationActual = utilizations[i];
		}
		

		for (i = 0; i < taskNumber; i++)
		{
			if (!resourceSet->checkTask(minTaskPeriodActual, maxTaskUtilizationActual))
				break;
		}

		if (i == taskNumber)
		{
			sort(&utilizations, &periods);

			for (int j = 0; j < taskNumber; j++)
			{
				tasks.push_back(new Task(periods[j], periods[j] * utilizations[j], j));
				unassignedTaskIndex.push_back(i);
			}

			return true;
		}

		count--;
		cout << "        taskSet " << 100 - count << " try fail" << endl;
	}

	return false;
}

double TaskSet::calculateMaxTaskUtilizationWithUtilizationBound(int minTaskPeriod, ResourceSet* resourceSet)
{
	double minUtilization = 1.0;
	double utilization = 0.0;
	int K = 0;
	Resource* resource = NULL;
	for (int i = 0; i < resourceSet->getResourceNumber(); i++)
	{
		resource = resourceSet->getResources()[i];

		K = 0;
		while ((K + 2)*resource->getPeriod() - resource->getPeriod()*resource->getCapacity() < minTaskPeriod)
			K++;

		utilization = resource->getCapacity() * ((double)K / (K + 2 * (1 - resource->getCapacity())));

		if (utilization < minUtilization)
			minUtilization = utilization;
	}

	return minUtilization;
}

void TaskSet::clear()
{
	for (int i = 0; i < tasks.size(); i++)
		delete tasks[i];

	tasks.clear();
	unassignedTaskIndex.clear();
	assignedTaskIndex.clear();
}

void TaskSet::sort(vector<double>* utilizations, vector<int>* periods)
{
	int tmpP = 0;
	double tmpU = 0.0;

	for (int i = 1; i < utilizations->size(); i++)
	{
		for (int j = 0; j < utilizations->size() - 1; j++)
		{
			if (utilizations->at(i) > utilizations->at(j))
			{
				tmpU = utilizations->at(i);
				utilizations->at(i) = utilizations->at(j);
				utilizations->at(j) = tmpU;

				tmpP = periods->at(i);
				periods->at(i) = periods->at(j);
				periods->at(j) = tmpP;
			}
		}
	}
}