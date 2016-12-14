#include "stdafx.h"
#include "Csimilarity.h"
#include <algorithm>
#include <windows.h>
#include <map>
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

	HandleFile(path);
	

	Compute();
	Output();

	return 0;
}


int Csimilarity::ModeThree()
{
	if (!Init())
	{
		cout << "Init error!";
		return 0;
	}
	GetKeywords();

	string           path,firstpath, temp;
	WIN32_FIND_DATA  FileInfo;
	map<double, string> FileList;


	//cout << "input filepath" << endl;
	//cin >> path;
	path = "d:\\aaa";
	
	firstpath =path+ "\\*.*";



	HANDLE hFile=FindFirstFile(firstpath.c_str(), &FileInfo);
	if (hFile == INVALID_HANDLE_VALUE)
	{

		cout << "open directory error" << endl;
		return 0;
	}
    
	while (FindNextFile(hFile, &FileInfo))
	{
		if ((FileInfo.cFileName[0] == '.') || (FileInfo.cFileName[0] == '..'))
			continue;
		if (!(FileInfo.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) && CompareFileType(FileInfo.cFileName))
		{
			if (!clear())
			{
				cout << "Clear error!";
				return 0;
			}
			string temp = path + "\\" + FileInfo.cFileName;
			HandleFile(temp);
			Compute();
			FileList.insert(make_pair(result, temp));

		}
	}

	
	

	for (map<double, string>::iterator it = FileList.begin(); it != FileList.end();++it)
	{
		cout << "rank by similarity values" << endl;
		cout << "Filename    " << "value" << endl;
		cout << (*it).second << "     " << (*it).first << endl;
	}

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


int Csimilarity::HandleFile(string &path)
{
	FILE *p = NULL;
	p = fopen(path.c_str(), "r");

	if (p == NULL)
	{
		cout << "open file error " << endl;
	}
	char buf[24] = { 0 };
	string temp;
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
	return 0;
}


bool Csimilarity::CompareFileType(char* filename)
{
	
	char *suffix = strstr(filename, ".txt");
	if (suffix != NULL)
	{
		return true;
	}
	return false;
}


bool Csimilarity::clear()
{

	result = 0;
	Q = 0;
	P_Q = 0;
	return true;
}
