#include <stdio.h>
#include <stdlib.h>

int static n_impressao;

struct carga
{
       int codigo;
       int prioridade;
};

void imprime(FILE* arquivo, struct carga *vetor, int inicio ,int t)
{
     int i;
     fprintf(arquivo, "%d: ", n_impressao);
     n_impressao++;
     for(i = 0; i < t; i++)
     {
           fprintf(arquivo, "%X ",vetor[i].codigo);
     }
     fprintf(arquivo, "\n");
}

void troca(struct carga *x, struct carga *y)
{
    struct carga temp;
     
    temp = *x;
    *x = *y;
    *y = temp;
}


int parente(i)
{
        return 2 * i + 1; // Retorna um dos filhos de i
}


void heapsort(FILE* arquivo, struct carga *vetor, int n)
{
    int inicio, fim;
    //int i;
 
    // heapify no vetor
    for(inicio = (n - 2) / 2; inicio >= 0; --inicio)  // pra toda a raiz
        {
        descer(vetor, inicio, n); // sift through it
        }
    
    imprime(arquivo, vetor, n, n);
     
    // Ordena��o do vetor
    for(fim = n - 1; fim; --fim) 
    {
        troca(&vetor[fim], &vetor[0]);  // troca dos valores
        descer(vetor, 0, fim);
        imprime(arquivo, vetor, n, n);
    }
}
 
int descer(struct carga *vetor, int inicio, int fim)
{
    int raiz, filho;
 
    raiz = inicio; 
    while(parente(raiz) < fim) // enquanto a raiz possuir filho
    {
        filho = parente(raiz); 
        if((filho + 1 < fim) && (vetor[filho].prioridade > vetor[filho+1].prioridade))
            ++filho; // verificar se outro filho � maior
        if(vetor[raiz].prioridade > vetor[filho].prioridade) // se a raiz � maior q o filho
        {
            troca(&vetor[filho], &vetor[raiz]); // troca dos valores
            raiz = filho; // descendo 
        }
        else 
            return; 
    }
}

/*int main(void)
{
    int vetor[5] = {6,4,3,5,2};
    int i,n = 5;
    FILE* entrada;
    heapsort(entrada, vetor, n);
    for(i = 0; i < n; i++)
    printf("%d ", vetor[i]);
    getch();
    return 0;
}*/


int main(int argc, char* argv[]){
    
    FILE* entrada;
    FILE* saida;
    //int *vetor;
    int i,n;
    int code, p;
    
    entrada = fopen(argv[1],"r");
    saida = fopen(argv[2],"w");
    
    fscanf(entrada,"%d",&n);
    
    //vetor = malloc(sizeof(int)*n);
    struct carga *vetor = (struct carga*) malloc(sizeof(struct carga)*n);
    
    for (i = 0; i < n; i++){
        fscanf(entrada,"%X %i",&code, &p);
        vetor[i].codigo = code;
        vetor[i].prioridade = p;
    } 
    heapsort(saida, vetor, n);
    return 0;
}

