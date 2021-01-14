#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>

using namespace std;

// Given the lower and higher part of a range, iterate through data and return a number representing the halves of the range
int range(int lower, int higher, string data){
	int result,  calc;
	double distance;
	// Iterate through character in data, except the last character
	for(char in : data.substr(0, data.length()-1)) {
	    // Get the range of higher and lower
        distance = higher - lower;

        // The F character represents the lower half
        // The B character represents the upper half
        if (in == 'F') { //F lower
            calc = floor((distance / 2));
            higher = lower + calc;
        } else if (in == 'B') { //B higher
            calc = ceil(distance / 2);
            lower = lower + calc;
        }
    }

	// Return lower or higher depending on character
    result = (data[data.length()-1] == 'F')? lower : higher;
	return result;
}

int main(int argc, char *argv[]){
    ifstream file("input");
	int rowL = 0;
	int rowH = 127;
	int colL = 0;
	int colH = 7;
	int colResult, rowResult, seatResult;
	int seatId = 0;
	string line, row, column, colFixed;
    if (file.is_open()) {
        while (getline(file, line)) {
            row = line.substr(0, line.length() - 3);
            column = line.substr(line.length() - 3, line.length());

            // Range function only works with F and B so this is to convert L to F and R to B
            replace(column.begin(), column.end(), 'L', 'F');
            replace(column.begin(), column.end(), 'R', 'B');

            // Calculate the rows and columns
            rowResult = range(rowL, rowH, row);
            colResult = range(colL, colH, column);

            // A seat id is row*8 + column
            seatResult = (rowResult * 8) + colResult;
            // If the current seatId is higher than the saved seatId, update saved seatId
            seatId = (seatResult > seatId) ? seatResult : seatId;
        }
        file.close();
    }
    cout << "Highest Seat ID -> " << seatId << endl;
}
