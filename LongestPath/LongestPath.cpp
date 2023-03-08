#include <vector>
#include <algorithm>
#include <iostream>

const size_t MAXN = 22;
const size_t MAXM = 1000;

size_t n, m;
std::vector<size_t> ns[MAXN];
bool vs[MAXN];

auto c = [](double a, double b) { return a > b; };

using path_t = std::vector<size_t>;

path_t dfs_path(size_t i) {
    vs[i] = true;
    path_t path{i};
    for (auto x : ns[i]) {
        if (vs[x]) continue;
        path_t p = dfs_path(x);
        p.push_back(i);
        if (p.size() > path.size()) path = p;
    }
    vs[i] = false;
    return path;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        std::cin >> a >> b;
        a--; b--;
        ns[a].push_back(b);
    }
    size_t ind = 0;
    path_t path;
    for (size_t i = 0; i < n; i++) {
        
        path_t p = dfs_path(i);
        if (p.size() > path.size()) {
            path = p;
            ind = i;
        }
        std::fill(vs, vs + n, false);
    }
    std::reverse(path.begin(), path.end());
    std::cout << (path.size() - 1) << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << (path[i] + 1) << ' ';
    }
    return 0;
}
