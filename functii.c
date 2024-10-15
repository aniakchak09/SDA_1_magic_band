// CRETU Dan Andrei 315CB

#include "functii.h"

TLista AlocCelula(char *elem) {
    TLista aux = malloc(sizeof(struct celula));   
    if (aux) {                                    
        aux->instructiune = elem;
        aux->urm = NULL;
    }
    return aux;                                   
}

TLista2 AlocCelula2(char x) {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = x;
    aux->pre = aux->urm = NULL;

    return aux;
}

TCoada InitQ () {                       //functia de initializare a cozii
  TCoada c;          
  c = malloc(1 * sizeof(struct coada));
  if (!c) return NULL;                 

  c->inc = c->sf = NULL;
  return c;        
}

int IntrQ(TCoada c, char* x) {          //functia de introducere in coada
    TLista aux;
    aux = malloc(sizeof(struct celula));

    aux->instructiune = malloc(50 * sizeof(char));

    if (!aux) return 0;
    
    strcpy(aux->instructiune, x);
    aux->urm = NULL;

    if ((c)->sf != NULL) {         
        (c)->sf->urm = aux;
    } else {                           
        (c)->inc = aux;
    }                    
    (c)->sf = aux; 

    return 1;
}

TCoada ExtrQ (TCoada coada, char *x) {  //functia de extragere din coada
  TLista aux;
  if ((coada)->inc==NULL){
    return 0;
  }

  else{
    aux = (coada)->inc;
    x = aux->instructiune;
    (coada)->inc = (coada)->inc->urm;
    free(x);
    free(aux);
  }

  return coada;
}

void DistrugeBanda(TBanda *banda) {
    TLista2 p = (*banda)->santinela;
    while (p != NULL) {         /* distrugere elementele listei */
        TLista2 aux = p;
        p = p->urm;
        free(aux);
    }
    
    free(*banda);                  /* distrugere santinela */
    *banda = NULL;
}

TStiva InitS ()                         //functia de initializare a stivei
{
    TStiva s;          
    s = malloc(1 * sizeof(struct stiva));
    if (!s) return NULL;                 

    s->vf = NULL;
    return s;  
}

int IntrS(TStiva stiva, char *x) {      //functia de introducere in stiva
    TLista aux;
    aux = malloc(sizeof(struct celula));

    aux->instructiune = malloc(50 * sizeof(char));

    if (!aux) return 0;
    
    strcpy(aux->instructiune, x);
    aux->urm = NULL;

    aux->urm = stiva->vf;
    stiva->vf = aux;
                   
    return 1;
}

TStiva ExtrS(TStiva stiva, char *x) {   //functia de extragere din stiva
    TLista aux;
    if (stiva->vf == NULL){
        return 0;
    }

    else{
        aux = stiva->vf;
        x = 0;
        stiva->vf = stiva->vf->urm;
        free(aux);
    }

  return stiva;
}

void DezalocaS(TStiva *stiva) {         //dezalocare stiva
    TLista p = (*stiva)->vf, aux;

    while (p) {
        aux = p;
        p = p->urm;
        free(aux->instructiune);
        free(aux);
    }
}

void MOVE_RIGHT (TBanda *banda) {       
    if (!(*banda)->deget->urm) {
        TLista2 aux = AlocCelula2('#');
        aux->pre = (*banda)->deget;
        (*banda)->deget->urm = aux;
    }
    
    (*banda)->deget = (*banda)->deget->urm;
}

void MOVE_LEFT (TBanda *banda) {
    if ((*banda)->deget->pre->pre) {
        (*banda)->deget = (*banda)->deget->pre;
    }
}

void MOVE_RIGHT_CHAR(TBanda *banda, char c) {
    while ((*banda)->deget->urm) {
        if ((*banda)->deget->info == c) break;

        (*banda)->deget = (*banda)->deget->urm;
    }

    if (((*banda)->deget->info != c) && ((*banda)->deget->urm == NULL)) {
        MOVE_RIGHT(banda);
    }
}

void MOVE_LEFT_CHAR(TBanda *banda, char c, FILE *output) {
    TLista2 b = malloc(sizeof(struct celula2));
    b->urm = b->pre = NULL;
    b->info = c;

    b = (*banda)->deget;

    while (b->pre) {
        if (b->info == c) break;

        b = b->pre;
    }

    if (b != (*banda)->santinela) {
        (*banda)->deget = b;
    } else {
        fprintf(output, "%s", "ERROR\n");
    }
}

void WRITE (TBanda *banda, char c) {
    (*banda)->deget->info = c;
}

void INSERT_RIGHT (TBanda *banda, char c) {
    TLista2 aux = AlocCelula2(c);
    // aux->info = c;

    aux->urm = (*banda)->deget->urm;
    aux->pre = (*banda)->deget;
    if ((*banda)->deget->urm)
        (*banda)->deget->urm->pre = aux;
    (*banda)->deget->urm = aux;

    (*banda)->deget = (*banda)->deget->urm;
}

void INSERT_LEFT (TBanda *banda, char c, FILE *output) {
    TLista2 aux = AlocCelula2(c);

    if ((*banda)->deget->pre->pre) {
        aux->pre = (*banda)->deget->pre;
        aux->urm = (*banda)->deget;
        (*banda)->deget->pre->urm = aux;
        (*banda)->deget->pre = aux;

        (*banda)->deget = (*banda)->deget->pre;
    } else {
        fprintf(output, "%s", "ERROR\n");
    }
}

void SHOW_CURRENT (TBanda *banda, FILE *output) {
    fprintf(output, "%c\n", (*banda)->deget->info);
}

