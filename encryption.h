#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>

// mpz_t N, mpz_t phi_n, mpz_t p, mpz_t q, mpz_t m, mpz_t beta, mpz_t g, mpz_t a, mpz_t b, mpz_t theta
void generate_PK(mpz_t N, mpz_t phi_n, mpz_t p, mpz_t q, mpz_t m, mpz_t beta, mpz_t g, mpz_t a, mpz_t b, mpz_t theta);

// ai[] contient les valeurs des bouts de clés 
void generate_SK_share_table_ai(mpz_t ai[], mpz_t beta, mpz_t m, mpz_t N, mpz_t SK, int nb_parts,int size_ai);


// L(u) = (u-1)/N
void L_function(mpz_t lu, mpz_t u, mpz_t N);

// Calcule f_x = f(num_server) = si grâce à ai[] tableau des bouts de clé
void F_shamir(mpz_t f_x, unsigned long int num_server,mpz_t ai[], unsigned long int size_ai, mpz_t N, mpz_t m);

// Multicandidate: generate M = A^j, j:chosen candidate, A=nb_voters+1 > nb_voters
void Generate_vote(mpz_t M, unsigned long int candidate, mpz_t nb_voters);

// Après déchiffrement, décomposer la somme des votes en base A
// Obtenir v0+v1*A+...+ vk−1*A^k−1, où vj est le nombre de votes pour le candidat j, vj=<l<A


// Fonctions de Key Generation


// C contient le chiffré du vote M
void Encryption(mpz_t C, mpz_t M, mpz_t g, mpz_t N);

// ci contient la partial decryption share ci du i^th player
void share_ci(mpz_t ci, mpz_t c, unsigned long int nb_servers, unsigned long int num_server,mpz_t ai[], unsigned long int size_ai, mpz_t si, mpz_t N, mpz_t m);


// Utilisée dans combining_decryption
void mu_0j_S(mpz_t res, mpz_t delta, unsigned long int j, 
mpz_t s[], unsigned long int nb_parts);

// Utilise toutes les partial decryption cj pour retrouver M
// M devra être décomposé en base A pour faire le décompte des votes
// v0+v1*A+...+ vk−1*A^k−1, où vj est le nombre de votes pour le candidat j, vj=<l<A
void combining_decryption(mpz_t M, mpz_t cj[], mpz_t N, mpz_t theta, mpz_t delta, mpz_t s[], unsigned long int nb_parts);
//return n!
unsigned long int factorial(unsigned long int n);
