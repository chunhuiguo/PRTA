#include "Task.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


Task::Task()
{
	period = 0;
	executionTime = 0.0;
	utilization = 0.0;
	assigned = false;
	index = 0;
}

Task::~Task()
{
}

Task::Task(int period, double executionTime, int index)
{
	this->period = period;
	this->executionTime = executionTime;
	this->utilization = executionTime / period;
	assigned = false;
	this->index = index;
}

void Task::markAssigned()
{
	assigned = true;
}

void Task::clearAssignedTasks()
{
	assigned = false;
}

int Task::getPeriod()
{
	return period;
}

double Task::getUtilization()
{
	return utilization;
}

double Task::getExecutionTime()
{
	return executionTime;
}

int Task::getIndex()
{
	return index;
}