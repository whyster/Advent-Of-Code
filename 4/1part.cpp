#include <iostream>
#include <fstream>
#include <regex>

using namespace std;


int main(int argc, char *argv[]){
    ifstream file("input");
    string line;
    string tests[]={"byr","iyr","eyr","hgt","hcl","ecl","pid"}; //,"cid"
    int subCount;
    int masterCount = 0;
    if (file.is_open()) {
        while (getline(file, line)) {
            subCount = 0;
            for (string test : tests) {
                if (line.find(test) != string::npos) {
                    ++subCount; // check if test even shows up within the input
                }
            }

            masterCount += (subCount == sizeof(tests) / sizeof(tests[0])) ? 1 : 0;

        }
        file.close();
    }
    cout << masterCount << endl;
}