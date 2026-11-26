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


int* min_p(int tab[], int n){
    int *min = tab;
    for(int i=0; i<n; i++){
        if(*min > tab[i]){
            *min = tab[i];
        }
    }
    return min;
}

// voir bonus.c 

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
    afficherTab(tab, n);
    qsort( tab, n, sizeof(int), intComparatorDesc );
    afficherTab(tab, n);
}


// EXERCICE 16 / thank god des gens font des cours
/*
https://www.youtube.com/watch?v=JsUSp4cf_2w
jsens la patate arriver entre les files les piles les ABR (can't wait de parcourir 800 arbres j'adore ça autant qu'la récursivité )
https://hichamjanati.github.io/media/C/structures.pdf
à la base la feuille d'exercice porte sur les pointeurs pourquoi j'apprends ça maintenant..
*/
typedef struct{
    char nom[32];
    int note;
} Etudiant;

void init(Etudiant *e, char *nom, int note){
    if (e==NULL){
        return; 
    }
    
    // quand on utilise une structure depuis des pointeurs on mets des ptites fleches au lieu des points
    // spot the difference
    strcpy(e->nom, nom);
    e->note = note;
}


// EXERCICE 17 ( jsais pas comment ca marche mais ca marche )
/*
wow
https://www.youtube.com/watch?v=oZLpB2BagHQ&
https://www.youtube.com/watch?v=XME03psQ9mo
incroyable le seul cours compréhensible 
*/


// debut->valeur est synonyme de (*debut).valeur

struct Elt{
    int val;
    struct Elt *suivant;
};
typedef struct Elt LISTE;

void push_front(LISTE** tete, int val) {
    LISTE* suiv = malloc(sizeof(LISTE)); // ...
    
    suiv->val = val;
    suiv->suivant = *tete;  
    *tete = suiv;
}


void push_end(LISTE** tete, int val){
    // on le place après 'en_place' 
    LISTE* pCourant; 

    pCourant = *tete;
    while(pCourant->suivant != NULL){
        pCourant = pCourant->suivant;
    }

    LISTE* courant = malloc(sizeof(LISTE));
    pCourant->suivant = courant;
    courant->val = val;

}


void push_toelt(LISTE** tete, int elt, int val){
    LISTE* pCourant; 

    pCourant = *tete;
    while(pCourant->val != elt){
        pCourant = pCourant->suivant;
    }

    if(pCourant!=0){
        LISTE* courant = malloc(sizeof(LISTE));
        courant->suivant = pCourant->suivant;
        pCourant->suivant = courant;
        courant->val = val;
    }
    // don't ask the else 
}

// EXERCICE 18 
/* merci à l'ia de m'explquer ces consignes incompréhensibles 
4. Ce que ta fonction doit faire
    En gros, elle doit :
    1. Repérer le début du premier token.
    2. Stocker son adresse dans out[0].
    3. Parcourir s.
    4. Chaque fois qu'elle rencontre une virgule :
    - remplacer la virgule par '\0' ;
    - enregistrer l'adresse du caractère suivant dans out[] (si c'est le début d'un token).
    5. Retourner le nombre de tokens trouvés.
*/

int sam_altman(char s[]){
    // on va prendre un texte sans espaces après le début du premier token
    char* curs = s;
    while (*curs == ' '){
        curs++;
    }

    char* out[10]; // faut pas mettre un roman non plus svp
    int i = 0;
    bool dernierVirgule = true;

    while (*curs != '\0'){
        if(*curs == ','){
            *curs = '\0';
            dernierVirgule = true ;
        }

        else if (dernierVirgule){
            dernierVirgule = false;
            out[i] = curs;
            i++;
        }
        curs++;
    }
    return i;
}


// EXERCICE 19
int dot(const int *A, const int *B, int n){
    const int *fin = A + n ;
    int somme = 0;
    while(A != fin){
        somme += *A * *B;
        A++;
        B++;
    }
    return somme ; 
}


// EXERCICE 20 - gcc 3.c -lm
/*
double fonction(double x){
    // double ret = pow(x,2);
    // return ret; 
    return x * 2;
}
*/

