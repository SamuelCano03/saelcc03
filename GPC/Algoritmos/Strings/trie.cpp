#include <bits/stdc++.h>
using namespace std;
#define maxn 1000000
int trie[maxn][26],nodos;
int term[maxn];
void init(){
    nodos=1;
    for(int i=0;i<maxn;i++){
        term[i]=0;
        for(int j=0;j<26;j++){
            trie[i][j]=0;
        }
    }
}

void addWord(string s){
    int cur=0;//nodo raiz
    for(char c: s){
        int edge=c-'a';
        if(trie[cur][edge]==0){
            trie[cur][edge]=nodos;
            nodos++;
        }
        cur=trie[cur][edge];
    }
    term[cur]=1;
}

bool existWord(string s){
    int cur=0;
    for( char c: s){
        int edge=c-'a';
        if(!trie[cur][edge])return 0;
        cur=trie[cur][edge];
    }
    return term[cur];
}

int main() {
    init();
    addWord("hola");
    addWord("he");
    addWord("hello");
    cout<<nodos<<endl;
    //busca "hel"
    cout<<existWord("he");
	return 0;
}
