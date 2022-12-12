#include <stdio.h>
#include <stdlib.h>
#include "ordvetor.h"


VETORORD* VETORD_create(int n, COMP* compara)
{
	VETORORD *p = (VETORORD*)malloc(sizeof(VETORORD));
	//p = ponteiro
	if(p == NULL)
	{
		fprintf(stderr, "Não foi possível alocar memória.\n");
		exit(EXIT_FAILURE);
	}
	//p -> N(do typedef VETORORD) = n(int n)
	p -> N = n;
	//'P' é atríbuto e não o ponteiro 
	p -> P = 0;
	//'p ->' comparador recebe compara
	p -> comparador = compara;
	p -> elems = (void**)malloc(sizeof(void*) * p->N);
	
	if(p -> elems == NULL)
	{
		fprintf(stderr, "Não foi possível alocar memória\n");
		exit(EXIT_FAILURE);
	}
	//nesse for vai ter um ponteiro e nele o ponteiro "p" apontará para "elems" e somará com a multiplicação de "i" pelo size of "void**" que sempre aponta "NULL".
	for(unsigned i = 0; i < p->N; ++i)
		p->elems[i] = NULL;
	
	return p;
}

void VETORD_add(VETORORD* vetor, void* newelem)
{
	//esse if certifica-se de que existe espaço dentro do vetor, que significa que, se P>=N, não tem espaço.
	if (vetor->P < vetor->N) 
	{
    	//esse if verifica a posição dos elementos.  
       	if (vetor->P == 0) 
            vetor->elems[0] = newelem;
        //else if verifica os elementos existentes no vetor implementado, após isso, vai comparar o newelem com os elementos do vetor, ele vê se pode add o elemento no final
        else if 
        (
			vetor->comparador(newelem, vetor->elems[vetor->P-1]) == 1 ||
			vetor->comparador(newelem, vetor->elems[vetor->P-1]) == 0
        ) 
            vetor->elems[vetor->P] = newelem;
		//esse else verifica a possibilidade de add elemento no meio do vetor 
		else 
        //o for servirá para "navegar" dentro do vetor e deslocar uma posição a frente.    
            for (int i = vetor->P-1; i > -1; --i) 
			{
        //o if é um swap que vai adicionar o novo elemento na posição.        
                if (vetor->comparador(newelem, vetor->elems[i]) == 1) 
				{
                    vetor->elems[i+1] = vetor->elems[i];
                    vetor->elems[i] = newelem;
                }
				else 
					break;
            

        vetor->P++;
    }	
}
//a função remove irá remover o elemento desejado e deslocar o resto do vetor para trás.
void* VETORD_remove(VETORORD* vetor)
{
	void* aux = vetor->elems[0];
 //o for irá deslocar todos os elementos.
    for(int i = 0; i < vetor->P-1; i++)
        vetor->elems[i] = vetor->elems[i+1]; 

    --vetor->P;

    return aux;
}
