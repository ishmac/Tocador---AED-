#include"stdio.h"
#include"stdlib.h"
#include"lseneutra.h"

typedef struct pilha t_pilha;

struct pilha
{
    int altura;
    t_lse *elementos;  
};

t_pilha* criar_pilha(){
    t_pilha* nova = malloc(sizeof(t_pilha));
    nova->altura = 0;
    nova->elementos = criar_lse(NULL,NULL);

    return nova;
}

void empilhar(t_pilha* p, void* novo){
    if(p!=NULL){
        inserir_lse(p->elementos, novo);
        p->altura++;
    }
}


void* desempilhar(t_pilha* p){
    void* el = NULL;
    if((p!= NULL )&& (p->altura>0)){
        el = remover_inicio_lse(p->elementos);
        p->altura--;
        el = acessar_lse(p->elementos,1);
    }
    return el;
}

void* topo(t_pilha *p){
    void *el = NULL;
    if((p!=NULL)&&(p->altura>0)){
        return acessar_lse(p->elementos,1);
    }
}

int altura_pilha(t_pilha *p){
    return p->altura;
}