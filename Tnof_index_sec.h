
#ifndef _Tnof_index_sec_H_
#define	_Tnof_index_sec_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define b_TnOF 1000
long int lire_stat_tnof=0;
long int ecrire_stat_tnof=0;
typedef struct Index_sec_adr
{
    int bloc;
    int indice_bloc;
}Index_sec_adr;
typedef struct EnregTnOF
{
    long int cle;
    int suiv_bloc;
    int suiv_indice_bloc;
}EnregTnOF;
typedef struct TblocTnOF
{
  EnregTnOF T[b_TnOF];
  int nbenreg;
}TblocTnOF;
typedef struct EnteteTnOF
{
    int nb_bloc;
    int nb_enr;
}EnteteTnOF;
typedef struct TnOF
{
    FILE *fichier;
    EnteteTnOF entete_TnOF;
}TnOF;



TnOF *ouvrirTnOF(char *nom_physique,char mode)
{

    TnOF *fichier=malloc(sizeof(TnOF));                      // allocation  de la structure
    if( (mode=='A') ||  (mode == 'a') )                        // mode ancien
    {
        fichier->fichier=fopen(nom_physique,"rb+");               // ouverture du fichier en mode binaire lecture et ecriture
        fread(&(fichier->entete_TnOF),sizeof(EnteteTnOF),1,fichier->fichier);  // chargement de l'entete enregistrée en debut de fichier
    }
    else
    {
        if( (mode=='N') ||  (mode == 'n') )                   // mode nouveau
        {
             fichier->fichier=fopen(nom_physique,"wb+");
             aff_enteteTnOF(fichier,1,0);
             aff_enteteTnOF(fichier,2,0);
             fwrite(&(fichier->entete_TnOF),sizeof(EnteteTnOF),1,fichier->fichier);
             alloc_blocTnOF(fichier);
        }
        else                                                // format d'ouverture incorrecte
        {
            fprintf(stderr,"format d'ouverture impossible");
        }
    }
    return(fichier);

}
void fermerTnOF(TnOF *f)
{
    rewind(f->fichier);
    fwrite(&(f->entete_TnOF),sizeof(EnteteTnOF),1,f->fichier);
    fclose(f->fichier);
    free(f);
}
void liredirTnOF(TnOF *f,int N_bloc,TblocTnOF *buffer)
{
    lire_stat_tnof++;
    if(N_bloc<=(f->entete_TnOF).nb_bloc)
    {
        fseek(f->fichier,sizeof(EnteteTnOF)+(N_bloc-1)*sizeof(TblocTnOF),SEEK_SET);
        fread(buffer,1,sizeof(TblocTnOF),f->fichier);
    }
}
void ecriredirTnOF(TnOF*f,int N_bloc,TblocTnOF *buffer)
{
    ecrire_stat_tnof++;
    if (N_bloc<=(f->entete_TnOF).nb_bloc)
    {
         fseek(f->fichier,sizeof(EnteteTnOF)+(N_bloc-1)*sizeof(TblocTnOF),SEEK_SET);
         fwrite(buffer,1,sizeof(TblocTnOF),f->fichier);
    }
}
int enteteTnOF(TnOF *f,int i)
{
    if(i==1) return (f->entete_TnOF).nb_bloc;
    if(i==2) return (f->entete_TnOF).nb_enr;
    else return -1;

}
void aff_enteteTnOF(TnOF *f,int i,int val)
{
    if(i==1)  (f->entete_TnOF).nb_bloc=val;
    if(i==2)  (f->entete_TnOF).nb_enr=val;
}
int alloc_blocTnOF(TOF *fichier)
{
       TblocTnOF *buf=malloc(sizeof(TblocTnOF));
        buf->nbenreg=0;
        aff_enteteTnOF(fichier,1,enteteTnOF(fichier,1)+1);
        ecriredirTnOF(fichier,enteteTnOF(fichier,1),buf);
     return enteteTnOF(fichier,1);
}
void insert_TnOF(TnOF *F,EnregTnOF eng,int *i,int *j)
{
    int k=enteteTOF(F,1);
    TblocTnOF buffer;
    liredirTnOF(F,k,&buffer);
    if (buffer.nbenreg>=b_TnOF) {
        alloc_blocTnOF(F);
        k=enteteTOF(F,1);
        liredirTnOF(F,k,&buffer);
    }
        (*j)=(buffer.nbenreg)++;
        buffer.T[(*j)]=eng;
        (*i)=k;
    aff_enteteTnOF(F,2,enteteTnOF(F,2)+1);
    ecriredirTnOF(F,k,&buffer);
}





#endif
