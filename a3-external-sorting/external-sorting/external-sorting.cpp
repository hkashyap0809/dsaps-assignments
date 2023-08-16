// 2022201050_A3_Q2.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <sys/time.h>
#include <stdio.h>
using namespace std;
struct NumIndex{
	long long value;
	long long index;
};
class MinHeap{
	public:
		long long topIndex;
		struct NumIndex heap[10000];
		MinHeap(){
			topIndex=-1;
		}
		
		void heapify(long long n, long long i){
			
			long long smallestNode = i;
			long long leftIndex = 2*i + 1;
			long long rightIndex = 2*i + 2;
			
			if(rightIndex < size() && heap[rightIndex].value<heap[smallestNode].value)
				smallestNode=rightIndex;
			if(leftIndex < size() && heap[leftIndex].value<heap[smallestNode].value){
				smallestNode=leftIndex;
			}
			if(smallestNode!=i){
				long long tempValue = heap[smallestNode].value;
				long long tempIndex = heap[smallestNode].index;
				
				heap[smallestNode].value = heap[i].value;
				heap[smallestNode].index = heap[i].index;
				
				heap[i].value = tempValue;
				heap[i].index = tempIndex;
				
				heapify(topIndex,smallestNode);	
			}
			
		}
		void buildHeap(){
			int nonLeafIndex = (size()/2)-1;
			
			for(int i=nonLeafIndex;i>=0;i--){
				heapify(topIndex,i);
			}
		}
		void pop(){
			long long tempValue =heap[0].value;
			long long tempIndex = heap[0].index;
			
			heap[0].value = heap[topIndex].value;
			heap[0].index = heap[topIndex].index;
			
			heap[topIndex].value = tempValue;
			heap[topIndex].index = tempIndex;
			
			topIndex--;
			heapify(topIndex,0);	
		}
		struct NumIndex top(){
			struct NumIndex topVal;
			topVal.value=heap[0].value;
			topVal.index=heap[0].index;
			return topVal;
		}
		void push(long long x, long long y){
			topIndex++;
			heap[topIndex].value = x;
			heap[topIndex].index = y;
			heapify(topIndex,0);	

		}
		long long size(){
			return topIndex+1;
		}

		void printHeap(){
			for(int i=0;i<=topIndex;i++){
				cout<<"("<<heap[i].value<<","<<heap[i].index<<") ";
			}
			cout<<endl;
		}
};

void mergeFile(string outputFile,long long noOfFiles, 
	long long totalNumbers,long long chunkSize){
	
	MinHeap minHeap;
	ifstream fin[noOfFiles];
	
	vector<bool> isFileEmpty(noOfFiles,false);
	
	// opening input files
	for(int i=0;i<noOfFiles;i++){
		string fileName = "./data/"+to_string(i)+".txt";
			fin[i].open(fileName);
	}
	
	long num;
	
	// pushing 1st number of each file to a heap
	for(int i=0;i<noOfFiles;i++){
		if(fin[i]>>num){
			minHeap.push(num,i);
		}
	}
	
	// opening output file
	ofstream fout;
	fout.open(outputFile,ofstream::out | ofstream::trunc);
	
	NumIndex pair;
	
	while(totalNumbers--){
			pair = minHeap.top();
			minHeap.pop();
			
			long number = pair.value;
			long index = pair.index;
			
			fout<<number<<"\n";
			
			if(!fin[index].eof()){
				fin[index]>>num;
				minHeap.push(num,index);
			}else{
				for(int i=0;i<noOfFiles;i++){
					if(!fin[i].eof()){
						index=i;
						break;
					}
				}
				fin[index]>>num;
				minHeap.push(num,index);
			}
			
	}
	
	for(int i=0;i<noOfFiles;i++){
		fin[i].close();
	}
	fout.close();
	
}

