#pragma once
#include <set>
#include <string>
using namespace std;
class Csimilarity
{
private:
	set<string> keyword;
	double result;
	double P;
	double Q;
	double P_Q;

public:
	Csimilarity();
	~Csimilarity();
	int ModeOne();
	int ModeTwo();
	int ModeThree();
	int Compute();
	bool Init();
	bool Output();
	bool GetKeywords();
	int HandleFile(string &path);
	bool CompareFileType(char* filename);
	bool clear();
};

