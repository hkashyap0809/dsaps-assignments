// 2022201050_A2_Q4.cpp
// Harshit Kashyap | IIIT Hyderabad | MTech CSE 
#include <iostream>
#include <algorithm>
using namespace std;

// ***********************************************
// SINGLY LINKED LIST NODE
// ***********************************************
template <class T>
class MatrixNode{
	public:
		int row;
		int col;
		T value;
		MatrixNode *next;
		MatrixNode(){
			row=0;
			col=0;
			value=NULL;
		}
		MatrixNode(int row,int col,T value){
			this->row=row;
			this->col=col;
			this->value=value;
		}
};
// ***********************************************
// SINGLY LINKED LIST
// ***********************************************
template <class T>
class MatrixLinkedList{
	public:
		MatrixNode<T>* head;
		MatrixLinkedList(){
			head=NULL;
		}
		
		void insertNode(int row,int col, T value){
			MatrixNode<T>* node = new MatrixNode<T>(row,col,value);
			MatrixNode<T>* temp = head;
	
			if(head==NULL){
				head = node;
				return;
			}
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=node;
		}
		void printSparseMatrix(){
			if(head==NULL){
				cout<<"(-1,-1,-1)"<<endl;
				return;
			}
			MatrixNode<T>* temp=head;
			while(temp!=NULL){
				cout<<temp->row<<" ";
				temp=temp->next;
			}
			cout<<endl;
			temp=head;
			while(temp!=NULL){
				cout<<temp->col<<" ";
				temp=temp->next;
			}
			cout<<endl;
			temp=head;
			while(temp!=NULL){
				cout<<temp->value<<" ";
				temp=temp->next;
			}
			cout<<endl;
		}
		
		void printMatrix(int row, int col){	
			MatrixNode<T>* temp = head;
			
			for(int i=0;i<row;i++){
				for(int j=0;j<col;j++){
					if(temp==NULL)
						cout<<"0 ";
					else{
						if(temp->row == i && temp->col==j){
							cout<<temp->value<<" ";
							temp=temp->next;
						}else
							cout<<"0 ";
					}
				}
				cout<<endl;
			}
		}
		
		void printBoth(int row, int col){
			cout<<"NORMAL MATRIX \n";
			printMatrix(row,col);
			cout<<"SPARSED MATRIX \n";
			printSparseMatrix();
			cout<<"\n";
		}
	
};
// ***********************************************
// SPARSE MATRIX OPERATIONS - LINKED LIST
// ***********************************************
template <class T>
class SparseMatrixLinkedList{
	public:
		void addSparseMatrixLinkedList(MatrixLinkedList<T> matrix1, MatrixLinkedList<T> matrix2,int row, int col){
			
			MatrixNode<T>* temp1 = matrix1.head;
			MatrixNode<T>* temp2 = matrix2.head;
			
			MatrixLinkedList<T> finalList;
			
			
			while(temp1!=NULL && temp2!=NULL){
				if(temp1->row==temp2->row){
					if(temp1->col==temp2->col){
						finalList.insertNode(temp1->row,temp1->col,temp1->value+temp2->value);
						temp1=temp1->next;
						temp2=temp2->next;
					}else if(temp1->col<temp2->col){
						finalList.insertNode(temp1->row,temp1->col,temp1->value);
						temp1=temp1->next;
					}else if(temp1->col>temp2->col){
						finalList.insertNode(temp2->row,temp2->col,temp2->value);
						temp2=temp2->next;
					}
				}else if(temp1->row<temp2->row){
						finalList.insertNode(temp1->row,temp1->col,temp1->value);
						temp1=temp1->next;
				}else if(temp1->row>temp2->row){
						finalList.insertNode(temp2->row,temp2->col,temp2->value);
						temp2=temp2->next;
				}	
			}
			while(temp1!=NULL){
				finalList.insertNode(temp1->row,temp1->col,temp1->value);
				temp1=temp1->next;		
			}
			while(temp2!=NULL){
				finalList.insertNode(temp2->row,temp2->col,temp2->value);
				temp2=temp2->next;
			}
			finalList.printMatrix(row,col);
			cout<<endl;
		}
		MatrixLinkedList<T> transposeMatrixLinkedList(MatrixLinkedList<T> matrix,int row,int col,int size){
			MatrixNode<T>* temp = matrix.head;
			
			while(temp!=NULL){
				int swap=temp->row;
				temp->row=temp->col;
				temp->col=swap;
				
				temp=temp->next;
			}
			
			MatrixNode<T>* newNode = mergeSortLinkedList(matrix.head);
			matrix.head=newNode;
			return matrix;
		}
		
