#ifndef _LnOVC_H_
#define _LnOVC_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Taille_bloc_L7OVC 1024
long int lire_stat_lonvc = 0;
long int ecrire_stat_lonvc = 0;
//*******************************************declaration des types
//********************************************//
typedef struct Tbloc_L7OVC {
  char tab[Taille_bloc_L7OVC + 1]; // le tableau de caract�re
  int suivant;                     // le numero du bloc suivant dans la liste
} Tbloc_L7OVC;
typedef struct Info_L7OVC {
  char Nom[31];
  char Prenom[31];
  int jour_Naissance;
  int mois_Naissance;
  int annee_Naissance;
  int Wilaya_Naissance;
  int Groupe_Sanguin;
  int Grade;
  int Force_Armee;
  int Region_Militaire;

} Info_L7OVC;
typedef struct Tbloc_L7OVC Buffer_L7OVC; // declaration du tampon
typedef struct enrg_L7OVC {
  bool eface;
  long int cle;
  Info_L7OVC Info;

} enrg_L7OVC;
typedef struct Entete_L7OVC // structure de l'entete du fichier en memoire
                            // centrale
{
  int nbbloc;
  int tete;
  int queue;
  int indice_libre; // l'indice libre dans le bloc de la queue
  int nb_car_sup;

} Entete_L7OVC;
typedef struct L7OVC {
  FILE *F;
  Entete_L7OVC entete;

} L7OVC;

//-------------------------------------permet de mettre a jour les elements de
//l'entete du ficher------------------------------//
void aff_entete_L7OVC(L7OVC *fichier, int i, int valeur);
//-------------------------------------permet d'obtenir les elements de l'entete
//du ficher------------------------------//
int entete_L7OVC(L7OVC *fichier, int i);

void liredir_L7OVC(L7OVC *fichier, int i, Buffer_L7OVC *buf);
void ecriredir_L7OVC(L7OVC *fichier, int i, Buffer_L7OVC *buf);
//---------------------------------------------------------permet d'ouvrir le
//fichier-----------------------------------------//
L7OVC *ouvrir_L7OVC(char nom_physique[], char mode);
void fermer_L7OVC(L7OVC *fichier); // procedure de fermeture du fichier
//-------------------------------------permet d'allouer un nouveau bloc dans le
//ficiher et de maettre a jour les caracteristiques des bloc eet de l'entete
//touches------------------------------//
void alloc_bloc_L7OVC(L7OVC *fichier);
//----------------------------------- // procedure qui permet d'ecrire n
//caract�re du buffer----------------------------------------------//
void ecrire_chaine_enrg(L7OVC *fichier, int *i, int *j, char chaine[],
                        Buffer_L7OVC *buf);
//----------------------------------- fonction qui permet de recuperer une
//chaine de longueur n dans le bloc i  lu dans buffer a partir de la position
//j-------------//
void recuperer_chaine_enrg(L7OVC *fichier, int *i, int *j, char chaine[],
                           Buffer_L7OVC *buf); //
//----------------------------------- fonction qui permet de construire la
//chaine correspondant a la forme de l'enregistrememnt-------------//
void turn_enr_to_string(char chaine[], enrg_L7OVC *A);

int turn_string_to_enrg(enrg_L7OVC *A, char chaine[]);

void insert_Fin_L7OVC(L7OVC *fichier, enrg_L7OVC eng, int *i1, int *j1);
//********************************************fonction de
//recherche**************************************************************//
void recherche_L7OVC(L7OVC *fichier, long int cle, int *trouv, int *i, int *j);
//--------------------------------------- insertion dans un
//fichier--------------------------------------------------//
void insertion_L7OVC(L7OVC *fichier, enrg_L7OVC Pr);
//----------------------- focntion de suppression lohgique dans le
//fichier--------------------------------------------//
void suppression_logique_L7OVC(L7OVC *fichier, long int cle);

