#include <iostream>
#include <vector>
#include <algorithm>

bool valid_topological_sort(const std::vector<std::vector<int>>& gr, 
                            const std::vector<int>& switched) {
    std::vector<int> position(gr.size(), -1);
    for (size_t i = 0; i < switched.size(); i++) {
        position[switched[i]] = i;
    }
    for (size_t i = 0; i < gr.size(); i++) {
        for (int neighbor : gr[i]) {
            if (position[i] > position[neighbor]) {
                return false; 
            }
        }
    }
    return true;
}

bool has_cycle_dfs(const std::vector<std::vector<int>>& gr, int v, std::vector<bool>& used, std::vector<bool>& in_stack) {
    used[v] = true;
    in_stack[v] = true;

    for (int u : gr[v]) {
        if (!used[u]) {
            if (has_cycle_dfs(gr, u, used, in_stack))
                return true;
        } else if (in_stack[u]) {
            return true;
        }
    }
    in_stack[v] = false;
    return false;
}

bool has_cycle(const std::vector<std::vector<int>>& gr) {
    std::vector<bool> used(gr.size(), false);
    std::vector<bool> in_stack(gr.size(), false);

    for (int i = 0; i < gr.size(); i++) {
        if (!used[i] && has_cycle_dfs(gr, i, used, in_stack))
            return true;
    }
    return false;
}
void generate_topological_sorts(const std::vector<std::vector<int>>& gr,
                                std::vector<int>& current,
                                std::vector<bool>& used,
                                std::vector<std::vector<int>>& all_sorts) {
    if (has_cycle(gr)) {
        std::cout << "Неверный ввод" << std::endl;
        return;
    }
    bool all_used = true;
    for (size_t i = 0; i < gr.size(); i++) {
        if (!used[i]) {
            all_used = false;
            used[i] = true;
            current.push_back(i);
            generate_topological_sorts(gr, current, used, all_sorts);
            current.pop_back();
            used[i] = false;
        }
    }
    if (all_used) {
        if (valid_topological_sort(gr, current)) {
            all_sorts.push_back(current);
        }
    }
}

std::vector<std::vector<int>> all_topological_sorts(const std::vector<std::vector<int>>& gr) {
  
    std::vector<int> current;
    std::vector<bool> used(gr.size(), false);
    std::vector<std::vector<int>> all_sorts;
    generate_topological_sorts(gr, current, used, all_sorts);
    return all_sorts;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> gr(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        gr[u].push_back(v);
    }
    std::vector<std::vector<int>> all_sorts = all_topological_sorts(gr);
    for (const auto& sort : all_sorts) {
        for (int v : sort) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
