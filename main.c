#include "TP.h"


int main()
{
    system("mode con LINES=1000 COLS=130");
    /*int co[10][max_input_radio];
    int ch[10][max_input_radio];
    co[0][1]=2;co[0][2]=2;co[0][3]=25;co[0][0]=2;
    co[1][1]=2;co[1][2]=3;co[1][3]=25;co[1][0]=4;
//    co={{2,2,2,30},{4,2,3,35}};
    ch[0][0]=1;ch[0][1]=0;
    ch[1][1]=1;ch[1][0]=0;
  //  ch={{1,0},{0,1}};
    printf("\n    lahcene  \t\t  bekaceme\n");
    printf("\n    karime  \t\t  mh");
    do{
        Input_radio(co,ch,2);
        gotoxy(1,10);
        printf("\t%d \t %d \n\t%d \t %d ",ch[0][0],ch[0][1],ch[1][0],ch[1][1]);
    }while(1);*/
    /*int a=1997,m=8,j=5;
       do{
        Input_Date(&j,&m,&a,10,5);
        gotoxy(1,10);
             textcolor(BLACK);
     textbackground(WHITE);

        printf("\t %2d/%2d/%4d ",j,m,a);
    }while(1);*/
    getch();
    ChioxMenu();




    return 0;
}

void ChioxMenu(){
    int i;
    int a=3,s=3;
    char*  S[] =    {
                     "Creat Fichier",
                     "consuleter fichier ",
                     "Quitter Le Programme"
                     };
    char*  A[] =    {
                     "Ajoute Nouveau",
                     "Recharche, consuleter, modifier, supprimer",
                     "Stat et structure"
                     };
    char Nom_fichier_utliser[50];
    long int nb=0;
            do{
             //Debut();
                 do{
                  textbackground(BLACK);
                  system("CLS");
                  textbackground(WHITE);
                  textcolor(GREEN);
                  FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
                  textcolor(BLACK);
                  i=Menu(S,s,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
                  if (i==0) break;
                  if (i==1){
                    // Creat Fichier
                    if (Fichier_cree(Nom_fichier_utliser,&nb)==0){
                        textbackground(BLACK);
                        textcolor(WHITE);
                        system("CLS");
                        printf("\t Pathainter un peu ...\n");
                        Creation_fichier_PERSONNEL_L7OVC(Nom_fichier_utliser,nb);
                        printf("\t le creation terminer\n\t");system("PAUSE");
                    }

                  }else if (i==2){
                    //consuleter fichier
                    char *nom_fichier;
                    if (Nom_Fichier(&nom_fichier)){
                        L7OVC *F_lovc=ouvrir_L7OVC(nom_fichier,'A');
                        Buffer_L7OVC buf;
                        enrg_L7OVC eng_lnovc;
                            do{
                              textbackground(BLACK);
                              system("CLS");
                              textbackground(WHITE);
                              textcolor(GREEN);
                              FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
                              textcolor(BLACK);
                              i=Menu(A,a,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
                              if (i==0) break;
                              if (i==1){
                                // Ajoute Nouveau
                                eng_lnovc.cle=111111L;
                                eng_lnovc.eface=0;
                                eng_lnovc.Info.annee_Naissance=1940;
                                eng_lnovc.Info.Force_Armee=1;
                                eng_lnovc.Info.Grade=1;
                                eng_lnovc.Info.Groupe_Sanguin=1;
                                eng_lnovc.Info.jour_Naissance=1;
                                eng_lnovc.Info.mois_Naissance=1;
                                eng_lnovc.Info.Nom[0]=0;
                                eng_lnovc.Info.Prenom[0]=0;
                                eng_lnovc.Info.Region_Militaire=1;
                                eng_lnovc.Info.Wilaya_Naissance=1;
                                if (lire_ENG(&eng_lnovc)==0){
                                    //insertion_L7OVC()
                                }

                              }else if (i==2){
                                //Recharche
                                afficher_fichier_lonvc(F_lovc);
                              }else if (i==3){
                               // Stat et structure
                                    textbackground(BLACK);
                                    textcolor(WHITE);
                                    system("CLS");
                                    printf("\t\t Noms des Fichiers \n");
                                    printf("\t\t\t Fichier Principale :  %s \n",nom_fichier);
                                    printf("\t\t\t Index Primaire :  %s_index_Primaire \n",nom_fichier);
                                    printf("\t\t\t Index secondaires \n");
                                    printf("\t\t\t\t Anne Naissanse :  %s_index_Sec_Year \n",nom_fichier);
                                    printf("\t\t\t\t Force Armee :  %s_index_Sec_Force_Armee \n",nom_fichier);
                                    printf("\t\t\t\t Grade :  %s_index_Sec_Grade \n",nom_fichier);
                                    printf("\t\t\t Table des index :  %s_Table_index_Sec \n",nom_fichier);
                                    printf("\n\t\t\t\t Entete \n");
                                    printf("\t nombre total de bloc alloues dans le fichier : %d \n",entete_L7OVC(F_lovc,1));
                                    printf("\t numero du bloc representatnt la tete du fichier : %d \n",entete_L7OVC(F_lovc,2));
                                    printf("\t numero du bloc representatnt la tete du ficheir : %d \n",entete_L7OVC(F_lovc,3));
                                    printf("\t la postion libre dans le bloc de queue : %d \n",entete_L7OVC(F_lovc,4));
                                    printf("\t nombre de caracteres supprime  : %d \n",entete_L7OVC(F_lovc,5));
                                    printf("\n\t Fichier Principale : \t le nombre lecteur %ld \t ecriteur %ld\n",ecrire_stat_lonvc,lire_stat_lonvc);
                                    printf("\n\t Index Primaire : \t le nombre lecteur %ld \t ecriteur %ld\n",ecrire_stat_tof,lire_stat_tof);
                                    printf("\n\t Index Secondaire : \t le nombre lecteur %ld \t ecriteur %ld\n",ecrire_stat_tnof,lire_stat_tnof);
                                    printf("\n\t Totale : \t le nombre lecteur %ld \t ecriteur %ld\n",ecrire_stat_tnof+ecrire_stat_lonvc+ecrire_stat_tof
                                           ,lire_stat_tnof+lire_stat_tof+lire_stat_lonvc);
                                    printf("\n\t Acces Totale MC : \t %ld \n",ecrire_stat_tnof+ecrire_stat_lonvc+ecrire_stat_tof
                                           +lire_stat_tnof+lire_stat_tof+lire_stat_lonvc);
                                    liredir_L7OVC(F_lovc,1,&buf);
                                    printf("\n \t bloc 1\n%s",buf.tab);
                                    liredir_L7OVC(F_lovc,2,&buf);
                                    printf("\n \t bloc 2\n%s",buf.tab);
                                    liredir_L7OVC(F_lovc,3,&buf);
                                    printf("\n \t bloc 3\n%s\n\n",buf.tab);
                                    system("pause");
                              }
                             }while(1);



                    }

                  }else if (i==3){
                   // Quiter Le programme

                   //FIN();
                   return 0;
                  }
                 }while(1);
            }while(1);

}
