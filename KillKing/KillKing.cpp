#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

const size_t MAXN = 100001;
const size_t MAXM = 300001;

size_t n, m, s, t;
std::vector<int> ns[MAXN];
bool us[MAXN];

using vis_t = std::vector<int>;
using path_t = std::vector<size_t>;

auto comp = [](const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) {
    return p1.first < p2.first;
};

path_t p;
std::set<std::pair<size_t, size_t>, decltype(comp)> ps(comp);
vis_t v;

bool get_path(size_t i, size_t j, path_t& path) {
    if (i == j) {
        path.push_back(i);
        return true;
    }
    us[i] = true;
    for (auto x : ns[i]) {
        if (us[x]) continue;
        if ( get_path(x, j, path) ) {
            path.push_back(i);
            return true;
        }
    }
    return false;
}

void dfs(int start, size_t i) {
    us[i] = true;
    auto g = ps.find({ i, 0 });
    if (g != ps.end()) {
        int ind = (*g).second;
        if (ind > start) {
            if (ind > start + 1) {
                v[start + 1] += 1;
                v[ind] -= 1;
            }
            return;
        }
    }
    for (auto x : ns[i]) {
        if (x < 0 || us[x]) continue;
        dfs(start, x);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> s >> t;
    s--; t--;
    for (size_t i = 0; i < m; i++) {
        size_t a, b;
        std::cin >> a >> b;
        if (a == b) continue;
        a--; b--;
        ns[a].push_back(b);
    }
    get_path(s, t, p);
    std::reverse(p.begin(), p.end());
    for (size_t i = 0; i < p.size(); i++) {
        ps.insert({ p[i], i });
    }
    
    v = vis_t(p.size(), 0);
    for (int i = 0; i < p.size() - 1; i++) {
        int a = p[i];
        int b = p[i + 1];
        std::replace(ns[a].begin(), ns[a].end(), b, -1);
    }
    std::fill(us, us + n, false);
    for (int i = 0; i < ps.size() - 2; i++) {
        dfs(i, p[i]);
    }
    std::vector<size_t> ans;
    int s = 0;
    for (size_t i = 1; i < p.size() - 1; i++) {
        s += v[i];
        if (!s) {
            ans.push_back(p[i]);
        }
    }
    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (auto x : ans) std::cout << (x + 1) << ' ';
    return 0;
}