#include <math.h>
#include <iostream>

class BI
{
public:
	short dg[200];
	short sz;

	BI( void ) {	}
	BI( int n ) {
		int ind(0);
		if (n > 0) {
			int d = 1;
			int v = 10;
			while ( (n % v) != n ) {
				v *= 10;
				d += 1;
			}
			for ( int i(1); i < d+1; ++i ) {
				int modA = n % (int)(pow(10, (double)i));
				int modB = n % (int)(pow(10, (double)(i-1)));
				dg[ind++] = (modA-modB)/(int)(pow(10, (double)(i-1)));
			}
			sz = d;
		} else {
			sz = 0;
		}
	}

	BI & operator=( const BI & ri ) {
		sz = ri.sz;
		for (int i(0); i < ri.sz; ++i) {
			dg[i] = ri.dg[i];
		}
		return *this;
	}

	bool operator<=( const BI & ri ) {
		if (sz < ri.sz) return true;
		if (sz > ri.sz) return false;

		for ( int i(sz-1); i >= 0; --i ) {
			if (dg[i] < ri.dg[i]) return true;
			if (dg[i] > ri.dg[i]) return false;
		}
		return true;
	}

	const BI operator!( void ) {
		BI fact(1);
		for (BI i(2); i <= *this; i += 1) {
			fact *= i;
		}
		return fact;
	}

	BI & operator+=( const BI & ri ) {
		int ca = 0;
		int i(0);
		for ( i; i < ri.sz; ++i ) {
			if (i >= sz) {
				dg[i] = (ri.dg[i]+ca)%10;
				++sz;
				ca = ((ri.dg[i]+ca) > 9) ? 1 : 0;
			} else {
				int c = ((dg[i]+ri.dg[i]+ca) > 9) ? 1 : 0;
				dg[i] = (dg[i]+ri.dg[i]+ca)%10;
				ca = c;
			}
		}
		while (i < sz && ca > 0) {
			int c = ((dg[i]+ca) > 9) ? 1 : 0;
			dg[i] = (dg[i]+ca)%10;
			ca = c;
			++i;
		}
		if (ca > 0) {
			dg[i++] = ca;
			++sz;
		}

		return *this;
	}

	BI & operator*=( const BI & ri ) {
		BI r = ri;
		BI l = *this;
		for ( BI j(2); j <= r; j += 1 ) {
			*this += l;
		}
		return *this;
	}
};

int main( const char **ppchArgs, int iN )
{
	int cases, num;
	std::cin >> cases;

	for (int i(0); i < cases; ++i) {
		std::cin >> num;
		BI f(num);
		f = !f;
		for ( int i(f.sz-1); i >= 0; --i )
			std::cout << f.dg[i];
		std::cout << "\n";
	}

	return 0;
}
