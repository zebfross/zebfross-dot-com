import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * For documentation, see onp.cpp
 * @author zeb
 */
public class onp {

    private class Expr {
        public char op;
        public Expr left;
        public Expr right;
        public Expr() {    }
        public void postPrint() {
            left.postPrint();
            right.postPrint();
            System.out.print(op);
        }
    }

    private class Atom extends Expr {
        public char symbol;
        public Atom(char o) {
            symbol = o;
        }
        public void postPrint() {
            System.out.print(symbol);
        }
    }

    public Expr readInfix(BufferedReader in) throws Exception {
        Expr expr = new Expr();
        char temp = (char)in.read();
        if (temp == '(') {
            expr.left = readInfix(in);
            expr.op = (char)in.read();
            expr.right = readInfix(in);
        } else if ((int)temp > 64 && (int)temp < 123) {
            return new Atom(temp);
        }
        in.mark(1);
        temp = (char)in.read();
        if (temp != ')')
            in.reset();
        return expr;
    }

    public onp() {
        BufferedReader in = new BufferedReader(
                new InputStreamReader(System.in));
        try {
            int cases = Integer.parseInt(in.readLine());
            for (int i=0; i<cases; ++i) {
                Expr expr = readInfix(in);
                expr.postPrint();
                System.out.print("\n");
                in.read();
            }
        } catch (Exception e) {

        }
    }

    public static void main(String[] args) {
        new onp();
    }
}
