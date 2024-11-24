#include "separation.h"

vector <vector<int> > MaxBack(double** x, int n){
    auto subtours = vector<vector<int>>();
    double cutMin = 0, cutVal;
    
    vector<int> S = vector<int>(n, 0);
    vector<int> Smin;
    S[0] = 1;
    vector<double> maxBackCosts = vector<double>(n,0);

    for (size_t i = 1; i < n; i++){
        maxBackCosts[i] += x[0][i];

        cutMin += maxBackCosts[i];
    }

    cutVal = cutMin;

    while(1){
        int idxMaxBackCost = -1;
        double maxBackCost = -1;
        bool noVertexOutsideS = true;

        for (size_t i = 0; i < maxBackCosts.size(); i++){
            if(maxBackCosts[i] > maxBackCost && !S[i]){
                idxMaxBackCost = i;
                maxBackCost = maxBackCosts[i];
                noVertexOutsideS = false;
            }
        }

        if(noVertexOutsideS)
            break;

        S[idxMaxBackCost] = 1;
        cutVal += 2 - 2 * maxBackCosts[idxMaxBackCost];

        for (size_t i = 0; i < S.size(); i++)
        {
            if(S[i])
                continue;

            int a = (i < idxMaxBackCost)? i : idxMaxBackCost;
            int b = (i > idxMaxBackCost)? i : idxMaxBackCost;

            maxBackCosts[i] = maxBackCosts[i] + x[a][b];
        }

        if(cutVal < cutMin){
            cutMin = cutVal;
            Smin = S;
        }
    }

    vector<int> subtour = vector<int>();
    int count = 0;

    for(size_t i = 0; i < Smin.size(); i++){
        if(Smin[i]){
            subtour.push_back(i);
            count++;
        }
    }
    
    if(count < n){
        cout << subtour.size() << "\n";
        for(size_t i = 0; i < subtour.size(); i++){
            cout << subtour[i] << " ";
        }
        cout << "\n";
        subtours.push_back(subtour);
    }

    return subtours;
}