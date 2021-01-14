#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* RecursiveWhile takes a file pointer, a string array pointer and a depth pointer
 * It will recursively search the file until the sum of 3 numbers equals 2020
 * Of which it will return true
 * */
int recursiveWhile(ifstream &file, string lines[], int depth){
    if(depth>0){
        // Base line search
        while(getline(file, lines[depth])){
            // Maintains same position technique
            auto g = file.tellg();

            int num = recursiveWhile(file, lines, depth-1);
            if(num == 2020){
                return num;
            }
            file.clear();
            file.seekg(g);
        }
    } else if(depth <= 0){
        while(getline(file, lines[depth])){
            // Check if lines in string array are not empty
            if(!lines[0].empty() && !lines[1].empty() && !lines[2].empty()){

                // Get sum of lines
                int stuff = ((stoi(lines[0], nullptr) + stoi(lines[1], nullptr) + stoi(lines[2], nullptr)));
                if(stuff == 2020){
                    return stuff;
                }

            }
        }
    }
    return 0;
}


int main(int argc, char *argv[]){

    string lines[3] = { to_string(3000), to_string(3000), to_string(3000)};
	ifstream myfile("input");
	if(myfile.is_open()) {


        while(getline(myfile, lines[2])){
            // Save position
            auto g = myfile.tellg();

            // Run recursive search
            if(recursiveWhile(myfile, lines, 1) == 2020){

                cout << lines[2] << "  |  " << lines[1] << "  |  " << lines[0] << endl;
                break;
            }

            // Fix the file
            myfile.clear();
            myfile.seekg(g);
        }


        myfile.close();
	}
	return 0;
}

