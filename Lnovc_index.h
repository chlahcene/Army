#ifndef _Lnovc_index_H_
#define	_Lnovc_index_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "String++.h"
#include "Math++.h"
#include "LnOVC.h"
#include "Tof_index.h"
#include "Tnof_index_sec.h"
//------------------------ affichage du ficher----------------------------------------------------------------//
void Affiche_TOF(TOF *F)
{
    int y=0;

    printf("\n entete nbr bloc %d \t nbr egr %d",enteteTOF(F,1),enteteTOF(F,2));
      TblocTOF buf;
      int i,j=0,nb=enteteTOF(F,1);

      for (i=1;i<=nb;i++){
        liredirTOF(F,i,&buf);
        printf("\n%d",buf.nbenreg);
        for (j=0;j<buf.nbenreg;j++){
            printf("\n%d %d %d: efface %d\t cle %d\t bloc %d \t indice_bloc %d",++y,i,j,buf.T[j].efface,buf.T[j].cle,buf.T[j].bloc,buf.T[j].indice_bloc);
        }
      }
}
void Affiche_Index_Tnof(TnOF *F,Index_sec_adr *tab,int n)
{
      printf("\n entete nbr bloc %d \t nbr egr %d",enteteTnOF(F,1),enteteTnOF(F,2));
      TblocTnOF buf;
      int i,j=0,b=-1,i1,j1;
      for (i=0;i<n;i++){
        printf("\n index '%d'\t",i);
        i1=tab[i].bloc;
        j1=tab[i].indice_bloc;
        if (i1==-1){
            printf("vide");
        }else{
            while(i1!=-1){
                if (b!=i1){
                    b=i1;
                    liredirTnOF(F,b,&buf);
                }
                printf(" %ld",buf.T[j1].cle);
                i1=buf.T[j1].suiv_bloc;
                j1=buf.T[j1].suiv_indice_bloc;
            }
        }
      }
}




void Creation_Index_Primaire(L7OVC *fichier,const char* Nom_fichier)
{

      TOF *F_TOF;
      EnregTOF eng_tof;
      enrg_L7OVC eng_lnovc;
      F_TOF=ouvrirTOF(Nom_fichier,'N');
    int i=entete_L7OVC(fichier,2); // positionnement a la tete du fichier
    int j=0,i1,j1,trouve,k=0;                  // positionnement au premier caractère
    int stop=0;
    Buffer_L7OVC buf;
    TblocTOF buf_tof;
    char *ch=malloc(sizeof(char)*Taille_bloc_L7OVC);
    liredir_L7OVC(fichier,i,&buf);    // lecture du premier bloc

  if(entete_L7OVC(fichier,1)!=0)
  {

    while(!stop)
    {
        i1=i;j1=j;
        recuperer_chaine_enrg(fichier,&i,&j,ch,&buf); // on commence a recuperer les enregistrememnt un a un
        turn_string_to_enrg(&eng_lnovc,ch);
        eng_tof.bloc=i1;
        eng_tof.indice_bloc=j1;
        eng_tof.efface=0;
        eng_tof.cle=eng_lnovc.cle;
        //if (eng_tof.cle<111111) printf("\n index %d",eng_tof.cle);
        insertion_TOF(F_TOF,eng_tof);

        if((i==entete_L7OVC(fichier,3)) && (j==entete_L7OVC(fichier,4))) // si on est la fin du ficher on arrete
        {
            stop=1;
        }
    }
    }
    free(ch);
    fermer_TOF(F_TOF);
    //printf("\n\tAAAA      %d\n",enteteTOF());system("PAUSE");

  }



void genere_enrg(enrg_L7OVC* eng){

    eng->eface=0;
    eng->cle=rand_a_b(111111,999999);
    eng->Info.annee_Naissance=(int)rand_a_b(1940,1999);
    eng->Info.mois_Naissance=(int)rand_a_b(1,12);
    eng->Info.jour_Naissance=(int)rand_a_b(1,maxjour(eng->Info.annee_Naissance,eng->Info.mois_Naissance));
    eng->Info.Force_Armee=(int)rand_a_b(1,8);
    eng->Info.Grade=(int)rand_a_b(1,17);
    eng->Info.Groupe_Sanguin=(int)rand_a_b(1,8);
    eng->Info.Region_Militaire=(int)rand_a_b(1,6);
    eng->Info.Wilaya_Naissance=(int)rand_a_b(1,48);
    int k,i,n=(int)rand_a_b(4,30);
    for (i=0;i<n;i++){
        k=(int)rand_a_b(1,26);
        if (i==0) eng->Info.Nom[i]=(char) 'A'+k-1 ;
        else eng->Info.Nom[i]=(char) 'a'+k-1 ;
    }
    eng->Info.Nom[i]=0;
    n=(int)rand_a_b(4,30);
    for (i=0;i<n;i++){
        k=(int)rand_a_b(1,26);
        if (i==0) eng->Info.Prenom[i]=(char) 'A'+k-1 ;
        else eng->Info.Prenom[i]=(char) 'a'+k-1 ;
    }
    eng->Info.Prenom[i]=0;
}

