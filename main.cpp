#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <Windows.h>
#include <math.h>
#include <direct.h>

#include "HarmonictityFitAssignmentAlgorithm.h"
#include "OptimalAssignmentAlgorithm.h"
#include "MyMath.h"

using namespace std;

void testBaseWithFixedResourcePeriod(int resourceCount, int loopCount, string folder, string testName, string variable, int index, int taskNumber, int maxTaskPeriod, int resourceNumber, int minResourcePeriod, int maxResourcePeriod, double resourceCapacity, double resourceCapacityBaseRatio, vector<double> harmonicities);
void testBase(bool tHr, int resourceCount, int loopCount, string folder, string testName, string variable, int index, int taskNumber, int minTaskPeriod, int maxTaskPeriod, int resourceNumber, int minResourcePeriod, int maxResourcePeriod, double resourceCapacity, double resourceCapacityBaseRatio, bool optimal, bool ratio);

void test2_50_05(string folder);
void test4(string folder);
void test5(string folder);
void test6_Optimal(string folder);

void test();



int main()
{	
	//test();	

	string folder("C://test//");
	
	//testtest2_50_05(folder);
	test4(folder);
	//test5(folder);
	//test6_Optimal(folder);
	
	cout << "**********************************************************************" << endl;
	cout << "test1 done    test1 done    test1 done    test1 done    test1 done" << endl;
	cout << "**********************************************************************" << endl;
	
	
	cout << "======================================================================" << endl;
	cout << "**********************************************************************" << endl;
	cout << "ALL DONE    ALL DONE    ALL DONE    ALL DONE    ALL DONE    ALL DONE" << endl;
	cout << "**********************************************************************" << endl;
	cout << "======================================================================" << endl;

	system("pause");
	return 0;
}

void test()
{
	vector<Task*> tasks;
	vector<Resource*> resources;	

	tasks.push_back(new Task(43, 5.37208, 0));
	tasks.push_back(new Task(44, 5.94485, 1));
	tasks.push_back(new Task(43, 5.15764, 2));
	/*
	tasks.push_back(new Task(11, 6.094, 2));
	tasks.push_back(new Task(16, 9.022, 3));
	tasks.push_back(new Task(10, 6.394, 4));
	tasks.push_back(new Task(15, 8.296, 5));
	tasks.push_back(new Task(12, 6.825, 6));
	tasks.push_back(new Task(11, 6.112, 7));
	tasks.push_back(new Task(11, 6.033, 8));
	tasks.push_back(new Task(20, 15.527, 9));
	*/

	resources.push_back(new Resource(19, 15.2384, 0));
	resources.push_back(new Resource(12, 8.81601, 1));
	resources.push_back(new Resource(19, 7.85291, 2));
	/*
	resources.push_back(new Resource(5, 5, 1));
	resources.push_back(new Resource(2, 2, 2));
	resources.push_back(new Resource(4, 4, 3));
	resources.push_back(new Resource(9, 9, 4));
	resources.push_back(new Resource(7, 7, 5));
	resources.push_back(new Resource(8, 8, 6));
	resources.push_back(new Resource(9, 9, 7));
	resources.push_back(new Resource(9, 9, 8));
	resources.push_back(new Resource(3, 3, 9));
	*/

	TaskSet* taskSet = new TaskSet(tasks);
	ResourceSet* resourceSet = new ResourceSet(resources, taskSet);


	AssignmentAlgorithm* bestFit = new BestFitAssignmentAlgorithm(taskSet, resourceSet);
	AssignmentAlgorithm* worstFit = new WorstFitAssignmentAlgorithm(taskSet, resourceSet);
	AssignmentAlgorithm* firstFit = new FirstFitAssignmentAlgorithm(taskSet, resourceSet);
	AssignmentAlgorithm* harmonicityFit = new HarmonictityFitAssignmentAlgorithm(taskSet, resourceSet);
	AssignmentAlgorithm* optimalSolution = new OptimalAssignmentAlgorithm(taskSet, resourceSet);

	bestFit->assign();
	bestFit->calculateResourceUtilizationRate();

	worstFit->assign();
	worstFit->calculateResourceUtilizationRate();

	firstFit->assign();
	firstFit->calculateResourceUtilizationRate();

	harmonicityFit->assign();
	harmonicityFit->calculateResourceUtilizationRate();

	optimalSolution->assign();
	//optimalSolution->calculateResourceUtilizationRate();

	delete bestFit;
	delete worstFit;
	delete firstFit;
	delete harmonicityFit;
	delete optimalSolution;
	delete taskSet;
	delete resourceSet;
}



