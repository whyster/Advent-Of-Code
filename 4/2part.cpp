#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

bool test(string line, int i, string tests[]){
    string test = tests[i];
    string eyes[] = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    string sub = "";
    string stuff;
    int digits;
    bool check = false;
    switch (i) {
        case 0: //amb 4 Digits between 1920 and 2002 inclusive
            // Get the important data for specific test
            sub = line.substr(line.find(test)+4, 4);

            // Check if data isn't empty
            if (!sub.empty()){

                digits = stoi(sub, nullptr);

                // Check if digits is between 1920 and 2002 inclusive
                check = (digits >= 1920 && digits <= 2002);
                return check;
            }
            break;
        case 1: //blu 4 Digits between 2010 and 2020 inclusive
            sub = line.substr(line.find(test)+4, 4);
            if (!sub.empty()){
                digits = stoi(sub, nullptr);

                // Check if digits is between 2010 and 2020 inclusive
                check = (digits >= 2010 && digits <= 2020);
                return check;
            }
            break;
        case 2: //brn 4 Digits between 2020 and 2030 inclusive
            sub = line.substr(line.find(test)+4, 4);
            if (!sub.empty()){
                digits = stoi(sub, nullptr);

                // Check if digits between 2020 and 2030 inclusive
                check = (digits >= 2020 && digits <= 2030);
                return check;
            }
            break;
        case 3: //gry Number followed by cm or in
            sub = line.substr(line.find(test)+4, line.length()-(line.find(test)+4));
            sub = sub.substr(0, sub.find(' ')); // Get important data

            // Check if digits followed by cm/in can be found in important data
            check = (regex_match(sub, regex("(?:[0-9]+)(?:cm|in)")));
            if (check) {
                // Get temporary substring containing the numbers
                stuff = sub.substr(0, sub.length() - 2);

                // Set digits to the numbers
                digits = stoi(stuff, nullptr);

                // Get either "cm" or "in"
                stuff = sub.substr(sub.length() - 2, 2);

                if (stuff == "cm") {
                    // If its in centimeters check if digits is between 150 and 193 inclusive
                    check = (digits >= 150 && digits <= 193);
                } else if (stuff == "in") {
                    // If its in inches check if digits is between 59 and 76 inclusive
                    check = (digits >= 59 && digits <= 76);
                }
            }
            return check;
            break;

        case 4: //grn A # followed by 6 hex characters
            // Get important data
            sub = line.substr(line.find(test)+4, line.length()-(line.find(test)+4));
            sub = sub.substr(0, sub.find(' '));

            // Check if important data can find a # followed by 6 hexadecimal digits
            check = (regex_match(sub, regex("(?:#)(?:[a-fA-F0-9]{6})")));
            return check;
            break;
        case 5: //hzl Exactly one of: amb, blu, brn, gry, grn, hzl, oth.
            // Get important data
            sub = line.substr(line.find(test)+4, line.length()-(line.find(test)+4));
            sub = sub.substr(0, sub.find(' '));

            // Compare the input data with the list of valid eye colors
            for(string eye : eyes){
                if (sub.find(eye) != string::npos) {
                    check = true;
                    break; // Break if eye matches input
                }
            }
            return check;
            break;
        case 6: //oth A nine digit number, including leading zeroes
            // Get important data
            sub = line.substr(line.find(test)+4, line.length()-(line.find(test)+4));
            sub = sub.substr(0, sub.find(' '));
            // Check if input matches 9 numbers
            check = (regex_match(sub, regex("(?:[0-9]{9})")));
            return check;
            break;
        default:
            return false;
        
    }
}

int main(int argc, char *argv[]){
    ifstream file("input");
    string line;
    string tests[]={"byr","iyr","eyr","hgt","hcl","ecl","pid"}; //,"cid"
    int i = 0;
    int subCount, masterCount;
    masterCount = 0;

    if (file.is_open()) {
        while (getline(file, line)) {
            subCount = 0;
            // Compare line with all 7 tests
            for (int i = 0; i < 7; ++i) {
                if (line.find(tests[i]) != string::npos) {
                    if (test(line, i, tests)) {
                        ++subCount;
                    }
                }
            }
            masterCount += (subCount == sizeof(tests) / sizeof(tests[0])) ? 1 : 0;
        }
        file.close();
    }
    cout << masterCount << endl;
}