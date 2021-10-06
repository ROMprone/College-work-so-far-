#include <windows.h>
#include <GL/glut.h>
#include<stdio.h>
#include<string.h>
int rol_utilizator=0;//0 pentru un utilizator, 1 pentru admin

void meniu_selectare_admin();
void meniu_selectare();
int nr_laptopuri=10;

struct laptop{
	char nume[30];
	char procesor[25];
	float dimensiune_ecran;
	int RAM;
	char tip_stocare[7];
	int capacitate_stocare;
	int pret;

}a[30];

void iesire(void)
{printf("\n\n  Have a great day! :)\n");

}

void display() {
   int i,j;
   float dy,dx;
   char nume[35];
   FILE *fisier;
   fisier=fopen("date.txt","r");
   for(i=0;i<nr_laptopuri;i++)
	   fscanf(fisier,"%s %s %f %d %s %d %d",a[i].nume,a[i].procesor,&a[i].dimensiune_ecran,&a[i].RAM,a[i].tip_stocare,&a[i].capacitate_stocare,&a[i].pret);
   dy=2.0/nr_laptopuri;
   dx=1.8/10500;
   glClearColor(0.0f, 0.5f, 1.0f, 0.5f);
   glClear(GL_COLOR_BUFFER_BIT);
   for(i=0;i<nr_laptopuri;i++){
	   glBegin(GL_QUADS);
	   glColor3f((i+1)/2.4f,(i+1)/7.5f, (i+1)/3.5f);
	   glVertex2f(1.0,1-i*dy);
	   glVertex2f(1.0,1.0-i*dy-0.10);
	   glVertex2f(1.0-a[i].pret*dx,1.0-i*dy-0.10);
	   glVertex2f(1.0-a[i].pret*dx,1.0-i*dy);
	   glEnd();
	   glRasterPos2f(1.0-a[i].pret*dx-0.15,1.0-i*dy-0.05);
	   sprintf(nume,"%s",a[i].nume);
	   for(j=0;j<strlen(nume);j++)
		   glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,nume[j]);
    }
  glFlush();
}


void add_prod(){
 FILE *add;
 FILE *fp;
 int i,n,m,b=0;
 add=fopen("adaugare_produs.txt","w");
 fp=fopen("date.txt","r");

 if(!add){
	 printf("Eroare la deschiderea fisierului!");
	 printf("\nDoriti sa va intoarceti la meniul principal?\n\nApasati 1 pentru meniu sau 0 pentru a iesi din program: ");
	 scanf("%d",&b);
	 if(b==1)
		 meniu_selectare_admin();
	 else
		 iesire();
 }
 for(i=0;i<nr_laptopuri;i++)
	 fscanf(fp,"%s %s %f %d %s %d %d",a[i].nume,a[i].procesor,&a[i].dimensiune_ecran,&a[i].RAM,a[i].tip_stocare,&a[i].capacitate_stocare,&a[i].pret);


 printf("\nIntroduceti numarul de produse pe care doriti sa il introduceti: ");
 scanf("%d",&n);
 for(i=nr_laptopuri;i<(nr_laptopuri+n);i++){
	 printf("\nIntroduceti denumirea produsului: ");
	 fflush(stdout);
	 scanf("%s",a[i].nume);
	 printf("\nIntroduceti denumirea procesorului: ");
	 fflush(stdout);
	 scanf("%s",a[i].procesor);
	 printf("\nIntroduceti dimensiune ecran: ");
	 fflush(stdout);
	 scanf("%f",&a[i].dimensiune_ecran);
	 printf("\nIntroduceti memorie RAM: ");
	 fflush(stdout);
	 scanf("%d",&a[i].RAM);
	 printf("\nIntroduceti tipul stocarii: ");
	 fflush(stdout);
	 scanf("%s",a[i].tip_stocare);
	 printf("\nIntroduceti capacitate stocare: ");
	 fflush(stdout);
	 scanf("%d",&a[i].capacitate_stocare);
	 printf("\nIntroduceti pretul: ");
	 fflush(stdout);
	 scanf("%d",&a[i].pret);
 }
 for(i=0;i<(nr_laptopuri+n);i++)
 	fprintf(add,"%s %s %.1f %d %s %d %d\n",a[i].nume,a[i].procesor,a[i].dimensiune_ecran,a[i].RAM,a[i].tip_stocare,a[i].capacitate_stocare,a[i].pret);
printf("\nOperatiune finalizata");
fclose(fp);
fclose(add);
printf("\nDoriti sa va intoarceti la meniul principal?\n\nApasati 1 pentru meniu sau 0 pentru a iesi din program: ");
fflush(stdout);
scanf("%d",&m);
     if(m==1)
     	meniu_selectare_admin();
     else
         iesire();
}

