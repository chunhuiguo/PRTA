#include "AssignmentAlgorithm.h"
#include "MyMath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



AssignmentAlgorithm::AssignmentAlgorithm()
{
	taskSet = NULL;
	resourceSet = NULL;
	resourceUtilizationRate = 0.0;
	assignedResourceNumber = 0;
	taskSetHarmonicityWithResourceSet = 0.0;
}

AssignmentAlgorithm::AssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet)
{
	this->taskSet = taskSet;
	this->resourceSet = resourceSet;
	resourceUtilizationRate = 0.0;
	assignedResourceNumber = 0;
	taskSetHarmonicityWithResourceSet = 0.0;
}

AssignmentAlgorithm::~AssignmentAlgorithm()
{
}

void AssignmentAlgorithm::assign()
{
	clearAssignedTasks();
	preProcess();

	Task* task = NULL;
	Resource* resource = NULL;
	while (taskSet->getUnassignedTaskIndex().size() != 0)
	{
		task = taskSet->getTasks()[taskSet->getUnassignedTaskIndex()[0]];
		resource = searchFitResource(task); //*fit resource for the given task
		resource->assign(task);
		taskSet->markTaskAssigned(task);

		task = searchFitTask(resource); //*fit task for the given resource
		while (task != NULL) //*fit task is null means the resource is full or all tasks are assigned
		{
			resource->assign(task);
			taskSet->markTaskAssigned(task);

			task = searchFitTask(resource); //*fit task for the given resource
		}

		resourceSet->markResourceFull(resource);
	}
}

Resource* AssignmentAlgorithm::searchFitResource(Task* task)
{
	return NULL;
}

Task* AssignmentAlgorithm::searchFitTask(Resource* resource)
{
	return NULL;
}

void AssignmentAlgorithm::preProcess()
{
}

void AssignmentAlgorithm::calculateResourceUtilizationRate()
{
	double assignedResourceCapacity = 0.0;
	Resource* resource = NULL;
	vector<Resource*> resources = resourceSet->getResources();

	assignedResourceNumber = 0;
	for (int j = 0; j < resourceSet->getResourceNumber(); j++)
	{
		resource = resources[j];
		if (resource->getAssignedTaskNumber() != 0)
		{
			assignedResourceCapacity = assignedResourceCapacity + resource->getCapacity();
			assignedResourceNumber++;
		}				
	}

	resourceUtilizationRate = taskSet->getUtilization() / assignedResourceCapacity;
}

/*
void AssignmentAlgorithm::calculateTaskSetHarmonicityWithResourceSet()
{
	vector<double> harmonicity;
	int taskPeriod = taskSet->getMinPeriod();
	vector<Resource*> resources = resourceSet->getResources();

	for (int i = 0; i < resources.size(); i++)
		harmonicity.push_back(DCT(taskPeriod, resources[i]->getPeriod()));

	MyMath math;
	taskSetHarmonicityWithResourceSet = math.average(harmonicity);
}
*/

double AssignmentAlgorithm::getResourceUtilizationRate()
{
	return resourceUtilizationRate;
}

int AssignmentAlgorithm::getAssignedResourceNumber()
{
	return assignedResourceNumber;
}

double AssignmentAlgorithm::getTaskSetHarmonicityWithResourceSet()
{
	return taskSetHarmonicityWithResourceSet;
}

void AssignmentAlgorithm::clearAssignedTasks()
{
	resourceSet->clearAssignedTasks();
	taskSet->clearAssignedTasks();		
}


double AssignmentAlgorithm::DCT(int taskPeriod, int resourcePeriod)
{
	double harmonicity = 1.0;
	int harmonicPeriod = 0;

	if (taskPeriod%resourcePeriod == 0 || resourcePeriod%taskPeriod == 0)
		return 1.0;

	if (taskPeriod > resourcePeriod)
	{
		harmonicPeriod = resourcePeriod * (taskPeriod / resourcePeriod);
		harmonicity = (double)harmonicPeriod / taskPeriod;
	}
	if (taskPeriod < resourcePeriod)
	{
		harmonicPeriod = resourcePeriod / (resourcePeriod / taskPeriod + 1);
		harmonicity = (double)harmonicPeriod / taskPeriod;
	}

	return harmonicity;
}