//-------------------------------------permet de mettre a jour les elements de
//l'entete du ficher------------------------------//
void aff_entete_L7OVC(L7OVC *fichier, int i, int valeur) {

  switch (i) {
  case 1: {
    fichier->entete.nbbloc =
        valeur; // nombre total de bloc alloues dans le fichier
  } break;
  case 2: {
    fichier->entete.tete =
        valeur; // numero du bloc representatnt la tete du fichier
  } break;
  case 3: {
    fichier->entete.queue =
        valeur; // numero du bloc representatnt la tete duf icheir
  } break;
  case 4: {
    fichier->entete.indice_libre =
        valeur; // la postion libre dans le bloc de queue
  } break;
  case 5: {
    fichier->entete.nb_car_sup =
        valeur; // nombre de caract�res suprime depuis la
                // creation du ficher afin de lancer la reorganiosation
  } break;
  };
}

//-------------------------------------permet d'obtenir les elements de l'entete
//du ficher------------------------------//
int entete_L7OVC(L7OVC *fichier, int i) {

  switch (i) {
  case 1: {
    return (fichier->entete.nbbloc);
  } break;
  case 2: {
    return (fichier->entete.tete);
  } break;
  case 3: {
    return (fichier->entete.queue);
  } break;
  case 4: {
    return (fichier->entete.indice_libre);
  } break;
  case 5: {
    return (fichier->entete.nb_car_sup);
  } break;
  };
}

void liredir_L7OVC(L7OVC *fichier, int i, Buffer_L7OVC *buf) {
  lire_stat_lonvc++;

  fseek(fichier->F, (sizeof(Entete_L7OVC) + sizeof(Tbloc_L7OVC) * (i - 1)),
        SEEK_SET); // positionnement au debut du bloc numero i
  fread(buf, sizeof(Buffer_L7OVC), 1,
        fichier->F); // lecture d'un bloc de caract�re correspondant a la taille
                     // du bloc dans le buffer
  rewind(fichier->F); // repositionnement endebut de fichier
}
void ecriredir_L7OVC(L7OVC *fichier, int i, Buffer_L7OVC *buf) {
  ecrire_stat_lonvc++;

  fseek(fichier->F, sizeof(Entete_L7OVC) + sizeof(Tbloc_L7OVC) * (i - 1),
        SEEK_SET); // positionnement au debut du bloc numero i
  fwrite(buf, sizeof(Buffer_L7OVC), 1,
         fichier->F); // ecriture du contenu du buffer dans le bloc numero i du
                      // fichier
}
//---------------------------------------------------------permet d'ouvrir le
//fichier-----------------------------------------//
L7OVC *ouvrir_L7OVC(char nom_physique[], char mode) {

  L7OVC *fichier = malloc(sizeof(L7OVC)); // allocation  de la structure
  Buffer_L7OVC buf;
  if ((mode == 'A') || (mode == 'a')) // mode ancien
  {
    fichier->F = fopen(
        nom_physique,
        "rb+"); // ouverture du fichier en mode binaire lecture et ecriture
    fread(&(fichier->entete), sizeof(Entete_L7OVC), 1,
          fichier->F); // chargement de l'entete enregistree en debut de fichier
  } else {
    if ((mode == 'N') || (mode == 'n')) // mode nouveau
    {
      fichier->F = fopen(
          nom_physique, "wb+"); // ouverture du fichier en mode binaire ecriture
      aff_entete_L7OVC(fichier, 1,
                       0); // mise a zeo du nombre de bloc si
                           // entete(fichier,1)=0 alors le fichier est vide
      aff_entete_L7OVC(fichier, 2, 1); // mettre tete au premier bloc
      aff_entete_L7OVC(fichier, 3, 1); // de meme pour la queue puisque au debut
                                       // tete est queue sont confondues
      aff_entete_L7OVC(fichier, 4,
                       0); // le premier caract�re du ficheir correspond a
                           // laposition libre puisqu'il est nouveau
      aff_entete_L7OVC(fichier, 5,
                       0); // aucun caract�re n'a encore ete supprime
      fwrite(&(fichier->entete), sizeof(Entete_L7OVC), 1,
             fichier->F);         // enregistrement de l'entete dans le fichier
      buf.suivant = -1;           // le suivant du premier bloc a NULL
      sprintf(buf.tab, "%s", ""); // initialisation du buffer a chaine vide
      ecriredir_L7OVC(fichier, 1,
                      &buf); // ecriture du premier bloc dans le fichier

    } else // format d'ouverture incorrecte
    {
      fprintf(stderr, "format d'ouverture impossible");
    }
  }
  return (fichier); // renvoyer la structure creee
}
void fermer_L7OVC(L7OVC *fichier) // procedure de fermeture du fichier
{
  rewind(fichier->F); // repositionnement du curseur en debut de fichier
  fwrite(&(fichier->entete), sizeof(Entete_L7OVC), 1,
         fichier->F); // sauvegarde de la derni�re version de l'entete de la
                      // strucuture L7OVC
                      // dans le fichier
  rewind(fichier->F); // repositionnement du curseur en debut de fichier
  fclose(fichier->F); // fermeture du fichier
}

