#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

// EXERCICE 1 

typedef struct {
    double x;
    double y;
} Point;

double dist0(const Point* a) {
    return sqrt(pow(a->x, 2) + pow(a->y, 2));
}


// EXERCICE 2 
// on ré-utilise la même structure 

void translater(Point *p, int dx, int dy){
    p->x = p->x + dx;
    p->y = p->y + dy;
}


// EXERCICE 3 

typedef struct {
    double L;
    double l;
} Rect;


double air(Rect r){
    return r.L * r.l ;
}


double peri(Rect r){
    return 2.0 * (r.l + r.L );
}


// EXEERCICE 4 (C QUOI CA)
typedef struct {
    double re;
    double im; 
} Cx; 


Cx add(Cx a, Cx b){
    Cx res = {0.0, 0.0};
    res.re = a.re + b.re ;
    res.im = a.im + b.im ;
    return res ;
}


double mod(Cx a){
    return sqrt(pow(a.re, 2) + pow(a.im, 2));
}


// EXERCICE 5
int pgcd(int a, int b){
    a = abs(a);
    b = abs(b);
    int r;
    while (b){
        r = a%b;
        a = b;
        b=r;
    }
    return a ;
}


typedef struct{
    int num;
    int den;
} Frac;


Frac normalize(Frac f){
    assert(f.den != 0 );
    if(f.den < 0){
        f.den = -f.den;
        f.num = -f.num;
    }
    int g = pgcd(f.num, f.den);
    f.num /= g;
    f.den /= g; 
    return f;
}


Frac addf(Frac a, Frac b){
    Frac res = {0.0, 0.0};
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    return(normalize(res));
}


// EXERCICE 6 

typedef struct{
    char nom[32];
    double note; 
} Etu;


void init(Etu* e, char* nom, double note){
    strcpy(e->nom, nom);
    e->note = note;
}


void affiche(Etu e){
    printf("Nom : %s | Note : %f\n", e.nom, e.note);
}


// EXERCICE 7 
Etu* best(Etu* e, int n){
    assert(n>0 && e!=NULL);
    Etu* max = e;
    for(int i = 1; i<n; i++){
        if(e[i].note > max->note);
            max = e + i ;
    }
    return max;
}


// EXERCICE 8 
void bubble_sort(Etu* e, int n ){
    // toujours les pires logs du monde c'est déplorable
    if(n>1){
        Etu temp;
        for(int i = 0; i<n-1; i++){
            printf("-1");
            for(int j = 0; j<n-1-i; j++){
                printf("-0");
                if(e[j].note > e[j+1].note){
                    printf("-1\n");
                    temp = e[j];
                    e[j] = e[j+1];
                    e[j+1] = temp;
                }
            }
        }
    }
    printf("\n");
}


// EXERCICE 9 
typedef struct{
    int h; 
    int m; 
    int s;
} Time;


Time norm(Time t){
    // secondes 
    int res_s = t.s / 60;
    t.s %= 60;
    
    // minutes 
    t.m += res_s;
    int res_m = t.m / 60;
    t.m %= 60;

    // heures
    t.h += res_m;
    return t;
}


Time addsec(Time t, int sec){
    t.s += sec;
    t = norm(t);
    return t;
}


// EXERCISE 10 
typedef struct {
    int j ;
    int m ;
    int y;
} Date;


bool isLeap(Date date){
    return ((date.y % 4 == 0) || (date.y % 100 == 0 && date.y % 400 == 0));
}


