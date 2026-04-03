#include <iostream>
#include <string>
#include <vector>

using namespace std;
 
vector<int> KMPpreprocess(string pattern){
    vector<int>pi(pattern.size());
    pi[0]=0;
    for(int i=1;i<pattern.size();i++){
        pi[i]=(pattern[pi[i-1]]==pattern[i]?pi[i-1]+1:0);
    }
    return  pi;
}
void KMPsearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pi = KMPpreprocess(pattern);
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j > 0 && pattern[j] != text[i]) {
            j = pi[j - 1];
        }
        if (pattern[j] == text[i]) {
            j++;
        }
        if (j == m) {
            cout << "Patrón encontrado en el indice: " << i - m + 1 << endl;
            j = pi[j - 1];
        }
    }
}

int main() {
    string text = "El curso de FPC esta genial. FPC es mejor que fisica";
    string pattern = "FPC";
    int q;
    do{cout<<"Ingresa cantidad de casos: ";cin>>q;}while(q<=1 or q>=10000);
    
    while(q--){
        cout<<"Ingrese el texto menor a 100 caracteres: ";cin>>text;
        cout<<"Ingrese el patron menor a 10 caracteres: ";cin>>pattern;
        if(pattern.size()>=10 or text.size()>=100){q++;continue;}
        
    }
    //KMPsearch(text, pattern);
    return 0;
}