//-------------------------------------permet d'allouer un nouveau bloc dans le
//ficiher et de maettre a jour les caracteristiques des bloc eet de l'entete
//touches------------------------------//
void alloc_bloc_L7OVC(L7OVC *fichier) {

  Buffer_L7OVC *buf = malloc(sizeof(Buffer_L7OVC)); // allocation du Buffer
  liredir_L7OVC(fichier, entete_L7OVC(fichier, 3),
                buf); // lecture du bloc correspondant a la queue
  buf->suivant =
      entete_L7OVC(fichier, 1) + 1; // mise a jour dui suvant de la queue au
                                    // bloc correspondant a la nouvelle queue
  ecriredir_L7OVC(fichier, entete_L7OVC(fichier, 3),
                  buf); // ecriture du bloc de queue dans le fichier
  aff_entete_L7OVC(fichier, 3,
                   entete_L7OVC(fichier, 1) +
                       1); // mise a jour du numero du bloc correspondant a la
                           // nouvelle queue dan sl'entete
  buf->suivant = -1;       // mise a jour du suivant a nill
  sprintf(buf->tab, "%s", ""); // vider la chaine du buffer
  ecriredir_L7OVC(
      fichier, entete_L7OVC(fichier, 3),
      buf); // ecriture du buffer dans le bloc representatnt la nouvelle queue
  aff_entete_L7OVC(fichier, 1,
                   entete_L7OVC(fichier, 1) +
                       1); // incrementation du nombre de bloc alloues
}
//----------------------------------- // procedure qui permet d'ecrire n
//caract�re du buffer----------------------------------------------//
void ecrire_chaine_enrg(L7OVC *fichier, int *i, int *j, char chaine[],
                        Buffer_L7OVC *buf) {

  int k = 0, n = strlen(chaine);
  for (k = 0; k < n; k++) // k pourn le deplacement dans la chaine
  {
    if ((*j) <= Taille_bloc_L7OVC) // si je suis toujours dans le bloc conserne
    {
      buf->tab[*j] = chaine[k]; // affectation des caract�res de la chaine dans
                                // le buffer un a un
      (*j)++; // deplacement da,s le buffer
    } else    // si la chaine a inserer depasse le buffer
    {
      buf->tab[*j] = '\0';
      ecriredir_L7OVC(fichier, *i,
                      buf);      // ecriture du precedent buffer dans le fichier
      alloc_bloc_L7OVC(fichier); // alocation d'un nouveau bloc afin de recevoir
                                 // le reste de la chaine
      (buf->tab)[0] = chaine[k]; // ecrtiture du kiem caract�re de la chaine
                                 // dans la position 0
      (*j) = 1;                  // passage a la position 1
      (*i) = entete_L7OVC(fichier, 3); // deplacement dans les bloc du ficher
    }
  }
  buf->tab[*j] = '\0'; // fin de la chaine
}
//----------------------------------- fonction qui permet de recuperer une
//chaine de longueur n dans le bloc i  lu dans buffer a partir de la position
//j-------------//
void recuperer_chaine_enrg(L7OVC *fichier, int *i, int *j, char chaine[],
                           Buffer_L7OVC *buf) //
{
  int k = 0;
  sprintf(chaine, "%s", "");
  do {
    if ((*j) > Taille_bloc_L7OVC) {
      (*i) = buf->suivant; // on passe au suivant du bloc i dans la liste
      liredir_L7OVC(fichier, (*i), buf); // lecture
      (*j) = 0;
    } else {
      chaine[k++] = (buf->tab)[(*j)];
      (*j)++;
    }

  } while (((buf->tab)[(*j)]) != '&');
  (*j)++;
  chaine[k++] = '&';
  chaine[k] = '\0';
}
int turn_string_to_enrg(enrg_L7OVC *A, char chaine[]) {
  if (chaine[0] != 0 && chaine[strlen(chaine) - 1] == '&') {
    sscanf(chaine, "%d$%ld$%d|%d|%d|%d|%d|%d|%d|%d", &(A->eface), &(A->cle),
           &(A->Info.jour_Naissance), &(A->Info.mois_Naissance),
           &(A->Info.annee_Naissance), &(A->Info.Force_Armee), &(A->Info.Grade),
           &(A->Info.Groupe_Sanguin), &(A->Info.Region_Militaire),
           &(A->Info.Wilaya_Naissance));
    char *pos = strchr(chaine, '#');
    if (pos != NULL) {
      int i = 0;
      pos++;
      do {
        A->Info.Nom[i++] = (*pos);
        pos++;
      } while ((*pos) != '#');
      (A->Info.Nom)[i] = '\0';
      i = 0;
      pos++;
      do {
        (A->Info.Prenom)[i++] = (*pos);
        pos++;
      } while ((*pos) != '&');
      (A->Info.Prenom)[i] = '\0';
    }

  } else
    return 0;
  return 1;
}
//----------------------------------- fonction qui permet de construire la
//chaine correspondant a la forme de l'enregistrememnt-------------//
void turn_enr_to_string(char chaine[], enrg_L7OVC *A) {
  sprintf(chaine, "%d$%d$%d|%d|%d|%d|%d|%d|%d|%d#%s#%s&", A->eface, A->cle,
          A->Info.jour_Naissance, A->Info.mois_Naissance,
          A->Info.annee_Naissance, A->Info.Force_Armee, A->Info.Grade,
          A->Info.Groupe_Sanguin, A->Info.Region_Militaire,
          A->Info.Wilaya_Naissance, A->Info.Nom, A->Info.Prenom);
  // printf("%s",chaine);
}

