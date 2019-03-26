#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define VERTICES 12

typedef struct node {
	int chave;
	struct node* prox;
} NO;

typedef struct graph {
	NO* ADJ[VERTICES + 1];
	char COR[VERTICES + 1];
	int MINOR[VERTICES + 1];
	int ORDEM[VERTICES + 1];
	int PAI[VERTICES + 1];
	int ord;
} GRAFO;

//COR: b = branco, c = cinza, p = preto

void inicializar(GRAFO* g) {
	for (int i = 1; i <= VERTICES; i++){
		g->ADJ[i] = NULL;
		g->COR[i] = 'b';
		g->MINOR[i] = 0;
		g->ORDEM[i] = 0;
		g->PAI[i] = 0;
		//printf("repeticao %i \n", i);
	}
	g->ord = 0;
}

void inserir(GRAFO* g, int vertice, int adjacente) {
	NO* aux = g->ADJ[vertice];
	if(aux == NULL) {
		NO* novo = (NO*) malloc (sizeof(NO));
		novo->chave = adjacente;
		novo->prox = NULL;
		g->ADJ[vertice] = novo;
	}
	else {
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		NO* novo = (NO*) malloc (sizeof(NO));
		novo->chave = adjacente;
		novo->prox = NULL;
		aux->prox = novo;
	}
}

void imprimir(GRAFO* g) {
	NO* aux;
	for (int i = 1; i <= VERTICES; i++) {
		aux = g->ADJ[i];
		printf("\nO vertice %i tem adjacentes ", i);
		while(aux) {
			printf("%i, ", aux->chave);
			aux = aux->prox;
		}
	}
	printf("\n");
}

void DFS1(GRAFO* g, int vertice) {
	NO* aux = g->ADJ[vertice];
	while(aux){
		if(g->COR[aux->chave] == 'b') {
			g->COR[aux->chave] = 'c';
			g->ORDEM[aux->chave] = ++(g->ord);
			g->MINOR[aux->chave] = g->ord;
			g->PAI[aux->chave] = vertice;
			DFS1(g, aux->chave);
		}
		aux = aux->prox;
	}
	g->COR[vertice] = 'p';
}

void DFS2(GRAFO* g, int vertice) {
	NO* aux = g->ADJ[vertice];
	while(aux){
		if(g->PAI[aux->chave] == vertice) {
			DFS2(g, aux->chave);
		}
		aux = aux->prox;
	}
	aux = g->ADJ[vertice];
	while(aux) {
		if((aux->chave != g->PAI[vertice]) && (g->MINOR[aux->chave] < g->MINOR[vertice])) {
			g->MINOR[vertice] = g->MINOR[aux->chave];
		}
		aux = aux->prox;
	}
}

bool ehBiconexo(GRAFO* g) {
	g->COR[1] = 'c';
	g->ORDEM[1] = ++(g->ord);
	g->MINOR[1] = g->ord;
	bool biconexo = false;
	DFS1(g, 1);

	if(g->ord == VERTICES) {
		g->MINOR[1] = g->ORDEM[1];
		DFS2(g, 1);
		biconexo = true;

		for(int i = 1; i <= VERTICES; i++){
			printf("\no vertice %i tem ordem %i e minor %i ", i, g->ORDEM[i], g->MINOR[i]);
			if((i != 1) && (g->ORDEM[i] == g->MINOR[i])) {
				printf("a aresta que liga os vertices %i e %i eh a aresta critica", i, g->PAI[i]);
				biconexo = false;
			}
		}
		return biconexo;
	}
	else
		return biconexo = false;

}

int main() {
	
	GRAFO* g = (GRAFO*) malloc (sizeof(GRAFO));
	inicializar (g);
	inserir (g, 1, 2);
	inserir (g, 1, 3);
	inserir (g, 2, 1);
	inserir (g, 2, 4);
	inserir (g, 2, 5);
	inserir (g, 3, 1);
	inserir (g, 3, 5);
	inserir (g, 4, 2);
	inserir (g, 4, 6);
	inserir (g, 4, 7);
	inserir (g, 5, 2);
	inserir (g, 5, 3);
	inserir (g, 5, 6);
	inserir (g, 6, 4);
	inserir (g, 6, 5);
	inserir (g, 7, 4);
	inserir (g, 7, 8);
	inserir (g, 7, 9);
	inserir (g, 7, 12);
	inserir (g, 8, 7);
	inserir (g, 8, 9);
	inserir (g, 9, 7);
	inserir (g, 9, 10);
	inserir (g, 10, 9);
	inserir (g, 10, 11);
	inserir (g, 10, 12);
	inserir (g, 11, 9);
	inserir (g, 11, 10);
	inserir (g, 12, 7);
	inserir (g, 12, 10);

	//imprimir(g);

	if(ehBiconexo(g))
		printf("\nO GRAFO EH BICONEXO\n\n");
	else
		printf("\nO GRAFO NAO EH BICONEXO\n\n");

	return 0;
}