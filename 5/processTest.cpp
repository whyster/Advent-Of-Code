#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

// Given a row to check and a column to check
// Return if there is no seat with said row and column
bool checkIfValid(basic_ifstream<char> &file, int rowCheck, int colCheck){
    string line, row, col;

    // Iterate through every line, return true if the seat is found
    while(getline(file, line)){
        row = line.substr(0, line.find(':'));
        col = line.substr(line.find(':')+1, line.length());

        if(row == to_string(rowCheck) && col == to_string(colCheck)){
            return true;
        }
    }
    return false;
}


int main(int argc, char *argv[]){
    ifstream file("test");
    bool result;
	int pureRow1, pureRow2, pureCol1, pureCol2, pureCol3, g, gSub;
	string line,nextLine, row, col;
    if (file.is_open()) {
        while (getline(file, line)) {
            g = file.tellg();
            // Get the current row and column
            row = line.substr(0, line.find(':'));
            col = line.substr(line.find(':') + 1, line.length());

            // Convert to integers for math
            pureRow1 = stoi(row, nullptr);
            pureCol1 = stoi(col, nullptr);

            // Iterate for second lines now
            while (getline(file, nextLine)) {

                // Get temporary string row and column
                row = nextLine.substr(0, nextLine.find(':'));
                col = nextLine.substr(nextLine.find(':') + 1, nextLine.length());

                // Convert to integers for math
                pureRow2 = stoi(row, nullptr);
                pureCol2 = stoi(col, nullptr);

                // Check if the first row and second row are the same
                if (pureRow1 == pureRow2) {
                    // If the difference of the 2 columns is equal to ±2
                    if (abs(pureCol1 - pureCol2) == 2) {
                        gSub = file.tellg();
                        file.clear(); // Clear file so that check function can iterate through all lines
                        file.seekg(0);

                        // Calculate the middle of the 2 columns
                        pureCol3 = (pureCol1 > pureCol2) ? pureCol2 + 1 : pureCol1 + 1;
                        // Check if there is a row with the middle column
                        result = checkIfValid(file, pureRow1, pureCol3);
                        if (!result) {
                            // If there is no middle column print to stdout
                            cout << pureRow1 << ':' << pureCol3 << endl;
                            break;
                        }

                        // restore original line position
                        file.clear();
                        file.seekg(gSub);

                    }
                }
            }
            file.clear();
            file.seekg(g);
        }
        file.close();
    }
}
