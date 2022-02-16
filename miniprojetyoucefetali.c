#include <stdio.h>
#include <stdlib.h>
#include<string.h>
 typedef struct
{
int jour;
int mois;
int annee;

}date;
typedef struct
{double matricule;
 char typeabo;
 int penalite;
    int cote;
}file;

typedef file Telm;


//déclaration de la File
typedef struct Element* EFile;
typedef struct Element { Telm  Val; EFile Suiv} CelluleF;
typedef struct {EFile Tete,Queue;} File;

////primitives des Files
//procedure Initfile
void Initfile(File *F)
{(*F).Tete=NULL; (*F).Queue=NULL;}

//procedure Enfiler
void Enfiler(File *F, Telm x)
{EFile V;
 V=malloc(sizeof(CelluleF));
 V->Val=x;
 V->Suiv=NULL;
 if ((*F).Tete==NULL) (*F).Tete=V; //la file est vide
 else (*F).Queue->Suiv=V;
 (*F).Queue=V;
}

//procedure Defiler
void Defiler(File *F, Telm *x)
{EFile V;
 V=(*F).Tete;
 *x=V->Val;
 if ((*F).Tete==(*F).Queue) {(*F).Tete=NULL; (*F).Queue=NULL;}
 else (*F).Tete=(*F).Tete->Suiv;
 free(V);
}

//Fonction Filevide
int Filevide(File F)
{if (F.Tete==NULL) return 1;
 else return 0;
}

//Fonction Tetefile
Telm Tetefile(File F)
{return F.Tete->Val;}



