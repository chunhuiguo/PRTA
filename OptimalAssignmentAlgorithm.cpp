#include "OptimalAssignmentAlgorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



OptimalAssignmentAlgorithm::OptimalAssignmentAlgorithm()
{
}

OptimalAssignmentAlgorithm::OptimalAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet) : AssignmentAlgorithm(taskSet, resourceSet)
{
}

OptimalAssignmentAlgorithm::~OptimalAssignmentAlgorithm()
{
}

void OptimalAssignmentAlgorithm::assign()
{
	clearAssignedTasks();
	
	Task* task = NULL;
	Resource* resource = NULL;
	Resource* resource2 = NULL;
	double maxResourceUtilizationRate = 0.0;
	double resourceUtilizationRateTmp = 0.0;
	double harmonicity = 0.0;
	bool harmonicSchedule = true;

	vector<Task*> tasks = taskSet->getTasks();
	vector<Resource*> resources = resourceSet->getResources();
	vector<Task*> tasksSortedForHarmonic;

	//one resource
	//general utilization bound
	assignedResourceNumber = 0;
	maxResourceUtilizationRate = 0.0;
	resourceUtilizationRate = 0.0;
	for (int i = 0; i < 3; i++)
	{
		clearAssignedTasks();
		resource = resources[i];

		task = tasks[0];
		if (resource->checkUtilizationBound(task))
			resource->assign(task);
		else
			continue;

		task = tasks[1];
		if (resource->checkUtilizationBound(task))
			resource->assign(task);
		else
			continue;

		task = tasks[2];
		if (resource->checkUtilizationBound(task))
			resource->assign(task);
		else
			continue;

		resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
		if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
		{
			resourceUtilizationRate = resourceUtilizationRateTmp;
			maxResourceUtilizationRate = resourceUtilizationRateTmp;
			assignedResourceNumber = 1;
		}
	}


	//one resource
	//harmonic utilization bound
	for (int i = 0; i < 3; i++)
	{		
		resource = resources[i];

		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[0]);
		tasksSortedForHarmonic.push_back(tasks[1]);
		tasksSortedForHarmonic.push_back(tasks[2]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}
				
		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}	

		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[0]);
		tasksSortedForHarmonic.push_back(tasks[2]);
		tasksSortedForHarmonic.push_back(tasks[1]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}

		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}

		
		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[1]);
		tasksSortedForHarmonic.push_back(tasks[0]);
		tasksSortedForHarmonic.push_back(tasks[2]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}

		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}

		
		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[1]);
		tasksSortedForHarmonic.push_back(tasks[2]);
		tasksSortedForHarmonic.push_back(tasks[0]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}

		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}

		
		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[2]);
		tasksSortedForHarmonic.push_back(tasks[0]);
		tasksSortedForHarmonic.push_back(tasks[1]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}

		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}

		
		clearAssignedTasks();
		tasksSortedForHarmonic.clear();
		tasksSortedForHarmonic.push_back(tasks[2]);
		tasksSortedForHarmonic.push_back(tasks[1]);
		tasksSortedForHarmonic.push_back(tasks[0]);
		harmonicSchedule = true;
		for (int j = 0; j < 3; j++)
		{
			task = tasksSortedForHarmonic[j];
			harmonicity = calculateHarmonicity(resource, task);
			if (resource->checkHarmonicUtilizationBound(task, harmonicity))
				resource->assign(task, harmonicity);
			else
			{
				harmonicSchedule = false;
				break;
				
			}

		}
		if (harmonicSchedule)
		{
			resourceUtilizationRateTmp = taskSet->getUtilization() / resource->getCapacity();
			if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
			{
				resourceUtilizationRate = resourceUtilizationRateTmp;
				maxResourceUtilizationRate = resourceUtilizationRateTmp;
				assignedResourceNumber = 1;
			}
		}		
	}


	if (assignedResourceNumber != 0)
		return;






	//two resource
	assignedResourceNumber = 0;
	maxResourceUtilizationRate = 0.0;
	resourceUtilizationRate = 0.0;
	resource = resources[0];
	resource2 = resources[1];
	if (checkTwoResources(resource, resource2, tasks))
	{
		resourceUtilizationRateTmp = taskSet->getUtilization() / (resource->getCapacity() + resource2->getCapacity());
		if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
		{
			resourceUtilizationRate = resourceUtilizationRateTmp;
			maxResourceUtilizationRate = resourceUtilizationRateTmp;
			assignedResourceNumber = 2;
		}
	}

	assignedResourceNumber = 0;
	maxResourceUtilizationRate = 0.0;
	resourceUtilizationRate = 0.0;
	resource = resources[0];
	resource2 = resources[2];
	if (checkTwoResources(resource, resource2, tasks))
	{
		resourceUtilizationRateTmp = taskSet->getUtilization() / (resource->getCapacity() + resource2->getCapacity());
		if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
		{
			resourceUtilizationRate = resourceUtilizationRateTmp;
			maxResourceUtilizationRate = resourceUtilizationRateTmp;
			assignedResourceNumber = 2;
		}
	}

	assignedResourceNumber = 0;
	maxResourceUtilizationRate = 0.0;
	resourceUtilizationRate = 0.0;
	resource = resources[1];
	resource2 = resources[2];
	if (checkTwoResources(resource, resource2, tasks))
	{
		resourceUtilizationRateTmp = taskSet->getUtilization() / (resource->getCapacity() + resource2->getCapacity());
		if (resourceUtilizationRateTmp > maxResourceUtilizationRate)
		{
			resourceUtilizationRate = resourceUtilizationRateTmp;
			maxResourceUtilizationRate = resourceUtilizationRateTmp;
			assignedResourceNumber = 2;
		}
	}
	
	if (assignedResourceNumber != 0)
		return;



	//three resource
	resourceUtilizationRate = taskSet->getUtilization() / resourceSet->getCapacity();
	assignedResourceNumber = 3;	
}

