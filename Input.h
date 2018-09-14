#ifndef _Input_H_
#define	_Input_H_

#include <string.h>
#include <ctype.h>

#include "String++.h"
#define max_input_radio 10
int Input_Text(char* text,int CooredonneX,int CooredonneY,int maxlength);
    // Defines a single-line text and save in text
int Input_Number(char* Number,int CooredonneX,int CooredonneY,int maxlength);
    // Defines a single-line Number and save in Number
int Input_MotPass(char* MotPass,int CooredonneX,int CooredonneY,int maxlength);
    // Defines a single-line Mot Pass and save in Number
int Input_Area_Number(char* Number,int CooredonneX,int CooredonneY,int maxlength,int maxLength_Line);
    // Defines a multi line Number
int SaiserCntrl(void);
    // Attendre que utilisateur taper les touch du controlle et ingnore les autres
void FrameRectangle(int x,int y,int length,int height,char charFrame);
    // display frame in screen with length and height made with charFrame
void DrawRectangle(int x,int y,int length,int height);
    // Draw rectangle
void AfficheButton(const char *NomButton,int x,int y,int length,int height);
    // display the button in the screen
void cputsxyTemp(int x,int y,const char *chain,int Temp);
    // print the string chain in the screen in position x and y with pause Temp ms between All char
int AreYouSure(int x,int y);
    // asking the user if he is sure
void AfficheErreur(int x,int y,const char *Erreur);
    // Affiche un erreur in th screen
int Menu(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu);
    // Affichez Le menu return le nemero choiser return 0 c'est choiser retourner en arreire
int Menu_sans(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu);
    // Affichez Le menu return le nemero choiser return 0 c'est choiser retourner en arreire sans
int Menu2(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu,int select_nemero);
    // Affichez Le menu return le nemero choiser return select_nemero c'est choiser retourner en arreire
int Menu2_sans(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu,int select_nemero);
    // Affichez Le menu return le nemero choiser return select_nemero c'est choiser retourner en arreire
void AffichezListeChoix(const char **ch,int NbrChoix ,int num,int MaxLongueurString,int x,int y);
    // Affichez un liste des chiox qui se trouve dans tableau ch de Nbrchoix phrase
void AffichezListeChoix_sans(const char **ch,int NbrChoix ,int num,int MaxLongueurString,int x,int y);
    // Affichez un liste des chiox qui se trouve dans tableau ch de Nbrchoix phrase
int SaiserCtrlText(void);
    // attendre que utilisateur taper les touch du controlle text comme cntrl F .. et ignore les autres


