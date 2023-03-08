#include <iostream>
#include <sstream>
#include <string>

size_t n;
char a[1000][1001];


int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    std::cin.ignore(1, '\n');
    for (size_t i = 0; i < n; i++) {
        std::cin.getline(a[i], n + 1);
    }

    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                if (a[i][k] == '1' && a[k][j] == '1') {
                    a[i][j] = '1';
                }
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        std::cout << a[i] << '\n';
    }

    return 0;
}