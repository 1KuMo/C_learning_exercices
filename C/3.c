#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>


// 1
void test(){
    int x = 1;
    int *p = &x;
    printf("x : %d\nadresse de x : %d\n", *p, p);
    *p += 1;
    printf("x : %d\n", *p);
}


// 2
void swap(int *a, int *b){
    int temp = *a ;
    *a = *b;
    *b = temp ;
}


// 3
void minetmax(int tab[], int n, int *min, int *max){
    *min = tab[0];
    *max = tab[0];
    for(int i=0; i<n; i++){
        if(*min > tab[i]){
            *min = tab[i];
        }
        if(*max < tab[i]){
            *max = tab[i];
        }
    }
}


// 4
int somme(int tab[],int n){
    int buffer = 0;
    for(int i=0; i<n; i++){
        buffer += *tab;
        *tab++ ;
    }
    return buffer;
}  


int moyenne(int tab[], int n){
    return somme(tab, n) / n ;
}


void afficherTab(int tab[], int n) {
    // print(tab) btw (zbi)
    for (int i = 0; i < n; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}


void inverser(int tab[], int n){
    // obligé de mettre n pour droite ( int **droite = &tab[-1]; )
    // error: initialization of ‘int **’ from incompatible pointer type ‘int *’ 
    int *droite = &tab[n-1];
    int *gauche = tab;
    int temp;
    while(gauche < droite){
        temp = *droite;
        *droite = *gauche;
        *gauche = temp;
        gauche ++;
        droite --;
    }
}


int len(char *s){
    int compteur = 0;
    while (*s!='\0'){
        s++; // comme c'est un tableau de plusieurs caracteres ca marche :D
        compteur++;
    }
    return compteur;
}


void copier(char *copie, char *base){
    for(int i = 0 ; i <= len(base) ; i++ ){ 
        // on recupere le \0 pour mettre une fin à notre copie 
        copie[i] = base[i]; 
    }
}


int nb_voyelles(char *chaine){
    int buffer = 0;
    while(*chaine != '\0'){
        char c = tolower(*chaine);
        // c in 'aeiouy' ?  oui -> pointeur vers ce caractere / non -> renvoie NULL
        if (strchr("aeiouy", c) != NULL) {
            buffer++;
        chaine++;
        }
    }
    return buffer;
}


void retirer_espaces(char *s){
    char *lecture = s;
    char *ecriture = s; 
    // on réecrit tout par dessus notre texte de base ( sans les espaces )
    while (*lecture != '\0'){
        if (*lecture != ' '){
            *ecriture = *lecture;
            *ecriture++;
        }
        *lecture++ ;
    }
    *ecriture = '\0';
}


int min_p(int tab[], int n){
    int *min = tab;
    for(int i=0; i<n; i++){
        if(*min > tab[i]){
            *min = tab[i];
        }
    }
    return min;
}


/*
EXERCICE 11
*/

void ajouter_reel(int **tab, int *n, int x){
    int *temp = realloc(*tab, (*n+1) * sizeof(int));
    if (temp == NULL){
        free(*tab);
        exit(1);
    } 

    *tab=temp;
    /*
    free(temp);
    output : free(): double free detected in tcache 2
    damn la fonction libère automatiquement temp puisqu'il est 
    directement déclaré dans la fonction ཐི ₍^. ̫.^₎ ཋྀ
    */
    int *cur = (*tab+*n);
    (*n)++ ;
    *cur = x ;
}


float calculer_moyenne(int *tab, int n){
    int somme = 0; 
    for(int i = 0; i < n; i++){
        // printf("%d\n", somme);
        somme+=*tab;
        tab++;
    }
    // printf("%d;%d\n", somme, n);
    float moyenne = (float)somme / n ;
    return moyenne;
}


// EXERCICE 12 
int* get(int A[], int N, int i, int j){
    /*
    A = matrice
    N = taille ( N * N )
    i / j = indices de l'objet voulu 
    pour la logique de ce code, voir help-ex12.png :D
    */
    int k = N;
    int l = 1 ;
    int *curs = A;
    printf("curs : %d\n", *curs);

    curs += (i * k) + (j * l);
    
    return curs;
}


void set(int A[], int N, int i, int j, int val){
    int *toReplace = get(A, N, i, j);
    *toReplace = val;
}


// EXERCICE 13 
void push_back(int **T,int *n,int v){
    int *temp = realloc(*T, (*n+1) * sizeof(int));
    if (temp == NULL){
        free(*T);
        exit(1);
    } 
    
    *T = temp;
    int *last = (*T + *n);
    (*n)++;
    *last = v;

}


// EXERCICE 14 
// https://www.w3schools.com/c/c_functions_callback.php

int doubler(int x) {
    x *= 2;
    // printf("%d\n", x);
    return x; 
}


void appliquer(int tab[], int n, int (*callback)(int)){
    int *i = tab;
    for(int j = 0 ; j<n ; j++){
        // printf("a\n");
        *i = callback(*i);
        i++;
    }
}


// EXERCICE 15 
// https://koor.fr/C/cstdlib/qsort.wp
// je préfère le shuffle sort mais bon exo oblige...

int intComparator ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int intComparatorDesc ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return -(firstInt - secondInt);
}


