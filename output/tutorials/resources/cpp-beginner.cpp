//*********************************************
/* Sample_1.cpp
 * 
 * Zeb Fross
 * 
 * 10/29/09
 *
 * Demonstrates common C++ syntax, including
 * the following:
 *     - Functions
 *     - Declaring Variables
 *     - Strings
 *     - Switch Case
 *     - Arrays
 *     - Getting input from file
 *     - Outputting to file
 *     - External Function Calls
 *     - Formatting Output
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
 * Functions external to main() must be declared above
 * where they are used.
 */
void foo(char letter)
{
	if (letter == 'a')
		cout << "letter is 'a'";
	else
		cout << "letter is not 'a'";
	cout << endl;
}

/*
 * This is a function that returns a value.
 */
char foo2(int n)
{
	if (n == 1)
		return 'a';
	else
		return '?';
}

int main()
{
	//*********************************************
	// DECLARING VARIABLES
	//*********************************************
	int a = 5;
	long double b(65000);

	//*********************************************
	// STRINGS
	//*********************************************
	string myString = "This is my string.";
	for (int i=0; i<myString.size(); i++) {	// Accessing elements
		cout << myString.at(i);
	}
	cout << endl;
	
	//*********************************************
	// SWITCH-CASE
	//*********************************************
	int num = 4;
	switch (num) {
    case 1:
         cout << "one" << endl;
         break;        // "break" is necessary
    case 2:
         cout << "two" << endl;
         break;
    case 3:
         cout << "three" << endl;
         break;
    case 4:
         cout << "four" << endl;
         break;
    case 5:
         cout << "five" << endl;
         break;
    }

	//*********************************************
	// ARRAYS
	//*********************************************
	int intArr[] = {5, 2, 1, 4, 3};
	char arr2d[3][3] = {{'a', 'b', 'c'}, {'a', 'b', 'c'}, {'a', 'b', 'c'}};
	char charArr[10];
	for (int i=0; i<10; i++) {
		charArr[i] = i;
	}
	sort(intArr, intArr+5);			// intArr = {1, 2, 3, 4, 5}

	/* in.txt
	 * 
	 * line 1
	 * line 2
	 * line 3
	 */
	 
	//*********************************************
	// GETTING INPUT FROM FILE
	//*********************************************
	string input;
	string input2;
	string line3Str;
	int line3Int;
	ifstream fin("in.txt");
	
	getline(fin, input);		    // input = entire first line of input file
	getline(fin, input2);			// input2 = entire second line of input file
	fin >> line3Str;				// reads characters until whitespace is reached
	fin >> line3Int;				// reads characters until whitespace is reached

	//*********************************************
	// OUTPUTTING TO FILE
	//*********************************************
	ofstream fout("out.txt");
	fout << input << endl;			// notice direction of <<
	fout << input2 << endl;
	fout << line3Str
		  << line3Int;
	fout << endl;

	/* out.txt
	 * 
	 * line 1
	 * line 2
	 * line3
	 */

	//*********************************************
	// EXTERNAL FUNCTION CALLS
	//*********************************************
	char aChar = 'a';
	int aInt = 0;
	foo(aChar);					// OUTPUT: letter is 'a'
	aChar = foo2(aInt);
	foo(aChar);					// OUTPUT: letter is not 'a'

	//*********************************************
	// FORMATTING OUTPUT
	//*********************************************
	string out = "output";
	cout << setfill('*') << setw(20) << ' ' << endl;
	double dub = 123.456789;
	cout << setprecision(3) << dub << endl;	// 123.456
	cout << setprecision(4) << dub << endl;	// 123.4567
	cout << setprecision(8) << dub << endl;	// 123.45678900

    system("PAUSE");
	return 0;
}

