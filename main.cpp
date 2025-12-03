#include <iostream>
#include <string>
#include <vector>
using namespace std;


int afs[4][4] = {
    {1, 3, 1, 3},
    {5, 1, 0, 1},
    {0, 1, 0, 4},
    {1, 3, 2, 3}
};

int letraIndex(char c){
    if(c == 'P'){
        return 0;
    }
    else if (c == 'N'){
        return 1;
    }
    else if(c == 'A'){
        return 2;
    }
    else if(c == 'B'){
        return 3;
    }
    return -1;
}




int afinidade(char a1, char a2){
    if(a1 == 'T' || a2 == 'T'){
        return 1;
    }

    return afs[letraIndex(a1)][letraIndex(a2)];
}



unsigned long long cost(int a, int i, int j, vector<int> potencial, string sequencia){
    //Pi−1 ×Af(C(i−1),C(i))×Pi +Pi ×Af(C(i),C(i+1))×Pi+1
    unsigned long long energia = (potencial[i-1] * afinidade(sequencia[i-1], sequencia[a]) * 
    potencial[a]) + (potencial[a] * afinidade(sequencia[a], sequencia[j+1]) * potencial[j+1]);

    return energia;
}


void optimalSequenceRec(vector<vector<int>> optimal, int i, int j, vector<int>& res){
    if(i > j){
        return;
    }
    int k = optimal[i][j];
    optimalSequenceRec(optimal, i, k-1 , res);
    optimalSequenceRec(optimal, k+1, j, res);
    res.push_back(k);
}


void printOutputSequence(vector<int> sequencia, int n){
    cout << sequencia[0];
    for(int i = 1; i < n ; i++){
        cout << ' ' << sequencia[i];
    }
    cout << endl;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n ; //nº de aminoácidos
    cin >> n;
    

    vector<int> potencial(n+2); //guardar potenciais
    potencial[0] = 1; //T inicial
    for(int i = 1; i <= n; i++){ 
        cin >> potencial[i]; 
    }
    potencial[n+1] = 1; //T final
    
    string aminoacidos;
    cin >> aminoacidos;  //ler a cadeia de AA's
    aminoacidos = 'T' + aminoacidos + 'T';

    
 


    vector<vector<unsigned long long>> cache(n+2, vector<unsigned long long>(n+2, 0)); //matriz para armazenar tabela
    
    vector<vector<int>> optimal(n + 2, vector<int>(n + 2, 0));//ultimo aminoácido a removeer

    unsigned long long total = 0;

    
    for(int l = n; l >= 0; l--){  
        for(int r = l; r <= n ; r++){
            for(int k = l; k <= r; k++){
                total = cost(k, l, r, potencial, aminoacidos) + cache[l][k-1] + cache[k+1][r];
                if (total > cache[l][r]){                    
                    cache[l][r] = total;
                    optimal[l][r] = k;
                }else if(total == cache[l][r]){
                    if(aminoacidos[k] < aminoacidos[optimal[l][r]]){
                        optimal[l][r] = k;
                    }
                }
            }
        }
    }
    
    
    vector<int> sequencia;
    optimalSequenceRec(optimal, 1, n, sequencia);

    //print energia
    cout << cache[1][n] << endl;

    //output sequencia final
    printOutputSequence(sequencia, n);

    return 0;

    
}