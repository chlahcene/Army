#ifndef _TP_H_
#define	_TP_H_

#include <stdio.h>
#include <stdlib.h>
#include "Lnovc_index.h"
#include <conio.h>
#include <conio2.h>
//#include <conio.c>
#include "Input.h"

#define PX  25
#define PY  10
#define HTR  20
#define LNGR 80

#define PX1  25
#define PY1  10
#define HTR1  30
#define LNGR1 80

    char*  WILAYA[] = {"Adrar","Chlef","Laghouat","Oum El Bouaghi","Batna","Bejaia","Biskra","Bechar","Blida","Bouira","Tamenrasset","Tebessa","Telemcen","Tiaret","Tizi Ouzou","Alger","Djelfa","Jijel","Setif","Saida","Sakikda","Sidi Bel Abbas","Annaba","Guelma","Constantine","Medea","Mostaganem","M'sila","Mascara","Ouargla","Oran","El Bayedh","Illizi","Bordj Bou Arreridj","Boumerdes","El Taref","Tindouf","Tissemsilt","El Oued","Khenchela","Souk Ahras","Tipaza","Mila","Ain Defla","Naama","Ain Temouchent","Ghardaia","Relizane"};
    char*  GROUPE_SANGUIN[] ={"O+","A+","B+","O-","A-","AB+","B-","AB-"};
    char*  GRADE[] = {"General de corps d'armee","General-Major","General","Colonel","Lieutenant-colonel","Commandant","Capitaine","Lieutenant","Sous-lieutenant","Aspirant","Adjudant-chef","Adjudant","Sergentchef","Sergent","Caporal-chef","Caporal","Djoundi" };
    char*  FORCE_ARMEE[] = {"Armee de terre","Armee de l'air","Marine nationale","Defense aerienne du territoire","Gendarmerie nationale","Garde republicaine","Departement du renseignement et de la securite","Sante militaire" };
    char*  REGION_MILITAIRE[] = { "1RM-Blida","2RM-Oran","3RM-Bechar","4RM-Ouargla","5RM-Constantine","6RMTamanrasset"};
void Affiche_ENG(enrg_L7OVC A)
{
      textbackground(BLACK);
      system("CLS");
      textbackground(WHITE);
      textcolor(YELLOW);
      int i=5,j=4;
      FrameRectangle(i,j,100,35,4);
      textcolor(WHITE);
      textbackground(BLACK);
      gotoxy(i+8,j+4);printf("Matrucule :\t %ld",A.cle);
      gotoxy(i+8,j+6);printf("Nom :\t %s",A.Info.Nom);
      gotoxy(i+8,j+8);printf("Prenom :\t %s",A.Info.Prenom);
      gotoxy(i+8,j+10);printf("Date Naissance :\t %d/%d/%d",A.Info.jour_Naissance,A.Info.mois_Naissance,A.Info.annee_Naissance);
      gotoxy(i+8,j+12);printf("Wilaya Naissance :\t %s",WILAYA[A.Info.Wilaya_Naissance-1]);
      gotoxy(i+8,j+14);printf("Groupe Sanguin :\t %s",GROUPE_SANGUIN[A.Info.Groupe_Sanguin-1]);
      gotoxy(i+8,j+16);printf("Grade :\t %s",GRADE[A.Info.Grade-1]);
      gotoxy(i+8,j+18);printf("Force Armee :\t %s",FORCE_ARMEE[A.Info.Force_Armee-1]);
      gotoxy(i+8,j+20);printf("Region Militaire :\t %s",REGION_MILITAIRE[A.Info.Region_Militaire-1]);
      gotoxy(i+8,j+22);system("PAUSE");

}

