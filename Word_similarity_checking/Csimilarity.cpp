#include "stdafx.h"
#include "Csimilarity.h"
#include <algorithm>
#include <windows.h>
#include <map>
#include <vector>
#include <utility>

typedef pair<string, double> PAIR;

//bool cmp_by_value(const PAIR& lhs, const PAIR& rhs) {
//	return lhs.second < rhs.second;
//}
struct CmpByValue {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second > rhs.second;
	}
};
Csimilarity::Csimilarity() :P(0), Q(0), P_Q(0), result(0)
{
	keyword.clear();
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

	cout << "Enter set of keywords for the query." << endl;
	cout << "Enter keywords, one per line. Enter a blank line when finished." << endl;
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
	cout << "Enter path of the document." << endl;
	cout << "Full path end with suffix txt ,i.e d:\\\\test.txt" << endl;
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

	string                 path,firstpath, temp;
	WIN32_FIND_DATA        FileInfo;
	map<string, double>    FileList;


	cout << "Enter path of the dirctory." << endl;
	cout << "Full path . i.e d:\\\\test" << endl;
	cin >> path;
	firstpath =path+ "\\*.*";


	HANDLE hFile=FindFirstFile(firstpath.c_str(), &FileInfo);
	if (hFile == INVALID_HANDLE_VALUE)
	{

		cout << "open directory error" << endl;
		return 0;
	}
	bool bfind = false;
	do 
	{
		bfind = FindNextFile(hFile, &FileInfo);

		if ((FileInfo.cFileName[0] == '.')  || 
			(FileInfo.cFileName[0] == '..') ||
			(FileInfo.cFileName == ""))
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
			FileList.insert(make_pair(FileInfo.cFileName, result));

		}
	} while (bfind);


	vector<PAIR> vfilelist(FileList.begin(), FileList.end());
	sort(vfilelist.begin(), vfilelist.end(), CmpByValue());
	cout << "rank by similarity values" << endl;
	cout << "Filename           " << "value" << endl;
	for (size_t i = 0; i < vfilelist.size(); ++i)
	{
		
		cout << vfilelist[i].first << "     " << vfilelist[i].second << endl;
	}


	//for (map<double, string>::const_reverse_iterator it = FileList.rbegin(); it != FileList.rend(); ++it)
	//{
	//	
	//	cout << "Filename             " << "value" << endl;
	//	cout << (*it).second << "     " << (*it).first << endl;
	//}

	return 0;
}


int Csimilarity::Compute()
{
	result = P_Q / (sqrt(Q) * sqrt(P));
	return 0;
}


bool Csimilarity::Init()
{
	P = 0;
	Q = 0;
	P_Q = 0;
	result = 0;
	keyword.clear();

	return true;
}


bool Csimilarity::Output()
{
	cout << "The similarity is  "<<result << endl;
	return true;
}


bool Csimilarity::GetKeywords()
{
	cout << "Enter set of keywords for the document." << endl;
	cout << "Enter keywords, one per line. Enter a blank line when finished." << endl;
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
