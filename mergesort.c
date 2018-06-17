#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct carga
{
       int codigo;
       int prioridade;
};

int static n_impressao = 0;

/*
*    Metodo comparable: compara a carga seguindo a prioridade:
*    1 - Codigo do propiet�rio
*    2 - Prioridade
*    3 - Codigo Numerico  
*/
bool comparable(struct carga a, struct carga b)
{       
    if((a.codigo & 0xFFF00000) < (b.codigo & 0xFFF00000))
	{
		return true;
	}
	else
	{
		if((a.codigo & 0xFFF00000) == (b.codigo & 0xFFF00000))
		{
			if(a.prioridade > b.prioridade)
			{
				return true;
			}
			else
			{
				if(a.prioridade == b.prioridade)
				{
					if((a.codigo & 0x000fffff) > (b.codigo & 0x000fffff))
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
		}
		else
		{
			return false;
		}
		return false;
	}                            
}    

void imprime(FILE* arquivo, struct carga *vetor, int inicio ,int t)
{
     int i;
     fprintf(arquivo, "%d: ", n_impressao);
     n_impressao++;
     for(i = inicio; i < t; i++)
     {
           fprintf(arquivo, "%X ",vetor[i].codigo);
     }
     fprintf(arquivo, "\n");
}

void Merge(FILE* arquivo, struct carga *vetor, struct carga *temp, int e, int q, int d, int n) 
{ 
  int p1, p2, tamanho; 
  int fim1=0, fim2=0; 
  int i;
  int j;
  int k;

  tamanho = d-e+1; 
  p1 = e;          
  p2 = q+1;   
  
  temp = (struct carga*) malloc(sizeof(struct carga)*tamanho);
  //struct carga *vetor_temporario_cargas = (struct carga*) malloc(sizeof(struct carga)*n);
  
     for(i=0; i<tamanho; i++) 
     { 
        if(!fim1 && !fim2)  // Nenhum dos vetores chegou ao fim // 
        { 
           if(comparable(vetor[p1], vetor[p2])) // Seleciona o maior //
           //if(vetor[p1].codigo > vetor[p2].codigo)
           {
                temp[i]=vetor[p1++];
           }
           else
           { 
                temp[i]=vetor[p2++]; 
                           }
           if(p1>q) 
                fim1=1; 
           if(p2>d) 
                fim2=1;
        } 
        else 
        { 
           if(!fim1)
           {
                temp[i]=vetor[p1++];
           }
           else 
           {
                temp[i]=vetor[p2++];
           }
        } 
     }
     for(j=0, k=e; j<tamanho; j++, k++)   // Copia do vetor tempor�rio p/ o vetor a ser retornado // 
         vetor[k]=temp[j]; 
         
         imprime(arquivo, vetor,0, n);
  
  free(temp); 
}

void MergeSort(FILE* arquivo, struct carga *A, struct carga *B, int e, int d, int n) 
{ 
  int q; 
  
  if (e < d)      
  { 
    q = ((e+d)-1)/2;   // Determina a metade do vetor // 
    MergeSort(arquivo, A, B, e, q, n);     // Primeira metade // 
    MergeSort(arquivo, A, B, q+1, d, n);   // Segunda metade //
    Merge(arquivo, A, B, e, q, d, n);       // Combina as metades j� ordenadas //
  } 
}

/*main(){
       int x=0;
       int vetor[6]={4, 5, 9, 7, 3, 8};
       int temp[6];
       MergeSort(vetor, temp ,0 ,5);
       //for(x=0;x<6;x++)
                        //printf("%d ",vetor[x]);
       //}
       system("pause");
}*/

int main(int argc, char* argv[]){
    
    FILE* entrada;
    FILE* saida;
    //int *vetor;
    //int *vetorTemporario;
    int i,n;
    int code, p;
    
    entrada = fopen(argv[1],"r");
    saida = fopen(argv[2],"w");
    
    fscanf(entrada,"%d",&n);
    
    //struct carga *cargas = (struct carga*) (malloc(sizeof(struct carga)));
    struct carga *vetor_cargas = (struct carga*) malloc(sizeof(struct carga)*n);
    struct carga *vetor_temporario_cargas = (struct carga*) malloc(sizeof(struct carga)*n);
    //vetorTemporario = malloc(sizeof(int)*n);
    
    //Leitura dos dados do arquivo
    for (i = 0; i < n; i++){
        fscanf(entrada,"%X %i",&code, &p);
        vetor_cargas[i].codigo = code;
        vetor_cargas[i].prioridade = p;
    } 
    imprime(saida, vetor_cargas,0, n);
    MergeSort(saida, vetor_cargas, vetor_temporario_cargas, 0, n - 1, n);
    //imprime(saida, vetor_cargas,0, i);
    return 0;
}
