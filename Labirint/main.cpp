#include <iostream>
#include <string>
#include "Scene.h"

using namespace std;

int main()
{
	string s;
	
	while (1)
	{
		cout << "Enter help to open the command list" << endl;
		cin >> s;
		if (s == "start")
		{
			int cellSize, height, weight;
			cout << "Enter cell size: ";
			cin >> cellSize;
			cout << "Enter the height of the maze: ";
			cin >> height;
			cout << "Enter the width of the maze: ";
			cin >> weight;

			Scene scene(cellSize, height, weight);
			scene.start();
		}
		else if (s == "exit")
		{
			break;
		}
		else if (s == "help")
		{
			
		}
		else if (s == "Examples")
		{
			int example;
			cin >> example;
			switch (example)
			{

			default:
				break;
			}
		}
	}
	
	return 0;
}