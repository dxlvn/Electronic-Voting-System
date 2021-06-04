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

int Nb_Lignes_Fichier_Votes_clairs(){
    int nbLignes = 0;
    ifstream in("votes_clairs.txt" , ios::in);
    string ligne;
    while(getline(in, ligne))
    {
        nbLignes++;
    }
    in.close();

    return nbLignes;
}

int main(int argc,char **argv){
	mpz_t message_clair, g, N;
	mpz_inits( g, N,NULL);
	ifstream monFlux("KEYGEN.txt");  /
        if(monFlux){
            string mot;
            while(monFlux.eof() == false){
                monFlux >> mot;
                if(mot == "N"){ 
                    monFlux >> mot;
                    mpz_set_str(N,mot.c_str(),10);
                }            
                if(mot == "g"){ 
                    monFlux >> mot;
                    mpz_set_str(g,mot.c_str(),10);
                }
            }
        }
        else{
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }
        monFlux.close();
	
    int Nb_lignes = Nb_Lignes_Fichier_Votes_clairs();
    mpz_t chiffré[Nb_lignes];
    cout<<Nb_lignes<<endl;
    mpz_init(message_clair);
    ifstream monFlux2("votes_clairs.txt");  //Ouverture d'un fichier en lecture
        if(monFlux2){
            int i = 0;
            string mot;
            while(monFlux2.eof() == false){
                mpz_init(chiffré[i]);
                monFlux2 >> mot;
                mpz_set_str(message_clair,mot.c_str(),10);
                Encryption(chiffré[i],message_clair,g,N);
                i++;
            }
           cout<<"i = "<<i<<endl;
        }
        else{
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }

        monFlux2.close();
        ofstream monFlux3("Votes.txt");  

        if(monFlux3)
        {
            char * str = NULL; 
            for(int i = 0 ; i < Nb_lignes; i++){
                monFlux3<< mpz_get_str(str,10,chiffré[i])<<endl;
            }
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }

        monFlux3.close();
	

	mpz_clears(g,N,NULL);
    for(int j = 0 ; j < Nb_lignes ; j++){
        mpz_clear(chiffré[j]);
    }
    cout<<Nb_lignes<<endl;
	return 0;
}

