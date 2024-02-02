#include "stdio.h"
#include "stdlib.h"
#include "lseneutra.h"

typedef struct elem_se{
    void* carga_util;
    struct elem_se* prox;
} t_elemento_lse;

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lse(void* carga_util){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga_util;
    novo->prox = NULL;

    //printf("Criando: %p %p %p\n", novo, novo->carga_util, novo->prox);

    return novo;
}

struct lse{
    t_elemento_lse* inicio;
    t_elemento_lse* fim;
    int tamanho;
    t_imprimir_lse impressora;
    t_comparar_lse comparador;
};


t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparador){ //, t_comparar_lse comparar){
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    l->impressora = impressora;
    l->comparador = comparador;

    return l;
}

void imprimir_lse(t_lse* lse){
    t_elemento_lse* cam = lse->inicio;

    while(cam!=NULL){
        //printf("%p\n", cam->carga_util);
        lse->impressora(cam->carga_util);
        cam = cam->prox;
    }
}


void inserir_lse(t_lse* lse, void* carga_util){
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo; 
    }else{
        novo->prox = lse->inicio;
        lse->inicio = novo;
    }

    lse->tamanho++;
}

void inserir_final_lse(t_lse* lse, void* carga_util){
    
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo;
    }else{
       lse->fim->prox = novo;
        lse->fim = novo;
    }
    lse->tamanho++;

}

void  inserir_ordenado_lse(t_lse* lse, void* carga){
    t_elemento_lse *novo= criar_elemento_lse(carga);
    if(lse->inicio==NULL){
        lse->inicio = lse->fim = novo;
        
    } else{
        t_elemento_lse *ant = NULL;//anterior
        t_elemento_lse *cam = lse->inicio;//caminhador
        while ((cam !=NULL)&&(lse->comparador(cam->carga_util, carga)<= 0))
        {
            ant = cam;
            cam = cam->prox;
        }
        if(cam==NULL){//inserir no  final
        lse->fim->prox = novo;
        lse->fim=novo;

        }else if(cam == lse->inicio){//inserir no inicio
            novo->prox=lse->inicio;
            lse->inicio = novo;

        } else{//entre dois elementos
            ant->prox = novo;
            novo->prox = cam;
        }
        
    }
}


void* acessar_lse(t_lse* lse, int pos){
    pos = (pos%lse->tamanho);
    pos = (pos == 0?lse->tamanho:pos);

    t_elemento_lse *cam = lse->inicio;
    for(int i=1;i<pos;i++){
        cam = cam->prox;  
    }
    return cam->carga_util;
}

void destruir_lse(t_lse* lse){
    t_elemento_lse* elem = lse->inicio;
    while(elem!=NULL){
        t_elemento_lse* proximo = elem->prox;
        //destruir_elem_lse(elem->carga);
        free(elem->carga_util);
        free(elem);
        elem = proximo;
    } 
}

void* remover_inicio_lse(t_lse* lse) {
    if (lse->inicio == NULL) {
        return NULL;
    }

    t_elemento_lse* removido = lse->inicio;
    void* carga_util = removido->carga_util;
    lse->inicio = removido->prox;
    free(removido);

    lse->tamanho--;

    if (lse->inicio == NULL) {
        lse->fim = NULL;
    }

    return carga_util;
}

void* remover_final_lse(t_lse* lse) {
    if (lse->inicio == NULL) {
        // Lista vazia, não há o que remover
        return NULL;
    }

    t_elemento_lse* removido;
    void* carga_util;

    if (lse->inicio == lse->fim) {
        removido = lse->inicio;
        carga_util = removido->carga_util;
        lse->inicio = lse->fim = NULL;
    } else {
        t_elemento_lse* anterior = lse->inicio;
        while (anterior->prox != lse->fim) {
            anterior = anterior->prox;
        }

        removido = lse->fim;
        carga_util = removido->carga_util;
        anterior->prox = NULL;
        lse->fim = anterior;
    }

    free(removido);
    lse->tamanho--;

    if (lse->inicio == NULL) {
        lse->fim = NULL;
    }

    return carga_util;
}

void* buscar_lse(t_lse *lse, void* buscado){
    t_elemento_lse *cam = lse->inicio;
    short achei = 0; // falso
    while( (cam != NULL) && (!achei) ){
        //printf("%p\n", cam->carga_util);
        if (lse->comparador(cam->carga_util,buscado)==0){
            achei=1; //verdade
        }else{
            cam = cam->prox;
        }
    }
    if (achei)
        return cam->carga_util;
    else
        return NULL;
    
}