typedef struct pliste1 *ouvrages;
typedef struct pliste1
{
    int cote;
    char titre[50];
    int nbexemplaireb;
    int nbexemplairepreter;
    ouvrages svt1,pcd1;
}louvrage;
typedef struct pliste2 *etudiant;
typedef struct pliste2
{
    double matricule;
char typeabo;
int penalite;
etudiant svt2,pcd2;
}letudiant;
typedef struct pliste3 *emprunts;
typedef struct pliste3{
double matricule;
int cote;
 date dateemprunt;
 date dateretour;
 emprunts svt3,pcd3;
}louvrageemprunter;
//***************************************************
void calculduree(date x,date *y,int z)
{ switch(x.mois)
{   case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:{
    (*y).jour=x.jour+z; if((*y).jour>31)
{
    (*y).jour=(x.jour+z)%31;
    (*y).mois=x.mois + 1;
     if((*y).mois>12)
        {
        (*y).mois=(*y).mois%12;
          (*y).annee=x.annee+1;}
    else(*y).annee=x.annee;

}
else{
(*y).mois=x.mois;
(*y).annee=x.annee;
}
}break;
    case 4:
    case 6:
    case 9:
    case 11:{
    (*y).jour=x.jour+z; if((*y).jour>30)
{
    (*y).jour=(x.jour+z)%30;
    (*y).mois=x.mois + 1;
    (*y).annee=x.annee;

}
else{
(*y).mois=x.mois;
(*y).annee=x.annee;
}
}break;
case 2:{(*y).jour=x.jour+z;
if((*y).jour>28)
{
    (*y).jour=(x.jour+z)%28;
    (*y).mois=x.mois + 1;
    (*y).annee=x.annee;

}
else{
(*y).mois=x.mois;
(*y).annee=x.annee;
}
}break;
}
}
//****************************************************
//suprimer ouvrage
void suppdebut(ouvrages *l)
{
ouvrages t;
 if((*l)!=NULL)
 { if((*l)->svt1==NULL)
 {
     free(*l);
     (*l)=NULL;
 }
 else
 {
     t=*l;
     (*l)=(*l)->svt1;
     (*l)->pcd1=NULL;
     free(t);

 }

 }
}
 void suppfin(ouvrages *q)
 {ouvrages p;
     if((*q)!=NULL)
     {
         if((*q)->pcd1==NULL)
         {
             free(*q);
             (*q)=NULL;

         }
         else
         {
             p=*q;
             (*q)=(*q)->pcd1;
             (*q)->svt1=NULL;
             free(p);


         }
     }
 }
 //ajouter ouvrage
 void insertfin(ouvrages l,int x,char s[50],int y,int z)
{
    ouvrages p,q;
q=l;
 while(q->svt1!=NULL)
{
    q=q->svt1;
}
 p=malloc(sizeof(louvrage));
p->cote=x;
strcpy(p->titre,s);
p->nbexemplaireb=y;
p->nbexemplairepreter=z;

  p->pcd1=q;
 p->svt1=NULL;
q->svt1=p;
q=p;

}
void ajoutouvrage(ouvrages *l,int x,char s[50],int y,int z)
{
    ouvrages p,q;
if((*l)==NULL)
{
    p=malloc(sizeof(louvrage));
p->cote=x;
strcpy(p->titre,s);
p->nbexemplaireb=y;
p->nbexemplairepreter=z;
   p->pcd1=NULL;
   p->svt1=NULL;
   (*l)=p;


}
else{
    insertfin(*l,x,s,y,z);
}
}
//consultation ouvrage
void consulterouvrage(ouvrages l)
{
    ouvrages p;
 p=l;
 if(p!=NULL)
 {
    while(p!=NULL)
    { printf("---------------------------------\n");
printf("cote:%d\ntitre:%s\nnombre d'exemplaire bibliotheque:%d\nnombre d'exemplaire emmprunter:%d\n",p->cote,p->titre,p->nbexemplaireb,p->nbexemplairepreter);
      printf("----------------------------------\n");
        p=p->svt1;
    }
 }
 else printf("pas d'ouvrages dans la bibliotheque\n");
}
void suppressionouvrage(ouvrages *l, int T)
{ ouvrages q,p; int b;
p=*l;
if(p!=NULL)
{
while((p!=NULL)&&(p->cote!=T))
{  p=p->svt1;
}
    if(p!=NULL)
    {
  if(p==(*l))
        { suppdebut(&(*l));

        }
 else if(p->svt1==NULL)
 {
     suppfin(&p);
 }

else{
            (p->pcd1)->svt1=p->svt1;
            (p->svt1)->pcd1=p->pcd1;
            free(p);

        }
      }
      else printf("ouvrage inexistant dans la bibliotheque");
}
else
    printf("pas d'ouvrages dans la bibliothèque\n");
}
//disponibilite ouvrage
void dispoouvrage(ouvrages l,int x)
{
    ouvrages p;
    p=l;
    while((p!=NULL)&&(x!=p->cote))
    {
        p=p->svt1;
    }
    if(p!=NULL)
    {
        if(p->nbexemplaireb>0)
        {
            printf(" %d exemplaire disponible\n",p->nbexemplaireb);
        }
        else{printf("exemplaire non disponible\n");}
    }
}
//ajouter etudiant
void insertfinetud(etudiant l,double x,char c,int y)
{
    etudiant p,q;
q=l;
 while(q->svt2!=NULL)
{
    q=q->svt2;
}
 p=malloc(sizeof(letudiant));
 p->matricule=x;
 p->typeabo=c;
 p->penalite=y;
  p->pcd2=q;
 p->svt2=NULL;
q->svt2=p;
q=p;

}
void ajoutetud(etudiant *l,double x,char c,int y)
{
    etudiant p,q;
if((*l)==NULL)
{
    p=malloc(sizeof(letudiant));

 p->matricule=x;
 p->typeabo=c;
 p->penalite=y;
   p->pcd2=NULL;
   p->svt2=NULL;
   (*l)=p;

}
else{
    insertfinetud(*l,x,c,y);
}
}
//afficher liste etudiants
void afficheletud(etudiant l)
{
    etudiant p;
    p=l;
    while(p!=NULL)
{    printf("-------------------------------------------------\n");
    printf("le matricule de l'etudiant est %lf\n",p->matricule);
    printf("le type d'abonnement de l'etudiant est %c\n",p->typeabo);
    printf("l'etudiant a %d  penalite\n",p->penalite);
    printf("---------------------------------------------\n");
    p=p->svt2;
}
}
//suprimer etudiant
    void suppdebutetud(etudiant *l)
{
etudiant t;
 if((*l)!=NULL)
 { if((*l)->svt2==NULL)
 {
     free(*l);
     (*l)=NULL;
 }
 else
 {
     t=*l;
     (*l)=(*l)->svt2;
     (*l)->pcd2=NULL;
     free(t);

 }
 }
}
 void suppfinetud(etudiant *q)
 {etudiant p;
     if((*q)!=NULL)
     {
         if((*q)->pcd2==NULL)
         {
             free(*q);
             (*q)=NULL;

         }
         else
         {
             p=*q;
             (*q)=(*q)->pcd2;
             (*q)->svt2=NULL;
             free(p);


         }
     }
 }
 void suppressionetud(etudiant *l, double y)
{
    etudiant q,p;
p=*l;
if(p!=NULL)
{
while((p!=NULL)&& (y!=p->matricule))
{ p=p->svt2;
}
if(p!=NULL)
{
     if(p==(*l))
        {
            suppdebutetud(&(*l));
        }
        else if(p->svt2==NULL)
    {
     suppfinetud(&p);
    }
    else
         {
            (p->pcd2)->svt2=p->svt2;
            (p->svt2)->pcd2=p->pcd2;
            free(p);

        }

}
else{  printf("etudiant non inscrit a la biliotheque\n");}
}
else
{
 printf("pas d'etudiant inscrit a la bibliothèque\n");
}
}
//consulter etudiant
void consulteretud(etudiant l,double x)
{
    etudiant p;
    p=l;
    if(p!=NULL)
    {
    while((p!=NULL)&&(x!=p->matricule))
    {
        p=p->svt2;
    }
    if(p!=NULL)
    {   printf("---------------------------------\n");
        printf("matricule: %lf\n",p->matricule);
        printf("type d'abonnement: %c\n",p->typeabo);
        printf("penalite: %d\n",p->penalite);
        printf("----------------------------------\n");
    }
    else
    { printf("etudiant non inscrit a la bibliotheque\n");

    }
    }
    else printf("pas d'etudiant inscrit a la bibliotheque\n");
}
//modifier etudiant
void modifetud(etudiant l,double x)
{
    etudiant p;
int b;
    p=l;
    while((p!=NULL)&&(x!=p->matricule))
    {
        p=p->svt2;
    }
    if(p!=NULL)
    { printf("'1':modification du matricule\n'2':modification du type d'abonnement\n'3':modification de la penalite\n'0':terminer la modification\n");
      do
    {
         printf("choisir la case a modifier\n");
           scanf("%d",&b);

        switch (b)
        { case 1: {printf("entrer le matricule modifier\n"); scanf("%ld",&(p->matricule));} break;
          case  2: {printf("entrer le type d'abonnement modifier_n"); scanf("%c",&(p->typeabo));} break;
          case 3: { printf("entrer la penalite modifier\n"); scanf("%d",&(p->penalite));} break;
        }
    }while(b!=0);
    }
    else
        printf("etudiant non inscrit a la bibliotheque\n");

}
//ajouter emprunt
void insertfinemprunt(emprunts l,int x,double y)
{  date h;
    emprunts p,q;
    int z;
q=l;
          while(q->svt3!=NULL)
{
    q=q->svt3;
}
 p=malloc(sizeof(louvrageemprunter));
 p->cote=x;
 p->matricule=y;
           printf("veuillez entrer la date de debut d'emprunt de l'ouvrage\n");
printf("entrer le jour\n");
scanf("%d",&((p->dateemprunt).jour));
printf("entrer le mois\n");
scanf("%d",&((p->dateemprunt).mois));
printf("entrer l'annee\n");
scanf("%d",&((p->dateemprunt).annee));
printf("entrer la duree de l'emprunt\n");
scanf("%d",&z);
printf("entrer la duree de l'emprunt\n");
scanf("%d",&z);
calculduree(p->dateemprunt,&h,z);
(p->dateretour).jour=h.jour;
(p->dateretour).mois=h.mois;
(p->dateretour).annee=h.annee;


  p->pcd3=q;
 p->svt3=NULL;
q->svt3=p;
q=p;

}
void ajoutemprunt(emprunts *l3,etudiant l2,ouvrages l1,int x,double y,File *fp,File *fc)
{
int z;
date k,h;
 file a;
    etudiant p2;
    emprunts q,p3;
    ouvrages p1;
    p3=*l3;
    p1=l1;

    while((p1!=NULL)&&(p1->cote!=x))
    {
        p1=p1->svt1;
    }
    if(p1==NULL)
    {
        printf("ouvrage inexistant dans la bibliotheque\n");
    } p2=l2;
        while((p2!=NULL)&&(p2->matricule!=y))
    {
        p2=p2->svt2;
    }
      if(p2==NULL)
    {
        printf("etudiant non inscrit a la bibliotheque\n");
    }
    if((p1!=NULL)&&(p2!=NULL))
    {
        if((p1->nbexemplaireb>0)&&(p2->penalite<8))
        { p1->nbexemplaireb--;
          p1->nbexemplairepreter++;
            if((*l3)==NULL)
          {
            p3=malloc(sizeof(louvrageemprunter));
            p3->cote=x;
            p3->matricule=y;

          printf("veuillez entrer la date de debut d'emprunt de l'ouvrage\n");
          printf("entrer le jour\n");
scanf("%d",&((p3->dateemprunt).jour));
printf("entrer le mois\n");
scanf("%d",&((p3->dateemprunt).mois));
printf("entrer l'annee\n");
scanf("%d",&((p3->dateemprunt).annee));
printf("entrer la duree de l'emprunt\n");
scanf("%d",&z);
calculduree(p3->dateemprunt,&h,z);
(p3->dateretour).jour=h.jour;
(p3->dateretour).mois=h.mois;
(p3->dateretour).annee=h.annee;
              p3->pcd3=NULL;
          p3->svt3=NULL;
           (*l3)=p3;

          }
          else
          {


              insertfinemprunt(*l3,x,y);
          }

        }
        else if(p1->nbexemplaireb==0)
        {
            if(p2->typeabo=='P')
            {
                printf("exemplaire de l'ouvrage non disponible,l'etudiant est mis en file d'attente premium\n");
                a.matricule=p2->matricule;
                a.penalite=p2->penalite;
                a.typeabo=p2->typeabo;
                a.cote=x;

                Enfiler(&(*fp),a);
            }
            else if(p2->typeabo=='C')
            {
                printf("exemplaire de l'ouvrage non disponible,l'etudiant est mis en file d'attente classic\n");
                   a.matricule=p2->matricule;
                a.penalite=p2->penalite;
                a.typeabo=p2->typeabo;
                a.cote=x;

                Enfiler(&(*fc),a);

            }
        }
         else{
             printf("etudiant interdit d'emprunt\n");
         }
    }

}
//afficher emprunt
void afficherlemprunt(emprunts l)
{emprunts p;
p=l;
while(p!=NULL)
{printf("----------------------------------\n");
    printf("matricule:%lf\n",p->matricule);
    printf("cote:%d\n",p->cote);
    printf("date debut emprunt:%d/%d/%d\n",(p->dateemprunt).jour,(p->dateemprunt).mois,(p->dateemprunt).annee);
    printf("date fin emprunt:%d/%d/%d\n",(p->dateretour).jour,(p->dateretour).mois,(p->dateretour).annee);
    p=p->svt3;
    printf("----------------------------------\n");
}


}
//suprimer emprunt
    void suppdebutempreint(emprunts *l)
{
emprunts t;
 if((*l)!=NULL)
 { if((*l)->svt3==NULL)
 {
     free(*l);
     (*l)=NULL;
 }
 else
 {
     t=*l;
     (*l)=(*l)->svt3;
     (*l)->pcd3=NULL;
     free(t);

 }
 }
}
 void suppfinempreint(emprunts *q)
 {emprunts p;
     if((*q)!=NULL)
     {
         if((*q)->pcd3==NULL)
         {
             free(*q);
             (*q)=NULL;

         }
         else
         {
             p=*q;
             (*q)=(*q)->pcd3;
             (*q)->svt3=NULL;
             free(p);


         }
     }
 }
 void suppressionempreint(emprunts *l, double y,int x)
{
    emprunts q,p;
p=*l;
if(p!=NULL)
{
while((p!=NULL)&& ((y!=p->matricule)||(x!=p->cote)))
{ p=p->svt3;
}
if(p!=NULL)
{
     if(p==(*l))
        {
            suppdebutempreint(&(*l));
        }
        else if(p->svt3==NULL)
    {
     suppfinempreint(&p);
    }
    else
         {
            (p->pcd3)->svt3=p->svt3;
            (p->svt3)->pcd3=p->pcd3;
            free(p);

        }

}
else{  printf("emprunt inexistant a la biliotheque\n");}
}
else
{
 printf("pas d'etudiant inscrit a la bibliothèque\n");
}
}
//returner emprunt
void retournerempreint(emprunts *l3,double y,int x,ouvrages l1,etudiant l2,File *f1,File *f2)
{emprunts p;
ouvrages p1;
 p=*l3;
 file z;

    while((p!=NULL)&& ((y!=p->matricule)||(x!=p->cote)))
{ p=p->svt3;
}
if(p!=NULL)
{
 if((Filevide(*f1))&&(Filevide(*f2)))
 {  p1=l1;
  while((p1!=NULL)&& (p1->cote!=x))
{ p1=p1->svt1;}
  printf("livre retourner\n");
p1->nbexemplaireb++;
p1->nbexemplairepreter--;
suppressionempreint(&(*l3),y,x);
 }
 else if(!Filevide(*f1))
 { printf("bien");
    p1->nbexemplaireb++;
    p1->nbexemplairepreter--;
     Defiler(&(*f1),&z);
     ajoutemprunt(&(*l3),l2,l1,z.cote,z.matricule,&(*f1),&(*f2));
 }
  else if(!Filevide(*f2))

 { printf("bien");
    p1->nbexemplaireb++;
    p1->nbexemplairepreter--;
     Defiler(&(*f2),&z);
     ajoutemprunt(&(*l3),l2,l1,z.cote,z.matricule,&(*f1),&(*f2));
 }
}
}
//ajouter penalitee
void ajoutepenalite(etudiant l2,double x)
{ etudiant p;
  p=l2;
    while((p!=NULL)&&(p->matricule!=x))
    {
        p=p->svt2;
    }
    if(p!=NULL)
  {
    if(p->typeabo=='P')
    {
        printf("impossible d'ajouter une penalite car etduiant premium\n");
    }

    else
    {
     p->penalite=p->penalite+1;
     printf("penalite ajoutee\n");

    }
  }
    else
    {
        printf("matricule inexistant\n");
    }
}
//suprimer penalitee
void supppenalite(etudiant l2,double x)
{ etudiant p;
p=l2;
    while((p!=NULL)&&(p->matricule!=x))
    {
        p=p->svt2;
    }
    if(p!=NULL)
    { if(p->penalite=='P')
    {
        printf("impossible de supprimer penalite car etudiant premium\n");
    }
    else if(p->penalite==0)
    {
        printf("impossible de supprimer  la penalite car elle est nul\n");
    }
    else{
     p->penalite=p->penalite-1;
     printf("penalite supprimer\n");
    }
    }
    else
    {
        printf("matricule inexistant\n");
    }
}
//consulter liste des penalitee
void consultlistepenalite(etudiant l2)
{
etudiant p;
p=l2; printf("liste des penalites:\n");
  while(p!=NULL)
  {
      printf("matricule :%ld\npenalite :%d\n",p->matricule,p->penalite);
      p=p->svt2;
  }
}
//modifier emprunt
void modifieremprunt(emprunts l,double x,int y)
{
        emprunts p;
int b;
    p=l;
    while((p!=NULL)&&((x!=p->matricule)||(y!=p->cote)))
    {
        p=p->svt3;
    }
    if(p!=NULL)
    { printf("'1':modification du matricule\n'2':modification de la date d'emprunt\n'3':modification la date de retour\n'0':terminer la modification\n");
      do
    {
         printf("choisir la case a modifier\n");
           scanf("%d",&b);

        switch (b)
        { case 1: {printf("entrer le matricule modifier\n"); scanf("%lf",&(p->matricule));} break;
          case 2: {printf("entrer le type d'abonnement modifier\n");
          printf("modifier le jour\n");
          scanf("%c",&((p->dateemprunt).jour));
          printf("modifier le mois\n");
          scanf("%c",&((p->dateemprunt).mois));
          printf("modifier l'annee\n");
          scanf("%c",&((p->dateemprunt).annee));} break;
          case 3: { printf("entrer la penalite modifier\n");printf("modifier le jour\n"); scanf("%d",&((p->dateretour).jour));printf("modifier le mois\n"); scanf("%d",&((p->dateretour).mois));printf("modifier l'annee\n"); scanf("%d",&((p->dateretour).annee));} break;
        }
    }while(b!=0);
    }
    else
        printf("emprunt inexistant \n");
}
//----------------------------------------------------------------------
// fonction d'afficahge d'ouvrages le plus sollicites
void Consultee_plus(ouvrages L)
{
  if (L == NULL) {
    puts("\nla liste des ouvrage est vide");
  }

  ouvrages max = L;
  L = L->svt1;
  while (L != NULL) {
    if (L->nbexemplairepreter > max->nbexemplairepreter) {
      max = L;
    }
    L = L->svt1;
  }
  printf("\nle plus sollicite des ouvrages est: %s\n", max->titre);
}
// fonction d'affichage de l'ouvrage le moins emprunte
void Consutee_mois(ouvrages L)
{
  if (L == NULL) {
    puts("\nla liste d'ouvrage est vide");
  }

  ouvrages min = L;
  L = L->svt1;
  while (L != NULL) {
    if (L->nbexemplairepreter < min->nbexemplairepreter) {
      min = L;
    }
    L = L->svt1;
  }
  printf("\nl'ouvrage le moins emprunte est: %s \n", min->titre);
}
///----------------------------------------------------------
void quitter(){
     system("cls");
 printf("\n\n        \t------------FIN-----------\n\n\n");
 printf("\n\n        \t------------MERCI-----------\n\n\n");
 }
