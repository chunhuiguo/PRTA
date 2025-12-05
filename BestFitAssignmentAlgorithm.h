#include "AssignmentAlgorithm.h"

#ifndef   BESTFITASSIGNMENTALGORITHM_H 
#define   BESTFITASSIGNMENTALGORITHM_H


class BestFitAssignmentAlgorithm : public AssignmentAlgorithm
{
public:
	BestFitAssignmentAlgorithm();
	BestFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	~BestFitAssignmentAlgorithm();

	Resource* searchFitResource(Task* task);
	Task* searchFitTask(Resource* resource);
};

#endif