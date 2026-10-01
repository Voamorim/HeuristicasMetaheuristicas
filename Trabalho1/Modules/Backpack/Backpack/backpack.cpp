#include "backpack.hpp"

pair<long long, vector<bool>> greedySolutionBackpack(Backpack* backpack) {
    const int n = backpack->items.size();
    vector<bool> solution(n, false);

    vector<pair<Item, int>> items(backpack->items.size());
    for (int i = 0; i < backpack->items.size(); ++i) {
        items[i].first = backpack->items[i];
        items[i].second = i;
    }
    sort(items.begin(), items.end(), compItemsCostBenefit);

    long long curr_capacity = backpack->capacity;
    long long fo = 0;

    for (int i = 0; i < items.size(); ++i) {
        auto& item = items[i].first;
        if (item.weight <= curr_capacity) {
            curr_capacity -= item.weight;
            fo += item.value;
            solution[items[i].second] = true;
        }
    }

    string title = "Heuristica por Custo Beneficio";
    printSolutionBackpack(solution, fo, title);
    cout << endl;

    return make_pair(fo, solution);
}

Backpack* readInputBackpack(void) {
    int n, m;
    cin >> n >> m;
    Backpack* backpack = new Backpack();
    backpack->capacity = m;
    for (int i = 0; i < n; ++i) {
        int value, weight;
        cin >> value >> weight;

        Item item = {value, weight};
        backpack->items.push_back(item);
    }
    return backpack;
}

pair<long long, bool> objectiveFunctionBackpack(const vector<bool> solution, Backpack* backpack,
                                                const bool penalty) {
    const int n = solution.size();

    long long total_value = 0;
    long long total_weight = 0;

    for (int i = 0; i < n; ++i) {
        if (solution[i]) {
            total_value += backpack->items[i].value;
            total_weight += backpack->items[i].weight;
        }
    }

    if (not penalty) return make_pair(total_value, true);

    const long long penalty_mult = 100;

    // Aplica punição à soluções inviáveis
    long long fo =
        total_value - penalty_mult * max((long long)0, total_weight - backpack->capacity);

    return make_pair(fo, total_weight <= backpack->capacity);
}

bool compItemsCostBenefit(const pair<Item, int>& item1, const pair<Item, int>& item2) {
    double costbenefit_item1 = (double)item1.first.value / item1.first.weight;
    double costbenefit_item2 = (double)item2.first.value / item2.first.weight;

    return costbenefit_item1 > costbenefit_item2;
}

void printSolutionBackpack(const vector<bool>& solution, const long long fo, const string title) {
    int title_size = title.size();
    int bar_size = 60;

    // Barra superior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;

    int n_espaces = (bar_size - title_size) / 2;
    while (n_espaces--) cout << ' ';
    cout << title << endl;

    // Barra inferior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;

    cout << "- FO: " << fo << endl;
    cout << "- Itens: ";
    for (int i = 0; i < solution.size(); ++i) {
        if (not solution[i]) continue;
        cout << i << ' ';
    }
    cout << endl;

    // Barra inferior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;
}
