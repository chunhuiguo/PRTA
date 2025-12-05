#include "Resource.h"
#include "TaskSet.h"

using namespace std;

#ifndef   RESOURCESET_H 
#define   RESOURCESET_H 


class ResourceSet
{
public:
	ResourceSet();
	virtual ~ResourceSet();

	
	ResourceSet(vector<Resource*> resources, TaskSet * taskSet);	
	ResourceSet(int resourceNumber, int minPeriod, int maxPeriod, double capacity, double capacityBaseRatio, bool fixedPeriod, bool ratio);	
	ResourceSet(int resourceNumber, int minPeriod, int maxPeriod, double capacityBaseRatio);
	

	bool checkTask(int minTaskPeriod, double maxTaskUtilization);

	void markResourceFull(Resource* resource);
	void clearAssignedTasks();

	int getResourceNumber();
	vector<Resource*> getResources();
	double getCapacity();
	vector<int> getUnfullResourceIndex();
	double getMinCapacity();
	double getMaxPeriodFactor();

private:
	bool generateResourceSet(int resourceNumber, int minPeriod, int maxPeriod, TaskSet * taskSet);
	bool generateResourceSet(int resourceNumber, double capacity, double capacityBaseRatio, TaskSet * taskSet);
	double calculateUtilizationBoundWithOneTask(int period, double capacity, int minTaskPeriod);
	bool checkConstraintOne(int period, double capacity, int minTaskPeriod); //T_{min} >= 2*Pi - Theta
	bool checkConstraintTwo(int period, double capacity, int minTaskPeriod, double maxTaskUtilization); //max task uilization > utilization bound(n=1, minTaskPeriod)
	double calculateCapacityBaseWithLooseUtilizationBound(double maxTaskUtilization);
	int calculateMaxPeriodWithCapacityBase(double capacityBase, int minTaskPeriod);

	void clear();


private:
	vector<Resource*> resources;
	double capacity;
	int resourceNumber;

	vector<int> fullResourceIndex;
	vector<int> unfullResourceIndex;
	double minCapacity;
	double maxPeriodFactor; // 2*period-allocationTime
};

#endif