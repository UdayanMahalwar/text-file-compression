#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;

int main()
{
    ifstream file("output.txt");
    if(!file.is_open())
    {
        cout << "Cannot open output.txt\n";
        return 1;
    }
    unordered_map<string,char> decodeMap;
    string line;
    while(getline(file,line))
{
    if(line == "...............................")
    {
        break;
    }

    int ascii;
    string code;

    stringstream ss(line);
    if(!(ss >> ascii >> code))
    {
        cout << "Invalid metadata line: " << line << endl;
        return 1;
    }
    ss >> ascii >> code;

    decodeMap[code] = (char)ascii;
}
string encoded;

while(getline(file,line))
{
    encoded += line;
}
string curr;
ofstream decoded("decoded.txt");
for(char bit : encoded)
{
    curr += bit;

    if(decodeMap.find(curr) != decodeMap.end())
    {
        decoded << decodeMap[curr];
        curr.clear();
    }
}
if(!curr.empty())
{
    cout << "Warning: corrupted encoded data\n";
}
}
