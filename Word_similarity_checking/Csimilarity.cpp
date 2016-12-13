#include "stdafx.h"
#include "Csimilarity.h"
#include <algorithm>

Csimilarity::Csimilarity()
{
}


Csimilarity::~Csimilarity()
{
}


int Csimilarity::ModeOne()
{
	
	
	if (!Init())
	{
		cout << "Init error!";
		return 0;
	}
	
	GetKeywords();

	cout << "input your query" << endl;
	string temp;
	getline(cin, temp);
	while (temp != "")
	{
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (keyword.count(temp)>0)
		{
			P_Q++;
		}
		Q++;
		getline(cin, temp);
	}


	Compute();
	Output();


	return 0;
}


int Csimilarity::ModeTwo()
{
	if (!Init())
	{
		cout << "Init error!";
		return 0;
	}
	GetKeywords();
	string path,temp;
	cout << "input filepath" << endl;
	cin >> path;
	FILE *p=NULL;
	p = fopen(path.c_str(), "r");

	if (p==NULL)
	{
		cout << "open file error "<<endl;
	}
	char buf[24] = { 0 };
	fscanf(p, "%s", buf);
	while (!feof(p))
	{
		
		temp = buf;
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		if (keyword.count(temp) > 0)
		{
			P_Q++;
		}
		Q++;
		fscanf(p, "%s", buf);
	}

	Compute();
	Output();

	return 0;
}


int Csimilarity::ModeThree()
{
	return 0;
}


int Csimilarity::Compute()
{
	result = P_Q / (sqrt(Q) * sqrt(P));
	return 0;
}


bool Csimilarity::Init()
{
	result = 0;
	P = 0;
	Q = 0;
	P_Q = 0;
	keyword.clear();


	return true;
}


bool Csimilarity::Output()
{
	cout << P << " " << Q << " " << P_Q << " " << result << endl;
	return true;
}


bool Csimilarity::GetKeywords()
{
	cout << "input your keyword" << endl;
	string temp;
	getline(cin, temp);
	while (temp != "")
	{
		std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		keyword.insert(temp);
		P++;
		getline(cin, temp);
	}
	return true;
}
