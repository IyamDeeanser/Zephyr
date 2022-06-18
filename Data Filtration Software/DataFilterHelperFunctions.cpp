#include "DataFilter.h"

//Reading .csv file into program
vector <string> readFileIntoVector(string fileName){
	vector <string> resultVector;
	ifstream fileInput;
	string newString;

	fileInput.open(fileName);
	while (!fileInput.eof()){
		fileInput >> newString;
		resultVector.push_back(newString);
	}
	fileInput.close();
	return resultVector;
}

//Writing new .csv file from program
void writeVectorIntoFile(string fileName, vector <string> strVec){
    ofstream file(fileName);
	for(int i = 0 ; i < strVec.size(); i++){
		file << strVec[i] << endl;
	}
	file.close();
}

//HELPERS FOR: vector <string> removeIncompleteData();

//Checks if all pieces of data are there by checking the number of commas 
bool enoughCommas(string s){
    int comCounter = 0;
    for (char c: s){
        if (c == ','){
            comCounter ++;
        }
    }
    if (comCounter == 23){
        return true;
    }
    else return false;
}

//HELPERS FOR: vector <string> removeGarbledData();

//Checks if a character is a digit
bool isDigit(char c){
    if (c >= 48 && c <= 57){return true;}
    else return false;
}

//Checks if a line of data consists of proper numbers (no numbers starting with decimals)
bool properNumbers(string s){
    if (s[0] == '.'){
        return false;
    }
    for (int i = 0; i < s.length(); i++){
        if (s[i] == '.'){
            if (!isDigit(s[i-1])){
                return false;
            }
        }
    }
    return true;
}

//Checks if a string has proper data (no letters or weird characters)
bool properData(string s){
    for (char c: s){
        if (!isDigit(c) && !(c=='.') && !(c == '-') && !(c == ',')){
            return false;
        }
    }
    return true;
}