main()
{
ouvrages p1,l1;
etudiant p2,l2;
emprunts p3,l3;
File fp,fc;
char s[25];
char c;
int v,b,a;
int T,x,y,z;
double n;
system("color 5E");
    printf("                                   gestion d'une bibliotheque           \n");
    printf("**********************************DAOUD YOUCEF    G6     202031060674**************************************\n");
    printf("**********************************MEDJKOUNE ALI   G5     202031063595**************************************\n");
    printf("ACAD B L2 \n");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    l1=NULL; l2=NULL; l3=NULL; Initfile(&fp); Initfile(&fc);
//initialisation liste ouvrage
ajoutouvrage(&l1,123,"Algorithmique_et_Structures_de_Donnees",20,5);
ajoutouvrage(&l1,124,"Architecture_des_ordinateur_01",15,6);
ajoutouvrage(&l1,125,"Analyse_numerique",15,4);
ajoutouvrage(&l1,126,"Logique_mathematique",15,4);
ajoutouvrage(&l1,127,"systheme_d'information",1,5);
//initialisation liste etudiants
ajoutetud(&l2,202031063585,'P',1);
ajoutetud(&l2,202031063595,'C',0);
ajoutetud(&l2,202031060674,'P',0);
ajoutetud(&l2,202039023985,'C',3);
ajoutetud(&l2,202031049367,'C',2);

     do{
                    printf("                         '0':quitter\n                         '1':gestion des ouvrages\n                         '2':gestion des etudiants\n                         '3':gestion des emprunts\n");
            printf("choisir la gestion a faire   :");
            scanf("%d",&a);
        switch (a)
        {
        case 1:system("cls");{
            do
            {
                printf("les taches");
            printf("                         '0':quitter \n                         '1': ajouter un ouvrage\n                         '2':supprimer un ouvrage\n                         '3':consulter les ouvrage de la bibliotheque\n                         '4':verifier la disponibilite d'un ouvrage\n                         '5':affichage de l'ouvrage le plus solicite\n                         '6':affichage de l'ouvrage le moins solicite\n");
            printf("choisir la tache :  ");
            scanf("%d",&y);
            switch(y)
        {
          case 1:{    printf("veuiller entrer la cote de l'ouvrage\n");
scanf("%d",&x);
printf("veuiller entrer le titre de l'ouvrage (espace = _)\n");
scanf("%s",&s);
printf("veuillez entrer le nombre d'exemplaire dans la bibliotheque\n");
scanf("%d",&v);
printf("veuillez entrer le nombre d'exemplaire emprunter\n");
scanf("%d",&z);
              ajoutouvrage(&l1,x,s,v,z);} break;
        case 2:{ printf("veuiller entrer la cote de l'ouvrage a supprimer\n");
                scanf("%d",&T);
                (suppressionouvrage(&l1,T));}break;
        case 3: consulterouvrage(l1);break;
        case 4: {printf("entrer la cote du livre\n");
             scanf("%d",&x); dispoouvrage(l1,x);} break;
        case 5:{ Consultee_plus(l1);}break;
        case 6:{Consutee_mois(l1);}break;

        }
        } while(y!=0);
        }break;
        case 2:system("cls");{
            do
        {
        printf("les taches");
        printf("                         '0':quitter\n                         '1':ajouter un etudiant\n                         '2':afficher la liste des etudiabts\n                         '3':supprimer un etudiant\n                         '4':consulter un etudiant\n                         '5':modifier un etudiant\n                         '6':ajouter une penalite\n                         '7':supprimer une penalite\n                         '8':consulter la liste des penalites\n");
        printf("choisir la tache :   ");
            scanf("%d",&y);
         switch(y)
         {

             case 1:     {    printf("veuiller entrer le matricule de l'etudiant\n");
scanf("%lf",&n);
scanf("%c",&c);
while((c!='C') && (c!='P')){printf("veuiller entrer le type d'abonnement de l'etudiant: 'P':premium     'C':classqiue\n");
scanf("%c",&c);}


do { printf("veuillez entrer nombre de penalite de l'etudiant (initialement a 0)\n"); scanf("%d",&v);} while(v!=0);
ajoutetud(&l2,n,c,v);}break;
        case 2: afficheletud(l2);break;
        case 3: { printf("veuiller entrer le matricule de l'etudiant a supprimer\n");
                   scanf("%lf",&n); suppressionetud(&l2,n);
                } break;
        case 4:      { printf("veuiller entrer le matricule de l'etudiant a consulter\n");
                   scanf("%lf",&n); consulteretud(l2,n);
                } break;
        case 5:{   printf("veuiller entrer le matricule de l'etudiant a modifier\n");
        scanf("%lf",&n);  modifetud(l2,n); }
        case 6: {printf("entrer le matricule de l'etudiant concerner\n");
            scanf("%lf",&n); ajoutepenalite(l2,n);}break;
            case 7: {printf("entrer le matricule de l'etudiant concerner\n");
            scanf("%lf",&n); supppenalite(l2,n);}break;
            case 8: consultlistepenalite(l2);break;

         }
        } while(y!=0);
        }break;

        case 3:system("cls");{ do
        {
        printf("les taches");
        printf("                         '0':quitter\n                         '1':ajouter un emprunt\n                         '2':afficher la liste des emprunt\n                         '3':supprimer un emprunt\n                         '4'retourner un emprunt\n                         '5':modifier un emprunt\n");
        printf("choisir la tache ");
            scanf("%d",&y);
            switch(y)
            {
         case 1: {printf("entrer la cote du livre a preter\n");
                  scanf("%d",&x);
                  printf("entrer le matricule de l'etudiant qui emprunte le livre\n");
                  scanf("%lf",&n);
                  ajoutemprunt(&l3,l2,l1,x,n,&fp,&fc);
                  }break;
        case 2:{afficherlemprunt(l3);}break;
        case 3: {printf("donner la cote de l'emprunt a supprimer\n");
        scanf("%d",&a);
        printf("donner le matirucle de l'emprunt a supprimer\n");
        scanf("%lf",&n);
        suppressionempreint(&l3,n,a);
        }break;
        case 4: {printf("donner la cote de l'emprunt a retourner\n");
        scanf("%d",&a);
        printf("donner le matricule de l'emprunt a retourner\n");
        scanf("%lf",&n);
        retournerempreint(&l3,n,a,l1,l2,&fp,&fc);}break;
        case 5:{printf("donner la cote de l'emprunt a modifier\n");
        scanf("%d",&a);
        printf("donner le matricule de l'emprunt a modifier\n");
        scanf("%lf",&n);
        modifieremprunt(l3,n,a);
        }
        }
        }while(y!=0);
        }break;


      }
            }while(a!=0);


}
