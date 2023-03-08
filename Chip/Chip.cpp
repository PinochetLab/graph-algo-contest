#include <vector>
#include <algorithm>
#include <iostream>

const size_t MAX = 50000;

size_t n;

size_t colors[MAX];
size_t numbers[2 * MAX];
int fst[MAX];
int snd[MAX];
std::vector<size_t> ns1[4 * MAX];
std::vector<size_t> ns2[4 * MAX];
size_t ans[MAX];

size_t get_index(size_t i, bool b) {
    return 2 * i + b;
}

bool eq_colored(size_t i, size_t j) {
    return colors[numbers[i]] == colors[numbers[j]];
}

bool used[4 * MAX];
int comp[4 * MAX];
std::vector<size_t> order;

void dfs1(size_t v) {
    used[v] = true;
    for (auto to : ns2[v]) {
        if (used[to]) continue;
        dfs1(to);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (auto to : ns1[v]) {
        if (comp[to] != -1) continue;
        dfs2(to, cl);
    }
}

int main()
{
    std::cin >> n;
    std::fill(fst, fst + n, -1);
    std::fill(snd, snd + n, -1);
    for (size_t i = 0; i < n; i++) {
        std::cin >> colors[i];
    }
    for (size_t i = 0; i < 2 * n; i++) {
        size_t num;
        std::cin >> num;
        num--;
        numbers[i] = num;
        if (fst[num] == -1) fst[num] = i;
        else snd[num] = i;
    }
    for (size_t i = 0; i < 2 * n; i++) {
        size_t ne = (i + 1) % (2 * n);
        size_t num = numbers[i];
        size_t ot = i == fst[num] ? snd[num] : fst[num];

        size_t ti = get_index(i, true);
        size_t fi = get_index(i, false);

        size_t tne = get_index(ne, true);
        size_t fne = get_index(ne, false);

        size_t tot = get_index(ot, true);
        size_t fot = get_index(ot, false);

        if (eq_colored(i, ne)) {
            ns1[ti].push_back(fne);
            ns2[fne].push_back(ti);

            ns1[tne].push_back(fi);
            ns2[fi].push_back(tne);
        }
        ns1[ti].push_back(fot);
        ns2[fot].push_back(ti);

        ns1[fi].push_back(tot);
        ns2[tot].push_back(fi);
    }
    
    std::fill(comp, comp + 4 * n, -1);
    std::fill(used, used + 4 * n, false);

    for (int i = 0; i < 4 * n; i++) {
        if (used[i]) continue;
        dfs1(i);
    }
    std::fill(used, used + 4 * n, false);

    for (size_t i = 0, j = 0; i < 4 * n; i++) {
        int v = order[4 * n - i - 1];
        if (comp[v] == -1) {
            dfs2(v, j++);
        }
    }

    for (size_t i = 0; i < 2 * n; i++) {
        if (comp[2 * i] == comp[2 * i + 1]) {
            std::cout << "NO";
            return 0;
        }
    }

    std::cout << "YES\n";

    for (size_t i = 0; i < 2 * n; ++i) {
        size_t fi = 2 * i;
        size_t ti = 2 * i + 1;
        if (comp[fi] > comp[ti]) {
            ans[numbers[i]] = i;
        }
    }

    for (size_t i = 0; i < n; i++) {
        std::cout << (ans[i] + 1) << ' ';
    }

    return 0;
}
