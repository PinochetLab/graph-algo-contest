#include <iostream>
#include <vector>
#include <algorithm>

size_t n, m; // число вершин
const size_t MAXN = 100001;
std::vector<int> g[MAXN]; // граф
bool used[MAXN];
std::vector<int> ans;

void dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs(to);
    }
    ans.push_back(v);
}

void topological_sort() {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    ans.clear();
    for (int i = 0; i < n; ++i)
        if (!used[i])
            dfs(i);
    std::reverse(ans.begin(), ans.end());
}


int main()
{
    std::cin >> n >> m;

    for (size_t i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
    }

    topological_sort();
    
    for (size_t i = 0; i < n - 1; i++) {
        int i1 = ans[i];
        int i2 = ans[i + 1];
        if (!std::count(g[i1].begin(), g[i1].end(), i2)) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES\n";

    for (size_t i = 0; i < n; i++) {
        std::cout << (ans[i] + 1) << ' ';
    }

    return 0;
}