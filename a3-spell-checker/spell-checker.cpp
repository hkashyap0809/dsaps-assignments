// spell-checker.cpp
#include<iostream>
#include <vector>
#include <string>
using namespace std;

class TrieNode{
	public:
		TrieNode* alphabets[26];
		bool isEnd=false;
		TrieNode(){
			for(int i=0;i<26;i++)
				alphabets[i]=NULL;
		}	
};
class Trie{
	public:
		TrieNode* trieRoot;
		vector<string> allWords;
		Trie(){
			trieRoot = new TrieNode();
		}
		
		// UTILITY FUNCTIONS
		static bool compare(string a, string b){
			return a.compare(b)<0;
		}
		
		void printVector(vector<string> words){
			for(int i=0;i<words.size();i++){
				cout<<words.at(i)<<endl;
			}
		}
		long min(long a, long b){
			return a<b ? a : b;
		}
		
		void getAllWordsFromThisRoot(TrieNode* trieNode, string str ,vector<string> &words){
			if(trieNode->isEnd)
				words.push_back(str);
			
			for(int i=0;i<26;i++){
				if(trieNode->alphabets[i]){
					getAllWordsFromThisRoot(trieNode->alphabets[i],str+((char)(i+'a')),words);
				}
			}
		}
		
		vector<string> getAllWordsFromThisRoot(TrieNode* trieNode,string word){
			vector<string> words;
			getAllWordsFromThisRoot(trieNode,word,words);
			return words;
		}
		
		void printCompleteTrie(){
			allWords = getAllWordsFromThisRoot(trieRoot,"");
			printVector(allWords);
		}
		
		void setAllWords(){
			allWords = getAllWordsFromThisRoot(trieRoot,"");
		}
		
		string giveWordsFromVector(vector<string> words){
			string result="";
			for(int i=0;i<words.size();i++){
				result=result+words[i]+"\n";
			}
			return result;
		}
		
		// INSERT A WORD INTO THE TRIE
		void insert(string word){			
			int wordLen = word.length();
			TrieNode* tempTrieRoot = trieRoot;
			
			for(int i=0;i<wordLen;i++){
				int ch = word[i]-'a';
								
				if(tempTrieRoot->alphabets[ch]==NULL){
					// children is not present
					TrieNode* temp = new TrieNode();
					tempTrieRoot->alphabets[ch]=temp;
				}else{
					// a child is already present
				}
				tempTrieRoot=tempTrieRoot->alphabets[ch];

			}
			tempTrieRoot->isEnd=true;
		}
		
		// SPELL CHECK
		//  Check if the input string is present in the dictionary.
		bool spellCheck(string word){
			TrieNode* tempTrieRoot = trieRoot;
			int wordLen = word.length();
			for(int i=0;i<wordLen;i++){
				int index = word[i]-'a';
				if(tempTrieRoot->alphabets[index]==NULL)
					return false;
				
				tempTrieRoot=tempTrieRoot->alphabets[index];
			}
			return tempTrieRoot->isEnd;
		}
		
		// AUTOCOMPLETE
		// Find all the words in the dictionary which begin with the given input.
		string autoComplete(string word){
			string result="";
			TrieNode* tempTrieRoot = trieRoot;
			int wordLen = word.length();
			
			for(int i=0;i<wordLen;i++){
				int index = word[i]-'a';
				if(tempTrieRoot->alphabets[index]==NULL)
					return "";
				
				tempTrieRoot=tempTrieRoot->alphabets[index];
			}

			vector<string> autoCompleteWords = getAllWordsFromThisRoot(tempTrieRoot,word);
			result = result + to_string(autoCompleteWords.size()) +"\n";
			result = result + giveWordsFromVector(autoCompleteWords);
			return result;

		}
		
		// AUTOCORRECT
		// Find all the words in the dictionary which are at an edit distance (Levenshtein distance) 
		// of at most 3 from the given input.
		int editDistanceDynamicProg(string word1, string word2){
			int wordLen1 = word1.length();
			int wordLen2 = word2.length();
			vector<vector<int>> memory(wordLen1+1,vector<int>(wordLen2+1,-1));
			for(int i=0;i<=wordLen1;i++){
				memory[i][0]=i;
			}
			for(int j=0;j<=wordLen2;j++){
				memory[0][j]=j;
			}
			
			for(int i=1;i<=wordLen1;i++){
				for(int j=1;j<=wordLen2;j++){
					if(word1[i-1]==word2[j-1]){
						memory[i][j]=memory[i-1][j-1];
					}else{
						memory[i][j]=1+min(memory[i-1][j],min(memory[i][j-1],memory[i-1][j-1]));
					}
				}
			}
			return memory[wordLen1][wordLen2];
		}
		
		string autocorrect(string str){
			string result="";
			vector<string> levenDist;
			setAllWords();
			for(int i=0;i<allWords.size();i++){
				if(editDistanceDynamicProg(str,allWords.at(i))<=3){
					levenDist.push_back(allWords.at(i));
				}
			}
			result=result+to_string(levenDist.size())+"\n";
			result =result + giveWordsFromVector(levenDist);
			return result;
		}
				
					
		
};

int main(){
	
	// MAIN
	int noOfWords,queries;
	cin>>noOfWords>>queries;
	
	Trie trie;
	for(int i=0;i<noOfWords;i++){
		string word;
		cin>>word;
		trie.insert(word);
	}
	
	string result="";
	
	while(queries--){
		int choice; string word;
		cin>>choice>>word;
		if(choice==1){
			// spell check
			result=result+to_string(trie.spellCheck(word))+"\n";
		}else if(choice==2){
			// autocomplete
			result=result+trie.autoComplete(word);
		}else if(choice==3){
			// autocorrect
			result=result+trie.autocorrect(word);
		}else{
			cout<<"INVALID CHOICE\n";
		}
	}
	cout<<result;
	return 0;
}