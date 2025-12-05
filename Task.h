#ifndef   TASK_H 
#define   TASK_H 

class Task
{
public:
	Task();
	virtual ~Task();
	Task(int period, double executionTime, int index);
	
	void markAssigned();
	void clearAssignedTasks();

	int getPeriod();
	double getUtilization();
	double getExecutionTime();
	int getIndex();
	

private:
	int period;
	double executionTime;
	double utilization;
	bool assigned;
	int index;
};

#endif