int Input_Text(char* text,int CooredonneX,int CooredonneY,int maxlength){

    /** Defines a single-line text
     ** il return la camande qui la fait sortire comme entre ou up ou down
     **/
    unsigned char toucheClavier,toucheClavier1;
    int TailleDuTexte=strlen(text);
    int i=TailleDuTexte;
    cputsxyBlanc(CooredonneX,CooredonneY,text,maxlength);
    do{
        gotoxy(CooredonneX+i,CooredonneY);
        toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            // on lit les touch des clavier qui a deux code
            toucheClavier1=getch();
            if (toucheClavier==224 && toucheClavier1==75){
                // touch clavier est touch lift
                if (i>0) i--; // on decremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==77){
                // touch clavier est touch right
                if (i<TailleDuTexte) i++; // on incremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==79){
                // touch clavier est touch Fin de Line
                i=TailleDuTexte; // on postiionne la curseur a la fin de la line
            }else if (toucheClavier==224 && toucheClavier1==71){
                // touch clavier est touch Debut de Line
                i=0; // on postiionne la curseur a la debut de la line
            }else if (toucheClavier==224 && toucheClavier1==83){
                // touch clavier est touch suppr inser
            if (i<TailleDuTexte){
                StrSuppChar(text,i);// on supprime le cractere de la postion i
                cputsxyBlanc(CooredonneX,CooredonneY,text,TailleDuTexte--);
            }else printf("%c",7);
            }else if (toucheClavier==224 && (toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72)){
                // touch clavier est touch up ou down ou page suivant ou precedant
                return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
            }
        }else if(iscntrl(toucheClavier)){
        if (toucheClavier==8){
            // touch supp
            if (i>0){
                StrSuppChar(text,--i);// on supprime le cractere de la postion i-1
                cputsxyBlanc(CooredonneX,CooredonneY,text,TailleDuTexte--);
            }else printf("%c",7);
        }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier; // on sort du la fonction avec return du le touch qui fait sortire
        }
        }else if (isprint(toucheClavier) || isCharSpFr(toucheClavier)){
             if (TailleDuTexte<maxlength){
                StrInsertChar(text,(char)toucheClavier,i++);// on Insert le cractere toucheClavier a la postion i
                cputsxy(CooredonneX,CooredonneY,text);
                TailleDuTexte++;
             }else printf("%c",7);
        }
    }while(1);
    return -1;
}
int Input_radio( int Cooredonne[][max_input_radio],int choix[][max_input_radio],int taille){

    /** Defines a input radio
     ** il return la camande qui la fait sortire comme entre ou up ou down
     **/

    unsigned char toucheClavier,toucheClavier1;
    int i=0,j=0;
    for (i=0;i<taille;i++){
        for (j=0;j<Cooredonne[i][1];j++){
            if (choix[i][j]==0) cputsxy(Cooredonne[i][j+2],Cooredonne[i][0]," ");
            else {
                cputsxy(Cooredonne[i][j+2],Cooredonne[i][0],"X");
                choix[i][j]=1;
            }
        }
    }
    i=0;j=0;
    while(taille>0){
        gotoxy(Cooredonne[i][j+2],Cooredonne[i][0]);
        toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            // on lit les touch des clavier qui a deux code
            toucheClavier1=getch();
            if (toucheClavier==224 && toucheClavier1==75){
                // touch clavier est touch left
                if (j>0) j--; // on decremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==77){
                // touch clavier est touch right
                if (j<Cooredonne[i][1]-1) j++; // on incremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==79){
                // touch clavier est touch Fin de Line
                i=taille-1; // on postiionne la curseur a la fin de la line
            }else if (toucheClavier==224 && toucheClavier1==71){
                // touch clavier est touch Debut de Line
                i=0; // on postiionne la curseur a la debut de la line
            }else if (toucheClavier==224 && toucheClavier1==83){
                // touch clavier est touch suppr inser
                  choix[i][j]=0;
                  cputsxy(Cooredonne[i][j+2],Cooredonne[i][0]," ");
            }else if (toucheClavier==224 && (toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72)){
                // touch clavier est touch up ou down ou page suivant ou precedant
                if (toucheClavier1==81 || toucheClavier1==80){
                    if (i==taille-1) return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
                    i++;
                }else if(toucheClavier1==73 || toucheClavier1==72){
                    if (i==0) return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
                    i--;
                }
            }
        }else if(iscntrl(toucheClavier)){
        if (toucheClavier==8){
            // touch supp

            choix[i][j]=0;
           cputsxy(Cooredonne[i][j+2],Cooredonne[i][0]," ");
        }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier; // on sort du la fonction avec return du le touch qui fait sortire
        }
        }else if (toucheClavier==(int)' '){
            choix[i][j]=!(choix[i][j]);
            if (choix[i][j])cputsxy(Cooredonne[i][j+2],Cooredonne[i][0],"X");
                else cputsxy(Cooredonne[i][j+2],Cooredonne[i][0]," ");
        }
    }
    return -1;
}
int Input_Number(char* Number,int CooredonneX,int CooredonneY,int maxlength){

    /** Defines a single-line Number
     ** il return la camande qui la fait sortir comme entre ou up ou down
     **/
    unsigned char toucheClavier,toucheClavier1;
    int NbrChiffre=strlen(Number);
    int i=NbrChiffre;
    cputsxyBlanc(CooredonneX,CooredonneY,Number,maxlength);
    do{
        gotoxy(CooredonneX+i,CooredonneY);
        toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            // on lit les touch des clavier qui a deux code
            toucheClavier1=getch();
            if (toucheClavier==224 && toucheClavier1==75){
                // touch clavier est touch lift
                if (i>0) i--; // on decremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==77){
                // touch clavier est touch right
                if (i<NbrChiffre) i++; // on incremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==79){
                // touch clavier est touch Fin de Line
                i=NbrChiffre; // on postiionne la curseur a la fin de la line
            }else if (toucheClavier==224 && toucheClavier1==71){
                // touch clavier est touch Debut de Line
                i=0; // on postiionne la curseur a la debut de la line
            }else if (toucheClavier==224 && toucheClavier1==83){
                // touch clavier est touch suppr inser
            if (i<NbrChiffre){
                StrSuppChar(Number,i);// on supprime le cractere de la postion i
                cputsxyBlanc(CooredonneX,CooredonneY,Number,NbrChiffre--);
            }else printf("%c",7);
            }else if (toucheClavier==224 && (toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72)){
                // touch clavier est touch up ou down ou page suivant ou precedant
                return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
            }
        }else if(iscntrl(toucheClavier)){
        if (toucheClavier==8){
            // touch supp
            if (i>0){
                StrSuppChar(Number,--i);// on supprime le cractere de la postion i-1
                cputsxyBlanc(CooredonneX,CooredonneY,Number,NbrChiffre--);
            }else printf("%c",7);
        }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier; // on sort du la fonction avec return du le touch qui fait sortire
        }
        }else if (isdigit(toucheClavier)){
             if (NbrChiffre<maxlength){
                StrInsertChar(Number,(char)toucheClavier,i++);// on Insert le cractere toucheClavier a la postion i
                cputsxy(CooredonneX,CooredonneY,Number);
                NbrChiffre++;
             }else printf("%c",7);
        }
    }while(1);
    return -1;
}
int SaiserCntrl(void){
    /** attendre que utilisateur taper les touch du controlle et ignore les autres
     ** return le code du touch
     **/
    unsigned char toucheClavier,toucheClavier1;
    do{
    toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            toucheClavier1=getch();
            if (toucheClavier==224){
                if (toucheClavier1==75 || toucheClavier1==77 || toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72){
                    return toucheClavier1;
                }
            }
       }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier;
        }
    }while(1);
    return -1;
}
int Input_MotPass(char* MotPass,int CooredonneX,int CooredonneY,int maxlength){

    /** Defines a single-line MotPass
     ** il return la commande qui la fait sortire comme entre ou up ou down
     **/
    unsigned char toucheClavier,toucheClavier1;
    int TailleDuTexte=strlen(MotPass);
    char text[maxlength+1];
    int i;
    for(i=0;i<TailleDuTexte;i++) text[i]='*';
    text[TailleDuTexte]='\0';
    cputsxyBlanc(CooredonneX,CooredonneY,text,maxlength);
    do{
        gotoxy(CooredonneX+i,CooredonneY);
        toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            // on lit les touch des clavier qui a deux code
            toucheClavier1=getch();
            if (toucheClavier==224 && toucheClavier1==75){
                // touch clavier est touch lift
                if (i>0) i--; // on decremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==77){
                // touch clavier est touch right
                if (i<TailleDuTexte) i++; // on incremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==79){
                // touch clavier est touch Fin de Line
                i=TailleDuTexte; // on postiionne la curseur a la fin de la line
            }else if (toucheClavier==224 && toucheClavier1==71){
                // touch clavier est touch Debut de Line
                i=0; // on postiionne la curseur a la debut de la line
            }else if (toucheClavier==224 && toucheClavier1==83){
                // touch clavier est touch suppr inser
            if (i<TailleDuTexte){
                StrSuppChar(MotPass,i);// on supprime le cractere de la postion i
                text[--TailleDuTexte]='\0';
                cputsxyBlanc(CooredonneX,CooredonneY,text,TailleDuTexte+1);
            }else printf("%c",7);
            }else if (toucheClavier==224 && (toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72)){
                // touch clavier est touch up ou down ou page suivant ou precedant
                return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
            }
        }else if(iscntrl(toucheClavier)){
        if (toucheClavier==8){
            // touch supp
            if (i>0){
                StrSuppChar(MotPass,--i);// on supprime le cractere de la postion i-1
                text[--TailleDuTexte]='\0';
                cputsxyBlanc(CooredonneX,CooredonneY,text,TailleDuTexte+1);
            }else printf("%c",7);
        }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier; // on sort du la fonction avec return du le touch qui fait sortire
        }
        }else if (isprint(toucheClavier) || isCharSpFr(toucheClavier)){
             if (TailleDuTexte<maxlength){
                StrInsertChar(MotPass,(char)toucheClavier,i++);// on Insert le cractere toucheClavier a la postion i
                text[TailleDuTexte++]='*';
                text[TailleDuTexte]='\0';
                cputsxy(CooredonneX,CooredonneY,text);
             }else printf("%c",7);
        }
    }while(1);
    return -1;
}
void FrameRectangle(int x,int y,int length ,int height,char charFrame){

    /** display frame in screen with length and height made with charFrame
     **/
     int i;
     gotoxy(x,y);
     for (i=0;i<length;i++) putch(charFrame);
     for (i=1;i<height-1;i++) {
        putchxy(x,y+i,charFrame);
        putchxy(x+length-1,y+i,charFrame);
    }
     gotoxy(x,y+height-1);
     for (i=0;i<length;i++) putch(charFrame);
}
void DrawRectangle(int x,int y,int length,int height){
    /// Draw rectangle
    int i,j;
    for (i=0;i<height;i++){
        gotoxy(x,y+i);
        for (j=0;j<length;j++) putch(' ');
    }
}
void AfficheButton(const char *NomButton,int x,int y,int length,int height){
    /// display the button in the screen
     DrawRectangle(x,y,length,height);
     cputsxy(x+(length-strlen(NomButton))/2,y+(height/2),NomButton);
}
void cputsxyTemp(int x,int y,const char *chain,int Temp){
    /// print the string chain in the screen in position x and y with pause Temp ms between All char
    int i=0,n=strlen(chain);
    gotoxy(x,y);
    for (i=0;i<n;i++) {
        putch(chain[i]);
       // i++;
        Sleep(Temp);
    }


}
int AreYouSure(int x,int y){
    /// asking the user if he is sure
    struct char_info * AncienTexte;
    AncienTexte =(struct char_info*)malloc (26*7*2*sizeof(char));
    gettext (x,y,x+25,y+6,AncienTexte);
    textbackground(WHITE);
    DrawRectangle(x,y,26,7);
    textcolor(RED);
    cputsxy(x+7,y+1,"Are you Sure");
    textcolor(BLACK);
    textbackground(LIGHTCYAN);
    AfficheButton("Non",x+14,y+3,9,3);
    textbackground(BLUE);
    AfficheButton("Oui",x+3,y+3,9,3);
    int i=1,c;
    do{
    do{
        c=SaiserCntrl();
    }while(c!=13 && c!=75 && c!=77);
    if (c==13){
        break;
    }else if (i==1){
        textbackground(LIGHTCYAN);
        AfficheButton("Oui",x+3,y+3,9,3);
        textbackground(BLUE);
        AfficheButton("Non",x+14,y+3,9,3);
        i=0;
    }else{
        textbackground(BLUE);
        AfficheButton("Oui",x+3,y+3,9,3);
        textbackground(LIGHTCYAN);
        AfficheButton("Non",x+14,y+3,9,3);
        i=1;
    }
    }while(1);
    puttext (x,y,x+25,y+6,AncienTexte);
    free(AncienTexte);
    return i;
}
void AfficheErreur(int x,int y,const char *Erreur){

    /// Affiche un erreur in th screen
    textbackground(WHITE);
    textcolor(RED);
    printf("%c",7);printf("%c",7);
    Page_Temporaire(x,y,40,5,Erreur);


}
void AffichezListeChoix(const char **ch,int NbrChoix ,int num,int MaxLongueurString,int x,int y){

    /** Affichez un liste des chiox qui se trouve dans tableau ch de Nbrchoix phrase
     * la taille maximan de ces phrase est MaxLongString
     * le premier pherase se trouve dans la postion (x,y) de ecran
     * le num est un debut numeration de la pherase à affichez
     */

    int i;
    char c[5];
    for (i=0;i<NbrChoix;i++){
                /// allez à la postion (x,y+i) le premier phrase se trouve dans (x,y) et la 2 se trouva dans (x,y+1) ...

        sprintf(c,"%d- ",num+i);
        cputsxyBlanc(x,y+i,c,5);/// affichez le numeration
        cputsxyBlanc(x+5,y+i,ch[i],MaxLongueurString-5);
        }
    gotoxy(x,y);
}