void afficher_fichier_lonvc(L7OVC *fichier)
{
    int i=entete_L7OVC(fichier,2); // positionnement a la tete du fichier
    int j=0;                  // positionnement au premier caractere
    int stop=0;
    Buffer_L7OVC buf;
    enrg_L7OVC A;
    char *ch=malloc(sizeof(char)*Taille_bloc_L7OVC);
    liredir_L7OVC(fichier,i,&buf);    // lecture du premier bloc
  if(entete_L7OVC(fichier,1)!=0)
  {
    while(!stop)
    {
        recuperer_chaine_enrg(fichier,&i,&j,ch,&buf); // on commence a recuperer les enregistrememnt un a un

        if(ch[0]=='0') //. si l'info n' pas ete supprime logiquement
        {
            turn_string_to_enrg(&A,ch);
            Affiche_ENG(A);
            printf("\n\n\t%s\n\t",ch);
            system("PAUSE");
        }
        if((i==entete_L7OVC(fichier,3)) && (j==entete_L7OVC(fichier,4))) // si on est la fin du ficher on arrete
        {
            stop=1;
        }
    }
  }
  else
  {
      printf("fichier vide");
  }
}
int Nom_Fichier(char **nom){
    // affiche liste des fichiers et l'utilisatuer choiser un nom fichier pour l'utiliser
          char **NFile;
          int i,j,taille;
          File_Derectory_Current(&NFile,&taille);
          do{
          textbackground(BLACK);
          system("CLS");
          textbackground(WHITE);
          textcolor(YELLOW);
          FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
          textcolor(BLACK);
          i=Menu(NFile,taille,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
          if (i!=0) {
            (*nom)=NFile[i-1];
            FILE* F=fopen(*nom,"r");
            if (F==NULL){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxyTemp(10,2,"THIS is derecotory try again file \n\t",15);
                system("PAUSE");
                continue;
            }
            fclose(F);
          }
            break;
          }while(1);
          for (j=0;j<taille;j++) if ((j+1)!=i) free(NFile[j]);
          free(NFile);
        return i;
}

void Page_Temporaire(int x,int y,int longueur,int hauteur,const char* text){
    /// affiche page avec text si apuiyer entre elle dispareur
        struct char_info * AncienTexte;
        AncienTexte = malloc ((longueur+2)*(hauteur+4)*sizeof(struct char_info));
        gettext (x,y-1,x+longueur,y+hauteur+3,AncienTexte);
        cputsxyBlanc(x,y-1," ",longueur);
        cputsxyAreaBlanc(x,y,text,hauteur,longueur," :");
        cputsxyBlanc(x,y+hauteur," ",longueur);
        cputsxyBlanc(x,y+hauteur+1," ",longueur);
        cputsxyBlanc(x,y+hauteur+2," ",longueur);
        textcolor(BLACK);
        textbackground(LIGHTCYAN);
        AfficheButton("Ok",x+longueur/2-5,y+hauteur,10,3);
        int c;
        do{
            c=getch();
        }while(c!=13);
        puttext (x,y-1,x+longueur,y+hauteur+3,AncienTexte);
        //free(AncienTexte);
    return 0;
}
int Fichier_cree(char* nom_fichier,long int *nbr_eng){
// textbackground(LIGHTBLUE);
    system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=40,y=2;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"Cree nouveau fichier avec n enregtrument");
    textcolor(WHITE);
    cputsxy(x,y+7,"Nom Fichier");
    cputsxy(x,y+13,"Nbr enregtrument");
    textcolor(RED);
    putchxy(x+16,y+7,'*');
    putchxy(x+25 ,y+13,'*');
    textbackground(WHITE);
    DrawRectangle(x,y+8,48,2);
    DrawRectangle(x,y+14,48,2);
    textbackground(LIGHTCYAN);
    textcolor(WHITE);
    AfficheButton("Cree",x,y+20,20,3);
    int NumbreInput=1;
    int c=0;
    nom_fichier[0]=0;char Nouveau_Mot[15]={"\0"};
    textbackground(WHITE);
    textcolor(BLACK);
    do{
        if (NumbreInput>0 && NumbreInput<3){

            if (NumbreInput==1){
                // Mot
                c=Input_Text(nom_fichier,x,y+9,48);

            }else if (NumbreInput==2){
                // Nouveau_Mot
                c=Input_Number(Nouveau_Mot,x,y+15,10);

            }
            if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
            else if (c==72 || c==73) {
                NumbreInput--;
                if (NumbreInput==0) NumbreInput=3;
            }
        }else if (NumbreInput==3){
            // Button recharche
            textbackground(BLUE);
            textcolor(WHITE);
            AfficheButton("Cree",x,y+20,20,3);
            do{
                c=SaiserCntrl();
            }while(c==75 || c==77 ); // car here touch left and right ne faite rien
            if (c==13){
                if (!(nom_fichier[0] && Nouveau_Mot[0])) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in the input they are required.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                sscanf(Nouveau_Mot,"%ld",nbr_eng);
                return 0;

            }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
             else if (c==72 || c==73) NumbreInput=2;
            textbackground(LIGHTCYAN);
            AfficheButton("Cree",x,y+20,20,3);
            textbackground(WHITE);
            textcolor(BLACK);
        }
        if (c==27){
            // return Backs
            if (AreYouSure(20,15)) return 1;
            textbackground(WHITE);
            textcolor(BLACK);
        }
    }while(1);
    return 0;
}
int lire_ENG(enrg_L7OVC *A){
       textbackground(BLACK);
     system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=35,y=2;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"Nouveaux venier");
    textcolor(WHITE);
    cputsxy(x,y+7,"Matricule ");
    cputsxy(x,y+13,"Nom ");
    cputsxy(x,y+19,"Prenom ");
    cputsxy(x,y+25,"Date naissance ");
    cputsxy(x,y+31,"Wilaya naissance ");
    cputsxy(x,y+37,"Groupe Sanguin");
    cputsxy(x,y+43,"Grade ");
    cputsxy(x,y+49,"Force Armee ");
    cputsxy(x,y+55,"Region Militaire  ");
    textcolor(RED);
    putchxy(x+9,y+7,'*');
    putchxy(x+11,y+13,'*');
    putchxy(x+10,y+19,'*');
    textbackground(WHITE);
    textcolor(BLACK);
    DrawRectangle(x,y+8,48,2);
    DrawRectangle(x,y+14,48,2);
    DrawRectangle(x,y+20,48,2);
    DrawRectangle(x,y+26,48,2);
    DrawRectangle(x,y+32,48,2);
    DrawRectangle(x,y+38,48,2);
    DrawRectangle(x,y+44,48,2);
    DrawRectangle(x,y+50,48,2);
    DrawRectangle(x,y+56,48,2);

    textbackground(LIGHTCYAN);
    textcolor(WHITE);
    AfficheButton("Ajoutez ",x,y+64,20,3);
    int NumbreInput=1;
    int c=0;
    char Matriculle[48]="\0",LastName[48]="\0",FirstName[48]="\0",ch[100];
    sprintf(Matriculle,"%ld",A->cle);
    sprintf(LastName,"%s",A->Info.Nom);
    sprintf(FirstName,"%s",A->Info.Prenom);
    textbackground(WHITE);
    textcolor(BLACK);
    cputsxy(x,y+9,Matriculle);
    cputsxy(x,y+15,LastName);
    cputsxy(x,y+21,FirstName);
    cputsxy(x,y+27,"");
    cputsxy(x,y+33,WILAYA[A->Info.Wilaya_Naissance]);
    cputsxy(x,y+39,GROUPE_SANGUIN[A->Info.Groupe_Sanguin]);
    cputsxy(x,y+45,GRADE[A->Info.Grade]);
    cputsxy(x,y+51,FORCE_ARMEE[A->Info.Force_Armee]);
    cputsxy(x,y+57,REGION_MILITAIRE[A->Info.Region_Militaire]);
    do{
        if (NumbreInput>0 && NumbreInput<10){

            if (NumbreInput==1){
                // Username
                c=Input_Text(Matriculle,x,y+9,6);

            }else if (NumbreInput==2){
                // First Name
                c=Input_Text(FirstName,x,y+15,30);

            }else if (NumbreInput==3){
                // Last Name
                c=Input_Text(LastName,x,y+21,30);

            }else if (NumbreInput==4){
                // Date naissance
                c=Input_Date(&(A->Info.jour_Naissance),&(A->Info.mois_Naissance),&(A->Info.annee_Naissance),x,y+27);

            }else if (NumbreInput==5){
                // Wilaya naissance
                A->Info.Wilaya_Naissance=Menu2(WILAYA,48,x,y+33,48,1,WHITE,WHITE,A->Info.Wilaya_Naissance);

            }else if (NumbreInput==6){
                // Groupe Sanguin
                A->Info.Groupe_Sanguin=Menu2_sans(GROUPE_SANGUIN,8,x,y+39,48,1,WHITE,WHITE,A->Info.Groupe_Sanguin);

            }else if (NumbreInput==7){
                // Grade
                A->Info.Grade=Menu2_sans(GRADE,17,x,y+45,48,1,WHITE,WHITE,A->Info.Grade);

            }else if (NumbreInput==8){
                // Force Armee
                A->Info.Force_Armee=Menu2_sans(FORCE_ARMEE,8,x,y+51,48,1,WHITE,WHITE,A->Info.Force_Armee);

            }else if (NumbreInput==9){
                // Region Militaire
                A->Info.Region_Militaire=Menu2_sans(REGION_MILITAIRE,6,x,y+57,48,1,WHITE,WHITE,A->Info.Region_Militaire);

            }
            if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
            else if (c==72 || c==73) {
                NumbreInput--;
                if (NumbreInput==0) NumbreInput=10;
            }
        }else if (NumbreInput==10){
            // Button Create new account
            textbackground(BLUE);
            textcolor(WHITE);
            AfficheButton("Ajoutez ",x,y+64,20,3);
            do{
                c=SaiserCntrl();
            }while(c==75 || c==77 ); // car here touch left and right ne fait rien
            if (c==13){
                // here est create new account

                if (!(Matriculle[0] && LastName[0] && FirstName[0])) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in required inputs.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                if (A->Info.annee_Naissance<1940 || A->Info.annee_Naissance>1999) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"La date naissance doit entre entre [1940 .. 1999]");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                 sscanf(Matriculle,"%ld",&(A->cle));
                if (A->cle<111111 || A->cle>999999) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"Le matricule doit entre entre [111111 .. 999999]");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                /// test du existense du cle

                    strcpy(A->Info.Nom,FirstName);
                    strcpy(A->Info.Prenom,LastName);
                    textbackground(BLACK);
                    system("CLS");
                    textcolor(WHITE);
                    cputsxyTemp(22,3," thanks you ...",10);
                    getch();
                    return 0;
            }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
             else if (c==72 || c==73) NumbreInput=9;
            textbackground(LIGHTCYAN);
            AfficheButton("Ajoutez ",x,y+64,20,3);
            textbackground(WHITE);
            textcolor(BLACK);
        }
        if (c==27){
            // return Backs
            if (AreYouSure(20,15)) return 1;
            textbackground(WHITE);
            textcolor(BLACK);
        }
    }while(1);

    return 1;

}







#endif
