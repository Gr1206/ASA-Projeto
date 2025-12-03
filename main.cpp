#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>
using namespace std;

// os prints documentados é para verificar que o input está mesmo
//a ser bem lido
/* caso seja 
// vai ser preciso mapear letras para estes indices talvez
T Af(T,c) ou Af(c,T) é sempre igual a 1 (depois meter um if?)
Af P N A B
P 1 3 1 3
N 5 1 0 1
A 0 1 0 4
B 1 3 2 3
*/
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

char getChar(int a, string sequencia){
    char c; //char do aminoacido correspondente ao index a

    return sequencia[a];
}

int cost(int a, int i, int j, vector<int> potencial, string sequencia){
    //Pi−1 ×Af(C(i−1),C(i))×Pi +Pi ×Af(C(i),C(i+1))×Pi+1
    int energia = (potencial[i-1] * afinidade(getChar(i-1, sequencia), getChar(a, sequencia)) * 
    potencial[a]) + (potencial[a] * afinidade(getChar(a, sequencia), getChar(j+1, sequencia)) * potencial[j+1]);

    return energia;
}

vector<int> optimalSequence(vector<vector<int>> optimal, vector<vector<int>> cache, int n){
    vector<int> sequencia(n);
    int x = n - 1;
    int a = 1;
    for(int i = 1, j = n; i != j; x--){
        sequencia[x] = optimal[i][j];

        if(cache[i+1][j] >= cache[i][j-1]){
            for(int y = x; y >= 0; y--){
                if(optimal[i+1][j] == sequencia[y]){
                    int a = 0;
                }
            }
            if(a == 1){
                i++;
            }
        }
        else{
            j--;
        }

    }

    return sequencia;
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

int main(){
    ifstream inputFile("input/input2.txt");
    int n;
    inputFile >> n; //número de aminoácidos na sequência

    vector<int> potencial(n+2); //guardar potenciais
    potencial[0] = 1; //T inicial
    for(int i = 1; i <= n; i++){ 
        inputFile >> potencial[i]; 
    }
    potencial[n+1] = 1; //T final
    
    string aminoacidos;
    inputFile >> aminoacidos; //ler a cadeia de AA's
    aminoacidos = 'T' + aminoacidos;
    aminoacidos += 'T';
    
 
    inputFile.close();

    vector<vector<int>> cache(n+2, vector<int>(n+2, 0)); //matriz para armazenar tabela
    
    vector<vector<int>> optimal(n + 2, vector<int>(n + 2, 0));//ultimo aminoácido a removeer

    int total = 0;
   
    for(int l = n; l >= 0; l--){  
        for(int r = l; r <= n ; r++){
            for(int k = l; k <= r; k++){
                total = cost(k, l, r, potencial, aminoacidos) + cache[l][k-1] + cache[k+1][r];
                //cout << total << ' ' << k << ' ' << endl;
                if (total > cache[l][r]){                    
                    cache[l][r] = total;
                    optimal[l][r] = k;
                }else if(total == cache[l][r]){
                    if(getChar(k, aminoacidos) < getChar(optimal[l][r], aminoacidos)){
                        optimal[l][r] = k;
                    }
                }
            }
        }
    }
    
    
    vector<int> sequencia = optimalSequence(optimal, cache, n);
    vector<int> sequenciaReq;
    optimalSequenceRec(optimal, 1, n, sequenciaReq);
    cout << cache[1][n] << endl;
    cout << optimal[1][n] << endl;

    for(int i = 0; i <=n; i++){
        for(int j = 0; j<=n; j++){
            cout << cache[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            cout << optimal[i][j] << ' ';
        }
        cout << endl;
    }
    

    for(int i = 0; i < n; i++){
        cout << sequenciaReq[i] << ' ';
    } 
    cout << endl; 

    return 0;

    
}