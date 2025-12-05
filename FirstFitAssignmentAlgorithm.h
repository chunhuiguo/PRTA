#include "WorstFitAssignmentAlgorithm.h"

#ifndef   FIRSTFITASSIGNMENTALGORITHM_H 
#define   FIRSTFITASSIGNMENTALGORITHM_H


class FirstFitAssignmentAlgorithm : public AssignmentAlgorithm
{
public:
	FirstFitAssignmentAlgorithm();
	FirstFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	~FirstFitAssignmentAlgorithm();

	Resource* searchFitResource(Task* task);
	Task* searchFitTask(Resource* resource);
};

#endif