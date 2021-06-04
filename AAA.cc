#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

using namespace std;

int main(int argc,char **argv){
	float temps;
    clock_t time1, time2;
    time1 = clock();

    gmp_randstate_t state;
	gmp_randinit_default(state);
	srand(time(NULL));
	unsigned long seed = rand()%1999;    
	gmp_randseed_ui(state,seed);
	
	int nb_parts = 10;
	int size_ai = 5;//t
	mpz_t N,p,q,phi_n,m,beta,a,b,g,SK,theta; 
	mpz_t ai[size_ai+1];
	mpz_t ci[nb_parts],si[nb_parts]; 
	
	for(int i = 0; i < nb_parts; ++i){
		mpz_init(ci[i]);
		mpz_init(si[i]);
	}
	generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);
	
	generate_SK_share_table_ai(ai,beta,m,N,SK,nb_parts,size_ai);

	mpz_t f_x;
	mpz_init(f_x);

	mpz_t M,M2,M_prime; 
	mpz_t UN,C_UN,ZERO;
	mpz_t C,C1,C2,C3,C4,C5;
	mpz_inits(M,C,M2,M_prime,NULL);
	mpz_inits(UN,C_UN,ZERO,NULL);
	mpz_inits(C,C1,C2,C3,C4,C5,NULL);
	

	cout<<"Encryption\n";
	//M=0,1
	mpz_set_ui(M,0);
	//mpz_set_ui(M2,5);
	mpz_set_ui(UN,1);
	mpz_set_ui(ZERO,0);
	
	
	Encryption(C,UN,g,N);
	Encryption(C1,ZERO,g,N);
	Encryption(C2,UN,g,N);
	Encryption(C3,ZERO,g,N);
	Encryption(C4,UN,g,N);
	Encryption(C5,ZERO,g,N);
	Encryption(C_UN,UN,g,N);

	
	//Test homomorphisme
	//mpz_mul(C,C,C1);
	//mpz_mul(C,C,C2);
	//mpz_div(C,C,C4);
	//mpz_div(C,C,C4);
	

	//mpz_div(C,C,C_UN);
	//mpz_div(C,C,C_UN);


	//conclusion : possibilité de retirer ou ajouter des chiffrés de 1 pour faire les comptes
	
	gmp_printf ("Value main M: %Zd\n",M);
	gmp_printf ("Value main C: %Zd\n",C);

    //génération des partial decryption cj(share)
    for(int i = 0; i <nb_parts; ++i){
		share_ci(ci[i],C,nb_parts,i,ai,size_ai,si[i],N,m);
		gmp_printf ("Share c%d: %Zd\n",i,ci[i]);
	}
    //delta
	mpz_t delta;
	mpz_init(delta);
	mpz_fac_ui(delta,nb_parts);

	cout<<"Combining decryption\n";
	//déchiffrement
	combining_decryption(M_prime,ci,N,theta,delta,si,nb_parts);
	gmp_printf ("M_prime = %Zd\n",M_prime);

	// Libération de la mémoire
	mpz_clear(N);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi_n);
    mpz_clear(m);
	mpz_clear(beta);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(g);
    mpz_clear(SK);
    mpz_clear(theta);
   	mpz_clear(f_x);
	mpz_clear(delta);
    

    for(int i = 0 ; i < nb_parts; i++){  
	
	
		mpz_clear(ci[i]);
		mpz_clear(si[i]);
    }
	for(int i = 0 ; i <= size_ai; i++){  
	
	
		mpz_clear(ai[i]);
    }
	

    time2 = clock();
    temps = (float)(time2-time1)/CLOCKS_PER_SEC;
    cout<<"Temps d'exécution :"<<temps<<"s"<<endl;
	return 0;
}

// make AAA et ./AAA
// ou make

// https://gmplib.org/#DOWNLOAD
// https://gmplib.org/gmp-man-6.2.1.pdf
