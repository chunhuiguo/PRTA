#include <vector>
#include <math.h>

#include "HarmonictityFitAssignmentAlgorithm.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



HarmonictityFitAssignmentAlgorithm::HarmonictityFitAssignmentAlgorithm()
{	
}

HarmonictityFitAssignmentAlgorithm::HarmonictityFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet) : AssignmentAlgorithm(taskSet, resourceSet)
{	
}

HarmonictityFitAssignmentAlgorithm::HarmonictityFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet, double taskSetHarmonicityWithResourceSet)
{
	this->taskSet = taskSet;
	this->resourceSet = resourceSet;
	resourceUtilizationRate = 0.0;
	assignedResourceNumber = 0;
	this->taskSetHarmonicityWithResourceSet = taskSetHarmonicityWithResourceSet;
}

HarmonictityFitAssignmentAlgorithm::~HarmonictityFitAssignmentAlgorithm()
{
}

void HarmonictityFitAssignmentAlgorithm::assign()
{
	clearAssignedTasks();
	preProcess();

	Task* task = NULL;
	Resource* resource = NULL;
	vector<int> indexMaxHarmonicity;

	while (taskSet->getUnassignedTaskIndex().size() != 0)
	{
		indexMaxHarmonicity = searchMaxHarmonicity();
		task = taskSet->getTasks()[indexMaxHarmonicity[0]];
		resource = resourceSet->getResources()[indexMaxHarmonicity[1]];
		if (resource->checkHarmonicUtilizationBound(task, harmonicity[indexMaxHarmonicity[0]][indexMaxHarmonicity[1]]) || resource->checkUtilizationBound(task))
		{
			resource->assign(task, harmonicity[indexMaxHarmonicity[0]][indexMaxHarmonicity[1]]);
			taskSet->markTaskAssigned(task);
			resetHarmonicityI(indexMaxHarmonicity[0]);
			recalculateSelectedResourceHarmonicityAfterAssignTask(resource);

			task = searchFitTask(resource); //harmonicity fit task for the given resource
			while (task != NULL) //*fit task is null means the resource is full
			{
				resource->assign(task, selectedResourceHarmonicity[task->getIndex()]);
				taskSet->markTaskAssigned(task);
				resetHarmonicityI(task->getIndex());
				recalculateSelectedResourceHarmonicityAfterAssignTask(resource);

				task = searchFitTask(resource); //harmonicity fit task for the given resource				
			}
			resourceSet->markResourceFull(resource);
		}
		else
		{
			resetHarmonicityIJ(indexMaxHarmonicity[0], indexMaxHarmonicity[1]);
		}
	}
}

Task* HarmonictityFitAssignmentAlgorithm::searchFitTask(Resource* resource)
{
	Task* harmonicityFitTask = NULL;
	Task* task = NULL;
	vector<int> indexMaxHarmonicityJ;
	
	for (int i = 0; i < taskSet->getUnassignedTaskIndex().size(); i++)
	{
		indexMaxHarmonicityJ = searchMaxSelectedResourceHarmonicity(resource->getIndex());
		//max harmonicity (recalculated after each assignment) of the given resource (colmun j, where j is index of the given resource) is 0.0 , i.e. the given resource is full
		if (indexMaxHarmonicityJ[0] == -1) 
			return NULL;
		task = taskSet->getTasks()[indexMaxHarmonicityJ[0]];

		if (resource->checkHarmonicUtilizationBound(task, selectedResourceHarmonicity[indexMaxHarmonicityJ[0]]) || resource->checkUtilizationBound(task))
			return harmonicityFitTask = task;
		else
		{
			resetHarmonicityIJ(indexMaxHarmonicityJ[0], indexMaxHarmonicityJ[1]);
			resetSelectedResourceHarmonicityIJ(indexMaxHarmonicityJ[0]);
		}
			
	}

	return harmonicityFitTask;
}

void HarmonictityFitAssignmentAlgorithm::preProcess()
{
	calculateHarmonicity();

	for (int i = 0; i < taskSet->getTaskNumber(); i++)
		selectedResourceHarmonicity.push_back(0.0);
}


void HarmonictityFitAssignmentAlgorithm::calculateHarmonicity()
{
	double harmonicityIJ = 0.0;
	for (int i = 0; i < taskSet->getTaskNumber(); i++)
	{
		vector<double> harmonicityTaskI;
		for (int j = 0; j < resourceSet->getResourceNumber(); j++)
		{
			harmonicityIJ = DCT(taskSet->getTasks()[i], resourceSet->getResources()[j]);
			harmonicityTaskI.push_back(harmonicityIJ);
		}			

		harmonicity.push_back(harmonicityTaskI);
	}
}

