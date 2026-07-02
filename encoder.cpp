#include<iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
using namespace std;
class node{
  public:
  node* left;
  node* right;
  char val ;
  int count;
  node(){
    left = nullptr;
    right = nullptr;
    count = 0;
    val = '?';
  }
  node(int cnt , char c)
  {
      this->left = nullptr;
      this->right = nullptr;
      this->count = cnt;
      this->val = c; 
  }
  
};
class comp{
    public:
  bool operator()(node* a , node* b)
  {
      return a->count > b->count;
  }
};
class Huffman{
    public:
    unordered_map<char , string>mp;
    node* root = nullptr;
    priority_queue<node* , vector<node*> , comp>pq;
    void push(char val , int count)
    {
        node* newNode = new node(count , val);
        pq.push(newNode);
    }
    void fill_map(node* root , string code)
    {
        if(root == nullptr)
        {
            return;
        }
        if(root->left == nullptr && root->right == nullptr)
        {
            mp[root->val] = code;
        }
        if(root->left)
        {
            fill_map(root->left , code+'0');
        }
        if(root->right)
        {
            fill_map(root->right , code+'1');
        }
    }
    void fill(){
        if(pq.empty())
        {
            return;
        }
        if(pq.size() == 1)
        {
            root = pq.top();
            mp[pq.top()->val] = "0";
            return;
        }
        while(pq.size() != 1)
        {
            node* first = pq.top();
            pq.pop();
            node* second = pq.top();
            pq.pop();
            int newVal = first->count+second->count;
            node* newNode = new node(newVal , '?');
            newNode->left = first;
            newNode->right = second;
            pq.push(newNode);
        }
        
        root = pq.top();
        fill_map(root , "");
    }
    void delete_Nodes(node* root){
        if(root == nullptr)
        {
            return ;
        }
        delete_Nodes(root -> left);
        delete_Nodes(root -> right);
        delete root;
    }
    void encode( ifstream &input , ofstream &output ,ofstream &meta , const unordered_map<char,int>& freq){
        char ch;

        while(input.get(ch))
        {
            output << mp[ch];
        }
        for(const auto& it : freq)
        {
            meta << (int)it.first << " "<< it.second << "\n";
        }
    }
    ~Huffman(){
            if(!pq.empty())
            {
                delete_Nodes(pq.top());
            }
        }
};
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
    ofstream meta("meta.txt");
    if(!meta.is_open())
    {
        cout << "Failed to create output file Transformer\n";
        return 0;
    }
    hm.encode(input , output , meta , freq);
    return 0;
}
