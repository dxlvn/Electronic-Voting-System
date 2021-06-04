#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <gmp.h>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include "encryption.h"

using namespace std;

int main(int argc,char **argv){
	mpz_t N,p,q,phi_n,m,beta,a,b,g,theta,SK; 
    generate_PK(N,phi_n,p,q,m,beta,g,a,b,theta);
    mpz_init(SK);
    mpz_mul(SK,m,beta);
    
    ofstream monFlux("KEYGEN.txt");
    char * str = NULL; //ne reconnait pas les string en c++

    if(monFlux)    
    {
        monFlux << "N "<< mpz_get_str(str,10,N)<<endl;
        monFlux << "phi_n "<< mpz_get_str(str,10,phi_n)<<endl;
        monFlux << "p "<< mpz_get_str(str,10,p)<<endl;
        monFlux << "q "<< mpz_get_str(str,10,q)<<endl;
        monFlux << "m "<< mpz_get_str(str,10,m)<<endl;
        monFlux << "beta "<< mpz_get_str(str,10,beta)<<endl;
        monFlux << "g "<< mpz_get_str(str,10,g)<<endl;
        monFlux << "a "<< mpz_get_str(str,10,a)<<endl;
        monFlux << "b "<< mpz_get_str(str,10,b)<<endl;
        monFlux << "theta "<< mpz_get_str(str,10,theta)<<endl;
        monFlux << "SK "<< mpz_get_str(str,10,SK)<<endl;


    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    monFlux.close();
    
    //Vider les votes dans le cas où l'on regénère les clés
    ofstream monFlux2("Votes.txt");
    if(monFlux2)    
    {}
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }
    monFlux2.close();
    

    delete(str);
    mpz_clear(N);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(phi_n);
    mpz_clear(m);
	mpz_clear(beta);
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(SK);

	return 0;
}
