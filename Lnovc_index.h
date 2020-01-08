#ifndef _Lnovc_index_H_
#define _Lnovc_index_H_
#include "LnOVC.h"
#include "Math++.h"
#include "String++.h"
#include "Tnof_index_sec.h"
#include "Tof_index.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//------------------------ affichage du
//ficher----------------------------------------------------------------//
void Affiche_TOF(TOF *F) {
  int y = 0;
  printf("\n entete nbr bloc %d \t nbr egr %d", enteteTOF(F, 1),
         enteteTOF(F, 2));
  TblocTOF buf;
  int i, j = 0, nb = enteteTOF(F, 1);
  for (i = 1; i <= nb; i++) {
    liredirTOF(F, i, &buf);
    for (j = 0; j < buf.nbenreg; j++) {
      printf("\n%d : efface %d\t cle %d\t bloc %d \t indice_bloc %d", ++y,
             buf.T[j].efface, buf.T[j].cle, buf.T[j].bloc,
             buf.T[j].indice_bloc);
    }
  }
}
void Affiche_Index_Tnof(TnOF *F, Index_sec_adr *tab, int n) {
  printf("\n entete nbr bloc %d \t nbr egr %d", enteteTnOF(F, 1),
         enteteTnOF(F, 2));
  TblocTnOF buf;
  int i, j = 0, b = -1, i1, j1;
  for (i = 0; i < n; i++) {
    printf("\n index '%d'\t", i);
    i1 = tab[i].bloc;
    j1 = tab[i].indice_bloc;
    if (i1 == -1) {
      printf("vide");
    } else {
      while (i1 != -1) {
        if (b != i1) {
          b = i1;
          liredirTnOF(F, b, &buf);
        }
        printf(" %ld", buf.T[j1].cle);
        i1 = buf.T[j1].suiv_bloc;
        j1 = buf.T[j1].suiv_indice_bloc;
      }
    }
  }
}

void Creation_Index_Primaire(L7OVC *fichier, const char *Nom_fichier) {

  TOF *F_TOF;
  EnregTOF eng_tof;
  enrg_L7OVC eng_lnovc;
  F_TOF = ouvrirTOF(Nom_fichier, 'N');
  int i = entete_L7OVC(fichier, 2); // positionnement a la tete du fichier
  int j = 0, i1, j1, trouve, k = 0; // positionnement au premier caract�re
  int stop = 0;
  Buffer_L7OVC buf;
  TblocTOF buf_tof;
  char *ch = malloc(sizeof(char) * Taille_bloc_L7OVC);
  liredir_L7OVC(fichier, i, &buf); // lecture du premier bloc

  if (entete_L7OVC(fichier, 1) != 0) {

    while (!stop) {

      recuperer_chaine_enrg(
          fichier, &i, &j, ch,
          &buf); // on commence a recuperer les enregistrememnt un a un
      turn_string_to_enrg(&eng_lnovc, ch);
      eng_tof.bloc = i;
      eng_tof.indice_bloc = j;
      eng_tof.efface = 0;
      eng_tof.cle = eng_lnovc.cle;
      insertion_TOF(F_TOF, eng_tof);

      if ((i == entete_L7OVC(fichier, 3)) &&
          (j ==
           entete_L7OVC(fichier, 4))) // si on est la fin du ficher on arrete
      {
        stop = 1;
      }
    }
  }
  free(ch);
  fermer_TOF(F_TOF);
  // printf("\n\tAAAA      %d\n",enteteTOF());system("PAUSE");
}

