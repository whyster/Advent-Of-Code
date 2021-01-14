#include <iostream>
#include <fstream>

using namespace std;


/*  Search takes in a file pointer, amount to search right per line, amount to go down per line
 *  It will return the amount of trees with the given path
 *
 * */
int search(ifstream &file, int right, int down){
    int trees = 0;
    int lineOffset = 32;
    char outPut;
    // The input file has a line size of about 32 bytes
    // The input file is 323 lines long
    for (int i = 1; i < 323; ++i) {

        // calculate g by modulating right*i so that it wraps around on a line instead of offsetting down
        int g =((right*i)%31) + lineOffset*i*(down);

        // Seek to the character in the file
        file.seekg(g);

        // Read the character to output
        file.get(outPut);

        // Put character back into the file
        file.unget();

        // If the character is '#' then add 1 to total tree count
        trees += (outPut == '#');
    }
    // Return
    return trees;
}

int main(int argc, char *argv[]){
    ifstream file("input");
    string line;
    if (file.is_open()) {
        int trees = search(file, 1, 1);
        cout << "Search(1 right, 1 down): " << trees << endl;
        trees = search(file, 3, 1);
        cout << "Search(3 right, 1 down): " << trees << endl;
        trees = search(file, 5, 1);
        cout << "Search(5 right, 1 down): " << trees << endl;
        trees = search(file, 7, 1);
        cout << "Search(7 right, 1 down): " << trees << endl;
        trees = search(file, 1, 2);
        cout << "Search(1 right, 2 down): " << trees << endl;
        file.close();
    }
}