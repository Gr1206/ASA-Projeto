#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


int afs[4][4] = {
    {0, 4, 1, 0},
    {2, 3, 3, 1},
    {0, 1, 1, 5},
    {1, 3, 3, 1}
};

int letraIndex(char c){
    switch(c){
        case 'A': return 0;
        case 'B': return 1;
        case 'N': return 2;
        case 'P': return 3;
        default: return -1;
    }
}




int afinidade(int a1, int a2){
    if(a1 == -1 || a2 == -1){
        return 1;
    }

    return afs[a1][a2];
}



unsigned long long cost(int a, int i, int j, vector<unsigned long long>& potencial, vector<int>& sequencia){
    //Pi−1 ×Af(C(i−1),C(i))×Pi +Pi ×Af(C(i),C(i+1))×Pi+1
    unsigned long long energia = (potencial[i-1] * afinidade(sequencia[i-1], sequencia[a]) * 
    potencial[a]) + (potencial[a] * afinidade(sequencia[a], sequencia[j+1]) * potencial[j+1]);

    return energia;
}


void optimalSequenceRec(vector<vector<int>>& optimal, int i, int j, int inicial){
    if(i > j){
        return;
    }
    int k = optimal[i][j];

    optimalSequenceRec(optimal, i, k-1, inicial);
    optimalSequenceRec(optimal, k+1, j, inicial);

    if(k == inicial){
        cout << k << endl;
    }
    else{
        cout << k << " ";
    }
}



int main(){
    auto start = high_resolution_clock::now();

    ios::sync_with_stdio(0);
    cin.tie(0);

    int n ; //nº de aminoácidos
    cin >> n;
    

    vector<unsigned long long> potencial(n+2); //guardar potenciais
    potencial[0] = 1; //T inicial
    for(int i = 1; i <= n; i++){ 
        cin >> potencial[i]; 
    }
    potencial[n+1] = 1; //T final
    
    vector<int> aminoacidos(n+2);
    aminoacidos[0] = -1;
    aminoacidos[n+1] = -1;
    for(int i = 1; i <= n; i++){
        char c;
        cin >> c; 
        aminoacidos[i] = letraIndex(c);

    }

    vector<vector<unsigned long long>> cache(n+2, vector<unsigned long long>(n+2, 0)); //matriz para armazenar tabela
    
    vector<vector<int>> optimal(n + 2, vector<int>(n + 2, 0));//ultimo aminoácido a removeer

    unsigned long long total = 0;
    unsigned long long maxEnergia = 0;
    int maxK = 0;

    for(int l = n; l > 0; l--){  
        for(int r = l; r <= n ; r++){
            maxEnergia = 0;
            maxK = l;
            for(int k = l; k <= r; k++){
                total = cost(k, l, r, potencial, aminoacidos) + cache[l][k-1] + cache[k+1][r];
                if (total > maxEnergia){                    
                    maxEnergia = total;
                    maxK = k;
                }else if(total == maxEnergia && k >= maxK){
                    maxK = k;
                }
            }
            cache[l][r] = maxEnergia;
            optimal[l][r] = maxK;
        

        }
    }
    

    
    

    //print energia
    cout << cache[1][n] << endl;

    //output sequencia final
    optimalSequenceRec(optimal, 1, n, optimal[1][n]);
    
    auto end = high_resolution_clock::now();

    // calcula duração em microsegundos
    auto duration_us = duration_cast<microseconds>(end - start);
    cout << "Tempo: " << duration_us.count() << " microsegundos\n";
    
    return 0;
}