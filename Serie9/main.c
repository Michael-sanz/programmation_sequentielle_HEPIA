#include <stdio.h>
#include <malloc.h>

struct Fraction_s{
    int num;
    int den;
};

typedef struct Fraction_s Fraction;

int PGCD(int nbr1, int nbr2)
{
    if (nbr2 != 0)
        return PGCD(nbr2, nbr1%nbr2);
    else
        return nbr1;
}

Fraction reduce(Fraction f1){
    int pgcd;
    Fraction res;
    pgcd = PGCD(f1.num, f1.den);
    res.num = f1.num / pgcd;
    res.den = f1.den / pgcd;
    return res;
}


Fraction lire(){
    int denominateur, numerateur;
    Fraction f_res;
    printf("\nEntrer la valeur du numerateur\n");
    scanf("%d", &numerateur);
    printf("\nEntrer la valeur du dénominateur\n");
    scanf("%d",&denominateur);
    f_res.num = numerateur;
    f_res.den = denominateur;
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
struct Monomes_S{
    int deg;
    Fraction frac;
};

typedef struct Monomes_S Monomes;

Monomes * lire_poly(){
    int nbMonomes;
    Monomes *polynomes;

    printf("Donner le nombre total de coefficients : ");
    scanf("%d", &nbMonomes);

    polynomes = (Monomes *) malloc(sizeof (Monomes)*nbMonomes);

    return polynomes;
}

int main() {
    printf("Hello, World!\n");
    return 0;
}

