#ifndef _Tof_index_H_
#define	_Tof_index_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define b_TOF 1000
long int lire_stat_tof=0;
long int ecrire_stat_tof=0;
typedef struct EnregTOF
{
    long int cle;
    bool efface;
    int bloc;
    int indice_bloc;
}EnregTOF;
typedef struct TblocTOF
{
  EnregTOF T[b_TOF];
  int nbenreg;
}TblocTOF;
typedef struct EnteteTOF
{
    int nb_bloc;
    int nb_enr;
    int nb_eng_sup;
}EnteteTOF;
typedef struct TOF
{
    FILE *fichier;
    EnteteTOF entete_TOF;
}TOF;



TOF *ouvrirTOF(char *nom_physique,char mode)
{

    TOF *fichier=malloc(sizeof(TOF));                      // allocation  de la structure
    if( (mode=='A') ||  (mode == 'a') )                        // mode ancien
    {

        fichier->fichier=fopen(nom_physique,"rb+");               // ouverture du fichier en mode binaire lecture et ecriture
        fread(&(fichier->entete_TOF),sizeof(EnteteTOF),1,fichier->fichier);  // chargement de l'entete enregistrée en debut de fichier
        //printf("\n ouvrire %d ",enteteTOF(fichier,2));system("PAUSE");

    }
    else
    {
        if( (mode=='N') ||  (mode == 'n') )                   // mode nouveau
        {
             fichier->fichier=fopen(nom_physique,"wb+");
             aff_enteteTOF(fichier,1,0);
             aff_enteteTOF(fichier,2,0);
             aff_enteteTOF(fichier,3,0);
             fwrite(&(fichier->entete_TOF),sizeof(EnteteTOF),1,fichier->fichier);
             //alloc_blocTOF(fichier);
        }
        else                                                // format d'ouverture incorrecte
        {
            fprintf(stderr,"format d'ouverture impossible");
        }
    }
    return(fichier);

}
void fermer_TOF(TOF *f)
{
        //printf("\nfermer %d ",enteteTOF(f,2));system("PAUSE");

        rewind(f->fichier);
        fwrite(&(f->entete_TOF),sizeof(EnteteTOF),1,f->fichier);
        fclose(f->fichier);
        free(f);
    }


void liredirTOF(TOF *f,int N_bloc,TblocTOF *buffer)
{
    lire_stat_tof++;
    if(N_bloc<=(f->entete_TOF).nb_bloc)
    {
        fseek(f->fichier,sizeof(EnteteTOF)+(N_bloc-1)*sizeof(TblocTOF),SEEK_SET);
        fread(buffer,1,sizeof(TblocTOF),f->fichier);
    }
}
void ecriredirTOF(TOF*f,int N_bloc,TblocTOF *buffer)
{
    ecrire_stat_tof++;
    if (N_bloc<=(f->entete_TOF).nb_bloc)
    {
         fseek(f->fichier,sizeof(EnteteTOF)+(N_bloc-1)*sizeof(TblocTOF),SEEK_SET);
         fwrite(buffer,1,sizeof(TblocTOF),f->fichier);
    }
}
int enteteTOF(TOF *f,int i)
{
    if(i==1) return (f->entete_TOF).nb_bloc;
    if(i==2) return (f->entete_TOF).nb_enr;
    if(i==3) return (f->entete_TOF).nb_eng_sup;
    else return -1;

}
void aff_enteteTOF(TOF *f,int i,int val)
{
    if(i==1)  (f->entete_TOF).nb_bloc=val;
    if(i==2)  (f->entete_TOF).nb_enr=val;
    if(i==3)  (f->entete_TOF).nb_eng_sup=val;
}
int alloc_blocTOF(TOF *fichier)
{
       TblocTOF *buf=malloc(sizeof(TblocTOF));
        buf->nbenreg=0;
        aff_enteteTOF(fichier,1,enteteTOF(fichier,1)+1);
        ecriredirTOF(fichier,enteteTOF(fichier,1),buf);
     return enteteTOF(fichier,1);
}

