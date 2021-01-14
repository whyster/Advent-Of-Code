#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]){
	string firstLine, secondLine;
	// Get filestream of input
	ifstream myfile("input");

	if(myfile.is_open()){
	    // Read first line
		while(getline(myfile, firstLine)){
		    // Save current position in file to reset when inner while loop finishes
		    auto g = myfile.tellg();
		    // Loop over every line
            while(getline(myfile, secondLine)){

                // Check if both lines are not empty
                if(!firstLine.empty() && !secondLine.empty()){
                    int firstNum = stoi(firstLine, nullptr);
                    int secondNum = stoi(secondLine, nullptr);

                    // If both lines add together to 2020, print their multiple
                    if((firstNum + secondNum)==2020)
                        cout<<(firstNum*secondNum)<<endl;
                }
            }
            // Reset file for loop
            myfile.clear();
            myfile.seekg(g);
		}

		// Close file
		myfile.close();
	}
	return 0;
}
