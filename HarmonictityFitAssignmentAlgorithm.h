#include "FirstFitAssignmentAlgorithm.h"

#ifndef   HARMONICITYFITASSIGNMENTALGORITHM_H 
#define   HARMONICITYFITASSIGNMENTALGORITHM_H


class HarmonictityFitAssignmentAlgorithm : public AssignmentAlgorithm
{
public:
	HarmonictityFitAssignmentAlgorithm();
	HarmonictityFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet);
	HarmonictityFitAssignmentAlgorithm(TaskSet * taskSet, ResourceSet * resourceSet, double taskSetHarmonicityWithResourceSet);
	~HarmonictityFitAssignmentAlgorithm();

	void assign();
	Task* searchFitTask(Resource* resource);
	void preProcess();

private:
	void calculateHarmonicity();
	double DCT(Task * task, Resource * resource);	
	void recalculateSelectedResourceHarmonicityAfterAssignTask(Resource * resource);

	vector<int> searchMaxHarmonicity();
	vector<int> searchMaxSelectedResourceHarmonicity(int j); //int j, selected resource index
	void resetHarmonicityI(int i);
	void resetHarmonicityIJ(int i, int j);
	void resetSelectedResourceHarmonicityIJ(int i); //J, selected resource index

	void clearSelectedResourceHarmonicity();


private:
	vector<vector<double>> harmonicity;
	vector<double> selectedResourceHarmonicity;
};

#endif