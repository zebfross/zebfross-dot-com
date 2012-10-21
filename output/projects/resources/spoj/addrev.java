import java.util.Scanner;

/**
 * For documentation, see test.cpp
 * @author zeb
 */
public class addrev {

    public int reverse(int num) {
	int total = 0;
	int digits = 1;
	while (num % (int)Math.pow(10, digits) != num)
            ++digits;

	int j=1;
	for (int i=digits-1; i>=0; --i) {
            int temp = num % (int)Math.pow(10, j);
            if (j > 1)
            temp /= (int)Math.pow(10, j-1);
            temp *= (int)Math.pow(10, i);

            total += temp;
            ++j;
	}
	return total;
    }

    public addrev() throws Exception {
        Scanner in = new Scanner(System.in);
        int cases = in.nextInt();
        for (int i=0; i<cases; ++i) {
            int intA = reverse(in.nextInt());
            int intB = reverse(in.nextInt());
            System.out.println(reverse(intA + intB));
        }
    }

    public static void main(String[] args) throws Exception {
        new addrev();
    }
}
