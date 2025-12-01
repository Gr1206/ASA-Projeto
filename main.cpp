#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
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
        cout << a1 << a2 << endl;
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



int main(){
    ifstream inputFile("input/input2.txt");
    int n;
    inputFile >> n; //número de aminoácidos na sequência

    vector<int> potencial(n+2); //guardar potenciais
    potencial[0] = 1; //T inicial
    for(int i = 1; i <= n; i++){ 
        inputFile >> potencial[i]; 
       //cout << potencial[i] << " ";
    }
    potencial[n+1] = 1; //T final
    // cout << endl;
    
    string aminoacidos;
    inputFile >> aminoacidos; //ler a cadeia de AA's
    aminoacidos = 'T' + aminoacidos;
    aminoacidos.push_back('T');
    cout << aminoacidos << endl;
    inputFile.close();

    vector<vector<int>> cache(n+2, vector<int>(n+2, 0)); //matriz para armazenar tabela
    
    vector<vector<int>> optimal(n + 2, vector<int>(n + 2, 0));

    //loop para ir aumentando o tamanho de L do problema
    // l = 1 [a1]; L = 2 [a1, a2]; L = 3 [a1, a2, a3] ...
    //dentro de cada um destes temos de escolher um para tirar em último
    //dentro de cada um deste que damos pop a todos e escolhemos o máximo deste pop
    int total = 0;

    for(int l = 1; l <= n; l++){
        for(int i = 1; i <= n - l + 1; i++){
            int j = i + l - 1;
            cache[i][j] = 0;
            for(int k = i; k <= j ;k++){
                int total = cost(k, i, j, potencial, aminoacidos) + cache[i][k-1] + cache[k+1][j];
                if(total > cache[i][j]){
                    cache[i][j] = total;
                    optimal[i][j] = k; //aminoacido optimo para cada sub intervalo
                }
            }
        }
    }
    cout << cache[1][n] << endl;


    return 0;

    
}