// c'est si beau
double integrale(double (*callback)(double), double a, double b, int n){
    double h = (b-a) / n ;
    double somme = (callback(a) + callback(b)) / 2.0 ;
    for(int i = 1; i < n; i++ ){
        somme += callback(a + i * h);
    }
    printf("%f\n", h*somme);
    return h * somme ;
}


int main(){
    /* 20 ( enfin ? ) 
    double n = 10;
    double ret = integrale(fonction, 0.0, 3.0, n);
    printf("%f\n", ret); 
    */

    /* 19 
    int A[] = {2,3,4};
    int B[] = {5,6,7};
    printf("<A|B> = %d\n", dot(A, B, 3));
    */

    /* 18 
    char prompt[] = "     Hello,wwoorld,wrouf,123";
    printf("%d\n", sam_altman(prompt));
    return 0;
    */


    /* 17 
    
    // LISTE *liste=0;
    // liste = maloc(sizeof(LISTE));

    // liste->val = 145;
    // liste->suivant = 0;
    
    LISTE* tab = NULL;

    push_front(&tab, 3);
    push_front(&tab, 2);
    push_front(&tab, 1);
    push_end(&tab, 40);
    push_toelt(&tab, 2, 6);

    LISTE* pt_tab = tab;
    printf("contenu de la liste : ");
    while (pt_tab != NULL) {
        printf("%d -> ", pt_tab->val);
        pt_tab = pt_tab->suivant; 
    }
    printf("trop null\n"); // j'ai 2 ans 

    */
    

    /* 16
    Etudiant e1;

    init(&e1, "toad", 20);
    printf("nom: %s, note: %d\n", e1.nom, e1.note);
    return 0;
    */

    /* 15
    int tab[] = {8, 3, 12, 1, 6};
    trier_qsort(tab, sizeof(tab)/sizeof(tab[0]));
    return 0;
    */

    /* 14
    int tab[] = {1,2,3,4,5};
    int n = sizeof(tab) / sizeof(tab[0]);
    appliquer(tab,n,doubler);
    afficher_tab(tab, n);
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

    /* 10
    int tab[] = {25, 50, 75, 100};
    int *p_min = min_p(tab, 4);

    if (p_min != NULL){
        int indice = p_min - tab;
        printf("minimum : %d\n", *p_min);
        printf("indice : %d\n", indice);
    }
    */

    /* 9
    char chaine[] = "Hello world o/ ! ";
    // je viens de découvrir la fameuse difference entre *chaine et chaine[]  (je hais les docs)
    // *chaine -> pointeur vers une chaine en mode lecture seule
    // chaine[] -> tab de caractere ( la base ) donc modifiable 
    printf("chaine de base : %s\n", chaine);
    retirer_espaces(chaine);
    printf("chaine sans espaces : %s\n", chaine);
    */

    /* 8
    char *s = "hello";
    printf("il y a %d voyelles dans la chaine\n", nb_voyelles(s));
    */

    /* 7
    char *base = "blabla";
    char copie[100]; // Segmentation fault (core dumped) :(
    copier(copie, base);
    printf("copie de la chaine : %s\n", copie);
    */

    /* 6
    char *chaine = "Hello World!";
    printf("il y a %d caract dans la chaine\n", len(chaine));
    */

    /* 5
    int tab[] = {25, 50, 75, 100};
    inverser(tab, 4);
    printf("tableau inversé !\n");
    afficherTab(tab, 4);    
    */

    /* 4 
    int tab[] = {25, 50, 75, 100};
    printf("somme : %d\nmoyenne : %d\n", somme(tab, 4), moyenne(tab, 4));
    */

    /* 3
    int tab[] = {25, 50, 75, 100};
    int min, max ;
    minetmax(tab, 4, &min, &max);
    printf("min : %d\nmax : %d\n", min, max);
    */

    /* 2 
    int a = 1, b=2;
    printf("a : %d\nb : %d\n", a, b);
    swap (&a, &b);
    printf("a : %d\nb : %d\n", a, b);
    */

    /* 1
    test();
    */

}