void del_prod(void){
	int t,i;
	int s=0,m=0;
	char num[30];
	FILE *list;
	FILE *n_lista;
	list=fopen("date.txt","r");
	n_lista=fopen("stergere_produse","w");
	 if(!list)
	    {printf("\nEROARE LA DESCHIDERA LISTEI!");
	     printf("\nDoriti sa va intoarceti la meniul principal?\n\nApasati 1 pentru meniu sau 0 pentru a iesi din program");
	     scanf("%d",&t);
	     if(t==1)
	     	meniu_selectare_admin();
	     else
	         iesire();}
    for(i=0;i<nr_laptopuri;i++)
    fscanf(list,"%s %s %f %d %s %d %d ",a[i].nume,a[i].procesor,&a[i].dimensiune_ecran,&a[i].RAM,a[i].tip_stocare,&a[i].capacitate_stocare,&a[i].pret);
    printf("\nIntrodu numele produsului:");
    scanf("%s",num);
    for(i=0;i<nr_laptopuri;i++){
         if(!strcmp(num,a[i].nume)){
        	 strcpy(a[i].nume,"delete");
        	 m++;
        	    for(i=0;i<nr_laptopuri;i++){
        	    	if(strcmp(a[i].nume,"delete")==0)
                        printf("\nProdus sters!");
        	              if(strcmp(a[i].nume,"delete")!=0){
        	              fprintf(n_lista,"%s %s %.1f %d %s %d %d\n",a[i].nume,a[i].procesor,a[i].dimensiune_ecran,a[i].RAM,a[i].tip_stocare,a[i].capacitate_stocare,a[i].pret);

          }
          }
          }
          }

fclose(list);
fclose(n_lista);

if(m==0){
	printf("\nProdusul nu a fost gasit");
	printf("\nDoriti sa faceti o recautare?\n\t1.Da\t\t2.Nu\t\t3.Iesire program\nR:");
	scanf("%d",&s);
    if(s==1)
   	 del_prod();
    else if(s==2)
   	 meniu_selectare_admin();
    else
   	 iesire();
}
}

void lista(){
 int i,m=0,nr=0;
 FILE *produse;
 produse=fopen("date.txt","r");
 if(!produse)
   {printf("\nEROARE LA DESCHIDERA LISTEI!");
    printf("\nDoriti sa va intoarceti la meniul principal?\n\nApasati 1 pentru meniu sau 0 pentru a iesi din program");
    scanf("%d",&m);
    if(m==1&&rol_utilizator==1)
    	meniu_selectare_admin();
    else if(m==1&&rol_utilizator==0)
        meniu_selectare();
    else
        iesire();}
 printf("\n  Denumire laptop\t\tProcesor\t   Dimensiune ecran\tRAM(GB)\t\t  Tip stocare\t    Capacitate stocare(GB)\t\tPret(lei)\n");
  for(i=0;i<nr_laptopuri;i++){
  while(fscanf(produse,"%s %s %f %d %s %d %d ",a[i].nume,a[i].procesor,&a[i].dimensiune_ecran,&a[i].RAM,a[i].tip_stocare,&a[i].capacitate_stocare,&a[i].pret)!=EOF){
  printf("%16s\t  %20s  \t%.2f\t\t%d\t\t\t%s\t\t\t%d\t\t\t%d\n",a[i].nume,a[i].procesor,a[i].dimensiune_ecran,a[i].RAM,a[i].tip_stocare,a[i].capacitate_stocare,a[i].pret);
  nr++;
  }
  }
  if(nr==0){
	  printf("\nNU EXISTA PRODUSE DISPONIBILE!\n");
  }
 fclose(produse);
 printf("\nDoriti sa va intoarceti la meniul principal?\n\nApasati 1 pentru meniu sau 0 pentru a iesi din program: ");
      scanf("%d",&m);
      if(m==1&&rol_utilizator==1)
      	meniu_selectare_admin();
      else if(m==1&&rol_utilizator==0)
          meniu_selectare();
      else
          iesire();
}