		// MERGE SORT
		int sizeOfLL(MatrixNode<T>* head){
			if(head==NULL)
				return 0;
			else if(head->next==NULL)
				return 1;
			
    		MatrixNode<T>* temp=head;
    		int count=0;
    		while(temp->next!=NULL){
        		count++;
        		temp=temp->next;
    		}
    		return count+1;	
		}
		
		MatrixNode<T>* middle(MatrixNode<T>* head){				
    		int size = sizeOfLL(head);
    		MatrixNode<T>* temp = head;
    		for(int i=0;i<(size/2)-1;i++){
		    	temp=temp->next;
		    }
		    return temp;
		}
				
		MatrixNode<T>* merge(MatrixNode<T>* head1, MatrixNode<T>* head2){
		    MatrixNode<T>* temp1=head1;
		    MatrixNode<T>* temp2=head2;
		    
		    MatrixNode<T>* mergedHead= NULL;
		    
			if(temp1->row > temp2->row || temp1->row==temp2->row && temp1->col>temp2->col){
		        mergedHead = new MatrixNode<T>(temp2->row,temp2->col,temp2->value);
		        temp2=temp2->next;
		    }
		    else{
		        mergedHead = new MatrixNode<T>(temp1->row,temp1->col,temp1->value);
		        temp1=temp1->next;
		    }
		    
		    MatrixNode<T>* temp = mergedHead;;
		    
		    while(temp1!=NULL && temp2!=NULL){
				if(temp1->row > temp2->row || temp1->row==temp2->row && temp1->col>temp2->col){
		            	MatrixNode<T>* node = new MatrixNode<T>(temp2->row,temp2->col,temp2->value);
		            	temp->next=node;
		            	temp=temp->next;
		            	temp2=temp2->next;
		        }else{
		            MatrixNode<T>* node = new MatrixNode<T>(temp1->row,temp1->col,temp1->value);
		            temp->next=node;
		            temp=temp->next;
		            temp1=temp1->next;
		        }
		    }
		    if(temp1){
		    	temp->next=temp1;
		    }
		    if(temp2){
		    	temp->next = temp2;
		    }
		    return mergedHead;   
		}

		MatrixNode<T>* mergeSortLinkedList(MatrixNode<T>* head) {
    		if(head->next==NULL)
    		    return head;
    		
    		MatrixNode<T>* list1;
    		MatrixNode<T>* list2;
    		MatrixNode<T>* temp;
    		list1 = head;
    		temp = middle(head);
    		list2=temp->next;
    		temp->next=NULL;    		
    		MatrixNode<T>* resultNode = merge(mergeSortLinkedList(list1),mergeSortLinkedList(list2));
    		return resultNode;
		}
		
