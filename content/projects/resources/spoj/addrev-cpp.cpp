/* ACM needs to calculate with reversed numbers.
 * Your task is to add two reversed numbers and
 * output their reversed sum. Of course, the
 * result is not unique because any particular
 * number is a reversed form of several numbers
 * (e.g. 21 could be 12, 120 or 1200 before
 * reversing). Thus we must assume that no zeros
 * were lost by reversing (e.g. assume that the
 * original number was 12).
 * Input
 *
 * The input consists of N cases (equal to about
 * 10000). The first line of the input contains
 * only positive integer N. Then follow the
 * cases. Each case consists of exactly one line
 * with two positive integers separated by space.
 * These are the reversed numbers you are to add.
 * Output
 *
 * For each case, print exactly one line
 * containing only one integer - the reversed
 * sum of two reversed numbers. Omit any leading
 * zeros in the output.
 *
 * Example
 *
 * Sample input:
 *
 * 3
 * 24 1
 * 4358 754
 * 305 794
 *
 * Sample output:
 *
 * 34
 * 1998
 * 1
 */

#include <math.h>
#include <iostream>
using std::cout;
using std::cin;

int reverse(int num) {
	int total = 0;
	int digits = 1;
	while (num % (int)pow(10, digits) != num)
		++digits;

	int j=1;
	for (int i=digits-1; i>=0; --i) {
		int temp = num % (int)pow(10, j);
		if (j > 1)
            temp /= (int)pow(10, j-1);
		temp *= (int)pow(10, i);

		total += temp;
		++j;
	}
	return total;
}

int main() {
	int N;
	cin >> N;
	int a;
	int b;
	int c;

	for (int i=0; i<N; i++) {
		cin >> a;
		cin >> b;
		a = reverse(a);
		b = reverse(b);
		c = a + b;
		c = reverse(c);
		cout << c << "\n";
	}

	return 0;
}

