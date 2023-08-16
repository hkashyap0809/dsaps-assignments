# Spell Checker

Design an efficient spell checker using trie data structure which supports the
functionalities mentioned below.
### Required Features:
- Spell Check: Check if the input string is present in the dictionary.
- Autocomplete: Find all the words in the dictionary which begin with
the given input.
- Autocorrect: Find all the words in the dictionary which are at an edit
distance(Levenshtein distance) of at most 3 from the given input.
### Input Format:
- First line will contain two space separated integers n, q which
represents the number of words in the dictionary and the number of
queries to be processed respectively.
- Next n lines will contain a single string s which represents a word in
the dictionary.
- Next q lines will contain two space separated values, First one will
be an integer ai and second will be a string t<sub>i</sub>.
- a<sub>i</sub> = 1 means Spell Check operation needs to be done on t<sub>i</sub>.
- a<sub>i</sub> = 2 means Autcomplete operation needs to be done on t<sub>i</sub>.
- a<sub>i</sub> = 3 means Autocorrect operation needs to be done on t<sub>i</sub>.
### Output Format:
For each query print the result in a new line.
- Spell check: Print ‘1’ if string is present in the dictionary, otherwise
‘0’.
- Autocomplete & Autocorrect: Print the number of words in the first
line. The following lines will be the set of words in lexicographical order.
- Constraints:<br/>
1 <= n <= 1000<br/>
1 <= q <= 1000<br/>
1 <= len(s) <= 100<br/>
1 <= len(t<sub>i</sub>) <= 110<br/>
s and t<sub>i</sub> will only contain lowercase alphabets(a,b,..y,z)<br/>
#### Sample Input:
10 4 <br/>
consider <br/>
filters <br/>
filers <br/>
entitled <br/>
tilers <br/>
litter <br/>
dames <br/>
filling <br/>
grasses <br/>
fitter <br/>
1 litter <br/>
1 dame <br/>
2 con<br/>
3 filter
#### Sample Output:
1<br/>
0<br/>
1<br/>
consider <br/>
5 <br/>
filers <br/>
filters <br/>
fitter <br/>
litter <br/>
tilers<br/>
#### Note:
- References: Levenshtein Distance
- Only trie should be used for storing the words in the dictionary.
- You are allowed to use vector for this problem