// 2022201050_A4_Q2a.cpp
#include <iostream>
using namespace std;

// ***********************************************
// SINGLY LINKED LIST NODE
// ***********************************************
template <class T1, class T2>
class Node{
	public:
		T1 key;
		T2 value;;
		Node *next;
		Node(T1 key,T2 value){
			this->key = key;
			this->value=value;
			this->next=NULL;
		}
};

// ***********************************************
// SINGLY LINKED LIST
// ***********************************************
template <class T1, class T2>
class LinkedList{
	public:
		Node<T1,T2>* head;
		T2 defaultValue;
		// DEFAULT CONSTRUCTOR
		LinkedList(){
			head=NULL;
		}
		
		// INSERTING AT THE HEAD
		void insert(T1 key, T2 value){
			Node<T1,T2>* node = new Node<T1,T2>(key,value);
			if(head==NULL){
				head = node;
				return;
			}
			node->next = head;
			head = node;
		}
		
		// SEARCHING IN THE LINKED LIST
		bool searchKey(T1 key){
			Node<T1,T2>* temp = head;
			while(temp){
				if(temp->key == key){
					return true;
				}
				temp=temp->next;
			}
			return false;
		}

		// DELETE A VALUE IN THE LINKED LIST
		void deleteKey(T1 key){
			Node<T1,T2>* temp = head;
			
			if(!searchKey(key))
				return;
			
			// first node to be deleted
			if(temp->key == key){
				head=temp->next;
				delete temp;
				return;
			}
			temp = temp->next;
			while(temp->next != NULL){
				if(temp->next->key==key){
					
					break;
				}
				temp=temp->next;
			}
			// last node to be deleted
			if(temp->next->next == NULL){
				Node<T1,T2>* del = temp->next;
				temp->next = NULL;
				delete del;
				return;
			}
			Node<T1,T2>* del = temp->next;
			temp->next = temp->next->next;
			delete del;
		}
		
		// PRINTING THE LINKED LIST
		void print(){
			Node<T1,T2>* temp = head;
			
			cout<<" [ ";
			while(temp){
				cout<<"("<<temp->key<<",";
				cout<<temp->value<<")";
				temp=temp->next;
				if(temp!= NULL)
					cout<<" , ";
			}
			cout<<" ] ";
			cout<<"\n";
		}
		
		// SEARCH KEY AND UPDATE
		bool searchKeyAndUpdateValue(T1 key, T2 value){
			Node<T1,T2>* temp = head;
			while(temp){
				if(temp->key == key){
					temp->value = value;
					return true;
				}
				temp=temp->next;
			}
			return false;	
		}
		
		T2 valueOfKey(T1 key){
			Node<T1,T2>* temp = head;
			T2 returnValue = defaultValue;
			while(temp){
				if(temp->key==key){
					returnValue = temp->value;
				}
				temp=temp->next;
			}
			return returnValue;
		}
};
// ***********************************************
// UNORDERED MAP
// ***********************************************
template <class T1, class T2>
class UnorderedMap{
	public:
		const int TABLE_SIZE = 997;
		LinkedList<T1,T2>* hashTable;
		T2 defaultValue;
		UnorderedMap(T2 defVal){
			hashTable = new LinkedList<T1, T2>[TABLE_SIZE];
			for(int i=0;i<TABLE_SIZE;i++){
				hashTable[i].head=NULL;
			}
			defaultValue=defVal;
		}
		
		// UTILITIES
		int HASH(string str){
			int hashCode = 7;
			int len = str.length();
			for(int i=0;i<len;i++){
				hashCode = hashCode*11 + str[i];
				hashCode = hashCode % TABLE_SIZE;
			}				
			return hashCode;
		}
		
		int HASH(int key){
			return key;
		}
		
		int HASH(char key){
			return key;
		}
		
		int HASH(float key){
			return (int)key;
		}
		int HASH(double key){
			return (int)key;
		}
		
		void print(){
			for(int i=0; i<TABLE_SIZE;i++){
				if(hashTable[i].head!=NULL){
					cout<<"KEY : "<<i<<" -> " ;
					hashTable[i].print();
				}
			}
		}
		
		// FUNCTIONS
		void insert(T1 mapKey,T2 mapValue){
			int key = HASH(mapKey);
			key = key % TABLE_SIZE;
			
			if(hashTable[key].head==NULL){
				LinkedList<T1,T2> list;
				list.insert(mapKey,mapValue);
				hashTable[key] = list;
				return;
			}
			
			// SEARCH FOR THE KEY
			if(hashTable[key].searchKeyAndUpdateValue(mapKey,mapValue)){
					return;
			}
			
			hashTable[key].insert(mapKey,mapValue);
		}
		
		void erase(T1 mapKey){
			int key = HASH(mapKey);
			key = key % TABLE_SIZE;
			
			if(hashTable[key].head != NULL){
				hashTable[key].deleteKey(mapKey);
			}
		}
		bool find(T1 mapKey){
			int key = HASH(mapKey);
			key = key % TABLE_SIZE;
			
			if(hashTable[key].head == NULL){
				return false;
			}
			
			if(hashTable[key].searchKey(mapKey)){
				return true;
			}
			return false;
		}
		
		T2 operator [](T1 mapKey){
			int key = HASH(mapKey);
			key = key % TABLE_SIZE;
			if(hashTable[key].head != NULL){
				return hashTable[key].valueOfKey(mapKey);
			}
			return defaultValue;
		}
};

// ***********************************************
// MAIN FUNCTION
// ***********************************************


int main(){
	int queries;
	cin>>queries;
	int input;
	
	UnorderedMap<string,double> hashMap(0);
	string key;
	double value;
	string result="";
	
	// hashMap.insert("boom",4.6);
	// hashMap.print();
	
	while(queries--){
		cin>>input;
		if(input==1){
			// INSERT
			cin>>key>>value;
			// cout<<"key "<<key<<" value :"<<value<<"\n";
			hashMap.insert(key,value);
		}else if(input==2){
			// ERASE
			cin>>key;
			hashMap.erase(key);
		}else if(input==3){
			// FIND
			cin>>key;
			result=result+to_string(hashMap.find(key))+"\n";
		}else if(input==4){
			// MAP
			cin>>key;
			result=result+to_string(hashMap[key])+"\n";
		}
	}	
	cout<<result;
	
}
