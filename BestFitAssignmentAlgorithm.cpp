#include "BestFitAssignmentAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



BestFitAssignmentAlgorithm::BestFitAssignmentAlgorithm()
{
}

BestFitAssignmentAlgorithm::BestFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet) : AssignmentAlgorithm(taskSet, resourceSet)
{
}

BestFitAssignmentAlgorithm::~BestFitAssignmentAlgorithm()
{
}

Resource* BestFitAssignmentAlgorithm::searchFitResource(Task* task)
{
	Resource* bestFitResource = NULL;
	Resource* resource = NULL;
	double minUtilizationDifferenceRate = 1.0;
	double utilizationDifferenceRate = 0.0;

	for (int i = 0; i < resourceSet->getUnfullResourceIndex().size(); i++)
	{
		resource = resourceSet->getResources()[resourceSet->getUnfullResourceIndex()[i]];
		utilizationDifferenceRate = resource->calculateUtilizationBoundDifference(task) / resource->getCapacity();

		if (utilizationDifferenceRate >= 0.0 && utilizationDifferenceRate < minUtilizationDifferenceRate)
		{
			minUtilizationDifferenceRate = utilizationDifferenceRate;
			bestFitResource = resource;
		}
	}

	return bestFitResource;
}

Task* BestFitAssignmentAlgorithm::searchFitTask(Resource* resource)
{
	Task* bestFitTask = NULL;
	Task* task = NULL;
	double minUtilizationDifferenceRate = 1.0;
	double utilizationDifferenceRate = 0.0;
	double resourceCapacity = resource->getCapacity();

	for (int i = 0; i < taskSet->getUnassignedTaskIndex().size(); i++)
	{
		task = taskSet->getTasks()[taskSet->getUnassignedTaskIndex()[i]];
		utilizationDifferenceRate = resource->calculateUtilizationBoundDifference(task) / resourceCapacity;

		if (utilizationDifferenceRate >= 0.0 && utilizationDifferenceRate < minUtilizationDifferenceRate)
		{
			minUtilizationDifferenceRate = utilizationDifferenceRate;
			bestFitTask = task;
		}
	}

	return bestFitTask;
}