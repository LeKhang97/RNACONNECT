#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

vector<string> split_string(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

int main(int argc, char* argv[])
{
    ofstream outfile("example.txt");

    for (int i = 1; i < argc; i++) {
            string x = argv[i];
            vector <string> y = split_string(x, ',');
            for(int j = 0; j < y.size(); j++){
                outfile << y[j] << endl;
            }
        }
    outfile.close();
    return 0;
}
