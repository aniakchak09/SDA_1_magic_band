// CRETU Dan Andrei 315CB

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* definire lista dublu inlantuita cu santinela */

typedef struct celula2 {
  char info;              
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

typedef struct banda {
  TLista2 santinela;
  TLista2 deget;
} *TBanda;

typedef struct celula {
  char *instructiune;
  struct celula *urm;
} TCelula, *TLista;

typedef struct coada {
  TLista inc, sf;
} *TCoada;

typedef struct stiva
{
  char *instructiune;
  TLista vf;
} *TStiva;


TLista AlocCelula(char* elem);
TLista2 AlocCelula2(char x);
void DistrugeBanda(TBanda *banda);

void MOVE_RIGHT (TBanda *banda);
void MOVE_LEFT (TBanda *banda);
void MOVE_RIGHT_CHAR ( TBanda *banda, char c);
void MOVE_LEFT_CHAR (TBanda *banda, char c, FILE *output);
void WRITE (TBanda *banda, char c);
void INSERT_LEFT (TBanda *banda, char c, FILE *output);
void INSERT_RIGHT (TBanda *banda, char c);
void SHOW_CURRENT (TBanda *banda, FILE *output);
void SHOW (TBanda *banda, FILE *output);
void UNDO (TBanda *banda, TStiva stiva, TStiva stiva_redo);
void REDO (TBanda *banda, TStiva stiva, TStiva strva_undo);

TStiva InitS ();
int IntrS(TStiva stiva, char *x);
TStiva ExtrS(TStiva stiva, char *x);
void AfisareS(TStiva stiva);
void DezalocaS(TStiva *stiva);

TCoada InitQ ();
int IntrQ(TCoada c, char *x);
TCoada ExtrQ (TCoada coada, char *x);
void AfisareQ(TCoada c);

void Citire(TCoada coada, TBanda *banda, TStiva s_u, TStiva s_r);
void Executare (TCoada coada, TBanda *banda, FILE *output);