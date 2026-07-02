#include <fstream>
#include <iostream>
#include <unordered_map>
#include "encoder.h"
using namespace std;
int main(){
    ifstream input("input.txt");
    if(!input.is_open())
    {
        cout << "Failed to open file\n";
        return 0;
    }
    char ch;
    unordered_map<char,int> freq;
    while(input.get(ch))
    {
        freq[ch]++;
    }
    input.close();
    Huffman hm;
    for(const auto &it : freq)
    {
        hm.push(it.first , it.second);
    }
    hm.fill();
    input.open("input.txt");
    if(!input.is_open())
    {
        cout << "Failed to reopen file\n";
        return 0;
    }
    ofstream output("output.txt");
    if(!output.is_open())
    {
        cout << "Failed to create output file\n";
        return 0;
    }
    hm.encode(input , output, freq);
    return 0;
}
