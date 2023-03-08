#include <iostream>
#include <queue>
#include <vector>
#include <vector>
#include <string>
#include <algorithm>

const size_t MAX = 100000;

size_t n, m;

bool vs[MAX];
std::vector<int> ns[MAX];
std::string ans[MAX];
bool us[MAX];
size_t groups[MAX];
int timer, tin[MAX], fup[MAX];

void dfs(int v, int p = -1) {
    us[v] = true;
    tin[v] = fup[v] = timer++;
    for (size_t i = 0; i < ns[v].size(); i++) {
        int to = ns[v][i];
        if (to < 0) continue;
        if (to == p)  continue;
        if (us[to])
            fup[v] = std::min(fup[v], tin[to]);
        else {
            dfs(to, v);
            fup[v] = std::min(fup[v], fup[to]);
            if (fup[to] > tin[v]) {
                ns[v][i] = -1;
                ns[to];
                std::replace(ns[to].begin(), ns[to].end(), v, -1);
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    for (int i = 0; i < n; ++i)
        us[i] = false;
    for (int i = 0; i < n; ++i)
        if (!us[i])
            dfs(i);
}

void find_friends(size_t x, size_t g) {
    std::queue<size_t> q;
    q.push(x);
    vs[x] = true;
    while (!q.empty()) {
        size_t a = q.front();
        q.pop();
        groups[a] = g;
        for (auto x : ns[a]) {
            if (x < 0) continue;
            if (vs[x]) continue;
            q.push(x);
            vs[x] = true;
        }
    }
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
        if (a == b) continue;
        ns[a].push_back(b);
        ns[b].push_back(a);
    }

    find_bridges();

    size_t ind = 0;

    for (size_t i = 0; i < n; i++) {
        if (vs[i]) {
            continue;
        }
        find_friends(i, ind);
        ind++;
    }

    for (size_t i = 0; i < n; i++) {
        ans[groups[i]] += std::to_string(i + 1) + ' ';
    }

    std::cout << ind << '\n';

    for (size_t i = 0; i < ind; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}