		void multiplyMatrixLinkedList(MatrixLinkedList<T> matrix1, MatrixLinkedList<T> matrix2,int m, int n, int p, int size1, int size2){
			MatrixLinkedList<T> transposeMatrix2 =  transposeMatrixLinkedList(matrix2,n,p,size2);
			
			MatrixLinkedList<T> resultMatrix;
			
			MatrixNode<T>* temp1 = matrix1.head;
			MatrixNode<T>* temp2 = transposeMatrix2.head;
			
			
			while(temp1!=NULL){
				
				int row1 = temp1->row;
				int col1 = temp1->col;
				T val1 = temp1->value;
				temp2 = transposeMatrix2.head;
				while(temp2!=NULL){
					int row2 = temp2->row;
					int col2 = temp2->col;
					T val2 = temp2->value;
					if(col1==col2){
						resultMatrix.insertNode(row1,row2,val1*val2);
					}
					temp2=temp2->next;
				}
				temp1=temp1->next;
			}	
			
			MatrixLinkedList<T> finalMatrix;
			temp1 = mergeSortLinkedList(resultMatrix.head);
			finalMatrix.insertNode(temp1->row,temp1->col,temp1->value);
			temp1=temp1->next;
			
			temp2=finalMatrix.head;

			// removing duplicates
			while(temp1!=NULL){
				int row1 = temp1->row;
				int col1 = temp1->col;
				T val1 = temp1->value;
				
				int row2 = temp2->row;
				int col2 = temp2->col;
				T val2 = temp2->value;
				
				if(row1==row2 && col1==col2){
					temp2->value= temp2->value + temp1->value;
				}else{
					finalMatrix.insertNode(temp1->row,temp1->col,temp1->value);
					temp2=temp2->next;
				}
				temp1=temp1->next;
			}
			// cout<<"RESULT MULTIPLICATION DUPLICATES REMOVED\n";
			finalMatrix.printMatrix(m,p);
		}
		
		void takeLinkedListInput1(){
			// Matrix1 input
			int row,col;
			cin>>row>>col;

			MatrixLinkedList<T> matrix;
	
			int size=0;
			// input for matrix
			for(int i=0;i<row;i++){
				for(int j=0;j<col;j++){
					T val;
					cin>>val;
					if(val!=0){
						matrix.insertNode(i,j,val);	
						size++;	
					}
				}
			}
			// matrix.printBoth(row,col);
			MatrixLinkedList<T> transposedMatrix;
			transposedMatrix = transposeMatrixLinkedList(matrix,row,col,size);
			// cout<<"TRANSPOSE\n";
			transposedMatrix.printMatrix(col,row);
		}
		void takeLinkedListInput2(int choice){
			// Matrix1 input
			int row1,col1;
			cin>>row1>>col1;

			MatrixLinkedList<T> matrix1;
	
			int size1=0;
			// input for matrix1
			for(int i=0;i<row1;i++){
				for(int j=0;j<col1;j++){
					T val;
					cin>>val;
					if(val!=0){
						matrix1.insertNode(i,j,val);	
						size1++;	
					}
				}
			}
			
			// Matrix2 input
			int row2,col2;
			cin>>row2>>col2;
			MatrixLinkedList<T> matrix2;
			int size2=0;
			// input for matrix2
			for(int i=0;i<row2;i++){
				for(int j=0;j<col2;j++){
					T val;
					cin>>val;
					if(val!=0){
						matrix2.insertNode(i,j,val);	
						size2++;	
					}
				}
			}

			// only addition and multiplication here
					
			if(choice == 1){
				// Matrix addition
				if(row1==row2 && col1==col2){
					addSparseMatrixLinkedList(matrix1,matrix2,row1,col1);
				}else{
					cout<<"Invalid order of matrix. Matrix cannot be added\n";
				}
			}else if(choice == 3){
				// Matrix Multiplication
				if(col1==row2){
					multiplyMatrixLinkedList(matrix1,matrix2,row1,col1,col2,size1,size2);
				}else{
					cout<<"Invalid order of matrix. Matrix cannot be multiplied.\n";
				}
			}
		}
};

// ***********************************************
// SPARSE MATRIX OPERATIONS - ARRAY  
// ***********************************************

template <class T>
class SparseMatrixArray{
	public:
		
		void printArray(T *array,int size){
			for(int i=0;i<size;i++){
				cout<<array[i]<<" ";
			}
			cout<<endl;
		}

