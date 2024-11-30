#include "separation.h"

vector <vector<int> > MaxBack(vector<vector<double>> x, int n, bool isMinCutPhase, double * currentCost){
    auto subtours = vector<vector<int>>();
    auto maxBackCosts = vector<double>(n, 0);
    vector<int> S = vector<int>(n, 0), idxS = {0}, Smin;
   
    double cutMin = 0, cutVal; 
    S[0] = 1;

    auto queueBackCosts = priority_queue<pair<double, vector<int>>>();
    for (size_t i = 1; i < n; i++){
        maxBackCosts[i] = x[0][i];
        vector<int> nodes = {i};
        queueBackCosts.push(make_pair(maxBackCosts[i], nodes));

        cutMin += maxBackCosts[i];
    }

    cutVal = cutMin;
    int count = 1;
    int nIterations = (isMinCutPhase)?n+1:n;
    while(count < n){
        auto maxBackCost = queueBackCosts.top();
        int firstIndex = maxBackCost.second[0];
    
        queueBackCosts.pop();
        if(S[firstIndex])
            continue;

        S[firstIndex] = 1;
        idxS.push_back(firstIndex);

        if(isMinCutPhase)
            cutVal = maxBackCost.first;
        else
            cutVal += 2 - 2 * maxBackCosts[firstIndex];

        for (size_t i = 0; i < S.size(); i++) {
            if(S[i])
                continue;

            int a = (i < firstIndex)? i : firstIndex;
            int b = (i > firstIndex)? i : firstIndex;

            maxBackCosts[i] =maxBackCosts[i] + x[a][b];
            vector<int> nodes = {i};
            queueBackCosts.push(make_pair(maxBackCosts[i], nodes));
        }

        count++;
        if((isMinCutPhase || cutVal < cutMin) && count < n){
            cutMin = cutVal;
            Smin = idxS;
        }
    }

    if(isMinCutPhase){
        auto tIndex = queueBackCosts.top().second[0];
        Smin.push_back(tIndex);
    }

    if(currentCost != NULL)
        *currentCost = cutMin;

    // if(isMinCutPhase)

    if(!isMinCutPhase && cutMin > (2-0.0000001))
        return subtours;

    subtours.push_back(Smin);


    if(!isMinCutPhase){
        cout << Smin.size() << "\n";
        for(size_t i = 0; i < Smin.size(); i++){
            cout << Smin[i] << " ";
        }
        cout << "\n";
    }

    return subtours;
}

vector <vector<int> > MinCut(vector<vector<double>> x, int n){
    int count = n;
    vector<vector<int>> minimumCut;
    vector<vector<int>> nodes;
    vector<vector<int>> bestNodes;

    for (size_t i = 0; i < n; i++)    {
        nodes.push_back({i}); 
    }
    
    double bestCurrentCost = 10000000, currentCost;

    while(count > 1){
        cout << "\n";
        for (size_t i = 0; i < x.size(); i++)
        {
            for (size_t j = 0; j < x[i].size(); j++)
            {
                cout << x[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
        auto subtours = MaxBack(x, count, true, &currentCost);
        
        int s = subtours[0][subtours[0].size()-2];
        int t = subtours[0][subtours[0].size()-1];
        subtours[0].pop_back();
        // subtours[0].pop_back();
        
        if(currentCost < bestCurrentCost){
            minimumCut = subtours;
            bestNodes = nodes;
            bestCurrentCost = currentCost;
        }


        if(s > t){
            int aux = s;
            s = t;
            t = aux;
        }

        // inserir nós de t em s
        nodes[s].insert(nodes[s].end(), nodes[t].begin(), nodes[t].end());
        // zerar arcos entre os nós s e t ok
        x[s][t] = 0;

        for (size_t i = 0;  i < count; i++){
            
            if(i == t || i == s)
                continue;

            int a = i, b = s;
            if(i > s){
                a = s;
                b = i;
            }

            //somar pesos dos novos arcos que conectavam com t nos pesos de s
            if( i < t){
                x[a][b] += x[i][t];
            }
            else{
                x[a][b] += x[t][i];
            }

            // excluir coluna do nó t
            x[i].erase(x[i].begin() + t);
        }

        for (size_t i = 0; i < x.size(); i++)
        {
            for (size_t j =0; j < x[i].size(); j++)
            {
                cout << x[i][j] << " ";
            }
            cout << "\n";
        }
        

        // excluir linha do nó t
        nodes.erase(nodes.begin() + t);
        x.erase(x.begin() + t);
        
        count--;
    }

    

    vector<vector<int>> minSubtours = vector<vector<int>>();
    if(bestCurrentCost > (2-0.0000001))
        return minSubtours;

    for (size_t i = 0; i < minimumCut.size(); i++){
        auto subtour = vector<int>();
        for (size_t j = 0; j < minimumCut[i].size(); j++){
            auto nodeList = bestNodes[minimumCut[i][j]];
            for (size_t k = 0; k < nodeList.size(); k++){
                subtour.push_back(nodeList[k]);
            }
        }
        if(subtour.size() > 2)
            minSubtours.push_back(subtour);
    }

    cout << minSubtours[0].size() << "\n";
    for(size_t i = 0; i < minSubtours[0].size(); i++){
        cout << minSubtours[0][i] << " ";
    }
    cout << "\n";

    return minSubtours;
}