void Ajoutes_enrg_Aleatoire(L7OVC* Fichier,long int nb){
    srand(time(NULL));
    enrg_L7OVC eng;
    int i,i1,j1;
    for (i=0;i<nb;i++){
        genere_enrg(&eng);
        //if (eng.cle<111111) printf(" %d ",eng.cle);
        insert_Fin_L7OVC(Fichier,eng,&i1,&j1);
    }
}

void Reorganisation(L7OVC *F1,TOF *F2,const char *Nom_Fichier,double u)
{
    char *tmp_chain;
    tmp_chain=malloc((strlen(Nom_Fichier)+30)*sizeof(char));
    TOF *FTOF;EnregTOF eng_tof;TblocTOF buf_tof,buf_tof1;
    TnOF *FY,*FF,*FG,*FR;EnregTnOF eng_tnof;
    L7OVC *F=ouvrir_L7OVC(Nom_Fichier,'N');enrg_L7OVC eng_lnovc;Buffer_L7OVC buf;

        sprintf(tmp_chain,"Data//%s_index_Primaire",Nom_Fichier);
        FTOF=ouvrirTOF(tmp_chain,'N');
        sprintf(tmp_chain,"Data//%s_index_Sec_Year",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'N');
        sprintf(tmp_chain,"Data//%s_index_Sec_Force_Armee",Nom_Fichier);
        FF=ouvrirTnOF(tmp_chain,'N');
        sprintf(tmp_chain,"Data//%s_index_Sec_Region",Nom_Fichier);
        FR=ouvrirTnOF(tmp_chain,'N');
        sprintf(tmp_chain,"Data//%s_index_Sec_Grade",Nom_Fichier);
        FG=ouvrirTnOF(tmp_chain,'N');
        Index_sec_adr tab_Year[60],tab_Force[8],tab_Grade[17],tab_Region[6];


    int i,j=0,i1,j1,i2,j2,k=0,nb;                  // positionnement au premier caractère
    for (i=0;i<60;i++) {
        tab_Year[i].bloc=-1;
        tab_Year[i].indice_bloc=-1;
    }
    for (i=0;i<8;i++) {
        tab_Force[i].bloc=-1;
        tab_Force[i].indice_bloc=-1;
    }
    for (i=0;i<17;i++) {
        tab_Grade[i].bloc=-1;
        tab_Grade[i].indice_bloc=-1;
    }
    for (i=0;i<6;i++) {
        tab_Region[i].bloc=-1;
        tab_Region[i].indice_bloc=-1;
    }
    char *ch=malloc(sizeof(char)*Taille_bloc_L7OVC);
    buf_tof1.nbenreg=0;
    nb=enteteTOF(F2,1);
    //int i3=1,j3=1;

    for (i=1;i<=nb;i++){
        liredirTOF(F2,i,&buf_tof);
        //printf("aaaaaaaaaaaaaaaaaaaaa");system("PAUSE");

        for (j=1;j<=buf_tof.nbenreg;j++){
               // printf("aaaaaaaaaaaaaaaaaaaaa");
            if ((buf_tof.T[j]).efface==0){
                i1=buf_tof.T[j].bloc;
                j1=buf_tof.T[j].indice_bloc;
                liredir_L7OVC(F1,i1,&buf);
                recuperer_chaine_enrg(F1,&i1,&j1,ch,&buf);
                turn_string_to_enrg(&eng_lnovc,ch);
                insert_Fin_L7OVC(F,eng_lnovc,&i1,&j1);
                //printf("\n%d %d --- %d  --- %s",buf_tof.T[j].cle,i1,j1,ch);
                //system("PAUSE");
                buf_tof1.T[buf_tof1.nbenreg]=buf_tof.T[j];
                buf_tof1.T[buf_tof1.nbenreg].bloc=i1;
                buf_tof1.T[buf_tof1.nbenreg].indice_bloc=j1;
                (buf_tof1.nbenreg)++;

                if ((buf_tof1.nbenreg)>(u*b_TOF)){
                    //printf("%d\t",buf_tof1.nbenreg);
                    alloc_blocTOF(FTOF);
                    ecriredirTOF(FTOF,enteteTnOF(FTOF,1),&buf_tof1);
                    buf_tof1.nbenreg=0;
                }
                // index year
                eng_tnof.efface=0;
                eng_tnof.cle=eng_lnovc.cle;

                eng_tnof.suiv_bloc=tab_Year[eng_lnovc.Info.annee_Naissance-1940].bloc;
                eng_tnof.suiv_indice_bloc=tab_Year[eng_lnovc.Info.annee_Naissance-1940].indice_bloc;
                insert_TnOF(FY,eng_tnof,&i2,&j2);
                tab_Year[eng_lnovc.Info.annee_Naissance-1940].bloc=i2;
                tab_Year[eng_lnovc.Info.annee_Naissance-1940].indice_bloc=j2;
                // index Grade
                eng_tnof.suiv_bloc=tab_Grade[eng_lnovc.Info.Grade-1].bloc;
                eng_tnof.suiv_indice_bloc=tab_Grade[eng_lnovc.Info.Grade-1].indice_bloc;
                insert_TnOF(FG,eng_tnof,&i2,&j2);
                tab_Grade[eng_lnovc.Info.Grade-1].bloc=i2;
                tab_Grade[eng_lnovc.Info.Grade-1].indice_bloc=j2;
                // index force
                eng_tnof.suiv_bloc=tab_Force[eng_lnovc.Info.Force_Armee-1].bloc;
                eng_tnof.suiv_indice_bloc=tab_Force[eng_lnovc.Info.Force_Armee-1].indice_bloc;
                insert_TnOF(FF,eng_tnof,&i2,&j2);
                tab_Force[eng_lnovc.Info.Force_Armee-1].bloc=i2;
                tab_Force[eng_lnovc.Info.Force_Armee-1].indice_bloc=j2;
                // index region
                eng_tnof.suiv_bloc=tab_Region[eng_lnovc.Info.Region_Militaire-1].bloc;
                eng_tnof.suiv_indice_bloc=tab_Region[eng_lnovc.Info.Region_Militaire-1].indice_bloc;
                insert_TnOF(FR,eng_tnof,&i2,&j2);
                tab_Region[eng_lnovc.Info.Region_Militaire-1].bloc=i2;
                tab_Region[eng_lnovc.Info.Region_Militaire-1].indice_bloc=j2;
    /*for (i=0;i<60;i++) {
        printf(" (%d,%d) ",tab_Year[i].bloc,tab_Year[i].indice_bloc);

    }
    printf("\n");
    for (i=0;i<8;i++) {
        printf(" (%d,%d) ",tab_Force[i].bloc,tab_Force[i].indice_bloc);
    }
    printf("\n");
    for (i=0;i<17;i++) {
        printf(" (%d,%d) ",tab_Grade[i].bloc,tab_Grade[i].indice_bloc);
    }
    printf("\n");
    for (i=0;i<6;i++) {
        printf(" (%d,%d) ",tab_Region[i].bloc,tab_Region[i].indice_bloc);
    }*/

                //system("PAUSE");
            }
        }
    }

        alloc_blocTOF(FTOF);
        ecriredirTOF(FTOF,enteteTnOF(FTOF,1),&buf_tof1);
        sprintf(tmp_chain,"Data//%s_Table_index_Sec",Nom_Fichier);
        FILE* Table_Index=fopen(tmp_chain,"wb");
        fwrite(tab_Year,sizeof(tab_Year),1,Table_Index);
        fwrite(tab_Force,sizeof(tab_Force),1,Table_Index);
        fwrite(tab_Grade,sizeof(tab_Grade),1,Table_Index);
        fwrite(tab_Region,sizeof(tab_Region),1,Table_Index);
        fclose(Table_Index);
  /*  Affiche_Index_Tnof(FY,tab_Year,60);
    Affiche_Index_Tnof(FG,tab_Grade,17);
    Affiche_Index_Tnof(FF,tab_Force,8);
    Affiche_Index_Tnof(FR,tab_Region,6);*/
    fermer_L7OVC(F);
    fermerTnOF(FY);fermerTnOF(FG);fermerTnOF(FF);fermerTnOF(FR);
    FTOF->entete_TOF.nb_enr=enteteTOF(F2,2);
    fermer_TOF(FTOF);
    free(tmp_chain);
    free(ch);

}

