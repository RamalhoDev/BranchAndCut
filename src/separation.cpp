#include "separation.h"

vector<vector<int>> MaxBack(vector<vector<double>> x, int n, bool isMinCutPhase, double* currentCost) {
	auto subtours = vector<vector<int>>();
	auto maxBackCosts = vector<double>(n, 0);
	vector<int> S = vector<int>(n, 0), idxS = {0}, Smin;

	double cutMin = 0, cutVal;
	S[0] = 1;

	auto queueBackCosts = priority_queue<pair<double, vector<int>>>();

	// for (size_t i = 0; i < x.size(); i++) {
	// 	for (size_t j = 0; j < x[i].size(); j++) {
	// 		cout << x[i][j] << " ";
	// 	}
	// 	cout << "\n";
	// }
	// cout << "\n";

	for (size_t i = 1; i < n; i++) {
		maxBackCosts[i] = (i < 0) ? x[i][0] : x[0][i];
		vector<int> nodes = {i};
		queueBackCosts.push(make_pair(maxBackCosts[i], nodes));

		cutMin += maxBackCosts[i];
	}

	cutVal = cutMin;
	int count = 1;
	while (count < n) {
		auto maxBackCost = queueBackCosts.top();
		int firstIndex = maxBackCost.second[0];

		queueBackCosts.pop();
		if (S[firstIndex]) continue;

		S[firstIndex] = 1;
		idxS.push_back(firstIndex);

		if (isMinCutPhase)
			cutVal = maxBackCost.first;
		else
			cutVal += 2 - 2 * maxBackCosts[firstIndex];

		for (size_t i = 0; i < S.size(); i++) {
			if (S[i]) continue;

			int a = (i < firstIndex) ? i : firstIndex;
			int b = (i > firstIndex) ? i : firstIndex;

			maxBackCosts[i] = maxBackCosts[i] + x[a][b];
			vector<int> nodes = {i};
			queueBackCosts.push(make_pair(maxBackCosts[i], nodes));
		}

		count++;
		if (isMinCutPhase || cutVal < cutMin && count < n) {
			cutMin = cutVal;
			Smin = idxS;
		}
	}

	if (currentCost != NULL) *currentCost = cutMin;

	if (!isMinCutPhase && cutMin > (2 - 0.0000001)) return subtours;

	subtours.push_back(Smin);

	// if (!isMinCutPhase) {
	// 	cout << Smin.size() << "\n";
	// 	for (size_t i = 0; i < Smin.size(); i++) {
	// 		cout << Smin[i] << " ";
	// 	}
	// 	cout << "\n";
	// }

	return subtours;
}

vector<vector<int>> MinCut(vector<vector<double>> x, int n) {
	int count = n;
	vector<vector<int>> minimumCut;
	vector<vector<int>> nodes;
	vector<vector<int>> bestNodes;

	for (size_t i = 0; i < n; i++) {
		nodes.push_back({i});
	}

	double bestCurrentCost = 10000, currentCost;

	while (count > 1) {
		auto subtours = MaxBack(x, count, true, &currentCost);
		int s = subtours[0][subtours[0].size() - 2];
		int t = subtours[0][subtours[0].size() - 1];
		subtours[0].pop_back();
		// cout << currentCost << "\n";
		// for (size_t i = 0; i < subtours[0].size(); i++) {
		// 	for (size_t j = 0; j < nodes[subtours[0][i]].size(); j++) {
		// 		cout << nodes[subtours[0][i]][j] + 1 << " ";
		// 	}
		// }

		// cout << " | ";

		// for (size_t j = 0; j < nodes[t].size(); j++) {
		// 	cout << nodes[t][j] << " ";
		// }
		// cout << "\n_______________________________________________________________________________________________\n";
		if (currentCost < bestCurrentCost) {
			minimumCut = subtours;
			bestNodes = nodes;
			bestCurrentCost = currentCost;
		}

		if (s > t) {
			int aux = s;
			s = t;
			t = aux;
		}

		// inserir nós de t em s
		nodes[s].insert(nodes[s].end(), nodes[t].begin(), nodes[t].end());

		for (size_t i = 0; i < count; i++) {
			if (i == t || i == s) continue;

			int a = i, b = s;
			if (i > s) {
				a = s;
				b = i;
			}

			// somar pesos dos novos arcos que conectavam com t nos pesos de s
			x[a][b] += (i < t) ? x[i][t] : x[t][i];

			// excluir coluna do nó t
			x[i].erase(x[i].begin() + t);
		}
		// excluir linha do nó t
		nodes.erase(nodes.begin() + t);
		x[s].erase(x[s].begin() + t);
		x.erase(x.begin() + t);

		count--;
	}

	vector<vector<int>> minSubtours = vector<vector<int>>();
	if (bestCurrentCost > (2 - 0.0000001)) return minSubtours;

	for (size_t i = 0; i < minimumCut.size(); i++) {
		auto subtour = vector<int>();
		for (size_t j = 0; j < minimumCut[i].size(); j++) {
			auto nodeList = bestNodes[minimumCut[i][j]];
			for (size_t k = 0; k < nodeList.size(); k++) {
				subtour.push_back(nodeList[k]);
			}
		}
		if (subtour.size() > 2) minSubtours.push_back(subtour);
	}

	// cout << minSubtours[0].size() << "\n";
	// for (size_t i = 0; i < minSubtours[0].size(); i++) {
	// 	cout << minSubtours[0][i] << " ";
	// }
	// cout << "\n";

	return minSubtours;
}