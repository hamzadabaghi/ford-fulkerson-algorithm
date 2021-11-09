#include <stdio.h>
#include<stdlib.h>

// les couleurs pour sauvgarder l'etat d'un sommet 

// pas encore traite

#define WHITE 0

// dans la chaine ameliorente

#define GRAY 1

// traite

#define BLACK 2

// maximum des noeuds

#define MAX_NODES 1000

// l'infinie 

#define oo 1000000000

// le nombre de sommet

int n; 

// le nombre d'arrets

int e; 

// matrice des capacites

int capacity[MAX_NODES][MAX_NODES]; 

// matrice des flux

int flow[MAX_NODES][MAX_NODES];

// pour garder l'etat d'un sommet 

int color[MAX_NODES]; 

// tableau pour stocker la chaine ameliorante

int pred[MAX_NODES]; 

// fonctionne qui retourne le min entre deux variables 

int min (int x, int y) {
    return x<y ? x : y; 
}


// head la tete du tableau , tail , la queue du tableau

int head,tail;

// tableau pour stocker temporairement le dernier et le prochain sommet dans la chaine ameliorante

int q[MAX_NODES+2];

// insere un element dans la queue du tableau , le marque par GRAY et change la tete

void enqueue (int x) {
    q[tail] = x;
    tail++;
    color[x] = GRAY;
}

// depile un element dans la tete du tableau , le marque par BLACK et change la tete

int dequeue () {
    int x = q[head];
    head++;
    color[x] = BLACK;
    return x;
}

// cherche une chaine ameliorente 

int bfs (int start, int target) {
    int u,v;
    
    /* marquer tous les sommets non visite */
    
    for (u=0; u<n; u++) {
	color[u] = WHITE;
    }   
    
    
    /* inialisation du tableau temporaire */
    head = tail = 0;
    
    /* marquer la source comme visite et en inserer dans le tableau temporaire */
    
    enqueue(start);
    
    /* son ensemble de predecesseur est ensemble vide */
    
    pred[start] = -1;
    
    /* tant que le tableau temporaire n'est pas vide faire */
    
    while (head!=tail) {
    
    /* on vide le tableau temporaire au debut ,
	s'il n'entre pas dans la conditione il sort de la boucle */
	
	u = dequeue();
   
    /*
	
	ce for en dessous , cherche dans tous les sommets dans le graphe d'ecart
	
	Recherche tous les neouds blancs adjacents v. Si la capacite
	de u a v dans le graphe d'ecart est positif, 
	il l'ajoute aux q ( empiler , depiler ) pour faire le meme traitement 
	et puis dans le tableau de la chaine ameliorente
    
    */
    
	for (v=0; v<n; v++) {
		
		/* si u et v sont connectes et que v n'est pas visite, alors */
		
	    if (color[v]==WHITE && capacity[u][v]-flow[u][v]>0) {
	    	
	    /* ajouter v dans le tableau temporaire , et le marquer comme visite et dans la liste ameliorente */
	    
		enqueue(v);
		
		/* le prodecesseur de v est l'ancien valeur dans la queue */
		
		pred[v] = u;
		
	    }
	}
    }
    
    /*  Si la couleur du neoud cible est maintenant noire
		cela signifie que nous l'avons atteint.
	*/
    return color[target]==BLACK;
}

int max_flow (int source, int sink) {
    int i,j,u;
   
    /* on initialise le flux a  zero */
    
    int max_flow = 0;
    for (i=0; i<n; i++) {
	for (j=0; j<n; j++) {
	    flow[i][j] = 0;
	}
    }
    
    /* tant qu'il ya une chaine ameliorente faire le traitement */
    
    while (bfs(source,sink)) {
       
    /* 
	   le for en dessous
	   Tant qu'il existe un chemin augmentant,
       incremente le flux le long de ce chemin. 
	*/   
	
	int increment = oo;
	
	/* afficher la chaine améliorente */
	
	printf("le chemin de la chaine ameliorente est : ( %d ) " , n-1 );
	
	for (u=n-1; pred[u]>=0; u=pred[u]) {
		
		/*
		
		Determine le minimum de la chaine ameliorente 
		par lequel on peut incrementer le flux.
		
		*/
		
	    increment = min(increment,capacity[pred[u]][u]-flow[pred[u]][u]);
	
	    printf("<-- ( %d ) " ,pred[u]);
	    
	    
	}
	
	printf("\n");
	
       
    /*  incrementer le flux ou le decrementer dans le cas si l'arc est indirect ( s'il existe bien sur ) , 
	
	dans le graphe d'ecart */

	for (u=n-1; pred[u]>=0; u=pred[u]) {
	    flow[pred[u]][u] += increment;
	    flow[u][pred[u]] -= increment;
	}
	max_flow += increment;
	
	printf("le flot augmentee par cette chaine est : %d \n", increment);
	
    }
   
   	/* s'il n y a pas de chaine ameliorente on a fini */
   	
   	
    return max_flow;
}

void read_input_file() {
    int a,b,c,i,j;
    FILE* input = fopen("data.txt","r");
    
    fscanf(input,"%d %d",&n,&e);
    printf("\nNombre de sommets : %d   les arcs : %d",n,e);
    
    /* inialise les capacites a  zero */
    
    for (i=0; i<n; i++) {
	for (j=0; j<n; j++) {
	    capacity[i][j] = 0;
	}
    }
    
    
    /* sommet a , sommet b , capacite c */
    
    for (i=0; i<e; i++) {
	fscanf(input,"%d %d %d",&a,&b,&c);
	capacity[a][b] = c;
	printf("\nA : %d  B : %d  Capacite : %d",a,b,c);
    }
    fclose(input);
}

int main () {
    read_input_file();
    printf("\nentre la source(s) et le puit(s) :\n");
    
    /* valeur par defaut de s et t : source , puits */
    
    int s=0,t=n-1;
    scanf("%d %d",&s,&t);
    
    /* calcul du flot */
    
    printf("\nle flot maximal est  : %d\n",max_flow(s,t));
    return 0;
}
