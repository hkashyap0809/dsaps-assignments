// dequeue.cpp
#include<iostream>
using namespace std;

template <class T>
class Deque{
	public:	
		
		T *array;
		int length;
		int frontIndex = -1;
		int rear = -1;
		T defaultVal;
		int sizeVal=0;
		
		Deque(T val){
			// constructor 
			length=10;
			array = new T[length];
			defaultVal=val;
		}
		
		void resize(){
			T *newArray = new T[2*length];
			
			if(frontIndex>rear){
				if(rear==0 && frontIndex==1){
					newArray[rear]=array[rear];
					for(int i=frontIndex;i<length;i++){
						newArray[i+length]=array[i];
					}	
					frontIndex=frontIndex+length;
				}else{
					for(int i=0;i<=rear;i++)
						newArray[i]=array[i];
					for(int i=frontIndex;i<length;i++)
						newArray[length+i]=array[i];
					frontIndex=frontIndex+length;
				}
			}else{
				if(frontIndex==0 && rear==length-1){
						for(int i=frontIndex;i<length;i++){
							newArray[i]=array[i];
						}
						// frontIndex=frontIndex+length;
				}else{
					for(int i=0;i<=frontIndex;i++)
						newArray[i]=array[i];
					for(int i=rear;i<length;i++)
						newArray[i+length]=array[i];
					rear=rear+length;
				}
			}
			array=newArray;
			length=2*length;	
			
		}
		
		void deque(){
			//creating a deque of fixed size
			length=10;
			array = new T[length];
		}
		
		void deque(int n, T x){
			// creating a deque of given size n
			array = new T[n];
			length = n;
			// push elements (to the front)
			for(int i=0;i<n;i++){
				push_back(x);
			}
			sizeVal=n;
		}
	
		bool empty() {
			// return whether the que is currently empty or not
			if(frontIndex == rear && frontIndex==-1)
				return true;
			else 
				return false;
		}
		
		int size() {
			// int size=0;
			// if(frontIndex==rear && frontIndex==-1)
			// {
			// 	// empty queue
			// 	return size;
			// }else{
			// 	int i=frontIndex;
			// 	while(i!=rear){
			// 		size++;
			// 		i=(i+1)%length;
			// 	}
			// }
			
			return sizeVal;
			
		}
		
		void push_front(T val){
 			// append data x at the beginning. Time complexity:O(1)
 			if(frontIndex==(rear+1)%length){
 				// if queue is full,then resize
 				resize();
 			}
			if(frontIndex==rear && frontIndex==-1){
				// queue is empty
				frontIndex=0;
				rear=0;
				array[frontIndex]=val;
				sizeVal++;
			}else if(frontIndex==0){
				frontIndex=length-1;
				array[frontIndex]=val;
				sizeVal++;
			}
			else{
				// in all the other cases
				frontIndex = (frontIndex-1)%length;
				array[frontIndex]=val;
				sizeVal++;
			}
		}
		
		void push_back(T val){
			// append data x at the end. Time complexity: O(1)
			if(frontIndex==(rear+1)%length){
				// if queue is full then resize
				resize();
			}		
			if(frontIndex==rear && frontIndex==-1){
				// queue is empty
				frontIndex=0;
				rear=0;
				array[rear]=val;
				sizeVal++;
			}else if(rear==length-1){
				rear = 0;
				array[rear]=val;
				sizeVal++;
			}
			else{
				// in all other cases
				rear=(rear+1)%length;
				array[rear]=val;
				sizeVal++;
			}
		}	
		void pop_front(){
			// erase an element from the beginning. 
			// Time complexity: O(1)
			
			if(frontIndex==rear && frontIndex==-1){
				// que is empty, print underflow
				cout<<"QUEUE UNDERFLOW"<<endl;
			}else if(frontIndex == rear){
				// only 1 element is present
				// remove the element and set both the pointers to -1
				frontIndex=-1;
				rear=-1;
				sizeVal--;
			}else if(frontIndex==length-1){
				// if front pointer is at last element then after pop
				// it should be pointing to the first element
				frontIndex=0;
				sizeVal--;
			}else{
				// in all the other cases, incrementing the front pointer
				frontIndex=frontIndex+1;
				sizeVal--;
			}
		}
		
		void pop_back(){
			// erase data at the end. Time complexity: O(1)
			if(frontIndex==rear && frontIndex==-1)
			{
				// que is empty, print underflow
				cout<<"QUEUE UNDERFLOW"<<endl;
			}else if(frontIndex==rear){
				// only 1 element is present
				// removing the element and setting both the pointers to -1
				frontIndex=-1;
				rear=-1;
				sizeVal--;
			}else if(rear==0){
				// if rear is pointing to the first element 
				// remvove the element and should point to last element
				rear=length-1;
				sizeVal--;
			}else{
				// in all the other cases decrementing the rear pointer
				rear=rear-1;
				sizeVal--;
			}
		}
			
