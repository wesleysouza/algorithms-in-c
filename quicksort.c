#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[55];

int static n_impressao = 0;
int static corrige = 0;

void imprime(FILE* arquivo, String *v, int n)
{
    int i;
    if((n_impressao == 1) && (corrige == 0))
    {
        //n_impressao--;
        corrige++;
    }
    else
    {               
        fprintf(arquivo, "%d: ", n_impressao);
        n_impressao++;
        for(i = 0; i < n; i++){
        fprintf(arquivo,"%s ", v[i]);
        //fputs(v[i], arquivo);
        //fwrite(&v[i],50,1,arquivo);
        }   
        fprintf(arquivo,"\n");
    }
}

void quickSort(FILE* arquivo, String *a, int l, int r, int t)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
       j = partition(a, l, r);
       imprime(arquivo, a, t);
       quickSort(arquivo, a, l, j-1, t);
       quickSort(arquivo, a, j+1, r, t);
   }
	
}



int partition(String *a, int l, int r) {
   int i, j;
   String pivot, t;
   //pivot = a[l];
   strcpy(pivot, a[l]);
   i = l; 
   j = r + 1;
		
   while(1)
   {
	    //a[i] <= pivot && i <= r 
    do ++i; while((((strcmp(a[i], pivot)) == -1) || ((strcmp(a[i], pivot)) == 0)) && (i <= r));
   	do --j; while((strcmp(a[j], pivot)) == 1);
   	if( i >= j ) break;
   	//t = a[i]; a[i] = a[j]; a[j] = t;
   	strcpy(t, a[i]);
   	strcpy(a[i], a[j]);
   	strcpy(a[j], t);
   }
   //t = a[l]; a[l] = a[j]; a[j] = t;
   strcpy(t, a[l]);
   strcpy(a[l], a[j]);
   strcpy(a[j], t);
   return j;
}

/*int main() 
{
	String a[5] = {"bbb.wma", "c.wav", "aaa.mp3", "z.mp3", "aaa_b.wav"};

	int i;
	//printf("\n\nUnsorted array is:  ");
	//for(i = 0; i < 5; ++i)
	//printf(" %s ", a[i]);
	printf("\n");

	quickSort( a, 0, 4);

	//printf("\n\nSorted array is:  ");
	//for(i = 0; i < 5; ++i)
	//	printf(" %s ", a[i]);
	getch();

}*/

int main(int argc, char* argv[])
{
    FILE* entrada;
    FILE* saida;
    String *vetor;
    int tamanho;
    int i;
    String c;
    
    entrada = fopen(argv[1],"r");
    saida = fopen(argv[2],"w");
    printf("X");
    fscanf(entrada,"%d",&tamanho);
    vetor = malloc(sizeof(String)*tamanho);
    printf("XX");
    for (i = 0; i < tamanho; i++){
        fscanf(entrada,"%s ",&c);
        //fgets(c,50,entrada);
        //fread(&c,50,1,entrada);
        //vetor[i] = c;
        strcpy(vetor[i], c);
    }
    //int p = retornaPivo(vetor, tamanho);
    //trocar(&vetor[tamanho], &vetor[p]);
    //particionar(vetor, 0, tamanho - 1);
    imprime(saida, vetor, tamanho);
    quickSort(saida, vetor, 0, tamanho -1, tamanho);
    return 0; 
}