void insert_Fin_L7OVC(L7OVC *fichier, enrg_L7OVC eng, int *i1, int *j1) {
  int i, j;
  Buffer_L7OVC buf;
  char chain[Taille_bloc_L7OVC];
  if (entete_L7OVC(fichier, 1) ==
      0) // si la cle n'a  pas ete trouve alors on insere dans le premier bloc
    aff_entete_L7OVC(fichier, 1, 1);
  sprintf(chain, "%s", "");
  i = entete_L7OVC(fichier, 3); // positionnelent dans le queue
  j = entete_L7OVC(
      fichier, 4); // positionnnement a la position libre dans le bloc de queue
  liredir_L7OVC(fichier, i, &buf); // lecture du  bloc
  (*i1) = i;
  (*j1) = j;
  turn_enr_to_string(chain, &eng);
  ecrire_chaine_enrg(fichier, &i, &j, chain,
                     &buf); // ecriture de la chaine construite
                            // printf("\n\t%s\t",chain);
                            // system("PAUSE");
  ecriredir_L7OVC(fichier, i,
                  &buf); // ecriture du dernier bloc en cas de chevauchement
  aff_entete_L7OVC(fichier, 3, i); // mise a jour de la quee
  aff_entete_L7OVC(fichier, 4, j); // mise a jour de la position libre
}

//********************************************fonction de
//recherche**************************************************************//
void recherche_L7OVC(L7OVC *fichier, long int cle, int *trouv, int *i, int *j) {
  Buffer_L7OVC buf;
  enrg_L7OVC Pr;
  char chaine[Taille_bloc_L7OVC];
  int stop = 0; // booleen pour l'arret de la recherche
  int bloc, pos;
  (*trouv) = 0; // initialisdation de trouv a 0
  (*i) = entete_L7OVC(
      fichier,
      2);   // positionnement au bloc entete pour une recherche sequentielle
  (*j) = 0; // premi�re position
  if (entete_L7OVC(fichier, 1) != 0) // si le fichier nest pas vide
  {
    liredir_L7OVC(fichier, *i,
                  &buf); // lecture du premier bloc afin d'entammer le parcours

    while ((stop == 0) &&
           ((*trouv) ==
            0)) // tant qu'on pas trouve ou qu'on est pas a la fin du ficher
    {
      bloc = (*i); // sauvegarde du bloc a partir duquel on a commence
                   // l'extraction de l'enregistrement
      pos = (*j);  // sauvegarde de la position
      recuperer_chaine_enrg(fichier, i, j, chaine,
                            &buf); // recuperation des champs
      turn_string_to_enrg(&Pr, chaine);
      if ((Pr.cle == cle) &&
          (Pr.eface == 0)) // si l'info n'est pas efface logiquement et que la
                           // cle correspond
      {
        (*trouv) = 1; // arret de la recherche
      } else {
        if (((*i) == entete_L7OVC(fichier, 3)) &&
            ((*j) ==
             entete_L7OVC(fichier,
                          4))) // si on est a la fin du fichier on arrete
        {
          stop = 1;
        }
      }
    }
    (*i) = bloc; // renvoi du bloc et de la position aux quels no n a trouve
                 // l'info si elle existe
    (*j) = pos;
  }
}