void genere_enrg(enrg_L7OVC *eng) {

  eng->eface = 0;
  eng->cle = rand_a_b(111111, 999999);
  eng->Info.annee_Naissance = (int)rand_a_b(1940, 1999);
  eng->Info.mois_Naissance = (int)rand_a_b(1, 12);
  eng->Info.jour_Naissance = (int)rand_a_b(
      1, maxjour(eng->Info.annee_Naissance, eng->Info.mois_Naissance));
  eng->Info.Force_Armee = (int)rand_a_b(1, 8);
  eng->Info.Grade = (int)rand_a_b(1, 17);
  eng->Info.Groupe_Sanguin = (int)rand_a_b(1, 8);
  eng->Info.Region_Militaire = (int)rand_a_b(1, 6);
  eng->Info.Wilaya_Naissance = (int)rand_a_b(1, 48);
  int k, i, n = (int)rand_a_b(4, 30);
  for (i = 0; i < n; i++) {
    k = (int)rand_a_b(1, 26);
    eng->Info.Nom[i] = (char)'A' + k - 1;
  }
  eng->Info.Nom[i] = 0;
  n = (int)rand_a_b(4, 30);
  for (i = 0; i < n; i++) {
    k = (int)rand_a_b(1, 26);
    eng->Info.Prenom[i] = (char)'A' + k - 1;
  }
  eng->Info.Prenom[i] = 0;
}

void Ajoutes_enrg_Aleatoire(L7OVC *Fichier, long int nb) {
  srand(time(NULL));
  enrg_L7OVC eng;
  int i, i1, j1;
  for (i = 0; i < nb; i++) {
    genere_enrg(&eng);
    insert_Fin_L7OVC(Fichier, eng, &i1, &j1);
  }
}