void edit_prod(void){
    int i,c,m=0,n=0;
    char nume[30];
    FILE *list,*n_lista;
    list=fopen("date.txt","r");
    n_lista=fopen("edit_produse","w");
    for(i=0;i<nr_laptopuri;i++)
    fscanf(list,"%s %s %f %d %s %d %d",a[i].nume,a[i].procesor,&a[i].dimensiune_ecran,&a[i].RAM,a[i].tip_stocare,&a[i].capacitate_stocare,&a[i].pret);
    printf("Introduceti numele produsului");
    scanf("%s",nume);
    for(i=0;i<nr_laptopuri;i++){
        if(strcmp(nume,a[i].nume)==0){
        	  m++;
              printf("\nCe doriti sa modificati?\n1.Procesorul\n2.Marimea ecranului\n3.RAM\n4.Tip stocare\n5.Capacitatea de stocare(GB)\n6.Pretul(lei)\n\nAlegerea dumneavoastra: ");
              scanf("%d",&c);

              switch(c){
           case 1:{
               printf("Introduceti noul nume al procesorului: ");
               scanf("%s",a[i].nume);
               printf("\nFinalizat!");
           }
           break;
           case 2:{
                   printf("Introduceti noua dimensiune al ecranului: ");
                   scanf("%f",&a[i].dimensiune_ecran);
                   printf("\nFinalizat");
               }
           break;
           case 3:{
                   printf("Introduceti noua memorie RAM: ");
                   scanf("%d",&a[i].RAM);
                   printf("\nFinalizat");
               }
           break;
           case 4:{
                   printf("Introduceti noul tip de stocare: ");
                   scanf("%s",a[i].tip_stocare);
                   printf("\nFinalizat");
               }
           break;
           case 5:{
                   printf("Introduceti noua capacitate a memoriei: ");
                   scanf("%d",&a[i].capacitate_stocare);
                   printf("\nFinalizat");
               }
           break;
           case 6:{
                   printf("Introduceti noul pret: ");
                   fflush(stdout);
                   scanf("%d",&a[i].pret);
                   printf("\nFinalizat");
               }
           break;
              }
        }
    }
    for(i=0;i<nr_laptopuri;i++)
        fprintf(n_lista,"%s %s %.1f %d %s %d %d\n",a[i].nume,a[i].procesor,a[i].dimensiune_ecran,a[i].RAM,a[i].tip_stocare,a[i].capacitate_stocare,a[i].pret);


fclose(list);
fclose(n_lista);

if(m==0){
	 printf("\nProdusul nu a fost gasit");
	 printf("\nDoriti sa faceti o recautare?\n\t1.Da\t\t2.Nu\t\t3.Iesire program\nR: ");
	 scanf("%d",&n);
     if(n==1)
    	 edit_prod();
     else if(n==2)
    	 meniu_selectare_admin();
     else
    	 iesire();
 }
}




void meniu_selectare_admin(void){
int alegere=0;
printf("\n\t\t\tMeniu principal");
fflush(stdout);
printf("\n\n\n  Bine ati venit!");
fflush(stdout);
printf("\n  Alegeti o optiune:\n\n\n\t1.Adauga produs\n\n\t2.Sterge produs\n\n\t3.Vezi lista de produse\n\n\t4.Editeaza un produs\n\n\t5.Iesire+grafic\n\n\tAlegerea dumneavoastra:");
fflush(stdout);

do{
scanf("%d",&alegere);
switch(alegere)
{
    case 1:add_prod();

    break;
    case 2:del_prod();

    break;
    case 3:lista();

    break;
    case 4:edit_prod();

    break;
    case 5:iesire();

    break;
    default:
    	printf("\n\tIntroduceti o optiune valida!\n");


}
}while(alegere<1||alegere>5);
}


void meniu_selectare(void)
{int alegere;
printf("\n\t\t\tMeniu principal");
fflush(stdout);
printf("\n\n\n  Bine ati venit!");
printf("\n  Alegeti o optiune:\n\n\n\t1.Vezi lista de produse\n\n\t2.Iesire\n\n\tAlegerea dumneavoastra:");
fflush(stdout);
do{
scanf("%d",&alegere);
if(alegere==1)
	lista();
else if(alegere==2)
	iesire();
else
	printf("\nAlegere invalida!");
}while(alegere<1||alegere>2);
}


int main(int argc, char** argv){
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	char nume[20], pswd[20];
	int s;
    retry:
	printf("Introduceti numele utilizatorului: ");
	fflush(stdout);
	scanf("%s",nume);
	printf("\nIntroduceti parola: ");
	scanf("%s",pswd);
	if(!strcmp(nume,"Admin")&&!strcmp(pswd,"1234")){
		rol_utilizator=1;
		meniu_selectare_admin();
	}
	else if(!strcmp(nume,"Admin")&&strcmp(pswd,"1234")){
		printf("\nParola gresita!");
		printf("\nDoriti sa reincercati logarea?\n1.DA\n2.NU\n3.MOD RESTRICTIONAT\nAlegerea dumneavoastra:");
		scanf("%d",&s);
		if(s==1)
			goto retry;
		else if(s==2)
			iesire();
		else if(s==3)
			meniu_selectare();
	}
	else{
		printf("\nAcest cont nu exista!");
		printf("\nDoriti sa reincercati logarea?\n1.DA\n2.NU\n3.MOD RESTRICTIONAT\nAlegerea dumneavoastra:");
		scanf("%d",&s);
		if(s==1)
			goto retry;
		else if(s==2)
			iesire();
		else if(s==3)
			meniu_selectare();
	}
	glutInit(&argc, argv);
	   glutInitWindowSize(320, 320);
	   glutInitWindowPosition(50, 50);
	   glutCreateWindow("Histograma preturi ");
	   glutDisplayFunc(display);
	   glutMainLoop();
	   return 0;
	}