void outputTaskData(ofstream& taskFile, TaskSet* taskSet, int index)
{
	Task * task = NULL;
	
	taskFile << "taskset" << index << "    " << "N" << " " << taskSet->getTaskNumber() << "    " << "U" << " " << taskSet->getUtilization() << "\n\n";
	taskFile << "index" << "    " << "period" << "    " << "executionTime" << "    " << "utilization" << "\n";
	
	for (int i = 0; i < taskSet->getTaskNumber(); i++)
	{
		task = taskSet->getTasks()[i];
		taskFile << i+1 << "    " << task->getPeriod() << "    " << task->getExecutionTime() << "    " << task->getUtilization() << "\n";
	}	

	taskFile << "\n\n";
}

void outputResourceData(ofstream& resourceFile, ResourceSet* resourceSet, int index)
{	
	Resource * resource = NULL;
	resourceFile << "resourceset" << index << "    " << "N" << " " << resourceSet->getResourceNumber() << "    " << "C" << " " << resourceSet->getCapacity() << "\n\n";
	resourceFile << "index" << "    " << "period" << "    " << "allocationTime" << "    " << "capacity" << "    " << "tasks" << "\n";
	
	//vector<Task*> assignedTasks;
	for (int i = 0; i < resourceSet->getResourceNumber(); i++)
	{
		resource = resourceSet->getResources()[i];
		resourceFile << i + 1 << "    " << resource->getPeriod() << "    " << resource->getAllocationTime() << "    " << resource->getCapacity() << "\n";

		/*
		assignedTasks = resource->getAssignedTasks();
		for (int j = 0; j < assignedTasks.size(); j++)
		{
			resourceFile << assignedTasks[j]->getIndex();
			if (j != assignedTasks.size()-1)
				resourceFile << ",";
		}

		resourceFile << "\n";
		*/
	}

	resourceFile << "\n\n";
}

void outputResultData(ofstream& resultFile, TaskSet* taskSet, AssignmentAlgorithm* bestFit, AssignmentAlgorithm* worstFit, AssignmentAlgorithm* firstFit, AssignmentAlgorithm* harmonicityFit, AssignmentAlgorithm* optimalSolution, int index, bool outputTitle)
{
	if (outputTitle)
		resultFile << "index" << "    " << "BFU" << "    " << "BFN" << "    " << "WFU" << "    " << "WFN" << "    " << "FFU" << "    " << "FFN" << "    " << "HU" << "    " << "HN" << "    " << "tHr" << "    " << "UT" << "    " << "OPTU" << "    " << "OPTN" << "\n";
	else
	{
		resultFile << index << "    ";
		resultFile << bestFit->getResourceUtilizationRate() << "    ";
		resultFile << bestFit->getAssignedResourceNumber() << "    ";

		resultFile << worstFit->getResourceUtilizationRate() << "    ";
		resultFile << worstFit->getAssignedResourceNumber() << "    ";

		resultFile << firstFit->getResourceUtilizationRate() << "    ";
		resultFile << firstFit->getAssignedResourceNumber() << "    ";

		resultFile << harmonicityFit->getResourceUtilizationRate() << "    ";
		resultFile << harmonicityFit->getAssignedResourceNumber() << "    ";
		resultFile << harmonicityFit->getTaskSetHarmonicityWithResourceSet() << "    ";

		resultFile << taskSet->getUtilization() << "    ";

		resultFile << optimalSolution->getResourceUtilizationRate() << "    ";
		resultFile << optimalSolution->getAssignedResourceNumber() << "\n";
	}	
}