void AffichezListeChoix_sans(const char **ch,int NbrChoix ,int num,int MaxLongueurString,int x,int y){

    /** Affichez un liste des chiox qui se trouve dans tableau ch de Nbrchoix phrase
     * la taille maximan de ces phrase est MaxLongString
     * le premier pherase se trouve dans la postion (x,y) de ecran
     * le num est un debut numeration de la pherase à affichez
     */

    int i;
    char c[5];
    for (i=0;i<NbrChoix;i++){
                /// allez à la postion (x,y+i) le premier phrase se trouve dans (x,y) et la 2 se trouva dans (x,y+1) ...

        cputsxyBlanc(x,y+i,ch[i],MaxLongueurString);
        }
    gotoxy(x,y);
}
int Menu(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu){

    /** Affichez Le menu
     ** return le nemero choiser
     ** return 0 c'est choiser retourner en arreire
     **/
     int Mn,chx=1,f=0;
     char c;
     Mn=Min(Hauteur,NbrPhrase); /// on prend le minimant pour affichez les choix pour evitez de soortire de cadre
     textbackground(colorbackground);
     DrawRectangle(x,y,Longueur,Hauteur);
     AffichezListeChoix(Ph+1,Mn-1,2,Longueur,x,y+1); /// affichez le reste des choix avec le Normal
     textbackground(colorMenu); /// Affichez le prmier choix avec le colorMenu
     AffichezListeChoix(Ph,1,1,Longueur,x,y);
     do {
            do{
                c=getch();
              }while((c!=-32)&&(c!=8)&&(c!=27)&&(c!=13));
             if ((c==8)||(c==27)) {
                chx=0; /// chiox pour retournez en arriere
                break;
                }
             if (c==13) break ; /// il chioser le choix selectionez
             c=getch();
             if ((c!=72)&&(c!=80)) continue;
             textbackground(colorbackground);
             if (c==72) {
             /// SI IL APPEUIYER SUR UP
              if ((f==0)&&(NbrPhrase>Mn)){
                if(chx==1) {
                    f=Mn-1;
                    AffichezListeChoix(&Ph[NbrPhrase-Mn],Mn-1,NbrPhrase-Mn+1,Longueur,x,y);
                }else AffichezListeChoix(&Ph[chx-1],Mn-1,chx,Longueur,x,y+1);
                }else {
                    AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
                    f=((f+Mn)-1)%Mn; /// decrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=((chx+NbrPhrase)-2)%NbrPhrase+1; /// decrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
            }else {
               if (c==80) {
                 if ((f==Mn-1)&&(NbrPhrase>Mn)){
                   if(chx==NbrPhrase) {
                    f=0;
                    AffichezListeChoix(&Ph[1],Mn-1,2,Longueur,x,y+1);
                      }else AffichezListeChoix(&Ph[chx-f],Mn-1,chx-f+1,Longueur,x,y);
                   }else {
                      AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
                      f=((f+Mn)+1)%Mn; /// incrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=(chx+NbrPhrase)%NbrPhrase+1; /// incrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
                }
                }
            textbackground(colorMenu); /// Affichez le prmier choix avec le color2
            AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
     }while(1);
     gotoxy(x,y);
     return chx;
}
int Menu2(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu,int select_nemero){

    /** Affichez Le menu
     ** return le nemero choiser
     **/
     int Mn,chx=select_nemero,f=0;
     char c;
     Mn=Min(Hauteur,NbrPhrase); /// on prend le minimant pour affichez les choix pour evitez de soortire de cadre
     textbackground(colorbackground);
     DrawRectangle(x,y,Longueur,Hauteur);
     textbackground(colorbackground);
     f=Max(Mn+select_nemero-NbrPhrase,1)-1;
     AffichezListeChoix(&Ph[chx-f-1],Mn,chx-f,Longueur,x,y);
     textbackground(colorMenu); /// Affichez le prmier choix avec le color2
     AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);


     do {
            do{
                c=getch();
              }while((c!=-32)&&(c!=8)&&(c!=27)&&(c!=13)&&(c!=9));
             if ((c==8)||(c==27)) {
                chx=select_nemero; /// choix pour retournez en arriere
                textbackground(colorbackground);
                f=Max(Mn+select_nemero-NbrPhrase,1)-1;
                AffichezListeChoix(&Ph[chx-f-1],Mn,chx-f,Longueur,x,y);
                textbackground(colorMenu); /// Affichez le prmier choix avec le color2
                AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
                break;
                }
             if ((c==13)||(c==9)) break ; /// il chioser le choix selectionez
             c=getch();
             if ((c!=72)&&(c!=80)&&(c!=81)&&(c!=83)&&(c!=77)&&(c!=75)) continue;
             textbackground(colorbackground);
             if (c==72) {
             /// SI IL APPEUIYER SUR UP
              if ((f==0)&&(NbrPhrase>Mn)){
                if(chx==1) {
                    f=Mn-1;
                    AffichezListeChoix(&Ph[NbrPhrase-Mn],Mn-1,NbrPhrase-Mn+1,Longueur,x,y);
                }else AffichezListeChoix(&Ph[chx-1],Mn-1,chx,Longueur,x,y+1);
                }else {
                    AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
                    f=((f+Mn)-1)%Mn; /// decrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=((chx+NbrPhrase)-2)%NbrPhrase+1; /// decrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
            }else {
               if (c==80) {
                 if ((f==Mn-1)&&(NbrPhrase>Mn)){
                   if(chx==NbrPhrase) {
                    f=0;
                    AffichezListeChoix(&Ph[1],Mn-1,2,Longueur,x,y+1);
                      }else AffichezListeChoix(&Ph[chx-f],Mn-1,chx-f+1,Longueur,x,y);
                   }else {
                      AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
                      f=((f+Mn)+1)%Mn; /// incrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=(chx+NbrPhrase)%NbrPhrase+1; /// incrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
                }else break;
                }
            textbackground(colorMenu); /// Affichez le prmier choix avec le color2
            AffichezListeChoix(&Ph[chx-1],1,chx,Longueur,x,y+f);
     }while(1);
     gotoxy(x,y);
     return chx;
}

int Menu_sans(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu){

    /** Affichez Le menu
     ** return le nemero choiser
     ** return 0 c'est choiser retourner en arreire
     **/
     int Mn,chx=1,f=0;
     char c;
     Mn=Min(Hauteur,NbrPhrase); /// on prend le minimant pour affichez les choix pour evitez de soortire de cadre
     textbackground(colorbackground);
     DrawRectangle(x,y,Longueur,Hauteur);
     AffichezListeChoix_sans(Ph+1,Mn-1,2,Longueur,x,y+1); /// affichez le reste des choix avec le Normal
     textbackground(colorMenu); /// Affichez le prmier choix avec le colorMenu
     AffichezListeChoix_sans(Ph,1,1,Longueur,x,y);
     do {
            do{
                c=getch();
              }while((c!=-32)&&(c!=8)&&(c!=27)&&(c!=13));
             if ((c==8)||(c==27)) {
                chx=0; /// chiox pour retournez en arriere
                break;
                }
             if ((c==13)||(c==9)) break ; /// il chioser le choix selectionez
             c=getch();
             if ((c!=72)&&(c!=80)) continue;
             textbackground(colorbackground);
             if (c==72) {
             /// SI IL APPEUIYER SUR UP
              if ((f==0)&&(NbrPhrase>Mn)){
                if(chx==1) {
                    f=Mn-1;
                    AffichezListeChoix_sans(&Ph[NbrPhrase-Mn],Mn-1,NbrPhrase-Mn+1,Longueur,x,y);
                }else AffichezListeChoix_sans(&Ph[chx-1],Mn-1,chx,Longueur,x,y+1);
                }else {
                    AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
                    f=((f+Mn)-1)%Mn; /// decrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=((chx+NbrPhrase)-2)%NbrPhrase+1; /// decrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
            }else if (c==80) {
                 if ((f==Mn-1)&&(NbrPhrase>Mn)){
                   if(chx==NbrPhrase) {
                    f=0;
                    AffichezListeChoix_sans(&Ph[1],Mn-1,2,Longueur,x,y+1);
                      }else AffichezListeChoix_sans(&Ph[chx-f],Mn-1,chx-f+1,Longueur,x,y);
                   }else {
                      AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
                      f=((f+Mn)+1)%Mn; /// incrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=(chx+NbrPhrase)%NbrPhrase+1; /// incrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
                }else break;

            textbackground(colorMenu); /// Affichez le prmier choix avec le color2
            AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
     }while(1);
     gotoxy(x,y);
     return chx;
}
int Menu2_sans(const char **Ph,int NbrPhrase,int x,int y,int Longueur,int Hauteur,int colorbackground,int colorMenu,int select_nemero){

    /** Affichez Le menu
     ** return le nemero choiser
     **/
     int Mn,chx=select_nemero,f=0;
     char c;
     Mn=Min(Hauteur,NbrPhrase); /// on prend le minimant pour affichez les choix pour evitez de soortire de cadre
     textbackground(colorbackground);
     DrawRectangle(x,y,Longueur,Hauteur);
     textbackground(colorbackground);
     f=Max(Mn+select_nemero-NbrPhrase,1)-1;
     AffichezListeChoix_sans(&Ph[chx-f-1],Mn,chx-f,Longueur,x,y);
     textbackground(colorMenu); /// Affichez le prmier choix avec le color2
     AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);


     do {
            do{
                c=getch();
              }while((c!=-32)&&(c!=8)&&(c!=27)&&(c!=13)&&(c!=9));
             if ((c==8)||(c==27)) {
                chx=select_nemero; /// choix pour retournez en arriere
                textbackground(colorbackground);
                f=Max(Mn+select_nemero-NbrPhrase,1)-1;
                AffichezListeChoix_sans(&Ph[chx-f-1],Mn,chx-f,Longueur,x,y);
                textbackground(colorMenu); /// Affichez le prmier choix avec le color2
                AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
                break;
                }
             if ((c==13)||(c==9)) break ; /// il chioser le choix selectionez
             c=getch();
             if ((c!=72)&&(c!=80)&&(c!=81)&&(c!=83)&&(c!=77)&&(c!=75)&&(c!=9)) continue;
             textbackground(colorbackground);
             if (c==72) {
             /// SI IL APPEUIYER SUR UP
              if ((f==0)&&(NbrPhrase>Mn)){
                if(chx==1) {
                    f=Mn-1;
                    AffichezListeChoix_sans(&Ph[NbrPhrase-Mn],Mn-1,NbrPhrase-Mn+1,Longueur,x,y);
                }else AffichezListeChoix_sans(&Ph[chx-1],Mn-1,chx,Longueur,x,y+1);
                }else {
                    AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
                    f=((f+Mn)-1)%Mn; /// decrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=((chx+NbrPhrase)-2)%NbrPhrase+1; /// decrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
            }else {
               if (c==80) {
                 if ((f==Mn-1)&&(NbrPhrase>Mn)){
                   if(chx==NbrPhrase) {
                    f=0;
                    AffichezListeChoix_sans(&Ph[1],Mn-1,2,Longueur,x,y+1);
                      }else AffichezListeChoix_sans(&Ph[chx-f],Mn-1,chx-f+1,Longueur,x,y);
                   }else {
                      AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
                      f=((f+Mn)+1)%Mn; /// incrimanter le f mais il dois restez sur intervale 0 .. Hauteur-1
                }
                chx=(chx+NbrPhrase)%NbrPhrase+1; /// incrimanter le chx mais il dois restez sur intervale 1 .. NbrPhrase
                } else break;
                }
            textbackground(colorMenu); /// Affichez le prmier choix avec le color2
            AffichezListeChoix_sans(&Ph[chx-1],1,chx,Longueur,x,y+f);
     }while(1);
     gotoxy(x,y);
     return chx;
}
int SaiserCtrlText(void){
    /** attendre que utilisateur taper les touch du controlle text comme cntrl F .. et ignore les autres
     ** return le code du touch
     **/
    unsigned char toucheClavier,toucheClavier1;
    do{
    toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            toucheClavier1=getch();
            if (toucheClavier==224){
                if (toucheClavier1==75 || toucheClavier1==77 || toucheClavier1==73 || toucheClavier1==81 || toucheClavier1==80 || toucheClavier1==72 || toucheClavier1==71 || toucheClavier1==79 || toucheClavier1==61){
                    return toucheClavier1;
                }
            }
       }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13 || toucheClavier==8 || toucheClavier==6 || toucheClavier==32){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier;
        }
    }while(1);
    return -1;
}
int Input_Area_Number(char* Number,int CooredonneX,int CooredonneY,int maxlength,int maxLength_Line){

    /** Defines a multi line Number
     ** il return la camande qui la fait sortir comme entre
     **/
    unsigned char toucheClavier,toucheClavier1;
    int NbrChiffre=strlen(Number);
    int i=NbrChiffre;
    cputsxyAreaBlanc(CooredonneX,CooredonneY,Number,maxlength/maxLength_Line+1,maxLength_Line,"0123456789");
    do{
        gotoxy(CooredonneX+i%maxLength_Line,CooredonneY+i/maxLength_Line);
        toucheClavier=getch();
        if (toucheClavier==0 || toucheClavier==224){
            // on lit les touch des clavier qui a deux code
            toucheClavier1=getch();
            if (toucheClavier==224 && toucheClavier1==75){
                // touch clavier est touch lift
                if (i>0) i--; // on decremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==77){
                // touch clavier est touch right
                if (i<NbrChiffre) i++; // on incremante la postiion du la curseur
            }else if (toucheClavier==224 && toucheClavier1==79){
                // touch clavier est touch Fin de Line
                i=NbrChiffre; // on postiionne la curseur a la fin de la line
            }else if (toucheClavier==224 && toucheClavier1==71){
                // touch clavier est touch Debut de Line
                i=0; // on postiionne la curseur a la debut de la line
            }else if (toucheClavier==224 && toucheClavier1==83){
                // touch clavier est touch suppr inser
            if (i<NbrChiffre){
                StrSuppChar(Number,i);// on supprime le cractere de la postion i
                cputsxyAreaBlanc(CooredonneX,CooredonneY,Number,NbrChiffre/maxLength_Line+1,maxLength_Line,"0123456789");
                NbrChiffre--;
            }else printf("%c",7);
            }else if (toucheClavier==224 && (toucheClavier1==80 || toucheClavier1==72)){
                // touch clavier est touch up ou down
                if (toucheClavier1==80) {
                    i=NbrChiffre+maxLength_Line;
                    if (i>NbrChiffre) i=NbrChiffre;
                }else {
                    i=NbrChiffre-maxLength_Line;
                    if (i<0) i=0;
                }
            }else if (toucheClavier==224 && (toucheClavier1==73 || toucheClavier1==81)){
                // page suivant ou precedant
                return toucheClavier1; // on sort du la fonction avec return du le touch qui fait sortire
            }
        }else if(iscntrl(toucheClavier)){
        if (toucheClavier==8){
            // touch supp
            if (i>0){
                StrSuppChar(Number,--i);// on supprime le cractere de la postion i-1
                cputsxyAreaBlanc(CooredonneX,CooredonneY,Number,NbrChiffre/maxLength_Line+1,maxLength_Line,"0123456789");
                NbrChiffre--;
            }else printf("%c",7);
        }else if (toucheClavier==9 || toucheClavier==27 || toucheClavier==13){
            // si les touch entres ou echap ou -- on sort de la fonction
               return toucheClavier; // on sort du la fonction avec return du le touch qui fait sortire
        }
        }else if (isdigit(toucheClavier)){
             if (NbrChiffre<maxlength){
                StrInsertChar(Number,(char)toucheClavier,i++);// on Insert le cractere toucheClavier a la postion i
                cputsxyArea(CooredonneX,CooredonneY,Number,maxLength_Line,"0123456789");
                NbrChiffre++;
             }else printf("%c",7);
        }
    }while(1);
    return -1;
}
void chargerA(int x,int y,int pl){
    gotoxy(x+50,y-1);
    printf("%02d%%",pl);
    DrawRectangle(x,y,pl,2);
}

int Input_Date(int *jour,int *mois,int *annee,int x,int y){

    /** Defines a date
     ** il return la camande qui la fait sortire comme entre ou up ou down
     **/
     textcolor(BLACK);
     textbackground(WHITE);
    unsigned char toucheClavier,toucheClavier1;
    int i,j=*jour,m=*mois,a=*annee,NumbreInput=1,c=0;
    char Year[4]="\0",Day[3]="\0";
    sprintf(Year,"%04d",*annee);
    sprintf(Day,"%02d",*jour);
    char*  Les_Mois[] = { "janvier","fevrier","mars","avril","mai","juin","juillet","aout","septembre","octobre","novembre","decembre"};
    cputsxy(x,y,"                      ");
    gotoxy(x,y);
    printf("%s  %s",Day,Les_Mois[m-1]);
    cputsxy(x+15,y,Year);
    do{
        if (NumbreInput>0 && NumbreInput<4){

            if (NumbreInput==1){
                // jour
                c=Input_Number(Day,x,y,2);

            }else if (NumbreInput==2){
                // mois
                m=Menu2_sans(Les_Mois,12,x+4,y,10,1,WHITE,WHITE,m);

            }else if (NumbreInput==3){
                // annee
                c=Input_Number(Year,x+15,y,4);

            }
            if (c==13 || c==27 ||(c==80 || c==81 || c==72 || c==73)){

                if (!(Year[0] && Day[0] && m)) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in required inputs.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    NumbreInput=1;
                    continue;
                }
                sscanf(Year,"%d",&a);sscanf(Day,"%d",&j);
                if (j>maxjour(a,m) || j<1){
                    char ch[100];
                    sprintf(ch,"Le Date %02d/%02d n'existe pas cette mois a %d jours ",j,m,maxjour(a,m));
                    AfficheErreur(x+5,y+5,ch);
                    textcolor(BLACK);
                    textbackground(WHITE);
                    NumbreInput=1;
                    continue;
                }
                (*annee)=a;(*mois)=m;(*jour)=j;

                    return c;
            }else if (c==9) {
                NumbreInput++;
                if (NumbreInput==4) NumbreInput=1;
            }
        }
    }while(1);



    return -1;
}

#endif
