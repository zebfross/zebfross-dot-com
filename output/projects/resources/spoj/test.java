import java.util.Scanner;

public class test {
	public static void main(String args[]) {
		Scanner in = new Scanner(System.in);
		
		int temp;

		temp = in.nextInt();

		while (temp != 42) {
			System.out.println(temp);
			temp = in.nextInt();
		}
		in.close();
	}
}
