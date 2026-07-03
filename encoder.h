#pragma once

#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class node {
public:
    node* left;
    node* right;
    char val;
    int count;

    node() {
        left = nullptr;
        right = nullptr;
        count = 0;
        val = '?';
    }

    node(int cnt, char c) {
        this->left = nullptr;
        this->right = nullptr;
        this->count = cnt;
        this->val = c;
    }
};

class comp {
public:
    bool operator()(node* a, node* b) {
        return a->count > b->count;
    }
};

class Huffman {
public:
    unordered_map<char, string> mp;
    node* root = nullptr;
    priority_queue<node*, vector<node*>, comp> pq;

    void push(char val, int count) {
        node* newNode = new node(count, val);
        pq.push(newNode);
    }

    void fill_map(node* root, string code) {
        if (root == nullptr) {
            return;
        }
        if (root->left == nullptr && root->right == nullptr) {
            mp[root->val] = code;
        }
        if (root->left) {
            fill_map(root->left, code + '0');
        }
        if (root->right) {
            fill_map(root->right, code + '1');
        }
    }

    void fill() {
        if (pq.empty()) {
            return;
        }
        if (pq.size() == 1) {
            root = pq.top();
            mp[pq.top()->val] = "0";
            return;
        }
        while (pq.size() != 1) {
            node* first = pq.top();
            pq.pop();
            node* second = pq.top();
            pq.pop();
            int newVal = first->count + second->count;
            node* newNode = new node(newVal, '?');
            newNode->left = first;
            newNode->right = second;
            pq.push(newNode);
        }

        root = pq.top();
        fill_map(root, "");
    }
    void delete_Nodes(node* root) {
        if (root == nullptr) {
            return;
        }
        delete_Nodes(root->left);
        delete_Nodes(root->right);
        delete root;
    }

    void encode(ifstream& input, ofstream& output, const unordered_map<char, int>& freq) {
        // Write metadata (frequency table)
        for (const auto& it : freq) {
            output << (int)it.first << " " << mp[it.first] << "\n";
        }
        output << "..............................." << "\n";
        
        // Build bit string
        string bitString = "";
        char ch;
        while (input.get(ch)) {
            bitString += mp[ch];
        }
        
        // Write total number of bits
        output << bitString.length() << "\n";
        
        // Switch to binary mode and pack bits into bytes
        output.clear();
        output.close();
        ofstream binaryOutput("output.txt", ios::binary | ios::app);
        
        unsigned char byte = 0;
        int bitCount = 0;
        
        for (char bit : bitString) {
            byte = (byte << 1) | (bit - '0');
            bitCount++;
            
            if (bitCount == 8) {
                binaryOutput.write(reinterpret_cast<const char*>(&byte), sizeof(unsigned char));
                byte = 0;
                bitCount = 0;
            }
        }
        
        // Write remaining bits (padded with zeros)
        if (bitCount > 0) {
            byte = byte << (8 - bitCount);
            binaryOutput.write(reinterpret_cast<const char*>(&byte), sizeof(unsigned char));
        }
        
        binaryOutput.close();
    }

    ~Huffman() {
        if (!pq.empty()) {
            delete_Nodes(pq.top());
        }
    }
};
