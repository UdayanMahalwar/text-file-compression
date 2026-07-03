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
    
    // Read metadata until separator
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
        
        decodeMap[code] = (char)ascii;
    }
    
    // Read total number of bits
    getline(file, line);
    long totalBits = stol(line);
    
    // Read binary data
    string encoded = "";
    unsigned char byte;
    long bitCounter = 0;
    
    while(file.read(reinterpret_cast<char*>(&byte), sizeof(unsigned char)))
    {
        for(int i = 7; i >= 0 && bitCounter < totalBits; i--)
        {
            encoded += ((byte >> i) & 1) ? '1' : '0';
            bitCounter++;
        }  
    }
    
    // Decode the bit string
    string curr = "";
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
    
    decoded.close();
    file.close();
    
    return 0;
}
