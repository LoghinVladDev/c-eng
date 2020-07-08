//
// Created by vladl on 08/07/2020.
//
#include <iostream>

/*
 * private = accesibil in clasa curenta si in prieteni
 * protected = accesibil in clasa curenta, prieteni si in mostenitori ( derivate )
 * public = accesibil de oriunde
 */

/**
 * Intr-o clasa derivata, se creeaza o instanta a clasei mostenitoare
 * Prima instr. din ctor ( daca exista ctor implicit in parinte, se apeleaza singur)
 */

/**
 * Clasa abstracta = O clasa care nu poate fi construita. E car. prin partile nedefinite
 * O clasa concreta mosteneste o clasa abstracta.
 */

/**
 * virtual = cuvand aplicat la functii pentru a mentiona ca, in cazul unei suprascrieri,
 * sa se ia functia suprascrietoare. Exista numai o singura functie de acel tip
 *
 * virtual f() = 0; functie pur abstracta. Daca un mostenitor nu o implementeaza,
 * obiectul mostenitor va fi tot abstract.
 *
 * O clasa concreta mostenitoare TREBUIE sa implementeze functiile abstracte primite
 *
 * Un obiect abstract NU POATE FI CONSTRUIT
 *
 * class A : public Common -> class A mostenitorul (clasa concreta/abstracta, clasa derivata)
 *                         -> Common : clasa (concreta/abstracta) din care se mosteneste
 *                         -> public ??? -> ce nivel de acces va avea instanta
 *
 */

/**
 * Cele 5 prop mari si late
 *  - incapsulare  ( r/w var )
 *  - supraincarcare operatori
 *  - mostenirea ( inherit properties / functions )
 *  - abstractizarea ( shape -> rectangle, circle )
 *  - polimorfismu
 */

int main(){

}