string getTaskFilePath(string folder, string testName, int index)
{
	stringstream ss;
	ss << index;
	string indexStr = ss.str();

	string str1("-task-");
	string str2(".txt");

	string filePath = folder;
	filePath = filePath + testName;
	filePath = filePath + str1;
	filePath = filePath + indexStr;
	filePath = filePath + str2;

	return filePath;
}

string getResourceFilePath(string folder, string testName, int index)
{
	stringstream ss;
	ss << index;
	string indexStr = ss.str();

	string str1("-resource-");
	string str2(".txt");

	string filePath = folder;
	filePath = filePath + testName;
	filePath = filePath + str1;
	filePath = filePath + indexStr;
	filePath = filePath + str2;

	return filePath;
}

string getResultFilePath(string folder, string testName, int index)
{
	stringstream ss;
	ss << index;
	string indexStr = ss.str();

	string str1("-result-");
	string str2(".txt");

	string filePath = folder;
	filePath = filePath + testName;
	filePath = filePath + str1;
	filePath = filePath + indexStr;
	filePath = filePath + str2;

	return filePath;
}

void testBase(bool tHr, int resourceCount, int loopCount, string folder, string testName, string variable, int index, int taskNumber, int minTaskPeriod, int maxTaskPeriod, int resourceNumber, int minResourcePeriod, int maxResourcePeriod, double resourceCapacity, double resourceCapacityBaseRatio, bool optimal, bool ratio)
{
	string taskFilePath = getTaskFilePath(folder, testName, index);
	string resourceFilePath = getResourceFilePath(folder, testName, index);
	string resultFilePath = getResultFilePath(folder, testName, index);

	
	ofstream taskFile;
	taskFile.open(taskFilePath, std::ofstream::app);
	ofstream resourceFile;
	resourceFile.open(resourceFilePath, std::ofstream::app);
	ofstream resultFile;
	resultFile.open(resultFilePath, std::ofstream::app);

	outputResultData(resultFile, NULL, NULL, NULL, NULL, NULL, NULL, 0, true);
	taskFile.close();
	resourceFile.close();
	resultFile.close();

	int i = 0;
	int j = 0;
	int resourceTryCount = 100;
	int taskTryCount = 100;
	ResourceSet* resourceSet = NULL;
	TaskSet* taskSet = NULL;
	AssignmentAlgorithm* bestFit = NULL;
	AssignmentAlgorithm* worstFit = NULL;
	AssignmentAlgorithm* firstFit = NULL;
	AssignmentAlgorithm* harmonicityFit = NULL;
	AssignmentAlgorithm* optimalSolution = NULL;
	while (j < resourceCount)
	{
		cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << endl;

		resourceTryCount = 100;
		while (resourceTryCount > 0)
		{
			if (ratio)
				resourceSet = new ResourceSet(resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, false, ratio);
			else
				resourceSet = new ResourceSet(resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacityBaseRatio);

			if (resourceSet->getResourceNumber() == 0)
			{
				resourceTryCount--;
				cout << "        resourceSet " << 100 - resourceTryCount << " try fail" << endl;
				continue;
			}
			else
			{
				cout << "    " << "resourceSet done" << endl;
				break;
			}
		}

		resourceFile.open(resourceFilePath, std::ofstream::app);
		outputResourceData(resourceFile, resourceSet, j + 1);
		resourceFile.close();


		if (resourceSet->getResourceNumber() != 0)
		{
			while (i < loopCount)
			{
				cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << endl;

				taskTryCount = 100;
				while (taskTryCount > 0)
				{
					taskSet = new TaskSet(taskNumber, minTaskPeriod, maxTaskPeriod, resourceSet);

					if (taskSet->getTaskNumber() == 0)
					{
						taskTryCount--;
						cout << "        taskSet " << 100 - taskTryCount << " try fail" << endl;
						continue;
					}
					else
					{
						cout << "    " << "taskSet done" << endl;
						break;
					}
				}

				taskFile.open(taskFilePath, std::ofstream::app);
				outputTaskData(taskFile, taskSet, i + 1);	
				taskFile.close();
				

				if (taskSet->getTaskNumber() != 0)
				{
					bestFit = new BestFitAssignmentAlgorithm(taskSet, resourceSet);
					worstFit = new WorstFitAssignmentAlgorithm(taskSet, resourceSet);
					firstFit = new FirstFitAssignmentAlgorithm(taskSet, resourceSet);
					harmonicityFit = new HarmonictityFitAssignmentAlgorithm(taskSet, resourceSet);
					optimalSolution = new OptimalAssignmentAlgorithm(taskSet, resourceSet);

					bestFit->assign();
					bestFit->calculateResourceUtilizationRate();
					cout << "    " << "bestFit done" << endl;

					worstFit->assign();
					worstFit->calculateResourceUtilizationRate();
					cout << "    " << "worstFit done" << endl;

					firstFit->assign();
					firstFit->calculateResourceUtilizationRate();
					cout << "    " << "firstFit done" << endl;

					harmonicityFit->assign();
					harmonicityFit->calculateResourceUtilizationRate();
					cout << "    " << "harmonicityFit done" << endl;

					if (optimal)
					{
						optimalSolution->assign();
						//optimalSolution->calculateResourceUtilizationRate();
						cout << "    " << "optimalSolution done" << endl;
					}					

					resultFile.open(resultFilePath, std::ofstream::app);
					outputResultData(resultFile, taskSet, bestFit, worstFit, firstFit, harmonicityFit, optimalSolution, i + 1, false);
					resultFile.close();

					delete bestFit;
					delete worstFit;
					delete firstFit;
					delete harmonicityFit;
					delete optimalSolution;
					bestFit = NULL;
					worstFit = NULL;
					firstFit = NULL;
					harmonicityFit = NULL;
					optimalSolution = NULL;
				}

				delete taskSet;
				taskSet = NULL;

				
				cout << "----------------------------------------------------------------------" << endl;
				cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << "    " << "done" << endl;
				cout << "----------------------------------------------------------------------" << endl;	
				i++;
			}
		}		


		delete resourceSet;
		resourceSet = NULL;

		
		cout << "======================================================================" << endl;
		cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "done" << endl;
		cout << "======================================================================" << endl;
		j++;
	}
	

	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << testName << "    " << variable << " " << index << "    " << "done" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << '\a' << '\a' << '\a';
}