		T front(){
			// returns the first element(value) in the deque. 
			// Time complexity: O(1)	
			if(frontIndex==-1)
				return defaultVal;
			
			return array[frontIndex];			
		} 
		
		T back(){
			// returns the last element(value) in the deque. 
			// Time complexity: O(1)
			if(rear==-1)
				return defaultVal;
			
			return array[rear];		
		}
		
		void clear(){
			// remove all elements of deque. Time complexity: O(1)
			// pointing both the pointer to -1
			frontIndex=-1;
			rear=-1;
			sizeVal=0;
		}
		
		void resize(int x , T d){
			// change the size dynamically to new size x. 
			// Time complexity: O(n)
			//(a)	If the new size x is greater than the current size of the deque, 
			// 		then insert new elements with default value d at the end of the queue.
			//(b)	If the new size x is smaller than the current size, 
			// 		then keep x elements from the beginning of the deque.
			int currentSize = size();
			if(x>currentSize){
				int sizeDiff=x-currentSize;
				for(int i=0;i<sizeDiff;i++){
					push_back(d);
				}
			}else{
				// in this case elements will either be missed out or if
				// current size is equal to x then the queue will be packed.
				T *newArray=new T[x];
				int count=0;
				int i=frontIndex;
				// cout<<"i : "<<array[i]<<endl;
				while(count<x){
					newArray[count]=array[i];
					// cout<<"At index "<<count<<" "<<array[i]<<" is saved."<<endl;
					count++;
					i=(i+1)%length;
				}
				array=newArray;
				frontIndex=0;
				rear=x-1;
			}
		}
		
		T operator [](int n){
			int currentSize=size();
						
			if(currentSize<n)
				return defaultVal;
			
			int index =(frontIndex+n)%length;
			return array[index];
		}
		
		// FUNCTIONS NOT REQUIRED ( ONLY FOR DEBUGGING )
		
		int getFrontIndex(){
			return frontIndex;
		}
		int getRearIndex(){
			return rear;
		}
		
		void printDeque(){
			// print the que from front to rear
			if(frontIndex==rear && frontIndex == -1)
				cout<<"QUEUE IS EMPTY"<<endl;
			else{
				int i=frontIndex;
				while(i!=rear){
					cout<<array[i]<<" ";
					i=(i+1)%length;
				}
				cout<<array[rear];
			}
			cout<<endl;
		}	
		
		void printArray(){
			// print the array in which the queue is stored
			for(int i=0;i<length;i++){
				cout<<array[i]<<" ";
			}
			cout<<endl;
		}	
		
		int capacity(){
			return length;
		}
};

void driver(){
	int choice;
	int val=0;
	Deque<int> deque(val);

	do{
		cin>>choice;
		switch(choice){
			case 0 :		break;
			case 1 :	{
							deque.deque();	
						}	break; 
			case 2 : 	{
							int n;
							cin>>n>>val;
							deque.deque(n,val);	
						}	break;
			case 3 :	{
							cin>>val;
							deque.push_back(val);
						}	break;
			case 4 :	{
							deque.pop_back();
						}	break;
			case 5 :	{
							cin>>val;
							deque.push_front(val);
						}	break;
			case 6 :	{
							deque.pop_front();
										
						}	break;
			case 7 :	{
							cout<<deque.front()<<endl;
						}	break;
			case 8 :	{
							cout<<deque.back()<<endl;
						}	break;
			case 9 :	{
							int n;
							cin>>n;
							cout<<deque[n]<<endl;
						}	break;
			case 10 :	{	
							if(deque.empty())
								cout<<" DEQUE EMPTY "<<endl;
							else
								cout<<" DEQUE NOT EMPTY "<<endl;
						}	break;
			case 11 :	{
							cout<<"SIZE : "<<deque.size()<<endl;
						}	break;
			case 12 :	{
							int x;
							cin>>x>>val;
							deque.resize(x,val);
						}	break;			
			case 13 : 	{
							cout<<"QUEUE CLEARED "<<endl;
							deque.clear();
						}	break;
			case 14 :	{
							deque.printDeque();
						}	break;
			case 15 : 	{
							cout<<deque.capacity()<<endl;
						}	break;
			case 16 :	{
							deque.printArray();
						}	break;
			default : 	{
							cout<<"Wrong Input. Enter number from 0-16"<<endl;
						}
			
		}
		
	}while(choice!=0);
}

int main(){
	driver();
	// 0 - exit
	// 1 - deque()
	// 2 - deque(n,x)
	// 3 - push_back()
	// 4 - pop_back()
	// 5 - push_front()
	// 6 - pop_front()
	// 7 - front()
	// 8 - back()
	// 9 - D[n]
	// 10 - empty()
	// 11 - size()
	// 12 - resize(x,val)
	// 13 - clear()
	// 14 - printDeque()
	// 15 - capacity()
	// 16 - printArray()
	return 0;
}