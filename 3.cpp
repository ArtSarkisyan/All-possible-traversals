#include <iostream>
#include <vector>
#include <algorithm>

void dfs_impl(
    const std::vector<std::vector<int>>& g,
    std::vector<char>& used,
    std::vector<int>& v,
    int u) {
    used[u] = true;
    for (int w : g[u]) {
        if (!used[w]) {
            dfs_impl(g, used, v, w);
        }
    }
    v.push_back(u);
}

void dfs(const std::vector<std::vector<int>>& g, std::vector<char>& used, std::vector<int>& v, int start) {
    dfs_impl(g, used, v, start);
}

std::vector<int> topological_sort(std::vector<std::vector<int>>& gr) {
    int size = gr.size();
    std::vector<char> used(size, false);
    std::vector<int> v;
    for (int u = 0; u < size; ++u) {
        if (!used[u]) {
            dfs(gr, used, v, u);
        }
    }
    std::reverse(v.begin(), v.end());
    return v;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
    }

    std::vector<int> result = topological_sort(g);
    for (int vertex : result) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}