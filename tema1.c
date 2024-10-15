// CRETU Dan Andrei 315CB

#include "functii.h"
#include <stdio.h>

int main() {
    TBanda banda = malloc(1 * sizeof(struct banda));
    int counter = 0; char x;
    TCoada c;
    TStiva s_undo, s_redo;
    FILE *output = fopen("tema1.out", "w");

    c = InitQ();
    s_undo = InitS();
    s_redo = InitS();

    TLista2 aux = AlocCelula2(' ');   //aici am initializat banda
    banda->santinela = aux;
    banda->santinela->pre = NULL;
    
    TLista2 aux2 = AlocCelula2('#');
    aux2->urm = NULL;
    aux2->pre = banda->santinela;
    banda->santinela->urm = aux2;
    banda->deget = aux2;

    Citire(c, &banda, s_undo, s_redo);

    free(c);
    DistrugeBanda(&banda);
    DezalocaS(&s_undo);
    DezalocaS(&s_redo);
    fclose(output);
    return 0;
}