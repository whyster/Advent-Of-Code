#include <iostream>
#include <fstream>

using namespace std;
// Basic template for reading lines from an input file

int main(int argc, char *argv[]){
    ifstream file("input");
	string line;
    if (file.is_open()){
        while(getline(file, line)){
        }
        file.close()
    }
}
