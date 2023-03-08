#include <string>
#include <iostream>
#include <queue>
#include <vector>

int is, ie, js, je;
size_t ds[8][8];
std::vector<std::pair<int, int>> ps[8][8];

const std::pair<int, int> vs[10]{ {1, 2}, {2, 1}, {-1, 2}, {2, -1}, {-2, -1}, {-1, -2}, {1, -2}, {-2, 1} };

bool isValid(int i) {
    return i >= 0 && i < 8;
}

void string_to_coords(const std::string& s, int& i, int& j) {
    j = std::stoi(std::string(1, s[1])) - 1;
    i = s[0] - 'a';
}

int main()
{
    for (size_t i1 = 0; i1 < 8; i1++) {
        for (size_t i2 = 0; i2 < 8; i2++) {
            ds[i1][i2] = 1000;
        }
    }

    std::string s1, s2;
    std::cin >> s1 >> s2;
    string_to_coords(s1, is, js);
    string_to_coords(s2, ie, je);
    ps[is][js] = { {is, js} };
    ds[is][js] = 0;
    std::queue<std::pair<size_t, size_t>> q;
    q.push({ is, js });
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        int i = v.first;
        int j = v.second;

        for (size_t k = 0; k < 8; k++) {
            int ind_i = i + vs[k].first;
            int ind_j = j + vs[k].second;
            if (isValid(ind_i) && isValid(ind_j)) {
                size_t d1 = ds[i][j] + 1;
                if (d1 < ds[ind_i][ind_j]) {
                    ds[ind_i][ind_j] = d1;
                    auto p = std::vector<std::pair<int, int>>(ps[i][j]);
                    p.push_back({ ind_i, ind_j });
                    ps[ind_i][ind_j] = p;
                    q.push({ ind_i, ind_j });
                }
            }
        }
    }

    for (size_t i = 0; i < ps[ie][je].size(); i++) {
        int ind_i = ps[ie][je][i].first;
        int ind_j = ps[ie][je][i].second;
        std::string s = char(ind_i + 'a') + std::to_string(ind_j + 1) + '\n';
        std::cout << s;
    }

    return 0;
}