		void printMatrix(T **matrix,int row,int col){
			int iter=0;
			for(int i=0;i<row;i++){
				for(int j=0;j<col;j++){
					if(matrix[0][iter]==i && matrix[1][iter]==j){
							cout<<matrix[2][iter]<<" ";
							iter++;
					}else{
						cout<<"0 ";
					}
				}
				cout<<endl;
			}
		}
		
		void printSparse(T** matrix, int size){
			printArray(matrix[0],size);
			printArray(matrix[1],size);
			printArray(matrix[2],size);
		}
		void printBoth(T **matrix,int row, int col, int size){
			cout<<"NORMAL 2D MATRIX"<<endl;
			printMatrix(matrix,row,col);
			cout<<"SPARSE MATRIX "<<endl;
			printSparse(matrix,size);
			cout<<"\n";
		}
		void merge(T** matrix, int start, int mid, int end){
			
			T arr[3][end-start+1];
			int i=start;
			int j = mid+1;
			int k=0;
			
			while(i<=mid && j<=end){
				if(matrix[0][i]==matrix[0][j] && matrix[1][i]>matrix[1][j] ||
					matrix[0][i] > matrix[0][j] ){
					arr[0][k] = matrix[0][j];
					arr[1][k] = matrix[1][j];
					arr[2][k] = matrix[2][j];
					k++;
					j++;				
				}else{
					arr[0][k] = matrix[0][i];
					arr[1][k] = matrix[1][i];
					arr[2][k] = matrix[2][i];
					k++;
					i++;
				}
			}
			
			while(i<=mid){
					arr[0][k] = matrix[0][i];
					arr[1][k] = matrix[1][i];
					arr[2][k] = matrix[2][i];
					k++;
					i++;
			}
			while(j<=end){
					arr[0][k] = matrix[0][j];
					arr[1][k] = matrix[1][j];
					arr[2][k] = matrix[2][j];
					k++;
					j++;
			}
			
			for(int i=0;i<k;i++){
				matrix[0][start+i] = arr[0][i];
				matrix[1][start+i] = arr[1][i];
				matrix[2][start+i] = arr[2][i];
			}
		}
		
		void mergeSortByRow(T** matrix, int start, int end){
			if(start<end){
				int mid = (start+end)/2;
				mergeSortByRow(matrix,start,mid);
				mergeSortByRow(matrix,mid+1,end);
				merge(matrix,start,mid,end);
			}
		}
		
		void addMatrixArray(T **matrix1, T **matrix2,int row, int col,int size1, int size2){
			T **matrix;
			matrix=new T*[3];
			matrix[0]=new T[size1+size2];
			matrix[1]=new T[size1+size2];
			matrix[2]=new T[size1+size2];
			
			int m1=0;int m2=0;int m=0;
			while(m1<size1 && m2<size2){
				if(matrix1[0][m1]==matrix2[0][m2]){
					if(matrix1[1][m1]==matrix2[1][m2]){
						// both row and columns are same - addition
						matrix[0][m]=matrix1[0][m1];
						matrix[1][m]=matrix1[1][m1];
						matrix[2][m]=matrix1[2][m1]+matrix2[2][m2];
						m1++;
						m2++;
						m++;
					}else if(matrix1[1][m1]<matrix2[1][m2]){
						// matrix1 should be copied
						matrix[0][m] = matrix1[0][m1];
						matrix[1][m] = matrix1[1][m1];
						matrix[2][m] = matrix1[2][m1];
						m++;
						m1++;
					}else if(matrix1[1][m1]>matrix2[1][m2]){
						// matrix2 should be copied
						matrix[0][m] = matrix2[0][m2];
						matrix[1][m] = matrix2[1][m2];
						matrix[2][m] = matrix2[2][m2];
						m2++;
						m++;
					}
				}else if(matrix1[0][m1]<matrix2[0][m2]){
					// matrix1 should be copied
					matrix[0][m]=matrix1[0][m1];
					matrix[1][m]=matrix1[1][m1];
					matrix[2][m]=matrix1[2][m1];
					m1++;
					m++;
				}else if(matrix1[0][m1]>matrix2[0][m2]){
					// matrix2 should be copied
					matrix[0][m] = matrix2[0][m2];
					matrix[1][m] = matrix2[1][m2];
					matrix[2][m] = matrix2[2][m2];
					m2++;
					m++;
				}
			}
		
			while(m1<size1){
				matrix[0][m]=matrix1[0][m1];
				matrix[1][m]=matrix1[1][m1];
				matrix[2][m]=matrix1[2][m1];
				m1++;
				m++;
			}
			while(m2<size2){
				matrix[0][m] = matrix2[0][m2];
				matrix[1][m] = matrix2[1][m2];
				matrix[2][m] = matrix2[2][m2];
				m2++;
				m++;
			}
			printMatrix(matrix,row,col);
		}
		
