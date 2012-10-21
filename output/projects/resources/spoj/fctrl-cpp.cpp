#include <math.h>
#include <iostream>

long Z(int num) {
    long zeroes = 0;
    int power = 1;
    long temp = num / pow(5, power);
    while (temp > 0) {
        zeroes += temp;
        ++power;
        temp = num / pow(5, power);
    }
    return zeroes;
}

int main() {
    int cases;
    std::cin >> cases;

    for (int i=0; i<cases; ++i) {
        long N;
        std::cin >> N;
        std::cout << Z(N) << "\n";
    }

    return 0;
}
