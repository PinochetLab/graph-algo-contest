#include <iostream>
#include <algorithm>

size_t n;
int a[101][101];

int main()
{
    std::cin >> n;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    for (size_t k = 0; k < n; k++) {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < n; j++) {
                a[i][j] = std::min(a[i][j], a[i][k] + a[k][j]);
            }
        }
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}