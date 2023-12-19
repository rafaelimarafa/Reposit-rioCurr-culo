#include "trab.h"

int main(){
    Hash* h = criaHash(26);

    int x;
    scanf("%d", &x);
    char str[50];
    int n;
    for(int i = 0; i < x; i++){
        scanf("%s %d", str, &n);
        insereHashABP(h, str, n);
    }
    scanf("%d", &x);
    for(int i = 0 ;i < x; i++){
        scanf("%s", str);
        buscaHashABP(h, str);
    }
    return 0;
}