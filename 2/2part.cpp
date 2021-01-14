#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, char *argv[]){
    int pos1, pos2, splitPos, count;
    int superCount = 0;
    char check;
    string line, passReq, passTest;
    ifstream file("input");
    if (file.is_open()) {
        while (getline(file, line)) {
            count = 0;
            // Pivot to split line into useful information
            splitPos = line.find(':');

            passReq = line.substr(0, splitPos); // Character positions to check
            passTest = line.substr(splitPos + 2, line.length()); // Password to check

            // Pivot to get the 2 positions to check
            splitPos = passReq.find('-');

            pos1 = stoi(passReq.substr(0, splitPos), nullptr);
            pos2 = stoi(passReq.substr(splitPos + 1, passReq.length() - 2), nullptr);

            // Get character to check for
            check = passReq[passReq.length() - 1];

            // Iterate through characters in password to check
            for (int i = 0; i < passTest.length(); ++i)
                count += (passTest[i] == check && (i == pos1 - 1 || i == pos2 - 1)); // If character is in either position add 1 to count

            superCount += (count == 1); // The password is only valid if the number of satisfied positions is 1
        }
        file.close();
    }
    cout << superCount;
}