void testBaseWithFixedResourcePeriod(int resourceCount, int loopCount, string folder, string testName, string variable, int index, int taskNumber, int maxTaskPeriod, int resourceNumber, int minResourcePeriod, int maxResourcePeriod, double resourceCapacity, double resourceCapacityBaseRatio, vector<double> harmonicities)
{
	string taskFilePath = getTaskFilePath(folder, testName, index);
	string resourceFilePath = getResourceFilePath(folder, testName, index);
	string resultFilePath = getResultFilePath(folder, testName, index);

	ofstream taskFile;
	taskFile.open(taskFilePath, std::ofstream::app);
	ofstream resourceFile;
	resourceFile.open(resourceFilePath, std::ofstream::app);
	ofstream resultFile;
	resultFile.open(resultFilePath, std::ofstream::app);

	outputResultData(resultFile, NULL, NULL, NULL, NULL, NULL, NULL, 0, true);
	taskFile.close();
	resourceFile.close();
	resultFile.close();

	int i = 0;
	int j = 0;
	int resourceTryCount = 100;
	int taskTryCount = 100;
	vector<double> taskUtilizations;
	int minTaskPeriodActual = maxTaskPeriod;
	ResourceSet* resourceSet = NULL;
	TaskSet* taskSet = NULL;
	AssignmentAlgorithm* bestFit = NULL;
	AssignmentAlgorithm* worstFit = NULL;
	AssignmentAlgorithm* firstFit = NULL;
	AssignmentAlgorithm* harmonicityFit = NULL;
	AssignmentAlgorithm* optimalSolution = NULL;
	while (j < resourceCount)
	{
		i = 0;
		cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << endl;

		resourceTryCount = 100;
		while (resourceTryCount > 0)
		{
			resourceSet = new ResourceSet(resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, true, true);

			if (resourceSet->getResourceNumber() == 0)
			{
				resourceTryCount--;
				cout << "        resourceSet " << 100 - resourceTryCount << " try fail" << endl;
				continue;
			}
			else
			{
				cout << "    " << "resourceSet done" << endl;
				break;
			}
		}
		

		resourceFile.open(resourceFilePath, std::ofstream::app);
		outputResourceData(resourceFile, resourceSet, j + 1);
		resourceFile.close();


		if (resourceSet->getResourceNumber() != 0)
		{
			while (i < loopCount)
			{
				cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << endl;

				taskUtilizations.clear();
				minTaskPeriodActual = maxTaskPeriod;
				for (int k = 0; k < harmonicities.size(); k++)
				{
					if (taskUtilizations.size() == 0)
					{
						taskTryCount = 100;
						while (taskTryCount > 0)
						{
							taskSet = new TaskSet(taskNumber, maxTaskPeriod, harmonicities[k], resourceSet);

							if (taskSet->getTaskNumber() == 0)
							{
								taskTryCount--;
								cout << "        taskSet " << 100 - taskTryCount << " try fail" << endl;
								continue;
							}
							else
							{
								minTaskPeriodActual = taskSet->getMinPeriod();
								for (int t = 0; t < taskNumber; t++)
									taskUtilizations.push_back(taskSet->getTasks()[t]->getUtilization());

								cout << "    " << "taskSet done" << endl;
								break;
							}
						}
					}
					else
					{
						taskTryCount = 100;
						while (taskTryCount > 0)
						{
							taskSet = new TaskSet(taskNumber, minTaskPeriodActual, maxTaskPeriod, taskUtilizations, harmonicities[k], resourceSet);

							if (taskSet->getTaskNumber() == 0)
							{
								taskTryCount--;
								cout << "        taskSet " << 100 - taskTryCount << " try fail" << endl;
								continue;
							}
							else
							{
								cout << "    " << "taskSet done" << endl;
								break;
							}
						}
					}

					taskFile.open(taskFilePath, std::ofstream::app);
					outputTaskData(taskFile, taskSet, (j + 1) * 10 + (i + 1));
					taskFile.close();
					


					if (taskSet->getTaskNumber() != 0)
					{
						cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << "    " << "harmonicityIndex " << k << endl;

						bestFit = new BestFitAssignmentAlgorithm(taskSet, resourceSet);
						worstFit = new WorstFitAssignmentAlgorithm(taskSet, resourceSet);
						firstFit = new FirstFitAssignmentAlgorithm(taskSet, resourceSet);
						harmonicityFit = new HarmonictityFitAssignmentAlgorithm(taskSet, resourceSet, harmonicities[k]);
						optimalSolution = new OptimalAssignmentAlgorithm(taskSet, resourceSet);


						bestFit->assign();
						bestFit->calculateResourceUtilizationRate();
						cout << "    " << "bestFit done" << endl;

						worstFit->assign();
						worstFit->calculateResourceUtilizationRate();
						cout << "    " << "worstFit done" << endl;

						firstFit->assign();
						firstFit->calculateResourceUtilizationRate();
						cout << "    " << "firstFit done" << endl;

						harmonicityFit->assign();
						harmonicityFit->calculateResourceUtilizationRate();
						cout << "    " << "harmonicityFit done" << endl;

						resultFile.open(resultFilePath, std::ofstream::app);
						outputResultData(resultFile, taskSet, bestFit, worstFit, firstFit, harmonicityFit, optimalSolution, (j + 1) * 10 + (i + 1), false);
						resultFile.close();
						

						delete bestFit;
						delete worstFit;
						delete firstFit;
						delete harmonicityFit;
						delete optimalSolution;
						bestFit = NULL;
						worstFit = NULL;
						firstFit = NULL;
						harmonicityFit = NULL;
						optimalSolution = NULL;

						cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
						cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << "    " << "harmonicityIndex " << k << "    " << "done" << endl;
						cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
					}

					delete taskSet;
					taskSet = NULL;
				}

				cout << "----------------------------------------------------------------------" << endl;
				cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "loop" << " " << i << "    " << "done" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				i++;
			}
		}


		delete resourceSet;
		resourceSet = NULL;


		cout << "======================================================================" << endl;
		cout << testName << "    " << variable << " " << index << "    " << "resourceCount " << j << "    " << "done" << endl;
		cout << "======================================================================" << endl;
		j++;
	}



	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << testName << "    " << variable << " " << index << "    " << "done" << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << '\a' << '\a' << '\a';
}