bool OptimalAssignmentAlgorithm::checkTwoResources(Resource * resource1, Resource* resource2, vector<Task*> tasks)
{
	clearAssignedTasks();

	bool schedule = false;

	Task* task1 = tasks[0];
	Task* task2 = tasks[1];
	Task* task3 = tasks[2];
	
	//general utilization bound
	clearAssignedTasks();
	resource1->assign(task1);
	resource2->assign(task2);
	if (resource1->checkUtilizationBound(task3) || resource2->checkUtilizationBound(task3))
		return true;

	clearAssignedTasks();
	resource1->assign(task1);
	resource2->assign(task3);
	if (resource1->checkUtilizationBound(task2) || resource2->checkUtilizationBound(task2))
		return true;
	
	clearAssignedTasks();
	resource1->assign(task2);
	resource2->assign(task1);
	if (resource1->checkUtilizationBound(task3) || resource2->checkUtilizationBound(task3))
		return true;

	clearAssignedTasks();
	resource1->assign(task2);
	resource2->assign(task3);
	if (resource1->checkUtilizationBound(task1) || resource2->checkUtilizationBound(task1))
		return true;

	clearAssignedTasks();
	resource1->assign(task3);
	resource2->assign(task1);
	if (resource1->checkUtilizationBound(task2) || resource2->checkUtilizationBound(task2))
		return true;

	clearAssignedTasks();
	resource1->assign(task3);
	resource2->assign(task2);
	if (resource1->checkUtilizationBound(task1) || resource2->checkUtilizationBound(task1))
		return true;



	//harmonic utilization bound
	double harmonicity = 0.0;
	
	clearAssignedTasks();
	resource1->assign(task1);
	harmonicity = calculateHarmonicity(resource2, task2);
	resource2->assign(task2, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task3);
	if (resource2->checkHarmonicUtilizationBound(task3, harmonicity))
		return true;
	clearAssignedTasks();
	resource1->assign(task1);
	harmonicity = calculateHarmonicity(resource2, task3);
	resource2->assign(task3, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task2);
	if (resource2->checkHarmonicUtilizationBound(task2, harmonicity))
		return true;

	clearAssignedTasks();
	resource2->assign(task1);
	harmonicity = calculateHarmonicity(resource1, task2);
	resource1->assign(task2, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task3);
	if (resource1->checkHarmonicUtilizationBound(task3, harmonicity))
		return true;
	clearAssignedTasks();
	resource2->assign(task1);
	harmonicity = calculateHarmonicity(resource1, task3);
	resource1->assign(task3, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task2);
	if (resource1->checkHarmonicUtilizationBound(task2, harmonicity))
		return true;



	clearAssignedTasks();
	resource1->assign(task2);
	harmonicity = calculateHarmonicity(resource2, task1);
	resource2->assign(task1, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task3);
	if (resource2->checkHarmonicUtilizationBound(task3, harmonicity))
		return true;
	clearAssignedTasks();
	resource1->assign(task2);
	harmonicity = calculateHarmonicity(resource2, task3);
	resource2->assign(task3, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task1);
	if (resource2->checkHarmonicUtilizationBound(task1, harmonicity))
		return true;

	clearAssignedTasks();
	resource2->assign(task2);
	harmonicity = calculateHarmonicity(resource1, task1);
	resource1->assign(task1, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task3);
	if (resource1->checkHarmonicUtilizationBound(task3, harmonicity))
		return true;
	clearAssignedTasks();
	resource2->assign(task2);
	harmonicity = calculateHarmonicity(resource1, task3);
	resource1->assign(task3, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task1);
	if (resource1->checkHarmonicUtilizationBound(task1, harmonicity))
		return true;



	clearAssignedTasks();
	resource1->assign(task3);
	harmonicity = calculateHarmonicity(resource2, task1);
	resource2->assign(task1, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task2);
	if (resource2->checkHarmonicUtilizationBound(task2, harmonicity))
		return true;
	clearAssignedTasks();
	resource1->assign(task3);
	harmonicity = calculateHarmonicity(resource2, task2);
	resource2->assign(task2, harmonicity);
	harmonicity = calculateHarmonicity(resource2, task1);
	if (resource2->checkHarmonicUtilizationBound(task1, harmonicity))
		return true;

	clearAssignedTasks();
	resource2->assign(task3);
	harmonicity = calculateHarmonicity(resource1, task1);
	resource1->assign(task1, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task2);
	if (resource1->checkHarmonicUtilizationBound(task2, harmonicity))
		return true;
	clearAssignedTasks();
	resource2->assign(task3);
	harmonicity = calculateHarmonicity(resource1, task2);
	resource1->assign(task2, harmonicity);
	harmonicity = calculateHarmonicity(resource1, task1);
	if (resource1->checkHarmonicUtilizationBound(task1, harmonicity))
		return true;


}

double OptimalAssignmentAlgorithm::calculateHarmonicity(Resource * resource, Task* task)
{
	int resourcePeriod = resource->getPeriod();
	vector<int> assignedTaskHarmonicPeriods = resource->getAssignedTaskHarmonicPeriods();
	int taskPeriod = task->getPeriod();
	int harmonicPeriod = 0;
	int harmonicFactor = 0; //ratio of task period and resource period, i.e., (int) taskPeriod/resourcePeriod
	int k = 0;
	bool harmonic = true;
	double harmonicity = 0.0;	


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
			harmonicity = (double)harmonicPeriod / taskPeriod;
			break;
		}

		k--;
	}

	return harmonicity;
}