#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include<stdio.h>
#include<ctype.h>

using namespace std;

void filterData (string fileName);
vector <string> removeIncompleteData(vector <string> strVec);
vector <string> removeGarbledData(vector <string> strVec);
