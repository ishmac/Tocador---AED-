#include "stdio.h"
#include "stdlib.h"
#include "lseneutra.h"

typedef struct 
{
    int a;
    double b;
}t_composto;



typedef struct{
    int a, b;
    double x, y;
} t_composto;

int* criar_int(int init){
    int* x = malloc(sizeof(int));
    *x = init;
    return x;
}


t_composto* criar_composto(int a, double b){
    t_composto* composto = malloc(sizeof(t_composto));
    composto->a = a;
    composto->b = b;

    return composto;
}

void imprimir_composto(t_composto *composto){
    printf("a: %d b:%lf", composto->a, composto->b);
}
void imprimir_int(int* nro){
    printf("%d\n",*nro);
}
int main(){
    t_lse* nros = criar_lse(imprimir_int);
    
    t_lse* dos_composto = criar_lse(imprimir_composto);


    int a;
    double b;
    scanf("%d %lf", &a, &b);
    while(a>=0){
        inserir_final_lse(nros, criar_composto(a,b));
        scanf("%d %lf", &a, &b);
    }

    // Povoando a lista
   // int a, b;
   // double x, y;
    //scanf("%d %d %lf %lf", &a, &b, &x, &y);

    //while (a >= 0){
       // t_composto* novo_composto = criar_composto(a, b, x, y);
       // inserir_final_lse(nros, novo_composto);

       // scanf("%d %d %lf %lf", &a, &b, &x, &y);
    //}

    // Acessando a lista
    //int pos;
    //scanf("%d", &pos);

    //while (pos > 0){
        //t_composto* composto = acessar_lse(nros, pos);
       // printf("Valores: a=%d b=%d x=%.2lf y=%.2lf na posição: %d\n", composto->a, composto->b, composto->x, composto->y, pos);
       // scanf("%d", &pos);
    //}
    // Posição
    //imprimir_lse(nros); 
     imprimir_lse(dos_composto);
    return 0;
}
