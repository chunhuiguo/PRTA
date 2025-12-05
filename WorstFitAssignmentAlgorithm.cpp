#include "WorstFitAssignmentAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


WorstFitAssignmentAlgorithm::WorstFitAssignmentAlgorithm()
{
}

WorstFitAssignmentAlgorithm::WorstFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet) : AssignmentAlgorithm(taskSet, resourceSet)
{
}

WorstFitAssignmentAlgorithm::~WorstFitAssignmentAlgorithm()
{
}

Resource* WorstFitAssignmentAlgorithm::searchFitResource(Task* task)
{
	Resource* worstFitResource = NULL;
	Resource* resource = NULL;
	double maxUtilizationDifferenceRate = 0.0;
	double utilizationDifferenceRate = 0.0;

	for (int i = 0; i < resourceSet->getUnfullResourceIndex().size(); i++)
	{
		resource = resourceSet->getResources()[resourceSet->getUnfullResourceIndex()[i]];
		utilizationDifferenceRate = resource->calculateUtilizationBoundDifference(task) / resource->getCapacity();

		if (utilizationDifferenceRate >= maxUtilizationDifferenceRate)
		{
			maxUtilizationDifferenceRate = utilizationDifferenceRate;
			worstFitResource = resource;
		}
	}

	return worstFitResource;
}

Task* WorstFitAssignmentAlgorithm::searchFitTask(Resource* resource)
{
	Task* worstFitTask = NULL;
	Task* task = NULL;
	double maxUtilizationDifferenceRate = 0.0;
	double utilizationDifferenceRate = 0.0;
	double resourceCapacity = resource->getCapacity();

	for (int i = 0; i < taskSet->getUnassignedTaskIndex().size(); i++)
	{
		task = taskSet->getTasks()[taskSet->getUnassignedTaskIndex()[i]];
		utilizationDifferenceRate = resource->calculateUtilizationBoundDifference(task) / resourceCapacity;

		if (utilizationDifferenceRate >= maxUtilizationDifferenceRate)
		{
			maxUtilizationDifferenceRate = utilizationDifferenceRate;
			worstFitTask = task;
		}
	}

	return worstFitTask;
}