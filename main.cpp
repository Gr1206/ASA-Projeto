#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// os prints documentados é para verificar que o input está mesmo
//a ser bem lido

int main(){
    ifstream inputFile("input/input2.txt");
    int n;
    inputFile >> n; //número de aminoácidos na sequência

    vector<int> potencial(n); //guardar potenciais
    for(int i = 0; i < n; i++){ 
        inputFile >> potencial[i]; 
       //cout << potencial[i] << " ";
    }
    // cout << endl;
    
    string aminoacidos;
    inputFile >> aminoacidos; //ler a cadeia de AA's

    // cout << aminoacidos << endl;
    inputFile.close();
    
    
    return 0;

    
}