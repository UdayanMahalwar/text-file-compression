#include<iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
class node{
    public:
  node* left;
  node* right;
  char val ;
  int count;
  node(){
  }
  node(int cnt , char c)
  {
      this->left = NULL;
      this->right = NULL;
      this->count = cnt;
      this->val = c; 
  }
};
class comp{
    public:
  bool operator()(node*&a , node*&b)
  {
      return a->count > b->count;
  }
};
class hoffman{
    public:
    unordered_map<char , string>mp;
    priority_queue<node* , vector<node*> , comp>pq;
    void push(char val , int count)
    {
        node* newNode = new node(count , val);
        pq.push(newNode);
    }
    void fill_map(node* root , string code)
    {
        if(root == NULL)
        {
            return;
        }
        if(root->left == NULL && root->right == NULL)
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
        fill_map(pq.top() , "");
    }
    void print(){
        for(auto it : mp)
        {
            cout<<it.first<<" "<<it.second<<endl;
        }
    }
};
int main(){
    hoffman hm;
    hm.push('a' , 5);
    hm.push('b' , 9);
    hm.push('c' , 12);
    hm.push('d' , 13);
    hm.push('e' , 16);
    hm.push('f' , 45);
    hm.fill();
    hm.print();
    return 0;
}
