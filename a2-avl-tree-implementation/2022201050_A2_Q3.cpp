// 2022201050_A2_Q3.cpp
#include <iostream>
#include <string>
using namespace std;
template <class T>
class TreeNode{
	public:
		T key;
		int frequency;			//frequency of the node
		int height;				//height of subtree from that node
		int leftNodes;			//no of nodes in the left subtree
		int rightNodes;			//no of nodes in the right subtree
		TreeNode* left;
		TreeNode* right;
		
		TreeNode(T key){
			this->key=key;
			this->frequency=1;
			this->height=1;
			this->leftNodes = 0;
			this->rightNodes = 0;
			this->left=NULL;
			this->right=NULL;
		}
};
class Dummy{
	public:
		string name;
		int rollNo;
		double marks;
		string program;
		int priority;
		Dummy(){
			name="";
			rollNo=0;
			marks=0.0;
			program="";
			priority=-1;
		}
		Dummy(string name,int rollNo,double marks,string program,int priority){
			this->name=name;
			this->rollNo=rollNo;
			this->marks=marks;
			this->program=program;
			this->priority=priority;
		}
};
template <class T>
class Comparator{
	public:
		// INTEGER
		int cmprtr(int a , int b){
			return a-b;
		}
		// FLOAT
		float cmprtr(float a , float b){
			return a-b;
		}
		// DOUBLE
		double cmprtr(double a , double b){
			return a-b;
		}
		// CHAR
		char cmprtr(char a , char b){
			return a-b;
		}
		// STRING
		int cmprtr(string a , string b){
			return a.compare(b);
		}
		// FOR GENERIC CLASS TYPE
		int cmprtr(Dummy a, Dummy b){
			return a.priority - b.priority ;
		}
};
template <class T>
class AVLTree {
	public:
		TreeNode<T>* root;
		int totalNodes;
		Comparator<T> comparator;
		T defaultValue;
		AVLTree(T val){
			root=NULL;
			defaultValue=val;
			totalNodes=0;
		}
		TreeNode<T>* getRoot(){	
			return root;
		}
		// INORDER FOR PRIMITIVE DATATYPE
		void inorderPrint(TreeNode<T>* root){
			if(root==NULL)
				return;
			
			inorderPrint(root->left);
			cout<<root->key<<" ";
			// cout 	<<"[K:"<<root->key<<"," 
			// 		<<"H:"<<root->height<<","
			// 		<<"C:"<<root->frequency<<","
			// 		<<"L:"<<root->leftNodes<<","
			// 		<<"R:"<<root->rightNodes<<"] ";
			inorderPrint(root->right);	
		}
		
		// INORDER PRINTING FOR CLASS TYPE
		// void inorderPrint(TreeNode<T>* root){
		// 	if(root==NULL)
		// 		return;
			
		// 	inorderPrint(root->left);
		// 	cout<<"["	<<root->key.name<<","
		// 				<<root->key.rollNo<<","
		// 				<<root->key.marks<<","
		// 				<<root->key.program<<","
		// 				<<root->key.priority<<"][C:"
		// 				<<root->frequency<<
		// 				"] ";
		// 	inorderPrint(root->right);	
		// }	
			
		// PRE-ORDER PRINTING FOR PRIMITIVE
		void preOrderPrint(TreeNode<T>* root){
			if(root==NULL)
				return;
		
			cout 	<< root->key<<" ";
				
			// cout 	<<"[K:"<<root->key<<"," 
			// 		<<"H:"<<root->height<<","
			// 		<<"C:"<<root->frequency<<","
			// 		<<"L:"<<root->leftNodes<<","
			// 		<<"R:"<<root->rightNodes<<"] ";			
			preOrderPrint(root->left);
			preOrderPrint(root->right);
		}
		
		// PRE-ORDER FOR CLASS TYPE
		// void preOrderPrint(TreeNode<T>* root){
		// 	if(root==NULL)
		// 		return;
			
		// 	cout<<"["	<<root->key.name<<","
		// 				<<root->key.rollNo<<","
		// 				<<root->key.marks<<","
		// 				<<root->key.program<<","
		// 				<<root->key.priority<<"][C:"
		// 				<<root->frequency<<
		// 				"] ";
		// 	preOrderPrint(root->left);
		// 	preOrderPrint(root->right);
		// }
		