void test2_50_05(string folder)
{
	string str("test2_50_05//");
	folder = folder + str;
	_mkdir(folder.c_str());

	int taskNumber = 20; //
	int maxTaskPeriod = 50;
	int minTaskPeriod = 20;
	//double eachTaskUtilization = 0.3;
	//double taskUtilization = eachTaskUtilization * taskNumber;
	//double taskUtilizationBaseRatio = 0.9;

	int resourceNumber = 20;
	int maxResourcePeriod = 20;
	int minResourcePeriod = 1;
	double eachResourceCapacity = 0.65;
	double resourceCapacity = eachResourceCapacity * resourceNumber;
	double resourceCapacityBaseRatio = 0.5;

	//true: recourseCapacity range is [eachResourceCapacity*resourceCapacityBaseRatio, 1.0]
	//false: recourseCapacity range is [resourceCapacityBaseRatio, 1.0]
	bool ratio = true;

	//int i = 14;
	int loopCount = 100; // loopCount = 100;
	int resourceCount = 200; // resourceCount = 10
	//testBase(false, 1, loopCount, folder, "test2_100_05", "resourceCount", 1, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio);


	vector<thread> threads;
	for (int i = 1; i <= resourceCount; i++)
		threads.push_back(thread(testBase, false, 200 / resourceCount, loopCount, folder, "test2_50_05", "resourceCount", i, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, false, ratio));

	for (int i = 0; i < threads.size(); i++)
		threads[i].join();

	

}


