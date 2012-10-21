import java.io.BufferedReader;
import java.io.InputStreamReader;

/**
 * For documentation, see fctrl.cpp
 * @author zeb
 */
public class fctrl {

    public static int Z(int N) {
        int zeroes = 0;
        int power = 1;
        int temp = (int)(N / Math.pow(5, power));
        while (temp > 0) {
            zeroes += temp;
            temp = (int)(N / Math.pow(5, ++power));
        }
        return zeroes;
    }

    public static void main(String[] args) {
        BufferedReader in = new BufferedReader(
                new InputStreamReader(System.in));
        try {
        int cases = Integer.parseInt(in.readLine());

        for (int i=0; i<cases; ++i) {
            System.out.println(Z(Integer.parseInt(in.readLine())));
        }
        } catch (Exception e) {
            // Do nothing!
        }
    }
}
