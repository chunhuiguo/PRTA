#include "AssignmentAlgorithm.h"

#ifndef   OPTIMALASSIGNMENTALGORITHM_H 
#define   OPTIMALASSIGNMENTALGORITHM_H


class OptimalAssignmentAlgorithm : public AssignmentAlgorithm
{
public:
	OptimalAssignmentAlgorithm();
	OptimalAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	~OptimalAssignmentAlgorithm();

	void assign();

private:
	bool checkTwoResources(Resource * resource1, Resource* resource2, vector<Task*> tasks);

	double calculateHarmonicity(Resource * resource, Task* task);
};

#endif