#include "BestFitAssignmentAlgorithm.h"

#ifndef   WORSTFITASSIGNMENTALGORITHM_H 
#define   WORSTFITASSIGNMENTALGORITHM_H


class WorstFitAssignmentAlgorithm : public AssignmentAlgorithm
{
public:
	WorstFitAssignmentAlgorithm();
	WorstFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	~WorstFitAssignmentAlgorithm();

	Resource* searchFitResource(Task* task);
	Task* searchFitTask(Resource* resource);
};

#endif