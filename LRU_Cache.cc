// source: https://www.hackerrank.com/challenges/abstract-classes-polymorphism/problem
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;
struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};
class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function
};
class LRUCache : public Cache{
   int listSize;
   public: 
   LRUCache(int cp) : listSize(0)
   {
       this->cp  = cp;
       head = tail = NULL;
   }
   void set(int, int); //set function
   int get(int); //get function
    private:
    Node *findItInCache(int key);
};
Node *LRUCache::findItInCache(int key)
{
    for(Node *p = head; p; p = p->next)
        if(p->key == key)
            return p;
    return NULL;
}
/*
set() - Set/insert the value of the key, if present, otherwise add the key 
as the most recently used key. If the cache has reached its capacity, 
it should replace the least recently used key with a new key.
*/
void LRUCache::set(int key, int value) //set function
{
    //cerr << " key = " << key << " " << value << endl;
    Node *current = findItInCache(key);
    if(current) // hit
    {
        current->value = value;
        if(current != head)
        {
            // move the key to the front
            current->prev->next = current->next;
            if(current->next)
                current->next->prev = current->prev;
            else // tail
                tail =  current->prev; // This is important!
            current->next = head;
            current->prev = NULL;
            head->prev = current;
            head = current;
        }
    }
    else //  
    {
        // not present
        if(listSize == cp) // full
        {  // Remove least used one
            tail = tail->prev;
            // delete tail->next;
            tail->next->next = NULL; // This is the previous tail
            tail->next->prev = NULL; // reset them when not in LRUCache    
            tail->next = NULL;
        }
        // Add the current one to the front
        if(mp.find(key) == mp.end())
        {
            mp[key] = new Node(key, value);
        }           
        Node *current = mp[key]; // its prev and next are NULL
        if(!head)
            head = tail = current;
        else
        {
            // Add the current in the front
            current->next = head;
            head->prev = current;
            head = current;
        }
        
        if(listSize != cp)
            ++listSize;
    }
}
/*
get() - Get the value (will always be positive) of the key if the key exists 
in the cache, otherwise return -1.
*/
int LRUCache::get(int key) //get function
{
    for(Node *p = head; p; p = p->next)
        if(p->key == key)
            return p->value;
    return -1;
}

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}