void Reorganisation(L7OVC *F1, TOF *F2, char *Nom_Fichier, double u) {
  char *tmp_chain;
  tmp_chain = malloc((strlen(Nom_Fichier) + 30) * sizeof(char));
  TOF *FTOF;
  EnregTOF eng_tof;
  TblocTOF buf_tof, buf_tof1;
  TnOF *FY, *FF, *FG;
  EnregTnOF eng_tnof;
  L7OVC *F = ouvrir_L7OVC(Nom_Fichier, 'N');
  enrg_L7OVC eng_lnovc;
  Buffer_L7OVC buf;

  sprintf(tmp_chain, "%s_index_Primaire", Nom_Fichier);
  FTOF = ouvrirTOF(tmp_chain, 'N');
  sprintf(tmp_chain, "%s_index_Sec_Year", Nom_Fichier);
  FY = ouvrirTnOF(tmp_chain, 'N');
  sprintf(tmp_chain, "%s_index_Sec_Force_Armee", Nom_Fichier);
  FF = ouvrirTnOF(tmp_chain, 'N');
  sprintf(tmp_chain, "%s_index_Sec_Grade", Nom_Fichier);
  FG = ouvrirTnOF(tmp_chain, 'N');
  Index_sec_adr tab_Year[60], tab_Force[8], tab_Grade[17];

  int i, j = 0, i1, j1, i2, j2, k = 0,
         nb; // positionnement au premier caract�re
  for (i = 0; i < 60; i++) {
    tab_Year[i].bloc = -1;
    tab_Year[i].indice_bloc = -1;
  }
  for (i = 0; i < 8; i++) {
    tab_Force[i].bloc = -1;
    tab_Force[i].indice_bloc = -1;
  }
  for (i = 0; i < 17; i++) {
    tab_Grade[i].bloc = -1;
    tab_Grade[i].indice_bloc = -1;
  }
  char *ch = malloc(sizeof(char) * Taille_bloc_L7OVC);
  buf_tof1.nbenreg = 0;
  nb = enteteTOF(F2, 1);
  // printf("aaaaa    %d",nb);system("PAUSE");
  for (i = 1; i <= nb; i++) {
    liredirTOF(F2, i, &buf_tof);
    // printf("aaaaaaaaaaaaaaaaaaaaa");system("PAUSE");
    for (j = 1; j <= buf_tof.nbenreg; j++) {
      // printf("aaaaaaaaaaaaaaaaaaaaa");
      if ((buf_tof.T[j]).efface == 0) {
        i1 = buf_tof.T[j].bloc;
        j1 = buf_tof.T[j].indice_bloc;
        liredir_L7OVC(F1, i1, &buf);
        recuperer_chaine_enrg(F1, &i1, &j1, ch, &buf);
        turn_string_to_enrg(&eng_lnovc, ch);
        insert_Fin_L7OVC(F, eng_lnovc, &i1, &j1);
        buf_tof1.T[buf_tof1.nbenreg] = buf_tof.T[j];
        buf_tof1.T[buf_tof1.nbenreg].bloc = i1;
        buf_tof1.T[buf_tof1.nbenreg].indice_bloc = j1;
        if ((buf_tof1.nbenreg) >= (u * b_TOF)) {
          alloc_blocTOF(FTOF);
          ecriredirTOF(FTOF, enteteTnOF(FTOF, 1), &buf_tof1);
          buf_tof1.nbenreg = 0;
        }
        // index year
        eng_tnof.cle = eng_lnovc.cle;
        eng_tnof.suiv_bloc =
            tab_Year[eng_lnovc.Info.annee_Naissance - 1940].bloc;
        eng_tnof.suiv_indice_bloc =
            tab_Year[eng_lnovc.Info.annee_Naissance - 1940].indice_bloc;
        insert_TnOF(FY, eng_tnof, &i2, &j2);
        tab_Year[eng_lnovc.Info.annee_Naissance - 1940].bloc = i2;
        tab_Year[eng_lnovc.Info.annee_Naissance - 1940].indice_bloc = j2;
        // index Grade
        eng_tnof.suiv_bloc = tab_Grade[eng_lnovc.Info.Grade - 1].bloc;
        eng_tnof.suiv_indice_bloc =
            tab_Grade[eng_lnovc.Info.Grade - 1].indice_bloc;
        insert_TnOF(FG, eng_tnof, &i2, &j2);
        tab_Grade[eng_lnovc.Info.Grade - 1].bloc = i2;
        tab_Grade[eng_lnovc.Info.Grade - 1].indice_bloc = j2;
        // index force
        eng_tnof.suiv_bloc = tab_Force[eng_lnovc.Info.Force_Armee - 1].bloc;
        eng_tnof.suiv_indice_bloc =
            tab_Force[eng_lnovc.Info.Force_Armee - 1].indice_bloc;
        insert_TnOF(FF, eng_tnof, &i2, &j2);
        tab_Force[eng_lnovc.Info.Force_Armee - 1].bloc = i2;
        tab_Force[eng_lnovc.Info.Force_Armee - 1].indice_bloc = j2;
      }
    }
  }
  alloc_blocTOF(FTOF);
  ecriredirTOF(FTOF, enteteTnOF(FTOF, 1), &buf_tof1);
  sprintf(tmp_chain, "%s_Table_index_Sec", Nom_Fichier);
  /*printf("\n\tyear\n");
  Affiche_Index_Tnof(FY,tab_Year,60);
  system("PAUSE");
  printf("\n\tFORCE ARMEE \n");
  Affiche_Index_Tnof(FF,tab_Force,8);
  system("PAUSE");
  printf("\n\tGRADE\n");
  Affiche_Index_Tnof(FG,tab_Grade,17);
  system("PAUSE");*/
  FILE *Table_Index = fopen(tmp_chain, "wb");
  fwrite(tab_Year, sizeof(tab_Year), 1, Table_Index);
  fwrite(tab_Force, sizeof(tab_Force), 1, Table_Index);
  fwrite(tab_Grade, sizeof(tab_Grade), 1, Table_Index);
  fclose(Table_Index);
  fermer_L7OVC(F);
  fermerTnOF(FY);
  fermerTnOF(FG);
  fermerTnOF(FF);
  fermer_TOF(FTOF);

  free(ch);
}

void Creation_fichier_PERSONNEL_L7OVC(const char *Nom_Fichier, long int nb) {
  L7OVC *New_File = ouvrir_L7OVC("TMP1", 'N');
  Ajoutes_enrg_Aleatoire(New_File, nb);
  Creation_Index_Primaire(New_File, "TMP2");
  // afficher_fichier(New_File);
  TOF *F_TOF = ouvrirTOF("TMP2", 'A');
  // printf("sss    %d",enteteTOF(F_TOF,1));system("PAUSE");
  // Affiche_TOF(F_TOF);
  // system("PAUSE");
  // printf("sss    %d",enteteTOF(F_TOF,1));system("PAUSE");
  Reorganisation(New_File, F_TOF, Nom_Fichier, 0.5);
  fermer_L7OVC(New_File);
  fermer_TOF(F_TOF);
  remove("TMP1");
  remove("TMP2");
}

#endif