void SHOW (TBanda *banda, FILE *output) {
    TLista2 p = (*banda)->santinela->urm;

    while (p) {
        if (p == (*banda)->deget) {
            fprintf(output, "|%c|", p->info);
        } else {
            fprintf(output, "%c", p->info);
        }

        p = p->urm;
    }
    
    fprintf(output, "%s", "\n");
}

void UNDO (TBanda *banda, TStiva stiva_undo, TStiva stiva_redo) {
    char *cmd;
    cmd = stiva_undo->vf->instructiune;

    IntrS(stiva_redo, cmd);

    if (!strcmp(cmd, "MOVE_RIGHT\n")) {
        MOVE_LEFT(banda);
    }

    if (!strcmp(cmd, "MOVE_LEFT\n")) {
        MOVE_RIGHT(banda);
    }
    stiva_undo = ExtrS(stiva_undo, cmd);

    free(cmd);
}

void REDO (TBanda *banda, TStiva stiva_redo, TStiva stiva_undo) {
    char *cmd;
    cmd = stiva_redo->vf->instructiune;

    if (!strcmp(cmd, "MOVE_RIGHT\n")) {
        MOVE_RIGHT(banda);
    }

    if (!strcmp(cmd, "MOVE_LEFT\n")) {
        MOVE_LEFT(banda);
    }

    stiva_redo = ExtrS(stiva_redo, cmd);

    free(cmd);
}

void Citire(TCoada coada, TBanda *banda, TStiva s_undo, TStiva s_redo) {    //cu functia asta parcurs operatiile si le execut
    FILE *input = fopen("tema1.in", "rt");
    FILE *output = fopen("tema1.out", "w");

    char *inst = malloc(50 * sizeof(char));
    char *data = malloc(50 * sizeof(char));

    int counter;
    fscanf(input, "%d\n", &counter);

    for (int i = 0; i < counter; i++) {
        fgets(inst, 50, input);

        strncpy(data, inst, 50);

        if (!strcmp(inst, "MOVE_RIGHT\n")) {            
            IntrQ(coada, inst);
            IntrS(s_undo, inst);
        }

        if (!strcmp(inst, "MOVE_LEFT\n")) {
            IntrQ(coada, inst);
            IntrS(s_undo, inst);
        }

        if (!strcmp(strtok(data, " "), "WRITE")) {
            IntrQ(coada, inst);
        }

        if (!strcmp(strtok(data, " "), "MOVE_RIGHT_CHAR")) {
            IntrQ(coada, inst);
        }

        if (!strcmp(strtok(data, " "), "MOVE_LEFT_CHAR")) {
            IntrQ(coada, inst);
        }

        if (!strcmp(strtok(data, " "), "INSERT_RIGHT")) {
            IntrQ(coada, inst);
        }

        if (!strcmp(strtok(data, " "), "INSERT_LEFT")) {
            IntrQ(coada, inst);
        }

        if (!strcmp(inst, "SHOW\n")) {
            SHOW(banda, output); 
        }

        if (!strcmp(inst, "SHOW_CURRENT\n")) {
            SHOW_CURRENT(banda, output);
        } 

        if (!strcmp(inst, "UNDO\n")) {
            UNDO(banda, s_undo, s_redo);
        }

        if (!strcmp(inst, "REDO\n")) {
            REDO(banda, s_redo, s_undo); 
        }

        if (!strcmp(inst, "EXECUTE\n")) {
            Executare(coada, banda, output);
            
            
            if (coada->inc->urm) {
                coada = ExtrQ(coada, inst);
            } else {
                TLista aux;
                aux = AlocCelula("z");          //aici, in cazul in care coada s-a golit in urma executarii operatiilor, adaug o celula in coada ca sa pastrez adresa sfarsitului cozii
                coada->sf->urm = aux;
                coada->sf = coada->sf->urm;
                coada->sf = coada->sf->urm;
                coada = ExtrQ(coada, inst);
                free(aux);
            }
        }
    }
    fclose(input);
    fclose(output);
    free(inst);
    free(data);
}

void Executare (TCoada coada, TBanda *banda, FILE *output) {                //functia de executare a operatiilor update 
    char letter;
    char *instr = malloc(50 * sizeof(char));

    strncpy(instr, (coada)->inc->instructiune, 50);

    letter = instr[strlen(instr) - 2];

    if(!strcmp(instr, "MOVE_RIGHT\n")) {
        MOVE_RIGHT(banda);
    }

    if (!strcmp(instr, "MOVE_LEFT\n")) {
        MOVE_LEFT(banda);
    }

    if (!strcmp(strtok(instr," "), "MOVE_RIGHT_CHAR")) {
        MOVE_RIGHT_CHAR(banda, letter);
    }

    if (!strcmp(strtok(instr," "), "MOVE_LEFT_CHAR")) {
        MOVE_LEFT_CHAR(banda, letter, output);
    }
    
    if (!strcmp(strtok(instr," "), "WRITE")) {
        WRITE(banda, letter);
    }

    if (!strcmp(strtok(instr," "), "INSERT_RIGHT")) {
        INSERT_RIGHT(banda, letter);
    }

    if (!strcmp(strtok(instr," "), "INSERT_LEFT")) {
        INSERT_LEFT(banda, letter, output);
    }

    free(instr);
}

void AfisareQ(TCoada coada)  /* afisare elementele cozii */
{
  TCoada p;

  for(p->inc = (coada)->inc; p->inc != NULL; p->inc = p->inc->urm)
    printf("%s\n", strtok(p->inc->instructiune, "\n"));
}

void AfisareS(TStiva stiva) {
    TStiva p;

  for(p->vf = stiva->vf; p->vf != NULL; p->vf = p->vf->urm)
    printf("%s\n", strtok(p->vf->instructiune, "\n"));
}