double HarmonictityFitAssignmentAlgorithm::DCT(Task * task, Resource * resource)
{
	double harmonicity = 1.0;
	int harmonicPeriod = 0;
	int taskPeriod = task->getPeriod();
	int resourcePeriod = resource->getPeriod();

	if (taskPeriod > resourcePeriod)
	{		
		harmonicPeriod = resourcePeriod * (int)floor((double)taskPeriod / resourcePeriod);
		harmonicity = (double)harmonicPeriod / taskPeriod;
	}
	if (taskPeriod < resourcePeriod)
	{		
		harmonicPeriod = resourcePeriod / (int)ceil((double)resourcePeriod / taskPeriod);
		harmonicity = (double)harmonicPeriod / taskPeriod;
	}

	return harmonicity;
}

void HarmonictityFitAssignmentAlgorithm::recalculateSelectedResourceHarmonicityAfterAssignTask(Resource * resource)
{
	int resourceIndex = resource->getIndex();
	int resourcePeriod = resource->getPeriod();
	vector<int> assignedTaskHarmonicPeriods = resource->getAssignedTaskHarmonicPeriods();
	int taskPeriod = 0;
	int harmonicPeriod = 0;
	int harmonicFactor = 0; //ratio of task period and resource period, i.e., (int) taskPeriod/resourcePeriod
	int k = 0;	
	bool harmonic = true;

	clearSelectedResourceHarmonicity();

	for (int i = 0; i < taskSet->getTaskNumber(); i++)
	{
		taskPeriod = taskSet->getTasks()[i]->getPeriod();

		if (harmonicity[i][resourceIndex] == 0.0)
			selectedResourceHarmonicity[i] = 0.0;
		else
		{
			harmonicFactor = taskPeriod / resourcePeriod;

			k = harmonicFactor;
			while (k > 0)
			{
				harmonicPeriod = resourcePeriod * k;

				harmonic = true;
				for (int j = 0; j < resource->getAssignedTaskNumber(); j++)
				{
					if (!(harmonicPeriod % assignedTaskHarmonicPeriods[j] == 0 || assignedTaskHarmonicPeriods[j] % harmonicPeriod == 0))
					{
						harmonic = false;
						break;
					}						
				}

				if (harmonic)
				{
					selectedResourceHarmonicity[i] = (double)harmonicPeriod / taskPeriod;
					break;
				}					

				k--;
			}
		}
	}
}

vector<int> HarmonictityFitAssignmentAlgorithm::searchMaxHarmonicity()
{
	int iMax = -1;
	int jMax = -1;
	double maxHarmonicity = 0.0;
	vector<int> maxIndex;

	for (int i = 0; i < taskSet->getTaskNumber(); i++)
	{
		for (int j = 0; j < resourceSet->getResourceNumber(); j++)
		{
			if (harmonicity[i][j] > maxHarmonicity)
			{
				maxHarmonicity = harmonicity[i][j];
				iMax = i;
				jMax = j;
			}
			else if (maxHarmonicity != 0.0 && harmonicity[i][j] == maxHarmonicity)
			{
				if (i != iMax && taskSet->getTasks()[i]->getUtilization() > taskSet->getTasks()[iMax]->getUtilization())
				{
					maxHarmonicity = harmonicity[i][j];
					iMax = i;
					jMax = j;
				}
			}
		}
	}

	maxIndex.push_back(iMax);
	maxIndex.push_back(jMax);
	return maxIndex;
}

vector<int> HarmonictityFitAssignmentAlgorithm::searchMaxSelectedResourceHarmonicity(int j)
{
	int iMax = -1;
	double maxHarmonicity = 0.0;
	vector<int> maxIndex;

	for (int i = 0; i < taskSet->getTaskNumber(); i++)
	{
		if (selectedResourceHarmonicity[i] > maxHarmonicity)
		{
			maxHarmonicity = selectedResourceHarmonicity[i];
			iMax = i;
		}

		if (maxHarmonicity != 0.0 && selectedResourceHarmonicity[i] == maxHarmonicity && taskSet->getTasks()[i]->getUtilization()>taskSet->getTasks()[iMax]->getUtilization())
		{
			maxHarmonicity = selectedResourceHarmonicity[i];
			iMax = i;
		}
	}

	maxIndex.push_back(iMax);
	maxIndex.push_back(j);
	return maxIndex;
}

void HarmonictityFitAssignmentAlgorithm::resetHarmonicityI(int i)
{
	for (int j = 0; j < resourceSet->getResourceNumber(); j++)
	{
		harmonicity[i][j] = 0.0;
	}
}

void HarmonictityFitAssignmentAlgorithm::resetHarmonicityIJ(int i, int j)
{
	harmonicity[i][j] = 0.0;
}

void HarmonictityFitAssignmentAlgorithm::resetSelectedResourceHarmonicityIJ(int i)
{
	selectedResourceHarmonicity[i] = 0.0;
}

void HarmonictityFitAssignmentAlgorithm::clearSelectedResourceHarmonicity()
{
	for (int i = 0; i < taskSet->getTaskNumber(); i++)
		selectedResourceHarmonicity[i] = 0.0;
}