void createSortedOutputFiles(string fileName,long long chunkSize,long long &fileIterator,
	long long &numIterator,
    long long &totalNumbers){
	vector<long long> numbers;
	long long num;

	ifstream input_file(fileName);
	if (!input_file.is_open()) {
        cout << "Error opening : "<<fileName<<endl;
        return ;
    }
    ofstream fout[10000]; 
    
    string outputfilename = "./data/"+to_string(fileIterator)+".txt";
	fout[fileIterator].open(outputfilename,ofstream::out | ofstream::trunc);
		
	while(input_file>>num){
		totalNumbers++;
		numIterator++;
		numbers.push_back(num);
		
		if(numIterator==chunkSize){
			// write into the file and open a new file
			sort(numbers.begin(),numbers.end());
			for(const auto &n : numbers){
				fout[fileIterator]<<n<<" ";
			}
			
			numbers.clear();
			numIterator=0;
			fileIterator++;
			outputfilename = "./data/"+to_string(fileIterator)+".txt";
			fout[fileIterator].open(outputfilename,ofstream::out | ofstream::trunc);
		}
	}
	
	// if the file is not empty
	if(totalNumbers>0){
		
		// the last file has not been written
		if(numIterator>0 && totalNumbers > chunkSize){
			sort(numbers.begin(),numbers.end());
			for(const auto &n : numbers){
					fout[fileIterator]<<n<<" ";
			}
		}
		
		// only one file was created
		if(totalNumbers<=chunkSize){
			sort(numbers.begin(),numbers.end());
			for(const auto &n : numbers){
					fout[fileIterator]<<n<<" ";
			}
	
		}
			
		// one extra file was created with no numbers in it
		if(numIterator==0){
			const char *deleteFile = outputfilename.c_str();
			remove(deleteFile);
			fileIterator--;
		}
	}
	
	// closing the output and input files
	for(int i=0;i<=fileIterator;i++){
		fout[i].close();
	}
	input_file.close();
	
}


int main(int argc, char** argv){
	
	string inputFile(argv[1]);
	string outputFile(argv[2]);
	long long chunkSize = 1000000;
	struct timeval start, end;

	long long fileIterator = 0;
    long long numIterator = 0;
    long long totalNumbers = 0;
    
    gettimeofday(&start, NULL);

	createSortedOutputFiles(inputFile,chunkSize,fileIterator,numIterator,totalNumbers);
	
	// if there were no numbers, then just delete the temporary file
	if(totalNumbers==0){
		remove(("./data/"+to_string(fileIterator)+".txt").c_str());
		fileIterator=-1;
		ofstream fout;
		fout.open(outputFile,ofstream::out | ofstream::trunc);
		fout.close();
	}
	
	// if only one file is created then just
	// write it directly to the output file
	if(totalNumbers>0 && fileIterator==0){
		string singleFile = "./data/0.txt";
		ifstream input_file(singleFile);
		ofstream fout;
		long long num;
		
		if(!input_file.is_open()){
			cout<<"Error opening file : 0.txt.\n";
		}
		
		fout.open(outputFile,ofstream::out | ofstream::trunc);
		while(input_file>>num){
			fout<<num<<"\n";
		}
		
		fout.close();
		input_file.close();
	}
	
	// there are numbers in the input file and there are more than 1 file created
	if(totalNumbers>0 and fileIterator>0){
 		mergeFile(outputFile,fileIterator+1,totalNumbers,chunkSize);
	}
	
	
	
	// time(&time2);
	gettimeofday(&end, NULL);

	double netTime = (end.tv_sec - start.tv_sec)*1e6;
	netTime = (netTime + (end.tv_usec - start.tv_usec))*1e-6;
	
	cout<<"Number of integers in the temporary file : "<<chunkSize<<"\n";
	cout<<"Number of temporary files created : "<<fileIterator+1<<"\n";	
	cout<<"Total time taken : "<<setprecision(2)<<fixed<<netTime<<" sec\n";
	

	

    return 0;
		
}