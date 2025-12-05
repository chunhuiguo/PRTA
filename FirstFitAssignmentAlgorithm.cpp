#include "FirstFitAssignmentAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



FirstFitAssignmentAlgorithm::FirstFitAssignmentAlgorithm()
{
}

FirstFitAssignmentAlgorithm::FirstFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet) : AssignmentAlgorithm(taskSet, resourceSet)
{
}

FirstFitAssignmentAlgorithm::~FirstFitAssignmentAlgorithm()
{
}

Resource* FirstFitAssignmentAlgorithm::searchFitResource(Task* task)
{
	Resource* firstFitResource = NULL;
	Resource* resource = NULL;

	for (int i = 0; i < resourceSet->getUnfullResourceIndex().size(); i++)
	{
		resource = resourceSet->getResources()[resourceSet->getUnfullResourceIndex()[i]];

		if (resource->checkUtilizationBound(task))
			return firstFitResource = resource;
	}

	return firstFitResource;
}

Task* FirstFitAssignmentAlgorithm::searchFitTask(Resource* resource)
{
	Task* firstFitTask = NULL;	
	Task* task = NULL;
	double resourceCapacity = resource->getCapacity();

	for (int i = 0; i < taskSet->getUnassignedTaskIndex().size(); i++)
	{
		task = taskSet->getTasks()[taskSet->getUnassignedTaskIndex()[i]];

		if (resource->checkUtilizationBound(task))
			firstFitTask = task;
	}

	return firstFitTask;
}