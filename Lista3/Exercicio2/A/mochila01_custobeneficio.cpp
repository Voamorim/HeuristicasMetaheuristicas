#include <bits/stdc++.h>

#include "../../Timer/timer.hpp"

using namespace std;

struct Item {
	int value, weight;
};

struct Backpack {
	vector<Item> items;
	int capacity;
};

Backpack* readInput(void);
int objectiveFunction(const vector<bool> solution, Backpack* backpack);

bool compItemsCostBenefit(const Item& item1, const Item& item2) {
	double costbenefit_item1 = (double)item1.value / item1.weight;
	double costbenefit_item2 = (double)item2.value / item2.weight;

	return costbenefit_item1 > costbenefit_item2;
}

int main() {
	string problema = "Solucao Gulosa por Custo Beneficio para o Problema da Mochila 0/1";
	Timer timer(problema);

	Backpack* backpack = readInput();
	int n = backpack->items.size();

	sort(backpack->items.begin(), backpack->items.end(), compItemsCostBenefit);

	int curr_capacity = backpack->capacity;
	int solution = 0;

	vector<int> selected_items;

	// Pega os itens de maior custo benefício que ainda cabem na mochila
	for (int i = 0; i < backpack->items.size(); ++i) {
		auto& item = backpack->items[i];

		if (item.weight <= curr_capacity) {
			curr_capacity -= item.weight;
			solution += item.value;
			selected_items.push_back(i);
		}
	}

	timer.stop();
	cout << endl;

	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "               Problema da Mochila                 " << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "- FO encontrada: " << solution << endl;
	cout << "- Itens escolhidos: ";
	for (auto& item : selected_items) {
		cout << item << ' ';
	}
	cout << endl;
	delete backpack;
	return 0;
}

Backpack* readInput(void) {
	Backpack* backpack = new Backpack();

	int n, m;
	cin >> n >> m;

	backpack->capacity = m;

	for (int i = 0; i < n; ++i) {
		int value, weight;
		cin >> value >> weight;

		Item item = {value, weight};
		backpack->items.push_back(item);
	}

	return backpack;
}

int objectiveFunction(vector<bool> solution, Backpack* backpack) {
	const int n = solution.size();

	int total_value = 0;
	int total_weight = 0;

	for (int i = 0; i < n; ++i) {
		if (solution[i]) {
			total_value += backpack->items[i].value;
			total_weight += backpack->items[i].weight;
		}
	}

	if (total_weight <= backpack->capacity) return total_value;

	return -100 * total_value;	// Penaliza solucoes invalidas
}
