#include <vector>
#include "math.h"

#include "Resource.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



Resource::Resource()
{
	period = 0;
	allocationTime = 0.0;
	capacity = 0.0;
	index = 0;
	full = false;

	assignedTaskNumber = 0;
	assignedMinTaskPeriod = 2147483647;
	assignedTaskUtilization = 0.0;
	assignedTaskHarmonicUtilization = 0.0;
}

Resource::~Resource()
{
}

Resource::Resource(int period, double allocationTime, int index)
{
	this->period = period;
	this->allocationTime = allocationTime;
	this->capacity = allocationTime / period;
	this->index = index;
	full = false;

	assignedTaskNumber = 0;
	assignedMinTaskPeriod = 2147483647;
	assignedTaskUtilization = 0.0;
	assignedTaskHarmonicUtilization = 0.0;
}

void Resource::assign(Task* task)
{
	assignedTasks.push_back(task);
	assignedTaskNumber = assignedTaskNumber + 1;
	assignedTaskUtilization = assignedTaskUtilization + task->getUtilization();
	//for non-harmonicity algorithm, assignedTaskHarmonicUtilization is the same with assignedTaskUtilization
	assignedTaskHarmonicUtilization = assignedTaskHarmonicUtilization + task->getUtilization();
	if (task->getPeriod() < assignedMinTaskPeriod)
		assignedMinTaskPeriod = task->getPeriod();
}

void Resource::assign(Task* task, double harmonicity)
{
	assignedTasks.push_back(task);
	assignedTaskHarmonicPeriods.push_back(task->getPeriod() * harmonicity);
	assignedTaskNumber = assignedTaskNumber + 1;
	assignedTaskUtilization = assignedTaskUtilization + task->getUtilization();
	assignedTaskHarmonicUtilization = assignedTaskHarmonicUtilization + task->getUtilization() / harmonicity;
	if (task->getPeriod() < assignedMinTaskPeriod)
		assignedMinTaskPeriod = task->getPeriod();
}

bool Resource::checkHarmonicUtilizationBound(Task* task, double harmonicity)
{
	double harmonicUtilization = assignedTaskHarmonicUtilization + task->getUtilization() / harmonicity;
	if (harmonicUtilization <= capacity)
		return true;

	return false;
}

bool Resource::checkUtilizationBound(Task* task)
{
	double utilizationBound = calculateUtilizationBound(task);
	if (assignedTaskUtilization + task->getUtilization() <= utilizationBound)
		return true;

	return false;
}

double Resource::calculateUtilizationBoundDifference(Task* task)
{
	double utilizationBound = calculateUtilizationBound(task);
	return utilizationBound - assignedTaskUtilization - task->getUtilization();
}

void Resource::markFull()
{
	full = true;
}

double Resource::calculateUtilizationRate()
{
	double utilizaitonRate = 0.0;
	double taskUtilization = 0.0;

	if (!assignedTasks.empty())
	{
		for (int i = 0; i < assignedTasks.size(); i++)
			taskUtilization = taskUtilization + assignedTasks[i]->getUtilization();

		utilizaitonRate = taskUtilization / capacity;
	}

	return utilizaitonRate;
}

void Resource::clearAssignedTasks()
{
	assignedTasks.clear();
	assignedTaskNumber = 0;
	assignedMinTaskPeriod = 2147483647;
	assignedTaskUtilization = 0.0;
	assignedTaskHarmonicUtilization = 0.0;
	assignedTaskHarmonicPeriods.clear();

	full = false;
}

int Resource::getPeriod()
{
	return period;
}

double Resource::getCapacity()
{
	return capacity;
}

double Resource::getAllocationTime()
{
	return allocationTime;
}

int Resource::getIndex()
{
	return index;
}

vector<Task*> Resource::getAssignedTasks()
{
	return assignedTasks;
}

int Resource::getAssignedTaskNumber()
{
	return assignedTaskNumber;
}

vector<int> Resource::getAssignedTaskHarmonicPeriods()
{
	return assignedTaskHarmonicPeriods;
}


double Resource::calculateUtilizationBound(Task* task)
{
	int N = assignedTaskNumber + 1;
	int K = 0;

	int minTaskPeriod = assignedMinTaskPeriod;
	if (task->getPeriod() < minTaskPeriod)
		minTaskPeriod = task->getPeriod();

	while ((K + 2)*period - period*capacity < minTaskPeriod)
		K++;

	return capacity*N*(pow((2 * K + 2 * (1 - capacity)) / (K + 2 * (1 - capacity)), 1 / (double)N) - 1);
}