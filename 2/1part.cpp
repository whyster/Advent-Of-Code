#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]){
    int min, max, splitPos, count;
    int superCount = 0;
    char check;
    string line, passReq, passTest;
    ifstream file("input");

    if (file.is_open()) {
        while (getline(file, line)) {
            count = 0;
            // Find the pivot to split the line into 2 substrings
            splitPos = line.find(':');

            passReq = line.substr(0, splitPos); // The password requirement
            passTest = line.substr(splitPos + 2, line.length()); // The password to test

            // Find the pivot to find the min max of the password requirement
            splitPos = passReq.find('-');

            min = stoi(passReq.substr(0, splitPos), nullptr);
            max = stoi(passReq.substr(splitPos + 1, passReq.length() - 2), nullptr);

            // Get the character to check for from the requirement
            check = passReq[passReq.length() - 1];

            // Iterate through every char
            for (char passCharacter : passTest)
                count += (passCharacter == check); // Count the number of check characters in the password to test
            superCount += (count >= min && count <= max); // If the number of characters is within the range min max inclusive add 1 to superCount

        }
        file.close();
    }
    // Return the number of valid passwords
    cout << superCount;
}