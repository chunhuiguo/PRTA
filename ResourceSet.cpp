#include "ResourceSet.h"
#include "Random.h"
#include "MyMath.h"

#include <iostream>

using namespace std;


ResourceSet::ResourceSet()
{
	resourceNumber = 0;
	capacity = 0.0;
	minCapacity = 1.0;
	maxPeriodFactor = 0.0;
}

ResourceSet::~ResourceSet()
{
	clear();
}


ResourceSet::ResourceSet(vector<Resource*> resources, TaskSet * taskSet)
{
	this->resources = resources;
	resourceNumber = resources.size();

	Resource* resource = NULL;
	for (int i = 0; i < resourceNumber; i++)
	{
		unfullResourceIndex.push_back(i);

		resource = resources[i];
		capacity = capacity + resource->getCapacity();

		minCapacity = 1.0;
		maxPeriodFactor = 0.0;
		if (resource->getCapacity() < minCapacity)
			minCapacity = resource->getCapacity();
		if (2 * resource->getPeriod() - resource->getAllocationTime() > maxPeriodFactor)
			maxPeriodFactor = 2 * resource->getPeriod() - resource->getAllocationTime();
	}
}

ResourceSet::ResourceSet(int resourceNumber, int minPeriod, int maxPeriod, double capacity, double capacityBaseRatio, bool fixedPeriod, bool ratio)
{
	clear();
	this->resourceNumber = resourceNumber;
	this->capacity = capacity;

	MyMath math;
	vector<double> util = math.decomposeRandom(resourceNumber, capacity, capacityBaseRatio, ratio); //last parameter true or false ???
	if (util.size() == 0)
	{
		this->resourceNumber = 0;
		this->capacity = 0;
		return;
	}
	
	vector<int> periods;
	Random rand;
	if (fixedPeriod)
	{
		int period = rand.nextInt(minPeriod, maxPeriod);
		for (int i = 0; i < resourceNumber; i++)
			periods.push_back(period);
	}
	else
	{		
		periods = rand.nextInts(resourceNumber, minPeriod, maxPeriod);
	}	

	minCapacity = 1.0;
	maxPeriodFactor = 0.0;
	Resource* resource = NULL;
	for (int i = 0; i < resourceNumber; i++)
	{
		resource = new Resource(periods[i], periods[i] * util[i], i);
		resources.push_back(resource);
		unfullResourceIndex.push_back(i);

		if (resource->getCapacity() < minCapacity)
			minCapacity = resource->getCapacity();
		if (2 * resource->getPeriod() - resource->getAllocationTime() > maxPeriodFactor)
			maxPeriodFactor = 2 * resource->getPeriod() - resource->getAllocationTime();
	}
}


ResourceSet::ResourceSet(int resourceNumber, int minPeriod, int maxPeriod, double capacityBaseRatio)
{
	clear();
	this->resourceNumber = resourceNumber;
	//this->capacity = capacity;

	
	Random rand;
	vector<double> util = rand.nextDoubles(resourceNumber, capacityBaseRatio, 1.0);
	vector<int> periods = rand.nextInts(resourceNumber, minPeriod, maxPeriod);
	
	minCapacity = 1.0;
	maxPeriodFactor = 0.0;
	Resource* resource = NULL;
	capacity = 0.0;
	for (int i = 0; i < resourceNumber; i++)
	{
		capacity = capacity + util[i];

		resource = new Resource(periods[i], periods[i] * util[i], i);
		resources.push_back(resource);
		unfullResourceIndex.push_back(i);

		if (resource->getCapacity() < minCapacity)
			minCapacity = resource->getCapacity();
		if (2 * resource->getPeriod() - resource->getAllocationTime() > maxPeriodFactor)
			maxPeriodFactor = 2 * resource->getPeriod() - resource->getAllocationTime();
	}
}


bool ResourceSet::checkTask(int minTaskPeriod, double maxTaskUtilization)
{
	int period = 0;
	double capacity = 0.0;
	bool mark = true;

	for (int i = 0; i < resourceNumber; i++)
	{
		period = resources[i]->getPeriod();
		capacity = resources[i]->getCapacity();

		if (checkConstraintOne(period, capacity, minTaskPeriod) && checkConstraintTwo(period, capacity, minTaskPeriod, maxTaskUtilization))
		{
			;
		}
		else
		{
			mark = false;
			break;
		}
	}

	return mark;
}

void ResourceSet::markResourceFull(Resource* resource)
{
	int resourceIndex = resource->getIndex();
	fullResourceIndex.push_back(resourceIndex);

	vector<int>::iterator it;
	for (it = unfullResourceIndex.begin(); it != unfullResourceIndex.end(); it++)
	{
		if (*it == resourceIndex)
		{
			unfullResourceIndex.erase(it);
			break;
		}
	}

	resource->markFull();
}

