#include "ResourceSet.h"

#ifndef   ASSIGNMENTALGORITHM_H 
#define   ASSIGNMENTALGORITHM_H


class AssignmentAlgorithm
{
public:
	AssignmentAlgorithm();
	AssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	virtual ~AssignmentAlgorithm();

	virtual void assign();
	virtual Resource* searchFitResource(Task* task);
	virtual Task* searchFitTask(Resource* resource);
	virtual void preProcess();
	virtual void calculateResourceUtilizationRate();
	//virtual void calculateTaskSetHarmonicityWithResourceSet();

	virtual double getResourceUtilizationRate();
	virtual int getAssignedResourceNumber();
	virtual double getTaskSetHarmonicityWithResourceSet();	

protected:
	void clearAssignedTasks();

private:	
	double DCT(int taskPeriod, int resourcePeriod);


protected:
	TaskSet * taskSet;
	ResourceSet * resourceSet;
	double resourceUtilizationRate;
	int assignedResourceNumber;	
	double taskSetHarmonicityWithResourceSet;
};

#endif