//********************************************fonction de recherche**************************************************************//
void recherche_TOF(TOF *fichier,long int cle,int *trouve,int *i, int *j )
{


    int  stop = 0,trouv=0;
    int inf, sup; //--- inf pour reprerenter la borne inferieur dans un bloc et sup la borne superieur ---//
    TblocTOF buff;
    int bi = 1, bs = enteteTOF(fichier, 1); //--- bi et bs representent respectivement le bloc de borne infereur et le bloc de borne superieur ---//
    (*j) = 0;
    while ( (bi <= bs) && (!trouv) && (!stop) )
    {
        (*i) = (bi + bs)/2;
        liredirTOF(fichier, *i, &buff);
        if ( (cle >= buff.T[0].cle) && (cle <= buff.T[buff.nbenreg-1].cle) )
        {
            inf = 0;
            sup = buff.nbenreg-1;
            while ( (inf <= sup) && (!trouv) )
            {
                *j = (inf + sup)/2;
                if ( (cle == buff.T[*j].cle) ) trouv = 1;
                else
                {
                    if ( cle < buff.T[*j].cle ) sup = *j-1;
                    else inf = *j+1;
                }
            }
            if (!trouv) *j = inf;
            stop = 1;
        }
        else
        {
            if ( cle < buff.T[0].cle ) bs = *i-1;
            else bi = *i+1;
        }
    }
    if ( (!trouv) && (!stop)) *i = bi; //--- Cas ou l'information recherchee devrait etre a la tete du fichier ou sa queue ---//

    if ( (*j == 0) && ( *i > 1) && (!trouv) ) //--- Cas d'un enregistrement qui devrait se trouver a la fin d'un bloc au lieu du debut---//
    {
        liredirTOF(fichier, *i-1, &buff);
        if ( buff.nbenreg < b_TOF) //--- Verification du bloc precedent : verifier si il est plein ---//
        {
            *j = buff.nbenreg;
            *i = *i - 1;
        }
    }

    if ((trouv) && ( buff.T[*j].efface == 1)) trouv = 0; //--- La recherche respecte la suppression logique ---//

    (*trouve) = trouv;
}
//--------------------------------------- insertion dans un fichier--------------------------------------------------//
int insertion_TOF(TOF *fichier,EnregTOF eng)
{

  int bloc=1, cell=0, k=0, continu=0,trouve=0;
    TblocTOF buff;
    EnregTOF e, x;
    recherche_TOF(fichier,eng.cle,&trouve, &bloc, &cell);
    if (trouve==0) //--- Recherche eventuelle de l'info dans le fichier ---//
    {
        //printf("%d ",enteteTOF(fichier,2));

        //printf("%d ",enteteTOF(fichier,2));
        continu = 1;
        liredirTOF(fichier, bloc, &buff);
        if (buff.T[cell].cle == eng.cle) //--- Cas ou la donnee en question est supprimee logique ---//
        {
            fichier->entete_TOF.nb_eng_sup = fichier->entete_TOF.nb_eng_sup - 1;

            buff.T[cell].efface = 0;

            ecriredirTOF(fichier,bloc,&buff);
        }else{
            fichier->entete_TOF.nb_enr = fichier->entete_TOF.nb_enr+ 1;
            e = eng;
            while ((continu) && (bloc <= enteteTnOF(fichier, 1)))
            {
                liredirTOF(fichier, bloc, &buff);
                x = buff.T[buff.nbenreg - 1];
                k = buff.nbenreg - 1;
                while (k > cell) //--- Décalage intra-bloc ---//
                {
                    buff.T[k] = buff.T[k-1];
                    k--;
                }
                buff.T[cell] = e; //--- Insertion de la donnee ---//
                if (buff.nbenreg < b_TOF) //--- Le bloc contient l'espace qu'il faut pour la donnee a inserer ---//
                {
                    buff.nbenreg = buff.nbenreg + 1;
                    if (k == cell) buff.T[buff.nbenreg - 1] = x;
                    ecriredirTOF(fichier, bloc, &buff);
                    continu = 0;
                }
                else //--- Decalage inter-bloc ---//
                {
                    ecriredirTOF(fichier, bloc, &buff);
                    bloc++;
                    cell = 0;
                    e = x;
                }
            }
            if (bloc > enteteTOF(fichier, 1) ) //--- Tous les blocs sont pleins necessite d'allocation d'un nouveau bloc ---//
            {
                buff.T[0] = e;
                buff.nbenreg = 1;
                alloc_blocTOF(fichier);
                ecriredirTOF(fichier, bloc, &buff);
            }
        }

        return 1;
    }
    else return 0;
}




//----------------------- focntion de suppression lohgique dans le fichier--------------------------------------------//
int suppression_logique_TOF(TOF *fichier, long int cle)
{
        int bloc, cell,trouve=0;
        recherche_TOF(fichier,cle,&trouve,&bloc,&cell);
    if (trouve==1)
    {

        TblocTOF buff;
        liredirTOF(fichier, bloc, &buff);
        buff.T[cell].efface = 1; //--- Remise du champ effa a 1 ---//
            //(*eng)=buff.T[cell];
        fichier->entete_TOF.nb_eng_sup= fichier->entete_TOF.nb_eng_sup+1;
        ecriredirTOF(fichier, bloc, &buff);
        return 1;
        }
        return 0;
}




#endif