void test5(string folder)
{
	string str("test5//");
	folder = folder + str;
	_mkdir(folder.c_str());

	int taskNumber = 20; //
	int maxTaskPeriod = 50;
	int minTaskPeriod = 20;
	//double eachTaskUtilization = 0.3;
	//double taskUtilization = eachTaskUtilization * taskNumber;
	//double taskUtilizationBaseRatio = 0.9;

	int resourceNumber = 20;
	int maxResourcePeriod = 20;
	int minResourcePeriod = 1;
	double eachResourceCapacity = 0.65;
	double resourceCapacity = eachResourceCapacity * resourceNumber;
	double resourceCapacityBaseRatio = 0.8;

	//true: recourseCapacity range is [eachResourceCapacity*resourceCapacityBaseRatio, 1.0]
	//false: recourseCapacity range is [resourceCapacityBaseRatio, 1.0]
	bool ratio = false;

	//int i = 14;
	int loopCount = 100; // loopCount = 100;
	int resourceCount = 200; // resourceCount = 10
	//testBase(false, 200 / resourceCount, loopCount, folder, "test5", "resourceCount", 1, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, false, ratio);

	vector<thread> threads;
	for (int i = 1; i <= resourceCount; i++)
		threads.push_back(thread(testBase, false, 200 / resourceCount, loopCount, folder, "test5", "resourceCount", i, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, false, ratio));

	for (int i = 0; i < threads.size(); i++)
		threads[i].join();

	
}