		int max(int a, int b){
			return a > b ? a : b;
		}
		int abs(int a){
			return a<0 ? -1*a : a;
		}
		int giveHeight(TreeNode<T>* node){
			if(node==NULL)
				return 0;
			return node->height;
		}
		int giveLeftNodes(TreeNode<T>* node){
			if(node==NULL)
				return 0;
			return node->leftNodes;
		}
		int giveRightNodes(TreeNode<T>* node){
			if(node==NULL)
				return 0;
			return node->rightNodes;
		}
		int giveFrequency(TreeNode<T>* node){
			if(node==NULL)
				return 0;
			return node->frequency;
		}
		int giveHeightDifference(TreeNode<T>* node){
			if(node==NULL)
				return 0;
			return (giveHeight(node->left) - giveHeight(node->right));
		}
		void updateHeight(TreeNode<T>* node){
			node->height = 1 + max(giveHeight(node->left),giveHeight(node->right));	
		}
		void updateNodeCount(TreeNode<T>* node){
			node->leftNodes = giveLeftNodes(node->left) + giveRightNodes(node->left) + giveFrequency(node->left);
			node->rightNodes = giveLeftNodes(node->right) + giveRightNodes(node->right) + giveFrequency(node->right);
		}
			
		TreeNode<T>* rotateRight(TreeNode<T>* node){
			TreeNode<T>* newRoot = node->left;
			TreeNode<T>* tempNode = newRoot->right;
			
			newRoot->right = node;
			node->left=tempNode;
			
			updateHeight(node);
			updateHeight(newRoot);
				
			updateNodeCount(node);
			updateNodeCount(newRoot);
			
			return newRoot;
		}	
		TreeNode<T>* rotateLeft(TreeNode<T>* node){
			TreeNode<T>* newRoot = node->right;
			TreeNode<T>* tempNode = newRoot->left;
			
			newRoot->left=node;
			node->right = tempNode;
			
			updateHeight(node);
			updateHeight(newRoot);
					
			updateNodeCount(node);
			updateNodeCount(newRoot);		
			return newRoot;
		}
		TreeNode<T>* insert(TreeNode<T>* node, T key){
			if(node==NULL){
				TreeNode<T>* newNode = new TreeNode<T>(key);
				root = newNode;
				return root;
			}	
			
			if(comparator.cmprtr(node->key,key)<0){
				node->right=insert(node->right,key);
			}else if(comparator.cmprtr(node->key,key)>0){
				node->left=insert(node->left,key);
			}else if(comparator.cmprtr(node->key,key)==0){
				node->frequency=node->frequency+1;
			}
			updateHeight(node);
			updateNodeCount(node);

			int balanceFactor = giveHeightDifference(node);
			if(balanceFactor > 1 ){
				if(comparator.cmprtr(key,node->left->key)<0)
					return rotateRight(node);
				else if(comparator.cmprtr(key,node->right->key)>0){
					node->left = rotateLeft(node->left);
					return rotateRight(node);
				}	
			}
			if(balanceFactor<-1){
				if(comparator.cmprtr(key,node->right->key)>0){
					return rotateLeft(node);
				}else if(comparator.cmprtr(key,node->right->key)<0){
					node->right = rotateRight(node->right);
					return rotateLeft(node);
				}
			}
			return node;
		}
		int count_occurences(T key){
			bool isPresent = false;
			int val=0;
			if(root==NULL)
				return val;
			
			TreeNode<T>* tempRoot = root;
			
			while(tempRoot!=NULL){
				if(comparator.cmprtr(tempRoot->key,key)>0)
					tempRoot=tempRoot->left;
				else if(comparator.cmprtr(tempRoot->key,key)<0)
					tempRoot=tempRoot->right;
				else if(comparator.cmprtr(tempRoot->key,key)==0){
					val=tempRoot->frequency;
					tempRoot=NULL;
				}
			}
			return val;
		}
		int count_range(TreeNode<T>* node,T e1, T e2){
			if(node==NULL)
				return 0;
			if(comparator.cmprtr(node->key,e1)>=0 && comparator.cmprtr(node->key,e2)<=0){
				return node->frequency + count_range(node->left,e1,e2) + count_range(node->right,e1,e2);
			}
			if(comparator.cmprtr(node->key,e1)<0)
				return count_range(node->right,e1,e2);
			else if(comparator.cmprtr(node->key,e2)>0)
				return count_range(node->left,e1,e2);
			else

			return 0;
		}
		T lower_bound(T key){
			T value = defaultValue;
			TreeNode<T>* tempRoot = root;
			while(tempRoot!=NULL){
				if(comparator.cmprtr(tempRoot->key,key)==0){
					value=tempRoot->key;
					break;
				}else if(comparator.cmprtr(tempRoot->key,key)>0){
					value=tempRoot->key;
					tempRoot=tempRoot->left;
				}else{
					tempRoot=tempRoot->right;
				}
				
			}
			return value;
		}
		T upper_bound(T key){
			T value=defaultValue;
			if(!search(key))
				return value;
			TreeNode<T>* tempRoot = root;
			while(tempRoot!=NULL){
				if(comparator.cmprtr(tempRoot->key,key)>0){
					value=tempRoot->key;
					tempRoot=tempRoot->left;
				}else{
					tempRoot=tempRoot->right;
				}
			}
			return value;
		}
		T lower_bound_rev(T key){
			T value = defaultValue;
			TreeNode<T>* tempRoot = root;
			while(tempRoot!=NULL){
				if(comparator.cmprtr(tempRoot->key,key)==0){
					value=tempRoot->key;
					break;
				}else if(comparator.cmprtr(tempRoot->key,key)<0){
					value=tempRoot->key;
					tempRoot=tempRoot->right;
				}else{
					tempRoot=tempRoot->left;
				}
				
			}
			return value;	
		}
		T closest_element(T key){
			if(root==NULL)
				return defaultValue;
			
			if(search(key)){
				return key;
			}
			
			T lb = lower_bound(key);
			T ub = lower_bound_rev(key);
			if(!search(ub))
				return lb;
			if(lb==ub)
				return lb;
			
			if(abs(comparator.cmprtr(lb,key)) < abs(comparator.cmprtr(ub,key))){
				return lb;
			}else{
				return ub;
			}
		}
		bool search(T key){
			if(root==NULL)
				return false;
			TreeNode<T>* tempRoot = root;
			while(tempRoot!=NULL){
				if(comparator.cmprtr(tempRoot->key,key)<0){
					tempRoot=tempRoot->right;
				}
				else if(comparator.cmprtr(tempRoot->key,key)>0){
					tempRoot=tempRoot->left;
				}
				else if(comparator.cmprtr(tempRoot->key,key)==0){
					return true;
				}
			}
			
			return false;
		}
		T Kth_largest(TreeNode<T>* node,int k){
			if(node==NULL)
				return defaultValue;
			if(k> node->rightNodes + node->frequency)
				return Kth_largest(node->left,k-node->rightNodes-node->frequency);
			if(k<=node->rightNodes)
				return Kth_largest(node->right,k);
			if(k>node->rightNodes && k<=node->rightNodes + node->frequency)
				return node->key;
		}
		TreeNode<T>* inorderSuccessor(TreeNode<T>* node){
			// first go right and then keep on going left
			TreeNode<T>* inorderSuccessorNode = node->right;
			if(inorderSuccessorNode->left==NULL)
				return inorderSuccessorNode;
			
			while(inorderSuccessorNode->left!=NULL){
				inorderSuccessorNode=inorderSuccessorNode->left;
			}
			return inorderSuccessorNode;
		}		
		TreeNode<T>* deleteNode(TreeNode<T>* node, T key){
			if(node==NULL)
				return node;
			
			if(comparator.cmprtr(node->key,key)>0)
				node->left=deleteNode(node->left,key);
			else if(comparator.cmprtr(node->key,key)<0)
				node->right = deleteNode(node->right,key);
			else if(comparator.cmprtr(node->key,key)==0){
				// we are at the node which is to be deleted
				
				if(node->right == NULL && node->left == NULL){
					// case 1 - the node to be deleted node is the leaf node
					// cout<<"deleting "<<node->key<<endl;
					node=NULL;
					free(node);
					// return node;
				}else if(node->left==NULL && node->right != NULL){
					// case 2 - the node to be deleted node has one child(right child)
					node=node->right;
				}else if(node->right==NULL && node->left !=NULL){
					// case 2 - the node to be deleted node has one child(left child)
					node=node->left;
				}else if(node->left !=NULL && node->right != NULL){
					// the node to be deleted has both child 
					TreeNode<T>* newNode = inorderSuccessor(node);
					node->key = newNode->key;
					node->frequency = newNode->frequency;
					node->right = deleteNode(node->right,newNode->key);
					free(newNode);
				}	
			}
			
			if(node==NULL)
				return node;
			
			updateHeight(node);
			updateNodeCount(node);
			
			int balanceFactor = giveHeightDifference(node);
			
			if(balanceFactor > 1 ){
				// cout<<"bf > 1 : imbalance at "<<node->key<<endl;
				if(giveHeightDifference(node->left) >= 0 )
					return rotateRight(node);
				else if(giveHeightDifference(node->left) < 0){
					node->left = rotateLeft(node->left);
					return rotateRight(node);
				}
					
			}
			
			if(balanceFactor<-1){
				if(giveHeightDifference(node->right) <= 0 ){
					return rotateLeft(node);
				}else if(giveHeightDifference(node->right) > 0 ){
					node->right = rotateRight(node->right);
					return rotateLeft(node);
				}
			}
 		   		
    		return node;
		}
		void deleteNode(T key){
			root=deleteNode(root,key);		
		}
		int count_range(T e1,T e2){
			return count_range(root,e1,e2);
		}
		void insert(T key){
			totalNodes++;
			root = insert(root,key);		
		}
		T Kth_largest(int k){
			if(k>totalNodes)
				return defaultValue;
			else
				return Kth_largest(root,k);
		}
		
};
/*
// DRIVER FOR CLASS
void driverForClass(){
	
	cout<<"1 - INSERT "<<endl;
	cout<<"2 - DELETE "<<endl;
	cout<<"3 - SEARCH "<<endl;
	cout<<"4 - COUNT OCCURENCES "<<endl;
	cout<<"5 - LOWER BOUND "<<endl;
	cout<<"6 - UPPER BOUND "<<endl;
	// cout<<"7 - CLOSEST ELEMENT "<<endl;
	cout<<"8 - KTH LARGEST "<<endl;
	cout<<"9 - COUNT RANGE"<<endl;
	cout<<"10 - PRINT INORDER"<<endl;
	cout<<"11 - PRINT PREORDER"<<endl;
	cout<<"0 - EXIT"<<endl;
	
	//default value for dummy 
	Dummy dummyDefault;
		
	// member variable for the dummy class
	string name,program;
	int rollNo,priority;
	double marks;
	
	AVLTree<Dummy> classAVLTree(dummyDefault);

	Dummy e1,e2;
	
	int ch;
	do{
		cin>>ch;
		switch(ch){
			case 0 :		break;
			case 1 :	{	//INSERT
							// if same priority is inserted no updation
							cin>>name>>rollNo>>marks>>program>>priority;
							Dummy input(name,rollNo,marks,program,priority);
							classAVLTree.insert(input);	
						}	break; 
						
			case 2 : 	{	//DELETE
							cin>>priority;
							Dummy input("",0,0.0,"",priority);
							classAVLTree.deleteNode(input);	
						}	break;
						
			case 3 :	{	//SEARCH
							cin>>priority;
							Dummy input("",0,0.0,"",priority);
							cout<<classAVLTree.search(input)<<endl;
						}	break;
						
			case 4 :	{	//COUNT OCCURENCES
							cin>>priority;
							Dummy input("",0,0.0,"",priority);
							cout<<classAVLTree.count_occurences(input)<<endl;
						}	break;
						
			case 5 :	{	//LOWER_BOUND
							cin>>priority;
							Dummy input("",0,0.0,"",priority);
							Dummy lowerBound = classAVLTree.lower_bound(input);
							cout<<"["	<<lowerBound.name<<","
										<<lowerBound.rollNo<<","
										<<lowerBound.marks<<","
										<<lowerBound.program<<","
										<<lowerBound.priority<<","
									"]\n";
							
						}	break;
						
			case 6 :	{	//UPPER_BOUND
							cin>>priority;
							Dummy input("",0,0.0,"",priority);
							Dummy upperBound = classAVLTree.upper_bound(input);
							cout<<"["	<<upperBound.name<<","
										<<upperBound.rollNo<<","
										<<upperBound.marks<<","
										<<upperBound.program<<","
										<<upperBound.priority<<","
									"]\n";										
						}	break;
						
			case 8 :	{	//KTH_LARGEST
							int k;
							cin>>k;
							Dummy kthLargest = classAVLTree.Kth_largest(k);
							cout<<"["	<<kthLargest.name<<","
										<<kthLargest.rollNo<<","
										<<kthLargest.marks<<","
										<<kthLargest.program<<","
										<<kthLargest.priority<<","
									"]\n";
						}	break;
						
			case 9 :	{	//COUNT_RANGE
							int priority1,priority2;
							cin>>priority1>>priority2;
							Dummy e1("",0,0.0,"",priority1);
							Dummy e2("",0,0.0,"",priority2);
							cout<<classAVLTree.count_range(e1,e2)<<endl;
						}	break;
						
			case 10 :	{	//INORDER PRINT
							classAVLTree.inorderPrint(classAVLTree.getRoot());
							cout<<endl;
						}	break;
			case 11 :	{	//PREORDER PRINT
							classAVLTree.preOrderPrint(classAVLTree.getRoot());
							cout<<endl;
						}	break;
			default : 	{
							cout<<"Wrong Input. Enter number from the menu"<<endl;
						}
			
		}
		
	}while(ch!=0);
}
*/

