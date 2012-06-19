//*********************************************
/* Sample_3.cpp
 * 
 * Zeb Fross
 * 
 * 12/28/09
 *
 * Demonstrates intermediate - advanced 
 *   C++ syntax, including the following:
 *   - Unions
 *   - Function Pointers
 */
//*********************************************

#include <iostream>
using std::cout;
using std::endl;

/// UNIONS
union Data {   char c;
               unsigned short s;
               unsigned long l;
               };
               
/*
 * Function Pointers - Not for the weak
 * These are the functions to be pointed to
 */
 template <class T>
T add(T one, T two) {  return one + two;   }             
 template <class T>
T sub(T one, T two) {  return one - two;   }
 template <class T>
T mul(T one, T two) {  return one * two;   }
 template <class T>
T div(T one, T two) {  return one / two;   }

// Function pointer
double (*mathOp)(double, double) = NULL;

// Accepting a function pointer as a parameter
template <class T>
T operate(T one, T two, T (*op)(T, T)) {
            return op(one, two);
}

// This function returns a pointer to a
// function. This gets real messy.
double (*getOp(char c))(double, double) {
       switch (c) {
       case 'a':
            return &add;
       case 's':
            return &sub;
       case 'm':
            return &mul;
       default:
            return &div;
       }
}

int main()
{	
	//*********************************************
	// UNIONS
	//*********************************************
    
    /* Uions use only one memory address for all
     *   their data members, so its size is only
     *   as big as the largest data member, in
     *   this case, a double.
     * Memory Allocation (/ = bit):
     * char  ////////
     * short ////////////////
     * long  ////////////////////////////////
     */
     Data data;
     data.l = 1073759267;
    /*
     * Memory Allocation after assignment:
     *   1-byte   2-byte   3-byte   4-byte
     * |00100011|01000100|00000000|01000000|
     * |   35   |
     * |      17443      |
     * |             1073759267            |
     */
    
    // Function Pointers
    mathOp = add;
    cout << mathOp(3, 3) << endl;  // 6
    mathOp = div;
    cout << mathOp(3, 3) << endl;  // 1

	//*********************************************
	// FUNCTION POINTERS AS PARAMETERS
	// The name of the function I wish to call is
	// being passed as a parameter.
	//*********************************************
	cout << "add " << operate(3, 3, add) << endl;
	cout << "sub " << operate(3, 3, sub) << endl;
	cout << "mul " << operate(3, 3, mul) << endl;
	cout << "div " << operate(3, 3, div) << endl;
	
	// Functions returning function pointers
	mathOp = getOp('m');
	cout << mathOp(3, 3) << endl;   // 9
	mathOp = getOp('s');
	cout << mathOp(3, 3) << endl;   // 0

    system("PAUSE");
	return 0;
}