void ResourceSet::clearAssignedTasks()
{
	fullResourceIndex.clear();
	unfullResourceIndex.clear();
	for (int i = 0; i < resourceNumber; i++)
	{
		resources[i]->clearAssignedTasks();
		unfullResourceIndex.push_back(i);
	}	
}

int ResourceSet::getResourceNumber()
{
	return resourceNumber;
}

vector<Resource*> ResourceSet::getResources()
{
	return resources;
}

double ResourceSet::getCapacity()
{
	return capacity;
}

vector<int> ResourceSet::getUnfullResourceIndex()
{
	return unfullResourceIndex;
}

double ResourceSet::getMinCapacity()
{
	return minCapacity;
}

double ResourceSet::getMaxPeriodFactor()
{
	return maxPeriodFactor;
}


bool ResourceSet::generateResourceSet(int resourceNumber, int minPeriod, int maxPeriod, TaskSet * taskSet)
{
	clear();
	//int count = 65536;

	Random rand;
	int period = 0;
	double capacity = 0.0;
	for (int i = 0; i < resourceNumber; i++)
	{
		period = rand.nextInt(minPeriod, maxPeriod);
		capacity = rand.nextDouble();

		if (checkConstraintOne(period, capacity, taskSet->getMinPeriod()) && checkConstraintTwo(period, capacity, taskSet->getMinPeriod(), taskSet->getMaxUtilization()))
		{
			resources.push_back(new Resource(period, period*capacity, i));
			unfullResourceIndex.push_back(i);
		}
		else
		{
			i--;
			continue;
		}
	}

	if (!resources.empty())
		return true;

	return false;
}

bool ResourceSet::generateResourceSet(int resourceNumber, double capacity, double capacityBaseRatio, TaskSet * taskSet)
{
	clear();
	int count = 100;// 1000;

	int minTaskPeriod = taskSet->getMinPeriod();
	double maxTaskUtilization = taskSet->getMaxUtilization();
	double capacityBase2 = calculateCapacityBaseWithLooseUtilizationBound(maxTaskUtilization);
	double capacityBase = capacity / resourceNumber * capacityBaseRatio;
	int maxPeriod = calculateMaxPeriodWithCapacityBase(capacityBase2, minTaskPeriod);

	MyMath math;
	vector<double> util;// = math.unifast(resourceNumber, capacity - capacityBase*resourceNumber);	
	vector<int> periods;
	int i = 0;

	while (count > 0)
	{
		util = math.unifast(resourceNumber, capacity - capacityBase*resourceNumber);
		Random rand;
		periods = rand.nextInts(resourceNumber, 1, maxPeriod);

		for (i = 0; i < resourceNumber; i++)
		{
			if (!(capacityBase+util[i]<=1.0 && checkConstraintOne(periods[i], capacityBase + util[i], taskSet->getMinPeriod()) && checkConstraintTwo(periods[i], capacityBase + util[i], minTaskPeriod, maxTaskUtilization)))
				break;
		}

		if (i == resourceNumber)
		{
			for (int j = 0; j < resourceNumber; j++)
			{
				resources.push_back(new Resource(periods[j], periods[j] * (capacityBase + util[j]), j));
				unfullResourceIndex.push_back(j);
			}				

			return true;
		}

		count--;

		cout << "        resourceSet " << 100-count << " try fail" << endl;
	}
	
	return false;
}
void ResourceSet::clear()
{
	for (int i = 0; i < resources.size(); i++)
		delete resources[i];

	resources.clear();
	unfullResourceIndex.clear();
	fullResourceIndex.clear();
}

bool ResourceSet::checkConstraintOne(int period, double capacity, int minTaskPeriod)
{
	if (minTaskPeriod >= 2*period - capacity*period)
		return true;

	return false;
}

bool ResourceSet::checkConstraintTwo(int period, double capacity, int minTaskPeriod, double maxTaskUtilization)
{
	if (maxTaskUtilization < calculateUtilizationBoundWithOneTask(period, capacity, minTaskPeriod))
		return true;

	return false;
}

double ResourceSet::calculateUtilizationBoundWithOneTask(int period, double capacity, int minTaskPeriod)
{
	int K = 0;
	while ((K + 2)*period - period*capacity < minTaskPeriod)
		K++;
	
	return capacity * ((double)K / (K + 2 * (1 - capacity)));
}

double ResourceSet::calculateCapacityBaseWithLooseUtilizationBound(double maxTaskUtilization)
{
	return 3 * maxTaskUtilization / (1 + 2 * maxTaskUtilization);
}

int ResourceSet::calculateMaxPeriodWithCapacityBase(double capacityBase, int minTaskPeriod)
{
	return (int)(minTaskPeriod / (2 - capacityBase));
}