// DRIVER FOR PRIMITIVE

void driverForPrimitive(){
	
	cout<<"1 - INSERT "<<endl;
	cout<<"2 - DELETE "<<endl;
	cout<<"3 - SEARCH "<<endl;
	cout<<"4 - COUNT OCCURENCES "<<endl;
	cout<<"5 - LOWER BOUND "<<endl;
	cout<<"6 - UPPER BOUND "<<endl;
	cout<<"7 - CLOSEST ELEMENT "<<endl;
	cout<<"8 - KTH LARGEST "<<endl;
	cout<<"9 - COUNT RANGE"<<endl;
	cout<<"10 - PRINT INORDER"<<endl;
	cout<<"11 - PRINT PREORDER"<<endl;
	cout<<"0 - EXIT"<<endl;
	
	// change the datatype and the default value
	
	int defaultVal=0, input,e1,e2;
	AVLTree<int> avlTree(defaultVal);
	
		
	int ch;
	do{
		cin>>ch;
		switch(ch){
			case 0 :		break;
			case 1 :	{	//INSERT
							cin>>input;
							avlTree.insert(input);	
						}	break; 
						
			case 2 : 	{	//DELETE
							cin>>input;
							avlTree.deleteNode(input);	
						}	break;
						
			case 3 :	{	//SEARCH
							cin>>input;
							cout<<avlTree.search(input)<<endl;
						}	break;
						
			case 4 :	{	//COUNT OCCURENCES
							cin>>input;
							cout<<avlTree.count_occurences(input)<<endl;
						}	break;
						
			case 5 :	{	//LOWER BOUND
							cin>>input;
							cout<<avlTree.lower_bound(input)<<endl;
						}	break;
						
			case 6 :	{	//UPPER BOUND
							cin>>input;
							cout<<avlTree.upper_bound(input)<<endl;
										
						}	break;
						
			case 7 :	{	//CLOSEST ELEMENT
							cin>>input;
							cout<<avlTree.closest_element(input)<<endl;
						}	break;
						
			case 8 :	{	//KTH_LARGEST
							int k;
							cin>>k;
							cout<<avlTree.Kth_largest(k)<<endl;
						}	break;
						
			case 9 :	{	//COUNT RANGE
							cin>>e1>>e2;
							cout<<avlTree.count_range(e1,e2)<<endl;
						}	break;
						
			case 10 :	{	//INORDER PRINT
							avlTree.inorderPrint(avlTree.getRoot());
							cout<<endl;
						}	break;
						
			case 11 :	{	//PREORDER PRINT
							avlTree.preOrderPrint(avlTree.getRoot());
							cout<<endl;
						}	break;
						
			default : 	{
							cout<<"Wrong Input. Enter number from the menu."<<endl;
						}
		}
		
	}while(ch!=0);	
}
// 
int main(){
	
	// driverForClass();
	driverForPrimitive();
	return 0;
}
		