/*
note de l'ia 
const void * : reçoit les pointeurs génériques transmis par qsort.
(const int *) first : convertit le pointeur générique en pointeur vers un entier constant.
* (const int *) first : récupère la valeur de l'entier pointé.
return firstInt - secondInt; : donne le sens de comparaison pour le tri croissant.

*/
void trier_qsort(int tab[], int n){
    qsort( tab, n, sizeof(int), intComparator );
    afficher_tab(tab, n);
    qsort( tab, n, sizeof(int), intComparatorDesc );
    afficher_tab(tab, n);
}


// EXERCICE 16 / thank god des gens font des cours
// jsens la patate arriver avec les vecteurs 
// https://hichamjanati.github.io/media/C/structures.pdf
typedef struct Etudiant Etudiant;
struct Etudiant{
    char nom[32];
    int note;
} Etudiant;


void init(Etudiant *e, char *nom, int note){
    if (e==NULL){
        return; 
    }
    
    e -> note = note;
    e -> nom = nom;
}


int main(){
    // 1
    // test();

    /* // 2 
    int a = 1, b=2;
    printf("a : %d\nb : %d\n", a, b);
    swap (&a, &b);
    printf("a : %d\nb : %d\n", a, b);
    */
 
    /* // 3
    int tab[] = {25, 50, 75, 100};
    int min, max ;
    minetmax(tab, 4, &min, &max);
    printf("min : %d\nmax : %d\n", min, max);
    */
    
    /* // 4 
    int tab[] = {25, 50, 75, 100};
    printf("somme : %d\nmoyenne : %d\n", somme(tab, 4), moyenne(tab, 4));
    */

    /* // 5
    int tab[] = {25, 50, 75, 100};
    inverser(tab, 4);
    printf("tableau inversé !\n");
    afficherTab(tab, 4);    
    */

    /* // 6
    char *chaine = "Hello World!";
    printf("il y a %d caract dans la chaine\n", len(chaine));
    */

    /* // 7 
    char *base = "blabla";
    char copie[100]; // Segmentation fault (core dumped) :(
    copier(copie, base);
    printf("copie de la chaine : %s\n", copie);
    */

    /* // 8
    char *s = "hello";
    printf("il y a %d voyelles dans la chaine\n", nb_voyelles(s));
    */

    /* // 9 
    char chaine[] = "Hello world o/ ! ";
    // je viens de découvrir la fameuse difference entre *chaine et chaine[]  (je hais les docs)
    // *chaine -> pointeur vers une chaine en mode lecture seule
    // chaine[] -> tab de caractere ( la base ) donc modifiable 
    printf("chaine de base : %s\n", chaine);
    retirer_espaces(chaine);
    printf("chaine sans espaces : %s\n", chaine);
    */
    
    /* // 10 
    int tab[] = {25, 50, 75, 100};
    int *p_min = min_p(tab, 4);

    if (p_min != NULL){
        int indice = p_min - tab;
        printf("minimum : %d\n", *p_min);
        printf("indice : %d\n", indice);
    }
    */

    /* 11
    int size = 0 ;
    int *tab = malloc(size * sizeof(int));

    ajouter_reel(&tab, &size, 18);
    ajouter_reel(&tab, &size, 20);
    ajouter_reel(&tab, &size, 2);
    ajouter_reel(&tab, &size, 11);

    printf("%d\n", size);
    for (int i = 0; i<size; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");

    printf("moyenne de tab : %f\n", calculer_moyenne(tab, size));

    free(tab);
    return 0; 
    */

    /* 12 
    int matrice[] = {4, 8, 7, 1, 9, 3, 0, 2, 5};
    // printf("taille tab; %d\n", sizeof(matrice) / sizeof(matrice[0]));
    int taille = sizeof(matrice) / sizeof(matrice[0]);
    afficher_tab(matrice, taille);
    set(matrice, 3, 2, 2, 18);
    // printf("%d\n", *rep);
    afficher_tab(matrice, taille);
    return 0;
    */

    /* 13 
    int n = 0 ;
    int *tab = malloc(n * sizeof(int));

    push_back(&tab, &n, 10);
    push_back(&tab, &n, 20);
    push_back(&tab, &n, 30);
    push_back(&tab, &n, 5);

    printf("%d\n", n);
    
    // afficher_tab(tab, sizeof(tab)/sizeof(tab[0]));

    printf("%d\n", n);
    for (int i = 0; i<n; i++){
        printf("C%d ", tab[i]);
    }
    printf("\n");
    
    free(tab);
    return 0;
    */

    /* 14 
    int tab[] = {1,2,3,4,5};
    int n = sizeof(tab) / sizeof(tab[0]);
    appliquer(tab,n,doubler);
    afficher_tab(tab, n);
    return 0;
    */

    /* 15 
    int tab[] = {8, 3, 12, 1, 6};
    trier_qsort(tab, sizeof(tab)/sizeof(tab[0]));
    return 0;
    */ 

    Etudiant e1;

    init(&e1, "toad", 20);
    return 0;
}
