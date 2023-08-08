// q1_b.cpp
// LFU CACHE 
#include <iostream>
#include <unordered_map>
using namespace std;

class CacheNode{
	public:
		int key;
		int value;
		int frequency;
		CacheNode* prev;
		CacheNode* next;
		
		CacheNode(){
			this->key=-8;
			this->value=-8;
			this->frequency=1;
			this->prev=NULL;
			this->next=NULL;
		}
		
		CacheNode(int key, int value,int frequency){
			this->key = key;
			this->value = value;
			this->frequency=frequency;
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
		CacheNode* insertAfterHead(int key, int value,int frequency){
			CacheNode* newNode = new CacheNode(key,value,frequency);
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
		
		bool isEmpty(){
			if(head->next->next==NULL)
				return true;
			else
				return false;
		}
};

class LFUCache{
	public:
		int capacity=0;
		int minFrequency;
		unordered_map<int,CacheLinkedList*> frequencyList;
		unordered_map<int,CacheNode*> cache;
		
		LFUCache(int capacity){
			this->capacity=capacity;
			minFrequency=0;
		}
		
		// CHECK - not updating in cache
	
		int get(int key){
			if(cache.find(key)!=cache.end()){
				CacheNode* deletedNode = cache[key];
				cache.erase(key);
				int deletedNodeKey = deletedNode->key;
				int deletedNodeFrequency = deletedNode->frequency;
				int deletedNodeVal = deletedNode->value;
				frequencyList[deletedNode->frequency]->deleteNode(deletedNode);
				
				if(deletedNodeFrequency==minFrequency && frequencyList[deletedNodeFrequency]->isEmpty()){
					minFrequency=minFrequency+1;
				}
				
				if(frequencyList.find(deletedNodeFrequency+1) != frequencyList.end()){
					CacheLinkedList* cacheList = frequencyList[deletedNodeFrequency+1];
					CacheNode* newNode = cacheList->insertAfterHead(key,deletedNodeVal,deletedNodeFrequency+1);
					cache[deletedNodeKey]=newNode;
				}else{
					CacheLinkedList* cacheList = new CacheLinkedList();
					CacheNode* newNode = cacheList->insertAfterHead(key,deletedNodeVal,deletedNodeFrequency+1);
					frequencyList[deletedNodeFrequency+1]=cacheList;
					cache[deletedNodeKey]=newNode;
				}
				
				
				return deletedNodeVal;
			}else{
				return -1;
			}
		}
		
		void set(int key, int value){
			if(cache.find(key) != cache.end()){
				// key found
				CacheNode* deletedNode = cache[key];
				int deletedNodeKey = deletedNode->key;
				int deletedNodeFrequency = deletedNode->frequency;
				frequencyList[deletedNode->frequency]->deleteNode(deletedNode);

				
				if(deletedNodeFrequency==minFrequency && frequencyList[deletedNodeFrequency]->isEmpty()){
					// frequencyList.erase(deletedNodeFrequency);
					minFrequency=minFrequency+1;
				}
				if(frequencyList.find(deletedNodeFrequency+1)!=frequencyList.end()){
					CacheLinkedList* cacheList = frequencyList[deletedNodeFrequency+1];
					CacheNode* newNode = cacheList->insertAfterHead(key,value,deletedNodeFrequency+1);
					cache[key]=newNode;
				}else{
					CacheLinkedList* cacheList = new CacheLinkedList();
					CacheNode* newNode = cacheList->insertAfterHead(key,value,deletedNodeFrequency+1);
					frequencyList[deletedNodeFrequency+1]=cacheList;
					cache[key]=newNode;
				}
				
				
			}else{
				if(capacity==0)
					return;
				if(capacity<=cache.size()){
					CacheNode* deletedNode = frequencyList[minFrequency]->deleteLRU();
					cache.erase(deletedNode->key);
					minFrequency=1;
					CacheLinkedList* cacheList = frequencyList[minFrequency];
					cache[key]=cacheList->insertAfterHead(key,value,1);
				}else{
					minFrequency=1;
					if(frequencyList.find(minFrequency)!= frequencyList.end()){
						CacheLinkedList* list = frequencyList[1]; 
						CacheNode* newNode = list->insertAfterHead(key,value,minFrequency);
						cache[key]=newNode;
					}else{
						CacheLinkedList* cacheList = new CacheLinkedList();
						CacheNode* newNode = cacheList->insertAfterHead(key,value,minFrequency);
						frequencyList[minFrequency]=cacheList;
						cache[key]=newNode;
					}
				}
			}
			
		}
		
		void printFrequencyList(){
			cout<<"FREQUENCY LIST \n";
			unordered_map<int, CacheLinkedList* >:: iterator iter;
			for(iter = frequencyList.begin(); iter!= frequencyList.end(); iter++){
				cout<<iter->first<<" : ";
				CacheNode* temp = (iter->second)->head;
					while(temp!=NULL){
						cout<<"("<<temp->key<<","<<temp->value<<","<<temp->frequency<<")";
							if(temp->next!=NULL)
								cout<<" -> ";
							temp=temp->next;
					}
					cout<<"\n";
			}
		}
		
		void printCache(){
			unordered_map<int, CacheNode* > :: iterator iter;
			cout<<"CACHE\n";
			for(iter = cache.begin(); iter!=cache.end();iter++){
				cout<<iter->first;
				cout<<" -> ("<<iter->second->key<<","<<iter->second->value<<","<<iter->second->frequency<<") : "<<iter->second<<endl; 
			}
		}	
		
		void print(){
			printFrequencyList();
			printCache();
			cout<<"------------------------------------\n";
			cout<<"MINIMUM FREQUENCY : "<<minFrequency<<endl;
			cout<<"------------------------------------\n";
		}
				
};


int main(){
	

	int cap,queries;
	cin>>cap>>queries;
	int result[queries];
	int i=0;
	LFUCache lfuCache(cap);
	while(queries--){
		int ch,key,value;
		cin>>ch;
		if(ch==1){
			cin>>key;
			result[i++]=lfuCache.get(key);
		}else if(ch==2){
			cin>>key>>value;
			lfuCache.set(key,value);
		}else{
			cout<<"Wrong output\n";
		}
	}
	for(int j=0;j<i;j++){
		cout<<result[j]<<endl;
	}
	return 0;

}