//--------------------------------------- insertion dans un
//fichier--------------------------------------------------//
void insertion_L7OVC(L7OVC *fichier, enrg_L7OVC Pr) {
  int i, j, trouv = 0; // declaration des variables
  recherche_L7OVC(fichier, Pr.cle, &trouv, &i,
                  &j); // recherche de la cle por eviter les  dopublon
  if (trouv == 0) {
    insert_Fin_L7OVC(fichier, Pr, &i, &j);
  } else {
    // fprintf(stderr,"insertion impossible cle deja existante\n");
  }
}

//----------------------- focntion de suppression lohgique dans le
//fichier--------------------------------------------//
void suppression_logique_L7OVC(L7OVC *fichier, long int cle) {
  int i, j, trouv;
  Buffer_L7OVC buf;
  char chaine[Taille_bloc_L7OVC];
  recherche_L7OVC(fichier, cle, &trouv, &i,
                  &j); // recherche de la cle fdans le fichihre
  if (trouv == 1)      // si la cmle a etet trouvee
  {
    liredir_L7OVC(fichier, i,
                  &buf); // lecture du bloc dans lequel on a trouve l'info
    recuperer_chaine_enrg(
        fichier, &i, &j, chaine,
        &buf); // recuperation de la chaine correpondant a la taille de l'info
    chaine[0] = '1';
    ecrire_chaine_enrg(fichier, &i, &j, chaine,
                       &buf); // ecriture de la chaine construite
    ecriredir_L7OVC(fichier, i,
                    &buf); // ecriture du dernier bloc en cas de chevauchement
    aff_entete_L7OVC(
        fichier, 5,
        entete_L7OVC(fichier, 5) +
            strlen(chaine)); // mise az jour du nombre de caract�re supprimes
                             // printf("\nsuppression logique reussie\n");
  } else {
    // printf("\n   suppression impossible cle inexistante\n");
  }
}

//------------------------ suppresiion physique dans un autre
//ficher----------------------------------------------------------------//
void suppression_physique_L7OVC(L7OVC *fichier, char *nom_physique) {
  Buffer_L7OVC buf1, buf2;
  L7OVC *fichier2;
  int bloc1, bloc2, pos1, pos2, cpt = 0;
  char chaine[Taille_bloc_L7OVC];
  fichier2 = ouvrir_L7OVC(nom_physique, 'n'); // ouverture du fichier
  bloc1 = entete_L7OVC(fichier, 2);
  pos1 = 0;
  aff_entete_L7OVC(fichier2, 1, 1);
  bloc2 = 1;
  pos2 = 0;
  liredir_L7OVC(fichier, bloc1,
                &buf1); // lecture du premier bloc dans le fichier 1
  int stop = 0;
  while (!stop) {
    sprintf(chaine, "%s", ""); // recuperation des chaines
    recuperer_chaine_enrg(fichier, &bloc1, &pos1, chaine, &buf1);
    if (chaine[0] == '0') // sila cle n'a pas etet supprime logiquement on
                          // l'ens�re dans le nouveau fichier
    {
      ecrire_chaine_enrg(fichier2, &bloc2, &pos2, chaine, &buf2);
      aff_entete_L7OVC(fichier2, 3, bloc2);
      aff_entete_L7OVC(fichier2, 4, pos2);
    }
    if ((bloc1 == entete_L7OVC(fichier, 3)) &&
        (pos1 ==
         entete_L7OVC(fichier,
                      4))) // si onn est la fin du ficher source on  arrete
    {
      stop = 1;
    }
  }
  ecriredir_L7OVC(fichier2, bloc2, &buf2);
}

#endif
