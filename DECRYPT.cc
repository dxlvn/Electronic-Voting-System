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

//Retourne le nombre de lignes du fichier
int Nb_Lignes_Fichier_Votes()
{
    int nbLignes = 0;
    ifstream in("Votes.txt" , ios::in);
    string ligne;
    while(getline(in, ligne)){
        nbLignes++;
    }
    in.close(); 
    return nbLignes;
}

int main(){
    mpz_t N,p,q,phi_n,m,beta,a,b,g,theta,SK; 
    mpz_inits(N,p,q,phi_n,m,beta,a,b,g,theta,SK,NULL);    // parametre null a ajouter 
    
    //RECUPERER LES CLES POUR LES OPERAIONS
    ifstream monFlux("KEYGEN.txt");  //Ouverture d'un fichier en lecture
        if(monFlux)
        {
            string mot;
            while(monFlux.eof() == false){    
                monFlux >> mot;
                if(mot == "N"){ 
                    monFlux >> mot;
                    mpz_set_str(N,mot.c_str(),10);
                }
                if(mot == "p"){ 
                    monFlux >> mot;
                    mpz_set_str(p,mot.c_str(),10);
                }
                if(mot == "q")
                { 
                    monFlux >> mot;
                    mpz_set_str(q,mot.c_str(),10);
                }
                if(mot == "phi_n"){ 
                    monFlux >> mot;
                    mpz_set_str(phi_n,mot.c_str(),10);
                }
                if(mot == "m"){ 
                    monFlux >> mot;
                    mpz_set_str(m,mot.c_str(),10);
                }
                if(mot == "beta"){ 
                    monFlux >> mot;
                    mpz_set_str(beta,mot.c_str(),10);
                }
                if(mot == "a"){ 
                    monFlux >> mot;
                    mpz_set_str(a,mot.c_str(),10);
                }
                if(mot == "b"){ 
                    monFlux >> mot;
                    mpz_set_str(b,mot.c_str(),10);
                }
                if(mot == "g"){ 
                    monFlux >> mot;
                    mpz_set_str(g,mot.c_str(),10);
                }
                if(mot == "theta"){ 
                    monFlux >> mot;
                    mpz_set_str(theta,mot.c_str(),10);
                }
                if(mot == "SK"){ 
                    monFlux >> mot;
                    mpz_set_str(SK,mot.c_str(),10);
                }
            }     
        }
        else{
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }
        monFlux.close();

    int nbLignes = Nb_Lignes_Fichier_Votes();
    mpz_t votes[nbLignes];
    
    //RECUPERER TUPLE VIA LA DB EN SQL
    ifstream monFlux2("Votes.txt");  //Ouverture d'un fichier en lecture

        if(monFlux2){
            string mot;
            int i = 0;
            while(monFlux2.eof() == false){
                monFlux2 >> mot;
                mpz_init_set_str(votes[i],mot.c_str(),10);
                i++;   
            }
        }
        else{
            cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        }

        monFlux2.close();
        

    //GENERATION DES VALEURS POUR LE DECHIFFREMENT
    int nb_parts = 4; 
    int size_ai = 2;//t A revoir pour ce nombre
	mpz_t ai[size_ai+1];
	mpz_t ci[nb_parts],si[nb_parts]; 
    mpz_t delta;
    mpz_init(delta);
    mpz_fac_ui(delta,nb_parts);

    for(int i = 0; i < nb_parts; ++i){
		mpz_init(ci[i]);
		mpz_init(si[i]);
	}

	generate_SK_share_table_ai(ai,beta,m,N,SK,nb_parts,size_ai);

    mpz_t resultat,C_tmp;
    mpz_init(C_tmp);
    
    //COMPTER LES VOTES
    int count = 0;

    for(int cmp = 0 ; cmp < nbLignes ; cmp ++){  
        mpz_init(resultat);
        mpz_init_set(C_tmp,votes[cmp]);

        for(int i = 0; i < nb_parts; ++i){
            share_ci(ci[i],C_tmp,nb_parts,i,ai,size_ai,si[i],N,m);
        }
        
        combining_decryption(resultat,ci,N,theta,delta,si,nb_parts);
        
        if(mpz_cmp_ui(resultat,0) != 0) count++;
        mpz_clear(resultat);
        
    }
    cout<<"Le candidat 0 a obtenu "<<(nbLignes - count)<<"votes"<<endl; 
    cout<<"Le candidat 1 a obtenu "<<count<<"votes"<<endl;

    //Libération de la mémoire
    mpz_clears(N,p,q,phi_n,m,beta,a,b,g,theta,SK,delta,NULL);
    
   
    for(int i = 0 ; i < nbLignes ; i++){
        mpz_clear(votes[i]);
    }
    
    for(int i = 0 ; i < nb_parts; i++){ 
		mpz_clear(ci[i]);
		mpz_clear(si[i]);
    }

	for(int i = 0 ; i <= size_ai; i++){  
		mpz_clear(ai[i]);
    }

    cout<<"lignes : "<<nbLignes<<endl;
	return 0;
}

