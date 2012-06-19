//*********************************************
/* Sample_2.cpp
 * 
 * Zeb Fross
 * 
 * 12/28/09
 *
 * Demonstrates intermediate C++ syntax,
 * including the following:
 *      - Sorting
 *      - Vectors
 *      - Iterators
 *      - Permutations
 *      - Stacks
 *      - Queues
 */
//*********************************************

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>
using namespace std;

/*
 * Comparison function for ints. Use as
 * third argument in sort functions.
 */
bool compare(const int& a, const int& b)
{
	if (a < b)
		return false;
	else
		return true;
}

int main()
{
	//*********************
	// SORT WITH ITERATORS
	// #INCLUDE <ALGORITHM>
	//*********************
	sort(myString.begin(), myString.end());
	cout << myString << endl;

	int find = myString.find('m');				// Searching
	// m will be found. find equals 10
	if (find == string::npos) {
		// 'm' was not found
		cout << "m was not found" << endl;
	} else {
		// 'm' was found
		cout << "m was found" << endl;
		cout << "find = " << find << endl;
	}

	myString.erase(8, 3);			// erase(position to start erasing, how far to erase)
	myString.insert(2, "-");

	string str1("hello ");
	str1 += "everyone";				// Combining strings -> str1 = "hello everyone"

	//*********************************************
	// VECTORS:
	// Don't be afraid of vectors. All they are are
	// glorified arrays. You can add elements to
	// them, retreive elements from them, and do
	// all kinds of things much more easily than
	// with arrays.
	//*********************************************
	vector<int> intVector;
	vector<vector<char> > charVector;			// two dimensional vector

	intVector.push_back(5);						// Adding elements

	int c = intVector.at(0);					// Accessing elements

	intVector.erase(intVector.begin());

	intVector.push_back(43);
	intVector.push_back(2);
	intVector.push_back(34);
	intVector.push_back(100);
	intVector.push_back(34);
	intVector.push_back(34);
	intVector.push_back(43);
	intVector.push_back(43);
	intVector.push_back(43);
	// Sorts the vector is descending order
	sort(intVector.begin(), intVector.end());

	//*********************************************
	// ITERATORS
	//*********************************************
	// Move all the non-unique values to the back of the vector
	vector<int>::iterator vecIT = unique(intVector.begin(), intVector.end());
	vector<int>::iterator vecBegin = intVector.begin();

	while (vecBegin != vecIT) {
		cout << *vecBegin << " ";
		++vecBegin;
	}
	cout << endl;

	//*********************************************
	// PERMUTATIONS
	// This function produces all the permutations
	// of the vector.
	//*********************************************
	sort(intVector.begin(), intVector.end());
	do {
		for (int i=0; i<intVector.size(); i++) {
			// Do something
		}
	} while (next_permutation(intVector.begin(), intVector.end()));

	//*********************************************
	// STACKS
	// First in, last out
	//*********************************************
	stack<char> charStack;
	charStack.push('a');
	charStack.push('b');
	charStack.push('c');

	char d = charStack.top();					// d = 'c'
	charStack.pop();
	d = charStack.top();						// d = 'b'

	//*********************************************
	// QUEUES
	// First in, first out
	//*********************************************
	queue<char> charQ;
	charQ.push('a');
	charQ.push('b');
	charQ.push('c');

	d = charQ.front();							// d = 'a'
	charQ.pop();
	d = charQ.front();							// d = 'b'

    system("PAUSE");
	return 0;
}
