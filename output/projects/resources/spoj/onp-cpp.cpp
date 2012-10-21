/* Transform the algebraic expression with brackets into
 * RPN form (Reverse Polish Notation). Two-argument
 * operators: +, -, *, /, ^ (priority from the lowest to
 * the highest), brackets ( ). Operands: only letters:
 * a,b,...,z. Assume that there is only one RPN form
 * (no expressions like a*b*c).
 * Input
 *
 * t [the number of expressions <= 100]
 * expression [length <= 400]
 * [other expressions]
 *
 * Text grouped in [ ] does not appear in the input file.
 * Output
 *
 * The expressions in RPN form, one per line.
 *
 * Example
 *
 * Input:
 * 3
 * (a+(b*c))
 * ((a+b)*(z+x))
 * ((a+t)*((b+(a+c))^(c+d)))
 *
 * Output:
 * abc*+
 * ab+zx+*
 * at+bac++cd+^*
 */

#include <iostream>
using namespace::std;

class Expr {
public:
    char op;
    Expr * left;
    Expr * right;
    Expr() {    }
    ~Expr() {
        delete left;
        delete right;
    }
    virtual void postPrint() {
        left->postPrint();
        right->postPrint();
        cout << op;
    }
};

class Atom : public Expr {
public:
    Atom(char v) {
        op = v;
    }
    void postPrint() {
        cout << op;
    }
};

Expr * readInfix(istream & in) {
    Expr * expr = new Expr();
    char temp = ' ';
    in >> temp;
    if (temp == '(') {
        expr->left = readInfix(in);
        in >> expr->op;
        expr->right = readInfix(in);
    } else {
        return new Atom(temp);
    }
    if (in.peek() == ')')
        in >> temp;
    return expr;
}

int main() {
    Expr * expr = new Expr();

    int cases;
    cin >> cases;

    for (int i=0; i<cases; ++i) {
        expr = readInfix(cin);
        expr->postPrint();
        cout << "\n";
    }

    return 0;
}
