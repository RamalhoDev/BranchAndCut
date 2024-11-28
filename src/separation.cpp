#include "separation.h"

vector <vector<int> > MaxBack(double** x, int n, bool isMinCutPhase, double * currentCost){
    auto subtours = vector<vector<int>>();
    auto maxBackCosts = vector<double>(n, 0);
    vector<int> S = vector<int>(n, 0), idxS = vector<int>();
   
    double cutMin = 0, cutVal; 
    vector<int> Smin;
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
        if(!isMinCutPhase && cutVal < cutMin && count < n){
            cutMin = cutVal;
            Smin = S;
        }
    }

    if(cutMin > (2-0.0000001))
        return subtours;
    if(currentCost != NULL)
        *currentCost = cutMin;
    vector<int> subtour = vector<int>();
    count = 0;

    for(size_t i = 0; i < Smin.size(); i++){
        if(Smin[i]){
            subtour.push_back(i);
            count++;
        }
    }
    
    if(count < n){
        subtours.push_back(subtour);
        cout << subtour.size() << "\n";
        for(size_t i = 0; i < subtour.size(); i++){
            cout << subtour[i] << " ";
        }
        cout << "\n";
    }

    // if(isMinCutPhase){

    // }

    return subtours;
}

vector <vector<int> > MinCut(double** x, int n){
    int count = n;
    vector<vector<int>> minimumCut;
    double bestCurrentCost = 10000000, currentCost;

    while(count > 1){
        auto subtours = MaxBack(x, n, true, &currentCost);
        if(currentCost < bestCurrentCost){
            minimumCut = subtours;
            bestCurrentCost = currentCost;
        }
        count--;
    }
}