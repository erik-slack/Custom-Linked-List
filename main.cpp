#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include "List.h"

using namespace std;


int main(int argc, char* argv[])
{
	string cmd_choice = argv[1];
	string save_choice = argv[2];

	List<string>* list1 = new List<string>();
	list1->loadCommands(cmd_choice, save_choice);
	
	delete list1;
	
	//cin.get();
	return 0;
}