		T **transposeMatrixArray(T **matrix,int size){
			// returnes the transpose of a matrix
			T **transposeMatrix;
			transposeMatrix=new T*[3];
			transposeMatrix[0]=new T[size];
			transposeMatrix[1]=new T[size];
			transposeMatrix[2]=new T[size];
			
			T newMatrix[3][size];

			
			for(int i=0;i<size;i++){
				transposeMatrix[0][i]=matrix[1][i];
				transposeMatrix[1][i]=matrix[0][i];
				transposeMatrix[2][i]=matrix[2][i];
				
				newMatrix[0][i] = transposeMatrix[0][i];
				newMatrix[1][i] = transposeMatrix[1][i];
				newMatrix[2][i] = transposeMatrix[2][i];
			}
			// sort the transposed matrix
			mergeSortByRow(transposeMatrix,0,size-1);			
			return transposeMatrix;			
		}
		void multiplyMatrixArray(T **matrix1, T ** matrix2, int rowA, int col, int rowB,int size1, int size2){
			T **newMatrix;
			newMatrix=transposeMatrixArray(matrix2,size2);
	
			T **resultMatrix;
			resultMatrix=new T*[3];
			resultMatrix[0]=new T[size1+size2];
			resultMatrix[1]=new T[size1+size2];
			resultMatrix[2]=new T[size1+size2];
			
			int resultSize=0;
			
			for(int i=0;i<size1;i++){
				int row1 = matrix1[0][i];
				int col1 = matrix1[1][i];
				T val1 = matrix1[2][i];
				
				for(int j=0;j<size2;j++){
					int row2 = newMatrix[0][j];
					int col2 = newMatrix[1][j];
					T val2 = newMatrix[2][j];
					if( col1 == col2){
						resultMatrix[0][resultSize] = row1;
						resultMatrix[1][resultSize] = row2;
						resultMatrix[2][resultSize] = val1*val2;
						resultSize++;
					}
					
				}	
			}
			
			mergeSortByRow(resultMatrix,0,resultSize-1);
			
			T **finalMatrix;
			finalMatrix=new T*[3];
			finalMatrix[0]=new T[size1+size2];
			finalMatrix[1]=new T[size1+size2];
			finalMatrix[2]=new T[size1+size2];
			
			int finalSize=0;
			finalMatrix[0][0]=resultMatrix[0][0];
			finalMatrix[1][0]=resultMatrix[1][0];
			finalMatrix[2][0]=resultMatrix[2][0];
			
			// Remove duplicates and add them
			for(int i=1;i<resultSize;i++){
				
				if(resultMatrix[0][i] == finalMatrix[0][finalSize] && resultMatrix[1][i] == finalMatrix[1][finalSize]){
					finalMatrix[2][finalSize] = finalMatrix[2][finalSize] + resultMatrix[2][i];
				}else{
					finalSize++;
					finalMatrix[0][finalSize] = resultMatrix[0][i];
					finalMatrix[1][finalSize] = resultMatrix[1][i];
					finalMatrix[2][finalSize] = resultMatrix[2][i];
				}		
			}
			
			finalSize=finalSize+1;
			
			printMatrix(finalMatrix,rowA,rowB);
			
		}
		void takeArrayInput1(){
			// Matrix 1 input
			int row,col;
			cin>>row>>col;
			
			T **matrix;
			matrix= new T*[3];
			matrix[0]=new T[row*col];
			matrix[1]=new T[row*col];
			matrix[2]=new T[row*col];
	
			int size=0;
			// input for matrix1
			for(int i=0;i<row;++i){
				for(int j=0;j<col;++j){
					T val;
					cin>>val;
					if(val!=0){
						matrix[0][size]=i;
						matrix[1][size]=j;
						matrix[2][size]=val;	
						size++;	
					}
				}
			}
			// take the transpose and print	
			T **transposedMatrix = 	transposeMatrixArray(matrix,size);
			printMatrix(transposedMatrix,col,row);
				
		}
		void takeArrayInput2(int choice){
			
			// Matrix 1 input
			int row1,col1;
			cin>>row1>>col1;
			
			T **matrix1;
			matrix1= new T*[3];
			matrix1[0]=new T[row1*col1];
			matrix1[1]=new T[row1*col1];
			matrix1[2]=new T[row1*col1];
	
			int size1=0;
			// input for matrix1
			for(int i=0;i<row1;++i){
				for(int j=0;j<col1;++j){
					T val;
					cin>>val;
					if(val!=0){
						matrix1[0][size1]=i;
						matrix1[1][size1]=j;
						matrix1[2][size1]=val;	
						size1++;	
					}
				}
			}
			
			//Matrix 2 input 
			int row2,col2;
			cin>>row2>>col2;
			T **matrix2;
			matrix2 = new T*[3];
			matrix2[0]=new T[row2*col2];
			matrix2[1]=new T[row2*col2];
			matrix2[2]=new T[row2*col2];
			
			int size2=0;
			for(int i=0;i<row2;++i){
				for(int j=0;j<col2;++j){
					T val;
					cin>>val;
					if(val!=0){
						matrix2[0][size2]=i;
						matrix2[1][size2]=j;
						matrix2[2][size2]=val;	
						size2++;	
					}
				}
			}
			
			if(choice == 1){
				// Matrix Addition
				if(row1==row2 && col1==col2){
					addMatrixArray(matrix1,matrix2,row1,col1,size1,size2);
				}else{
					cout<<"The order of the matrix is wrong. The matrices cannot be added.\n";
				}
			}else if(choice == 3){
				// Matrix Multiplication
				if(col1==row2){
					multiplyMatrixArray(matrix1,matrix2,row1,col1,col2,size1,size2);
				}else{
					cout<<"The order of the two matrix is wrong.The matrices cannot be multiplied."<<endl;
				}
			}
	}

};
// ***********************************************
// MAIN FUNCTION 
// ***********************************************
int main(){
	int choice;
	cout<<"1 - Array \n";
	cout<<"2 - Linked List\n";
	cin>>choice;
	if(choice==1){
		// Array
		SparseMatrixArray<float> arrayOperation;
		int ch;
		cout<<"1 - Adddition\n";
		cout<<"2 - Transpose\n";
		cout<<"3 - Multiplication\n";
		cin>>ch;
		if(ch==2){
			arrayOperation.takeArrayInput1();
		}else if(ch==1 || ch == 3){
			arrayOperation.takeArrayInput2(ch);
		}else {
			cout<<"Wrong Input\n";
			cout<<"EXIT\n";
		}
	}else if(choice==2){
		// LinkedList1
		SparseMatrixLinkedList<double> linkedListOperation;
		int ch;
		cout<<"1 - Adddition\n";
		cout<<"2 - Transpose\n";
		cout<<"3 - Multiplication\n";
		cin>>ch;
		if(ch==2){
			linkedListOperation.takeLinkedListInput1();
		}else if(ch==1 || ch == 3){
			linkedListOperation.takeLinkedListInput2(ch);
		}else {
			cout<<"Wrong Input\n";
			cout<<"\n";
		}
	}else{
		cout<<"Wrong Input\n";
		cout<<"EXIT\n";
	}
	return 0;
}