void test4(string folder)
{
	string str("test4//");
	folder = folder + str;
	_mkdir(folder.c_str());

	int taskNumber = 20; //
	int maxTaskPeriod = 200000000; //maxTaskPeriod = 500
	int minTaskPeriod = 11639628; //minTaskPeriod = 20
	int fixedTaskPeriod = 20;
	//double eachTaskUtilization = 0.3;
	//double taskUtilization = eachTaskUtilization * taskNumber;
	//double taskUtilizationBaseRatio = 0.9;

	int resourceNumber = 20;
	int maxResourcePeriod = 11639628; //maxResourcePeriod = 20
	int minResourcePeriod = 11639628; //minResourcePeriod = 2
	double eachResourceCapacity = 0.65;
	double resourceCapacity = eachResourceCapacity * resourceNumber;
	double resourceCapacityBaseRatio = 0.72;

	double harmonicityBase = 0.7;
	double harmonicityStep = 0.05;
	vector<double> harmonicities;
	harmonicities.push_back(0.65);
	harmonicities.push_back(0.6);
	harmonicities.push_back(0.55);
	for (int i = 0; i < 7; i++)
		harmonicities.push_back(harmonicityBase + i*harmonicityStep);


	int loopCount = 10; // loopCount = 100;
	int resourceCount = 100; // resourceCount = 10
	//testBaseWithFixedResourcePeriod(10, 2, folder, "test4", "resourceCount", 1, taskNumber, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, harmonicities);



	vector<thread> threads;
	for (int i = 1; i <= resourceCount; i++)
	{
		threads.push_back(thread(testBaseWithFixedResourcePeriod, 10, loopCount, folder, "test4", "resourceCount", i, taskNumber, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, harmonicities));

	}

	for (int i = 0; i < threads.size(); i++)
		threads[i].join();

	

}



void test6_Optimal(string folder)
{
	string str("test6_Optimal//");
	folder = folder + str;
	_mkdir(folder.c_str());

	int taskNumber = 3; //
	int maxTaskPeriod = 50;
	int minTaskPeriod = 20;
	//double eachTaskUtilization = 0.3;
	//double taskUtilization = eachTaskUtilization * taskNumber;
	//double taskUtilizationBaseRatio = 0.9;

	int resourceNumber = 3;
	int maxResourcePeriod = 20;
	int minResourcePeriod = 1;
	double eachResourceCapacity = 0.65;
	double resourceCapacity = eachResourceCapacity * resourceNumber;
	double resourceCapacityBaseRatio = 0.5;

	//true: recourseCapacity range is [eachResourceCapacity*resourceCapacityBaseRatio, 1.0]
	//false: recourseCapacity range is [resourceCapacityBaseRatio, 1.0]
	bool ratio = true; 

	//int i = 14;
	int loopCount = 100; // loopCount = 100;
	int resourceCount = 200; // resourceCount = 200
	//testBase(false, 1, loopCount, folder, "test6_Optimal", "resourceCount", 1, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, true, ratio);


	vector<thread> threads;
	for (int i = 1; i <= resourceCount; i++)
		threads.push_back(thread(testBase, false, 200 / resourceCount, loopCount, folder, "test6_Optimal", "resourceCount", i, taskNumber, minTaskPeriod, maxTaskPeriod, resourceNumber, minResourcePeriod, maxResourcePeriod, resourceCapacity, resourceCapacityBaseRatio, true, ratio));

	for (int i = 0; i < threads.size(); i++)
		threads[i].join();

	

}