int dayOfYear(Date date){
    int s = 0; 
    int tab[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(isLeap(date) && date.m > 2){
        s++ ;
    }
    for(int i = 0; i<date.m - 1 ; i++){
        s+=tab[i];
    }
    return s + date.j;
}


// EXERCICE 11 
typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;


int toGray(RGB rgb){
    return 0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b ;
}


// EXERCISE 12 
typedef struct {
    double a;
    double b;
    double c;
} Poly2;


double eval(Poly2 p, double x){
    return (p.a * x + p.b) * x + p.c ;
}


// EXERCICE 13
typedef struct{
    Point c;
    double r;
} Cercle ;


double aire(Cercle k){
    return M_PI * k.r * k.r;
}


bool contient(Cercle k, Point p){
    return pow((p.x - k.c.x), 2 ) + pow((p.y - k.c.y), 2) <= pow(k.r, 2);
}


// EXERCICE 14 
typedef struct{
    double a11;
    double a12;
    double a21;
    double a22;
} Mat2;


Point mul(Mat2 m, Point p){
    Point ret;
    ret.x = m.a11 * p.x + m.a12 * p.y ;
    ret.y = m.a21 * p.x + m.a22 * p.y ;
    return ret;
}


// EXERCICE 15 

typedef struct{
    char titre[64];
    char auteur [48];
    int an;
} Livre;


Livre findByAuthor(Livre* tab, char auteur){
    bool found = false;
    Livre* cur = tab;
    while(!found && cur!=NULL){
        if(cur->auteur == auteur){
            found = true ;
            return *cur;
        }
        cur++;
    }
    return NULL;
}


int main(){
    /* 15 */
    Livre l = {"bleu", "toad", 1900};
    Livre l2 = {"rouge", "mario", 1900};
    Livre l3 = {"vert", "luigi", 1900};

    Livre tab[] = {l, l2, l3};
    /* 14 
    Mat2 m = {1, 0, 0, 1};
    Point p = {3.0, 4.0};
    Point ret = mul(m, p);
    printf("x : %f | y : %f\n", ret.x, ret.y); 
    */

    /* 13 
    Cercle k = {{2.0, 3.0}, 5.0};
    Point p = {6.0, 7.0};
    printf("%f\n", aire(k));
    printf("%d\n", contient(k, p));
    */

    /* 12 
    Poly2 p = {2.0, -3.0, 5.0};
    double x = 0.5 ;
    printf("%f\n", eval(p, x));
    */

    /* 11 
    RGB c = {0,0,0};
    printf("%d\n", toGray(c));

    RGB c2 = {255, 255, 255};
    printf("%d\n", toGray(c2));

    RGB c3 = {0, 200, 0};
    printf("%d\n", toGray(c3));
    */
    
    /* 10 
    Date date = {0,0,2026};
    printf("%d\n", isLeap(date));
    Date date2 = {31, 12, 2024};
    printf("%d\n", dayOfYear(date2));
    */

    /*
    int tab[5][3];
    // tab[0] = {"o", "x", "x"}; tab[0][1]
    // tab[1] = {"x", "o", "x"};
    // tab[2] = {"o", "x", "o"};
    // tab[3] = {"o", "x", "o"};
    // tab[4] = {"o", "x", "o"}; tab[4][0]

    int elt;
    for(int i; i<5; i++){
        for(int j = 0 ;j < 3 ; j++){
            scanf("%d", &elt);
            tab[i][j] = elt;
        }
    }
    */


    /* 9 
    Time t= {1, 20, 95};
    t = norm(t);
    printf("%d:%d:%d\n", t.h, t.m, t.s);
    Time t2 = {10, 45, 30};
    t2 = addsec(t2, 5000);
    printf("%d:%d:%d\n", t2.h, t2.m, t2.s);
    */


    /* 8 
    // hardcode, again, dont do this at home
    Etu tab[100];
    Etu a;
    Etu b; 
    Etu c;
    Etu d;
    Etu e;
    Etu f;
    init(&a, "red toad", 18.0);
    init(&b, "blue toad", 7.0);
    init(&c, "yellow toad", 16.0);
    init(&d, "green toad", 5.0);
    init(&e, "purple toad", 13.0);
    init(&f, "pink toad", 12.0);
    tab[0] = a;
    tab[1] = b;
    tab[2] = c;
    tab[3] = d;
    tab[4] = e;
    tab[5] = f;
    bubble_sort(tab, 6);
    for(int i = 0; i < 6 ; i++){
        affiche(tab[i]);
    } 
    */

    /* 7 
    // hardcode, dont do this at home
    Etu tab[100];
    Etu a;
    Etu b; 
    Etu c;
    init(&a, "noob", 1.0);
    init(&b, "pro", 10.0);
    init(&c, "hacker", 20.0);
    tab[0] = a;
    tab[1] = b;
    tab[2] = c;
    Etu* top = best(tab, 3);
    if(top != NULL ){
        printf("Nom : %s | Note : %f", top->nom, top->note);
    }
    */

    /* 6 
    Etu e;
    init(&e, "toad", 12.0);
    affiche(e);
    */

    /* 5 
    printf("pgcd ; %d\n", pgcd(-15, 25));
    Frac a = {12.0, 18.0};
    Frac b = normalize(a);
    printf("normalised form of %d / %d : %d / %d\n", a.num, a.den, b.num, b.den);
    Frac c = {1.0, 4.0};
    Frac d = {1.0, 4.0};
    Frac e = addf(c,d);
    printf("result : %d / %d", e.num, e.den);
    */

    /* 4 
    Cx a = {2.0, 3.0};
    Cx b = {4.0, -5.0};
    printf("add : %f\n", add(a,b));
    */

    /* 3 
    Rect r = {5.0, 3.0};
    printf("aire : %f ; perimetre : %f\n", air(r), peri(r));
    */

    /* 2 
    Point a = {2.0, 3.0};
    translater(&a, 4.0, 5.0);
    printf("%f, %f\n", a.x, a.y);
    */
    
    /* 1
    Point a = {2.0, 3.0};
    printf("%f\n", dist0(&a));
    */

    return 0;
}
