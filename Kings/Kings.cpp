#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using path_t = std::vector<size_t>;

const size_t MAX = 100000;

size_t n, m;
size_t b[MAX];
std::vector<size_t> ns[MAX];
bool vs[MAX];
path_t ps[MAX];
std::pair<size_t, size_t> ds[MAX];

std::pair<size_t, size_t> length(path_t path) {
    size_t len = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        len += (b[path[i + 1]] != b[path[i]]) * (1 + (path[i] % 2 == 1));
    }
    return { len, path.size() };
}

std::vector<size_t> add_to_path(const path_t& v, size_t a) {
    path_t r(v);
    r.push_back(a);
    return r;
}

bool has_path(size_t i1, size_t i2) {
    vs[i1] = true;
    if (i1 == i2) return true;
    for (auto x : ns[i1]) {
        if (!vs[x] && has_path(x, i2)) return true;
    }
    return false;
}

bool contains(const path_t& path, size_t v) {
    return std::count(path.begin(), path.end(), v);
}

void deikstra(size_t index) {
    std::queue<path_t> q;
    q.push({ index });
    while (!q.empty()) {
        path_t p = q.front();
        size_t v = p.back();
        q.pop();
        for (auto x : ns[v]) {
            if (contains(p, x)) continue;
            path_t pa = add_to_path(p, x);
            auto l = length(pa);
            if (l < ds[x]) {
                ds[x] = l;
                ps[x] = path_t(pa);
                q.push(pa);
            }
        }
    }
}

int main()
{
    std::cin >> n >> m;
    for (size_t i = 0; i < n; i++) {
        std::cin >> b[i];
        ds[i] = { MAX, MAX };
    }
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        std::cin >> a >> b;
        a--; b--;
        ns[a].push_back(b);
        ns[b].push_back(a);
    }
    if (!has_path(0, n - 1)) {
        std::cout << "impossible";
        return 0;
    }

    deikstra(0);
    auto l = ds[n - 1];
    auto path = ps[n - 1];
    std::cout << l.first << ' ' << l.second << '\n';
    for (auto x : path) {
        std::cout << (x + 1) << ' ';
    }
    return 0;
}