void Creation_fichier_PERSONNEL_L7OVC(const char *Nom_Fichier,long int nb){
    L7OVC *New_File= ouvrir_L7OVC("Data//TMP1",'N');
    Ajoutes_enrg_Aleatoire(New_File,nb);
    Creation_Index_Primaire(New_File,"Data//TMP2");
    //afficher_fichier(New_File);
    TOF *F_TOF=ouvrirTOF("Data//TMP2",'A');
    //printf("sss    %d",enteteTOF(F_TOF,1));system("PAUSE");
    //Affiche_TOF(F_TOF);
    //system("PAUSE");
   // printf("sss    %d",enteteTOF(F_TOF,1));system("PAUSE");
    Reorganisation(New_File,F_TOF,Nom_Fichier,0.5);
    fermer_L7OVC(New_File);
    fermer_TOF(F_TOF);
    remove("Data//TMP1");
    remove("Data//TMP2");

}
int Insert(const char* Nom_Fichier,L7OVC *F,enrg_L7OVC A){

        char *tmp_chain;
        tmp_chain=malloc((strlen(Nom_Fichier)+30)*sizeof(char));
        TOF *FTOF;EnregTOF eng_tof;TblocTOF buf_tof,buf_tof1;
        enrg_L7OVC eng_lnovc;
        sprintf(tmp_chain,"Data//%s_index_Primaire",Nom_Fichier);
        FTOF=ouvrirTOF(tmp_chain,'A');
        int trouve,i,j;
        eng_tof.cle=A.cle;
        eng_tof.efface=0;
        eng_tof.bloc=F->entete.queue;
        eng_tof.indice_bloc=F->entete.indice_libre;
        if (insertion_TOF(FTOF,eng_tof)){
            insertion_L7OVC(F,A);
            insert_sec(Nom_Fichier,A);
            free(tmp_chain);
            fermer_TOF(FTOF);
            return 1;
        }
        fermer_TOF(FTOF);
        free(tmp_chain);
        return 0;
}
void insert_sec(const char* Nom_Fichier,enrg_L7OVC eng_lnovc){
        char *tmp_chain;
        tmp_chain=malloc((strlen(Nom_Fichier)+30)*sizeof(char));
        Index_sec_adr tab_Year[60],tab_Force[8],tab_Grade[17],tab_Region[6];
        sprintf(tmp_chain,"Data//%s_Table_index_Sec",Nom_Fichier);
        FILE* Table_Index=fopen(tmp_chain,"ab+");
        fseek(Table_Index,0,SEEK_SET);
        fread(tab_Year,sizeof(tab_Year),1,Table_Index);
        fread(tab_Force,sizeof(tab_Force),1,Table_Index);
        fread(tab_Grade,sizeof(tab_Grade),1,Table_Index);
        fread(tab_Region,sizeof(tab_Region),1,Table_Index);
        int i2=0,j2=0;
        TnOF *FY,*FF,*FG,*FR;EnregTnOF eng_tnof;
        sprintf(tmp_chain,"Data//%s_index_Sec_Year",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'A');
        // index year
        eng_tnof.cle=eng_lnovc.cle;
        eng_tnof.efface=0;
        eng_tnof.suiv_bloc=tab_Year[eng_lnovc.Info.annee_Naissance-1940].bloc;
        eng_tnof.suiv_indice_bloc=tab_Year[eng_lnovc.Info.annee_Naissance-1940].indice_bloc;
        insert_TnOF(FY,eng_tnof,&i2,&j2);
        tab_Year[eng_lnovc.Info.annee_Naissance-1940].bloc=i2;
        tab_Year[eng_lnovc.Info.annee_Naissance-1940].indice_bloc=j2;
        // index Grade
        sprintf(tmp_chain,"Data//%s_index_Sec_Grade",Nom_Fichier);
        FG=ouvrirTnOF(tmp_chain,'A');
        eng_tnof.suiv_bloc=tab_Grade[eng_lnovc.Info.Grade-1].bloc;
        eng_tnof.suiv_indice_bloc=tab_Grade[eng_lnovc.Info.Grade-1].indice_bloc;
        insert_TnOF(FG,eng_tnof,&i2,&j2);
        tab_Grade[eng_lnovc.Info.Grade-1].bloc=i2;
        tab_Grade[eng_lnovc.Info.Grade-1].indice_bloc=j2;
        // index force
        sprintf(tmp_chain,"Data//%s_index_Sec_Force_Armee",Nom_Fichier);
        FF=ouvrirTnOF(tmp_chain,'A');
        eng_tnof.suiv_bloc=tab_Force[eng_lnovc.Info.Force_Armee-1].bloc;
        eng_tnof.suiv_indice_bloc=tab_Force[eng_lnovc.Info.Force_Armee-1].indice_bloc;
        insert_TnOF(FF,eng_tnof,&i2,&j2);
        tab_Force[eng_lnovc.Info.Force_Armee-1].bloc=i2;
        tab_Force[eng_lnovc.Info.Force_Armee-1].indice_bloc=j2;
        // index Region
        sprintf(tmp_chain,"Data//%s_index_Sec_Region",Nom_Fichier);
        FR=ouvrirTnOF(tmp_chain,'A');
        eng_tnof.suiv_bloc=tab_Region[eng_lnovc.Info.Region_Militaire-1].bloc;
        eng_tnof.suiv_indice_bloc=tab_Region[eng_lnovc.Info.Region_Militaire-1].indice_bloc;
        insert_TnOF(FR,eng_tnof,&i2,&j2);
        tab_Region[eng_lnovc.Info.Region_Militaire-1].bloc=i2;
        tab_Region[eng_lnovc.Info.Region_Militaire-1].indice_bloc=j2;

        fermerTnOF(FY);fermerTnOF(FG);fermerTnOF(FF);fermerTnOF(FR);
        fseek(Table_Index,0,SEEK_SET);
        fwrite(tab_Year,sizeof(tab_Year),1,Table_Index);
        fwrite(tab_Force,sizeof(tab_Force),1,Table_Index);
        fwrite(tab_Grade,sizeof(tab_Grade),1,Table_Index);
        fwrite(tab_Region,sizeof(tab_Region),1,Table_Index);
        fclose(Table_Index);

}
int suppression_logique(const char* Nom_Fichier,L7OVC *F,long int cle){
        char *tmp_chain;
        tmp_chain=malloc((strlen(Nom_Fichier)+100)*sizeof(char));
        TOF *FTOF;EnregTOF eng_tof;TblocTOF buf_tof,buf_tof1;
        Buffer_L7OVC buf;
        enrg_L7OVC eng_lnovc;
        sprintf(tmp_chain,"Data//%s_index_Primaire",Nom_Fichier);
        FTOF=ouvrirTOF(tmp_chain,'A');
        if (suppression_logique_TOF(FTOF,cle)){
            suppression_sec(Nom_Fichier,cle);
            free(tmp_chain);
            fermer_TOF(FTOF);
            return 1;
        }

        /*
        if (enteteTOF(FTOF,3)*2<enteteTOF(FTOF,2)){

            Reorganisation(F,FTOF,"inter",0.5);

        }*/
        fermer_TOF(FTOF);
        free(tmp_chain);
        return 0;
}
void suppression_sec(const char* Nom_Fichier,long int cle){
        char *tmp_chain;
        tmp_chain=malloc((strlen(Nom_Fichier)+30)*sizeof(char));
        TnOF *F;
        sprintf(tmp_chain,"Data//%s_index_Sec_Year",Nom_Fichier);
        F=ouvrirTOF(tmp_chain,'A');
        supp_logique_TnOF(F,cle);
        fermerTnOF(F);
        sprintf(tmp_chain,"Data//%s_index_Sec_Force_Armee",Nom_Fichier);
        F=ouvrirTOF(tmp_chain,'A');
        supp_logique_TnOF(F,cle);
        fermerTnOF(F);
        sprintf(tmp_chain,"Data//%s_index_Sec_Grade",Nom_Fichier);
        F=ouvrirTOF(tmp_chain,'A');
        supp_logique_TnOF(F,cle);
        sprintf(tmp_chain,"Data//%s_index_Sec_Region",Nom_Fichier);
        F=ouvrirTOF(tmp_chain,'A');
        supp_logique_TnOF(F,cle);
        fermerTnOF(F);
        free(tmp_chain);
}






#endif
