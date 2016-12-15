// Word_similarity_checking.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Csimilarity.h"
#include <string>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Csimilarity checking;

	int choose=1;
	
	
	do 
	{
		cout << endl;
		cout << endl;
		cout << "input number 1,2,3 to choose mode" << endl;
		cout << "number 1 : Extra point " << endl;
		cout << "number 2 : Extra Extra point " << endl;
		cout << "number 3 : Extra Extra Extra point " << endl;
		cout << "number 0 : quit" << endl;



		cin >> choose;
		cin.clear();
		cin.sync();
		switch (choose)
		{
		case 1:
			checking.ModeOne();
			break;
		case 2:
			checking.ModeTwo();
			break;
		case 3:
			checking.ModeThree();
			break;
		default:
			cout << "input error" << endl;
			break;
		}
	} while (choose!=0);


	return 0;
}

