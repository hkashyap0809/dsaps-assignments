// q1.cpp
// LRU LFU CACHE
#include <iostream>
#include <unordered_map>
using namespace std;

class CacheNode{
	public:
		int key;
		int value;
		CacheNode* prev;
		CacheNode* next;
		
		CacheNode(){
			this->key=INT_MIN;
			this->value=INT_MIN;
			this->prev=NULL;
			this->next=NULL;
		}
		
		CacheNode(int key, int value){
			this->key = key;
			this->value = value;
			this->prev = NULL;
			this->next = NULL;
		}
};

class CacheLinkedList{
	public:
		CacheNode* head = new CacheNode();
		CacheNode* tail = new CacheNode();
		CacheLinkedList(){
			head->next=tail;
			head->prev=NULL;
			tail->prev=head;
			tail->next=NULL;
		}
		CacheNode* insertAfterHead(int key, int value){
			CacheNode* newNode = new CacheNode(key,value);
			CacheNode* tempNode = head->next;
			head->next=newNode;
			newNode->prev=head;
			newNode->next=tempNode;
			tempNode->prev=newNode;
			return newNode;
		}
		
		void deleteNode(CacheNode* node){
			CacheNode* previousNode = node->prev;
			CacheNode* nextNode = node->next;
			previousNode->next = nextNode;
			nextNode->prev=previousNode;
			
			delete(node);
		}
		
		CacheNode* deleteLRU(){
			CacheNode* node = tail->prev;
			CacheNode* previousNode = node->prev;
			previousNode->next=tail;
			tail->prev=previousNode;
			return node;
		}
		
		
		void print(){
			CacheNode* temp = head;
			while(temp!=NULL){
				cout<<"("<<temp->key<<","<<temp->value<<")";
				if(temp->next!=NULL)
					cout<<" -> ";
				temp=temp->next;
			}
			cout<<"\n";
		}
};
class LRUCache{
	public:
		int capacity;
		unordered_map<int,CacheNode*> cache;
		CacheLinkedList cacheList;
		
	LRUCache(int capacity){
		this->capacity=capacity; 
	}
	
	int get(int key){
		if(cache.find(key)!=cache.end()){
			// key found
			CacheNode* node = cache[key];
			int value = node->value;
			cacheList.deleteNode(node);
			cache.erase(key);
			CacheNode* newNode = cacheList.insertAfterHead(key,value);
			cache[key]=newNode;
			return newNode->value;
		}else{
			return -1;
		}
	}
	void set(int key, int value){ 		
		if(cache.find(key)!=cache.end()){
			// key found
			CacheNode* node = cache[key];
			cacheList.deleteNode(node);
			CacheNode* newNode = cacheList.insertAfterHead(key,value);
			cache.erase(key);
			cache[key]=newNode;
		}else{
			if(capacity<=cache.size()){
				CacheNode* deletedNode = cacheList.deleteLRU();
				cache.erase(deletedNode->key);
				CacheNode* newNode = cacheList.insertAfterHead(key,value);
				cache[key]=newNode;
			}else{
				CacheNode* newNode = cacheList.insertAfterHead(key,value);
				cache[key]=newNode;
			}
		}
	}
	
	void printCache1(){
			unordered_map<int, CacheNode* > :: iterator iter;
			cout<<"CACHE\n";
			for(iter = cache.begin(); iter!=cache.end();iter++){
				cout<<iter->first;
				cout<<" -> ("<<iter->second->key<<","<<iter->second->value<<") : "<<iter->second<<endl; 
			}
		}	
	
	void printCache(){
		cout<<"cache size : "<<cache.size()<<" capacity : "<<capacity<<endl; 
		cacheList.print();
		cout<<"******************************************\n\n";
	}
};


int main(){
	
	int cap,queries;
	cin>>cap>>queries;
	int result[queries];
	int i=0;
	LRUCache lruCache(cap);
	while(queries--){
		int ch,key,value;
		cin>>ch;
		if(ch==1){
			cin>>key;
			result[i++]=lruCache.get(key);
		}else if(ch==2){
			cin>>key>>value;
			lruCache.set(key,value);
		}else{
			cout<<"Wrong output\n";
		}
	}
	for(int j=0;j<i;j++){
		cout<<result[j]<<endl;
	}
	return 0;
}