#include <stdio.h>
#include <malloc.h>

struct Fraction_s{
    int num;
    int den;
};

typedef struct Fraction_s Fraction;

int PGCD(int a, int b){
    while(b!=0){
        int c=a%b;
        a=b;
        b=c;
    }
    return a;
}

Fraction reduce(Fraction f1){
    int pgcd;
    Fraction res;
    pgcd = PGCD(f1.num, f1.den);
    res.num = f1.num / pgcd;
    res.den = f1.den / pgcd;
    if(res.den <0){
        res.num = - res.num;
        res.den = - res.den;
    }
    return res;
}

Fraction lire(){
    int denominateur, numerateur;
    Fraction f_res;
    printf("\nEntrer la valeur du numerateur\n");
    scanf("%d", &numerateur);
    printf("\nEntrer la valeur du denominateur\n");
    scanf("%d",&denominateur);
    f_res.num = numerateur;
    f_res.den = denominateur;
    return f_res;
}

Fraction add(Fraction f1, Fraction f2){
    Fraction fraction_result;
    fraction_result.num = f1.den * f2.num + f2.den * f1.num;
    fraction_result.den = f1.den * f2.den;
    fraction_result = reduce(fraction_result);
    return fraction_result;
}

Fraction soustract(Fraction f1, Fraction f2){
    Fraction f_res;
    f_res.num = f1.den * f2.num - f2.num * f1.den;
//    f_res.num = f1.num - f2.num;
    f_res.den = f1.den * f2.den;
    f_res = reduce(f_res);
    return f_res;
}

Fraction mult1(Fraction f1, Fraction f2){
    Fraction f_res;
    f_res.num = f1.num * f2.num;
    f_res.den = f2.den * f2.den;
    f_res = reduce(f_res);
    return f_res;
}

Fraction mult2(Fraction f1, int entier){
    Fraction f_res;
    f_res.num = f1.num * entier;
    f_res.den = f1.den * 1;
    f_res = reduce(f_res);
    return f_res;
}

Fraction mult3(int entier, Fraction f1){
    return mult2(f1,entier);
}

Fraction div(Fraction f1, Fraction f2){
    Fraction f_res;
    f_res.num = f1.num * f2.den;
    f_res.den = f1.den * f2.num;
    f_res = reduce(f_res);
    return f_res;
}

Fraction div2(Fraction f1, int entier){
    Fraction f_res;
    f_res.num = f1.num * 1;
    f_res.den = f1.den * entier;
    f_res = reduce(f_res);
    return f_res;
}

Fraction div3( int entier, Fraction f1){
    Fraction f_res;
    f_res.num = f1.num * entier;
    f_res.den = f1.den * 1;
    f_res = reduce(f_res);
    return f_res;
}

struct Monomes_S{
    int deg;
    Fraction frac;
};

typedef struct Monomes_S Monomes;

Monomes * lire_poly(){
    int nbMonomes,i;
    Fraction f1;
    Monomes *polynomes; // tableau de monomes => Polynome
    printf("Donner le nombre total de coefficients : ");
    scanf("%d", &nbMonomes);
    polynomes = (Monomes *) malloc(sizeof (Monomes)*nbMonomes);
    for (i = 0; i < nbMonomes ; ++i) {
        polynomes->deg = i;
        printf("Donner la valeur du coef sous forme de fractions : ");
        f1 = lire();
        polynomes->frac = f1;
    }
    return polynomes;
}

void ecrire_poly( Monomes *polynomes){
    int i;
    for (i = 0; i <3; ++i) {
        printf("[%d], [%d], [%d]\n", polynomes[i].deg,  polynomes[i].frac.num, polynomes[i].frac.den);
    }
}


//
//void mis_a_zero(int * pa ){
//    *pa = 0;
//}
//
//void ajoute1(int *pn){
//    *pn = *pn +1;
//}
//
//void ajoute2(int *pm){
//    ajoute1(pm);
//    ajoute1(pm);
//}
//
//void echange(int * pa, int * pb){
//    int tmp;
//    tmp = *pa;
//    *pa = *pb;
//    *pb = tmp;
//}
//
//int ajoute1_aux_elements(int * tab, int nb_elements){
//    int i;
//
//    for(i=0;i<nb_elements;i++){
//
//        ajoute1(&tab[i]);
//        printf("%d\n", tab[i]);
//    }
//}

int main() {
    ecrire_poly(lire_poly());
    return 0;
}

