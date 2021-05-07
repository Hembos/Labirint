#include <iostream>
#include <string>
#include "Scene.h"

using namespace std;

int getNum()
{
	string nums = "0123456789";
	string str;
	int res = 0;

	cin >> str;

	for (const char& c : str)
	{
		if (nums.find(c) == string::npos)
		{
			throw "Wrong data";
		}
	}

	res = stoi(str);

	return res;
}

int main()
{
	string s;
	
	cout << "Enter help to open the command list" << endl;

	while (1)
	{
		if (!(cin >> s))
		{
			break;
		}
		if (s == "start")
		{
			try
			{
				int cellSize, height, width;
				cout << "Enter cell size: ";
				cellSize = getNum();
				cout << "Enter the height of the maze: ";
				height = getNum();
				cout << "Enter the width of the maze: ";
				width = getNum();

				Scene scene(cellSize, height, width);
				scene.start();
			}
			catch (const char* s)
			{
				cout << s << endl;
			}
		}
		else if (s == "exit")
		{
			break;
		}
		else if (s == "help")
		{
			cout << "Enter start to start working with the maze" << endl;
			cout << "Enter exit to exit the program" << endl;
		}
		else
		{
			cout << "Command not found" << endl;
		}
	}
	
	return 0;
}