#include <iostream>
#include <vector>
#include <algorithm>

const size_t MAX1 = 2001;
const size_t MAX2 = 10001;

struct door {
    size_t x, y;
    int bonus;
};

size_t n, m;
bool vs[MAX1];
door doors[MAX2];
int d[MAX1];
bool s[MAX1];
std::vector<size_t> ns[MAX1];

bool has_path(size_t i1, size_t i2) {
    vs[i1] = true;
    if (i1 == i2) return true;
    for (auto x : ns[i1]) {
        if (!vs[x] && has_path(x, i2)) return true;
    }
    return false;
}

std::vector<size_t> iterate() {
    std::vector<size_t> res;
    for (size_t i = 0; i < m; i++) {
        door door = doors[i];
        size_t a = door.x;
        if (!s[a]) continue;
        size_t b = door.y;
        auto c = d[a] + door.bonus;
        if (c > d[b] || !s[b]) {
            d[b] = c;
            s[b] = true;
            res.push_back(b);
        }
    }
    return res;
}

void belman_ford(size_t index) {
    d[index] = 0;
    s[index] = true;
    for (size_t i = 0; i < n - 1; i++) {
        auto qs = iterate();
        if (qs.empty()) break;
    }
}

int main()
{
    std::cin >> n >> m;
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        int c;
        std::cin >> a >> b >> c;
        a--; b--;
        doors[i] = { a, b, c };
        ns[a].push_back(b);
    }

    belman_ford(0);

    if (!s[n - 1]) {
        std::cout << ":(";
        return 0;
    }

    auto cs = iterate();

    for (auto x : cs) {
        if (has_path(x, n - 1)) {
            std::cout << ":)";
            return 0;
        }
        std::fill(vs, vs + n, false);
    }

    std::cout << d[n - 1];

    return 0;
}
