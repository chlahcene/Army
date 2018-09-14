#include "TP.h"
int KJ=0;
void cputsxyTemp(int x,int y,const char *chain,int Temp){
    /// print the string chain in the screen in position x and y with pause Temp ms between All char
    int i=0;
    gotoxy(x,y);
    while(chain[i]!=0){
        putch(chain[i++]);
        //Sleep(Temp);
    }

}
void rechar_mat(L7OVC *F,const char* nom)
{
    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    int x=35,y=2,i;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+3,"Recharche par matricule");
    textcolor(WHITE);
    cputsxy(x,y+7,"matricule");
    textbackground(WHITE);
    DrawRectangle(x,y+9,20,2);
    int c=0;
    char Nouveau_Nom[48]="\0";
    textbackground(WHITE);
    textcolor(BLACK);
    long int s=0;
    do{
    c=Input_Number(Nouveau_Nom,x,y+9,6);
    if (c==27) if (AreYouSure(30,20)) return 1;
        if (c==13)
            if (Nouveau_Nom[0]==0) {// This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in the input they are required.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
            s=atoll(Nouveau_Nom);
            if(s<111111 || s>999999){
                    AfficheErreur(x+5,y+5,"Le nombre doit etre entre 111111 et 999999.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
            }
            break;
    }while(1);
    char ch[100];
    sprintf(ch,"Data//%s_index_Primaire",nom);
    TOF* F1=ouvrirTOF(ch,'A');
    consulter_eng(F,F1,nom,s);
}
int recuper_eng(L7OVC *F,TOF *FTOF,long int cle,enrg_L7OVC *A){
    int i,j,trouve;
    char ch[1000];
    TblocTOF buff;
    Buffer_L7OVC buf;
    recherche_TOF(FTOF,cle,&trouve,&i,&j);

    if (trouve==1){
        liredirTOF(FTOF, i, &buff);
        i=buff.T[j].bloc;
        j=buff.T[j].indice_bloc;
        liredir_L7OVC(F,i,&buf);
        recuperer_chaine_enrg(F,&i,&j,ch,&buf); // on commence a recuperer les enregistrememnt un a un
        turn_string_to_enrg(A,ch);
        return 1;
    }
    return 0;
}
int consulter_eng(L7OVC *F,TOF *FTOF,const char* Nom_Fichier,long int cle){
    textbackground(BLACK);
    textcolor(WHITE);
    system("CLS");
    enrg_L7OVC A;
    if (recuper_eng(F,FTOF,cle,&A)){
        Affiche_ENG(A);
        int i;
        int s=3;
        char*  S[] = {
                     "Modifier",
                     "Supprimer",
                     "retourner en arriere"
                     };
            textbackground(BLACK);
            system("CLS");
            textbackground(WHITE);
            textcolor(GREEN);
            FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
            textcolor(BLACK);
            i=Menu(S,s,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
            if (i==1){
                lire_ENG(&A,F,Nom_Fichier,1);
            }else if (i==2){
                suppression_logique(Nom_Fichier,F,A.cle);
                    textbackground(BLACK);
    textcolor(WHITE);
    system("CLS");
                printf("\n\n \t\t Le suppmriion terminer avec sucess \n\t");
                system("PAUSE");
            }
            return 1;
    }else {
                textbackground(BLACK);
                textcolor(WHITE);
                system("CLS");
                printf("\n\n \t\t Le matricule n'existe pas \n\t");
                system("PAUSE");
            }


    return 0;



}
int Consulter(const char* nom,L7OVC *F,TOF *FTOF,const char* Nom_Fichier)
{
    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    FILE* F1=fopen(nom,"rb");
    long int nb=0,T[100];
    fread(&nb,sizeof(nb),1,F1);
    printf("\n\tLe Nombre des resultats trouver est %d\n\n\t",nb);
    if (nb==0){
        fclose(F1);
        return 0;
    }
    system("PAUSE");
    int i;
    int a=3,s=2,j;
    char*  S[] =    {
                     "Supprimer tous",
                     "traiter un par un "
                     };
    char*  A[100];
    for (i=0;i<100;i++) A[i]=malloc(sizeof(char)*10);
                  textbackground(BLACK);
                  system("CLS");
                  textbackground(WHITE);
                  textcolor(GREEN);
                  FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
                  textcolor(BLACK);
    i=Menu(S,s,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
    if (i==0) {
            fclose(F);
            return 1;
    }
    if (i==1){
        textbackground(BLACK);
        system("CLS");
        textcolor(WHITE);
        printf("\n\t  Le supprition est en cours de excution patienter ... \n\n\t");
        fseek(F1,sizeof(nb),SEEK_SET);
        do{
            i=fread(T,sizeof(nb),100,F1);
            for (j=0;j<i;j++){
                suppression_logique(Nom_Fichier,F,T[j]);
            }
        }while(feof(F1)!=0);
        printf("\n\t  Le supprition est terminer ... \n\n\t");
        system("PAUSE");
        fclose(F1);
        return 1;

    }else if (i==2){
        int c=75,b1=100;
        do{
            if(c==75){
                b1=Max(0,b1-100);

            }else if (c==77){
                b1=Min(nb,b1+100);
            }
            if (c==75 || c==77){
                fseek(F1,sizeof(nb)*(b1+1),SEEK_SET);
                a=fread(T,sizeof(nb),100,F1);
                for (i=0;i<a;i++) sprintf(A[i],"%ld",T[i]);
                i=1;
            }
                  textbackground(BLACK);
                  system("CLS");
                  textbackground(WHITE);
                  textcolor(GREEN);
                  FrameRectangle(PX-1,PY-1,42,HTR+2,4);
                  textcolor(BLACK);
            i=Menu3_sans(A,a,PX,PY,40,HTR,WHITE,LIGHTGRAY,i,&c);
            if (c==13){
                if (i==0) {
                        fclose(F1);
                        return 1;
                }
                consulter_eng(F,FTOF,Nom_Fichier,T[i-1]);
            }

        }while(1);
    }


}
int search_file(const char *nom,long int nombre)
{
    int i,trouve=0,j;
    FILE* F=fopen(nom,"rb");
    long int nb=0,T[1000];
    fread(&nb,sizeof(nb),1,F);
    do{
        i=fread(T,sizeof(nb),1000,F);
        for (j=0;j<i;j++){
            //printf("%d %d -- %d -- %d \n",nombre,j,i,T[j]);
            if (T[j]==nombre){
                trouve=1;
                break;
            }
        }

    }while(i!=0 && trouve==0);
    fclose(F);
    //system("PAUSE");
    return trouve;

}
void Intersection(const char* nom_fichier,char **liste_fichier,int n)
{
    if (n>1){
            int i,j,k1=1,l;
        FILE* F=fopen(nom_fichier,"wb+");
        FILE* F1=fopen(liste_fichier[0],"rb");
        long int nb=0,s=0,nb_res=0,k=0,T[1000],T1[1000];
        fwrite(&nb,sizeof(nb),1,F);
        fread(&nb,sizeof(nb),1,F1);
        //printf("\n\n\tle nombre est %d",nb);
        for (;k1!=0;)
        {

            k1=fread(T1,sizeof(s),1000,F1);
           // printf("%d -- %d\n",k,s);
            for (l=0;l<k1;l++){
                for (j=1;j<n;j++){
                if (search_file(liste_fichier[j],T1[l])==0){
                    break;
                }
            }
            if (j>=n){

                T[k++]=T1[l];
                if (k==1000){
                    nb_res+=k;
                    fwrite(T,sizeof(k),k,F);
                    k=0;
                }
            }
            }

        }
        nb_res+=k;
        fwrite(T,sizeof(k),k,F);
        fseek(F,0,SEEK_SET);
        fwrite(&nb_res,sizeof(nb_res),1,F);
        fclose(F);
        fclose(F1);


    }



}
void ajoute_cle_resulte(FILE *F,TnOF *F1,Index_sec_adr I)
{
    //printf("%d\n",++KJ);
    int i=I.bloc,j=I.indice_bloc;
    int i1=0,j1=0,n=0;
    long int K=0,L=0;
    long int T[1000];
    fseek(F,0,SEEK_SET);
    fread(&L,sizeof(K),1,F);
    //printf("L = %d\n",L);
    fseek(F,sizeof(K)*(L+1),SEEK_SET);
    TblocTnOF buf;

    while(i!=-1){

        if (i!=i1){
            liredirTnOF(F1,i,&buf);
            i1=i;
        }
        if (buf.T[j].efface==0) T[n++]=buf.T[j].cle;
        i=buf.T[j].suiv_bloc;
        j=buf.T[j].suiv_indice_bloc;
        if (n==1000){
            fwrite(T,sizeof(K),n,F);
            K+=n;
            n=0;
        }
    }
    K+=n;
    fwrite(T,sizeof(K),n,F);
    fseek(F,0,SEEK_SET);
    K+=L;
    //printf("%d \n",K);
    fwrite(&K,sizeof(K),1,F);
    /*fseek(F,0,SEEK_SET);
    fread(&L,sizeof(K),1,F);
    printf("L = %d\n",L);*/
}
void Recharche_fichier(L7OVC *F,const char* Nom_Fichier,int mn,int mx,int *ForceArmee,int *Region,int *Grade)
{
    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    printf("\n\t Le Le recharche est en cours de excution patainter ... \n\n\t");
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
        fclose(Table_Index);
        int i2=0,j2=0;
        TnOF *FY,*FF,*FG,*FR;EnregTnOF eng_tnof;
        char* tab_result[5];
        FILE* F_result=fopen("Data//result1","wb+");
        long int nb_result=0;
        fwrite(&nb_result,sizeof(nb_result),1,F_result);
        sprintf(tmp_chain,"Data//%s_index_Sec_Year",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'A');
        // index year
        if (mn>mx){
            i2=mn;mn=mx;mx=i2;
        }
        int i;
        int B1=Max(mn-1940,0);
        int B2=Min(mx-1940,60);
        //Affiche_Index_Tnof(FY,tab_Year,60);
        for (i=B1;i<=B2;i++){
            ajoute_cle_resulte(F_result,FY,tab_Year[i]);
        }
        fermerTnOF(FY);
        tab_result[0]=malloc(10*sizeof(char));strcpy(tab_result[0],"Data//result1");
        fclose(F_result);
        F_result=fopen("Data//result2","wb+");
        nb_result=0;
        fwrite(&nb_result,sizeof(nb_result),1,F_result);
        sprintf(tmp_chain,"Data//%s_index_Sec_Force_Armee",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'A');
        //Affiche_Index_Tnof(FY,tab_Force,8);
        for (i=0;i<8;i++){
            if (ForceArmee[i]==1) ajoute_cle_resulte(F_result,FY,tab_Force[i]);
           // else printf("FA |%d %d| ",i,ForceArmee[i]);
        }
        fermerTnOF(FY);
        tab_result[1]=malloc(10*sizeof(char));strcpy(tab_result[1],"Data//result2");
        fclose(F_result);

        F_result=fopen("Data//result3","wb+");
        nb_result=0;
        fwrite(&nb_result,sizeof(nb_result),1,F_result);
        sprintf(tmp_chain,"Data//%s_index_Sec_Grade",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'A');
        //Affiche_Index_Tnof(FY,tab_Grade,17);
        for (i=0;i<17;i++){
            if (Grade[i]==1) ajoute_cle_resulte(F_result,FY,tab_Grade[i]);
           // else printf("G |%d %d| ",i,Grade[i]);
        }
        fermerTnOF(FY);
        tab_result[2]=malloc(10*sizeof(char));strcpy(tab_result[2],"Data//result3");
        fclose(F_result);

        F_result=fopen("Data//result4","wb+");
        nb_result=0;
        fwrite(&nb_result,sizeof(nb_result),1,F_result);
        sprintf(tmp_chain,"Data//%s_index_Sec_Region",Nom_Fichier);
        FY=ouvrirTnOF(tmp_chain,'A');
        //Affiche_Index_Tnof(FY,tab_Region,6);
        for (i=0;i<6;i++){
            if (Region[i]==1) ajoute_cle_resulte(F_result,FY,tab_Region[i]);
           // else printf("R |%d %d| ",i,Region[i]);
        }
        fermerTnOF(FY);
        tab_result[3]=malloc(10*sizeof(char));strcpy(tab_result[3],"Data//result4");
        fclose(F_result);

        Intersection("Data//resulte finale",tab_result,4);
        TOF *FTOF;
        sprintf(tmp_chain,"Data//%s_index_Primaire",Nom_Fichier);
        FTOF=ouvrirTOF(tmp_chain,'A');
        Consulter("Data//resulte finale",F,FTOF,Nom_Fichier);
        for (i=0;i<4;i++) {
            remove(tab_result[i]);
            //free(tab_result[i]);
        }
        fermer_TOF(FTOF);


}


void Recharche(L7OVC *F,const char* Nom_Fichier)
{
     textbackground(BLACK);
     system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=35,y=2,color=LIGHTGRAY;
    //long int mat=A->cle;
    int i1=y+4,i2=y+9,i3=y+20,i4=y+28,i10=y+44;
    textcolor(LIGHTBLUE);
    char bot[30];

        cputsxy(x+10,y,"Recharchez");
        strcpy(bot," Recharchez ");

    textbackground(WHITE);
    textcolor(GREEN);
    cputsxy(x,i1-1,"Age");
    cputsxy(x,i1+2,"MIN");
    cputsxy(x+14,i1+2,"MAX");
    cputsxy(x,i2,"Force Armee ");
    cputsxy(x,i3,"Region Militaire  ");
    cputsxy(x,i4,"Grade ");
    textbackground(WHITE);
    textcolor(BLACK);
    DrawRectangle(x+6,i1+1,6,2);
    DrawRectangle(x+20,i1+1,6,2);
//  force armee
    int FA[10][max_input_radio],chFA[10][max_input_radio],j;
    for (j=0;j<4;j++){
        FA[j][0]=i2+2*(j+1);// corrodonner y
        FA[j][1]=2;// nombre choix dans y
        FA[j][2]=x+1;FA[j][3]=x+50;
        textbackground(WHITE);
        textcolor(BLACK);
        gotoxy(FA[j][2],FA[j][0]);printf("%c",251);
        gotoxy(FA[j][3],FA[j][0]);printf("%c",251);
        textbackground(BLACK);
        textcolor(WHITE);
        cputsxy(FA[j][2]+2,FA[j][0],FORCE_ARMEE[j*2]);
        chFA[j][0]=1;

        cputsxy(FA[j][3]+2,FA[j][0],FORCE_ARMEE[j*2+1]);
        chFA[j][1]=1;
    }
//  Region militaire
    int RM[10][max_input_radio],chRM[10][max_input_radio];
    for (j=0;j<2;j++){
        RM[j][0]=i3+2*(j+1);// corrodonner y
        RM[j][1]=3;// nombre choix dans y
        RM[j][2]=x+1;RM[j][3]=x+20;RM[j][4]=x+40;
        textbackground(WHITE);
        textcolor(BLACK);
        gotoxy(RM[j][2],RM[j][0]);printf("%c",251);
        gotoxy(RM[j][3],RM[j][0]);printf("%c",251);
        gotoxy(RM[j][4],RM[j][0]);printf("%c",251);
        textbackground(BLACK);
        textcolor(WHITE);
        cputsxy(RM[j][2]+2,RM[j][0],REGION_MILITAIRE[j*3]);
        chRM[j][0]=1;

        cputsxy(RM[j][3]+2,RM[j][0],REGION_MILITAIRE[j*3+1]);
        chRM[j][1]=1;

        cputsxy(RM[j][4]+2,RM[j][0],REGION_MILITAIRE[j*3+2]);
        chRM[j][2]=1;
    }
//  GRADE
    int GR[10][max_input_radio],chGR[10][max_input_radio];
        GR[0][0]=i4+2;// corrodonner y
        GR[0][1]=2;// nombre choix dans y
        GR[0][2]=x+1;GR[0][3]=x+30;
        textbackground(WHITE);
        textcolor(BLACK);
        gotoxy(GR[0][2],GR[0][0]);printf("%c",251);
        gotoxy(GR[0][3],GR[0][0]);printf("%c",251);
        textbackground(BLACK);
        textcolor(WHITE);
        cputsxy(GR[0][2]+2,GR[0][0],GRADE[0]);
        chGR[0][0]=1;

        cputsxy(GR[0][3]+2,GR[0][0],GRADE[1]);
        chGR[0][1]=1;
    for (j=1;j<6;j++){
        GR[j][0]=i4+2*(j+1);// corrodonner y
        GR[j][1]=3;// nombre choix dans y
        GR[j][2]=x+1;GR[j][3]=x+20;GR[j][4]=x+40;
        textbackground(WHITE);
        textcolor(BLACK);
        gotoxy(GR[j][2],GR[j][0]);printf("%c",251);
        gotoxy(GR[j][3],GR[j][0]);printf("%c",251);
        gotoxy(GR[j][4],GR[j][0]);printf("%c",251);
        textbackground(BLACK);
        textcolor(WHITE);
        cputsxy(GR[j][2]+2,GR[j][0],GRADE[j*3-1]);
        chGR[j][0]=1;

        cputsxy(GR[j][3]+2,GR[j][0],GRADE[j*3]);
        chGR[j][1]=1;

        cputsxy(GR[j][4]+2,GR[j][0],GRADE[j*3+1]);
        chGR[j][2]=1;
    }


    textbackground(LIGHTCYAN);
    textcolor(WHITE);
    AfficheButton(bot,x,i10,20,3);
    int NumbreInput=1;
    int c=0;
    char mn[48]="19",mx[48]="78",ch[100];
    textbackground(WHITE);
    textcolor(BLACK);
    cputsxy(x+6,i1+2,mn);
    cputsxy(x+20,i1+2,mx);

    do{
        if (NumbreInput>0 && NumbreInput<6){

            if (NumbreInput==1){
                // min
                c=Input_Number(mn,x+6,i1+2,2);

            }else if (NumbreInput==2){
                // max
                c=Input_Number(mx,x+20,i1+2,2);

            }else if (NumbreInput==3){
                // Force Armee
                c=Input_radio(FA,chFA,4);

            }else if (NumbreInput==4){
                // Region Militaire
                c=Input_radio(RM,chRM,2);

            }else if (NumbreInput==5){
                // GRADE
                c=Input_radio(GR,chGR,6);

            }
            if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
            else if (c==72 || c==73) {
                NumbreInput--;
                if (NumbreInput==0) NumbreInput=10;
            }
        }else if (NumbreInput==6){
            // Button Create new account
            textbackground(BLUE);
            textcolor(WHITE);
            AfficheButton(bot,x,i10,20,3);
            do{
                c=SaiserCntrl();
            }while(c==75 || c==77 ); // car here touch left and right ne fait rien
            if (c==13){
                // here est create new account
                if (!(mn[0] && mx[0])) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in required inputs.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                int i;
                int ForceArmee[20],Region[20],Grade[20];
                for (i=0;i<4;i++) {
                    ForceArmee[i*2]=chFA[i][0];
                    ForceArmee[i*2+1]=chFA[i][1];
                }
                for (i=0;i<2;i++) {
                    Region[i*3]=chRM[i][0];
                    Region[i*3+1]=chRM[i][1];
                    Region[i*3+2]=chRM[i][2];
                }
                    Grade[0]=chGR[0][0];
                    Grade[1]=chGR[1][1];
                for (i=1;i<6;i++) {
                    Grade[i*3-1]=chGR[i][0];
                    Grade[i*3]=chGR[i][1];
                    Grade[i*3+1]=chGR[i][2];
                }
                Recharche_fichier(F,Nom_Fichier,2018-atoi(mn),2018-atoi(mx),ForceArmee,Region,Grade);
                system("PAUSE");
                return 0;
            }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
             else if (c==72 || c==73) NumbreInput=9;
            textbackground(LIGHTCYAN);
            AfficheButton(bot,x,i10,20,3);
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



int main()
{
    system("mode con LINES=10000 COLS=130");
 /*   int co[10][max_input_radio];
    int ch[10][max_input_radio];
    co[0][1]=2;co[0][2]=2;co[0][3]=25;co[0][0]=2;
    co[1][1]=2;co[1][2]=3;co[1][3]=25;co[1][0]=4;
    Input_radio(co,ch,2);
//    co={{2,2,2,30},{4,2,3,35}};
    ch[0][0]=1;ch[0][1]=0;
    ch[1][1]=1;ch[1][0]=0;
  //  ch={{1,0},{0,1}};
    printf("\n    lahcene  \t\t  bekaceme\n");
    printf("\n    karime  \t\t  mh");
    do{

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
    /*getch();
    cputsxyTemp(14,12,"fklsjglksdjgkljsdqklgjdsqklgjsdkl",10);
    getch();*/
    ChioxMenu();




    return 0;
}

void ChioxMenu(){
    int i;
    int a=4,s=3;
    char*  S[] =    {
                     "Creer Fichier",
                     "consulter fichier ",
                     "Quitter Le Programme"
                     };
    char*  A[] =    {
                     "Ajouter Nouveau venu",
                     "Recharche, consulter, modifier, supprimer",
                     "recharhce par matricule",
                     "Stats et structure"
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
                        printf("\t Patainter un peu ...\n");
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
                                eng_lnovc.cle=111111;
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
                                eng_lnovc.Info.Wilaya_Naissance=16;
                                lire_ENG(&eng_lnovc,F_lovc,nom_fichier,0);



                              }else if (i==2){
                                //Recharche

                                system("CLS");
                                /*char tmp_chain[100];
                                sprintf(tmp_chain,"Data//%s_index_Primaire",nom_fichier);
                                TOF* F1=ouvrirTOF(tmp_chain,'A');*/
                                Recharche(F_lovc,nom_fichier);
                               /* Affiche_TOF(F1);
                                fermer_TOF(F1);
                                system("PAUSE");
                                system("CLS");
                                afficher_fichier_lonvc(F_lovc);*/
                              }else if (i==3){
                               // recharche
                               system("CLS");
                                rechar_mat(F_lovc,nom_fichier);
                              }else if (i==4){
                               // Stat et structure
                                Affiche_state(nom_fichier,F_lovc);
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
