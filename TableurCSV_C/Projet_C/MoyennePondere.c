#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdarg.h>
#include "header/MoyennePondere.h"
#include "Aux.c"



int * conversion (char *s){
	char taille=0;
	char temp [2];
	temp[1]='\0';
	for(int i=strlen(s)-1; i>0 ; i--){
		if(s[i]=='*'){                              //converti les int d'un string dans un tableau de int
			taille++;
		}
	}
	int * tab = (int *)malloc(taille*sizeof(int));
	int i=0;
	int j=0;
	 while (i<strlen(s)){
	 	while(s[i]!='*'){
	 		i++;
	 	}
	 	temp[0]=s[i-1];
	 	tab[j]=atoi(temp);
		temp[0]= '\0';
	 	j++;
	 	i++;
	}
	return tab;
}



float * conversion2 (char * s){
	char taille=0;
	char nombre[4];
	nombre[3]='\0';
	for(int i=strlen(s)-1; i>0 ; i--){
		if(s[i]=='*'){
			taille++;
		}
	}
	float * tab = (float *)malloc(taille*sizeof(float));  //converti les float d'un string dabs un tableau de float
	int i=0;
	int j=0;
	int k=0;

	 while (i<strlen(s)){
	 	while(s[i]!='*'&& i<strlen(s)){
	 		i++;
	 	}
	 	i++;
	 	while(s[i]!='+' && i< strlen(s)){
	 		nombre[k]=s[i];
	 		k++;
	 		i++;
	 	}

	 	tab[j]=atof(nombre);
	 	j++;
	 	nombre[0]='\0';nombre[1]='\0';nombre[3]='\0';
	 	k=0;
	}
	 return tab;
}



 	int is_number(int s){
 		return (s=='1' || s=='2' || s=='3' || s=='4' || s=='5' || s=='6' || s=='7' || s=='8' || s=='9' || s=='0');
 	}
 	int is_float_1 (int a,int b, int c){
 		return (is_number(a) && b=='.' && is_number(c));
		}
	int is_float_2 (int a,int b,int c, int d){
		return (is_number(a) && c=='.'&& is_number(b) && is_number(d));
	}
	int is_abs (int a, int b, int c){
		return (a=='a' && b=='b' && c=='s');
	}
	int is_space (int s){
		return (s==' ');
	}


 void lectf (float * t){
 	for(int i=0; i<5; i++){
 		printf("%.2f ",t[i]);
 	}
 }

  void lecti (int* t){
 	for(int i=0; i<36; i++){
 		printf("%c",(char)t[i]);
 	}
 }


 void moyenne_ponderePrint(char* fich, char* s){
 	FILE * un = fopen(fich,(char *)"r");
 	int *  tab1 = conversion(s);                     	   /* recupere les numeros de champ du string'*/
 	float * tab2 = conversion2(s);

 										 		 /* les coefs du string */
 	int taille = 1000;
 	char nombre[4];
 	int count_champ=1;				//Les champs sont indexés a partir de 1
 	int count_ligne=0;
 	int i = 0;
 	int j = 0;
 	int cop;
 	float moy=0.0;
 	char moyenne[4];
 	float divise = 0.0;
 	char c = giveSep(fich);
  	int com;
 	if(c == ';'){
     com = comptecomment(fich);
   }
   else{
     com = comptecomment(fich)+1;
   }
 	int * ligne = (int *)malloc(taille*sizeof(int));

 	while(i < com && (cop=fgetc(un))!=EOF ){
 		if(cop == '\n'){
   				i++;
   	}
 	}

   	i=0;

 	cop =fgetc(un);
   while(cop!=EOF){

   	while(cop!=10  && cop!=13 && cop!=EOF){
   		printf("%c",cop);
   		if(!is_space(cop)){
   			ligne[i]=cop;
   			i++;                                                   //on copie le fichier et on copie une ligne dans un tableau
   			count_ligne++;
   		}
   		cop=fgetc(un);
   	}
 		int bis=0;
 		int bi=0;
   	int k=0;

   		while ( k < count_ligne){
   			if (tab1[j] == count_champ){
   				if (is_float_2(ligne[k],ligne[k+1],ligne[k+2],ligne[k+3]) ){	// cas ou l'on rencontre un float superieu à 10
 						for(bis = 0; bis < 4; bis++){																// avec ce tableau on travaille sur la ligne on repere les champs
   						nombre[bis]=(char)ligne[k+bis];
 						}

   					moy = moy + (tab2[j]*atof(nombre));
 						bis = 0;
 						for(bis = 0; bis < 4; bis++){
   							nombre[bis]='\0';
 						};
   					k = k+5;

   				}
 					else{
 						if (is_float_1 (ligne[k],ligne[k+1],ligne[k+2])){ 		// cas ou l on rencontre un float inferieur à 10
 							for(bi = 0; bi < 3; bi++){													// avec ce tableau on travaille sur la ligne on repere les champs
 	  						nombre[bi]=(char)ligne[k+bi];
 							}
   						moy = moy + (tab2[j]*atof(nombre));
 							bi = 0;
 							for(bi = 0; bi < 3; bi++){												// avec ce tableau on travaille sur la ligne on repere les champs
 	  							nombre[bi]='\0';
 							}
   						k = k+4;
   					}
 						else{
 							if (is_abs (ligne[k],ligne [k+1],ligne[k+2])){        // cas absent
   							tab2[j] = 0.0;
   							k = k+4;
   						}
 							else{
 								if (ligne[k]==c){
   								k++;																//cas champ vide
   							}
   						}
   					}
   				}
   				j++;
   				count_champ++;
   		}
 			else{
   			while(ligne[k]!=c &&  k<=count_ligne){
   				k++;
   			}
   			k++;
   			count_champ++;
   		}
   	}


   	for(int l=0; l<j;l++){
   		divise = divise + tab2[l];              // additionne les coefs
   	}

   	printf("%c",c);
   	if(divise == 0){
   		printf("%s","abs");
   	}
 		else{
   		moy = moy/divise;
   		sprintf(moyenne,"%.2f",moy);
   		printf("%c",' ');
   		printf("%s",moyenne);
   	}

   	printf("%c",'\n');
    	j=0;
    	i=0;                                     	//reinitialisation des variables pour passer à lal ligne suivante
    	count_champ=1;
    	count_ligne=0;
    	moy=0;
    	divise=0;
    	moyenne[0]='\0'; moyenne[1]='\0';moyenne[2]='\0';moyenne[3]='\0';
    	tab2 = conversion2(s);

  		cop=fgetc(un);
  		if(cop==13|| cop==10){
  			cop=fgetc(un);
  		}
 	}
 	fclose(un);
 }


void moyenne_pondereFile(char* fich, char* s, char* sortie){
	FILE * un = fopen(fich,(char *)"r");
	FILE * nv_fichier = fopen(sortie,"a");  							/* cree un nouveau fichier*/
	int *  tab1 = conversion(s);                     	   /* recupere les numeros de champ du string'*/
	float * tab2 = conversion2(s);

										 		 /* les coefs du string */
	int taille = 1000;
	char nombre[4];
	int count_champ=1;				//Les champs sont indexés a partir de 1
	int count_ligne=0;
	int i = 0;
	int j = 0;
	int cop;
	float moy=0.0;
	char moyenne[4];
	float divise = 0.0;
	char c = giveSep(fich);
 	int com;
	if(c == ';'){
    com = comptecomment(fich);
  }
  else{
    com = comptecomment(fich)+1;
  }
	int * ligne = (int *)malloc(taille*sizeof(int));

	while(i < com && (cop=fgetc(un))!=EOF ){
		if(cop == '\n'){
  				i++;
  	}
	}

  	i=0;

	cop =fgetc(un);
  while(cop!=EOF){

  	while(cop!=10  && cop!=13 && cop!=EOF){
  		fputc(cop,nv_fichier);
  		if(!is_space(cop)){
  			ligne[i]=cop;
  			i++;                                                   //on copie le fichier et on copie une ligne dans un tableau
  			count_ligne++;
  		}
  		cop=fgetc(un);
  	}
		int bis=0;
		int bi=0;
  	int k=0;

  		while ( k < count_ligne){
  			if (tab1[j] == count_champ){
  				if (is_float_2(ligne[k],ligne[k+1],ligne[k+2],ligne[k+3]) ){	// cas ou l'on rencontre un float superieu à 10
						for(bis = 0; bis < 4; bis++){																// avec ce tableau on travaille sur la ligne on repere les champs
  						nombre[bis]=(char)ligne[k+bis];
						}

  					moy = moy + (tab2[j]*atof(nombre));
						bis = 0;
						for(bis = 0; bis < 4; bis++){
  							nombre[bis]='\0';
						};
  					k = k+5;

  				}
					else{
						if (is_float_1 (ligne[k],ligne[k+1],ligne[k+2])){ 		// cas ou l on rencontre un float inferieur à 10
							for(bi = 0; bi < 3; bi++){													// avec ce tableau on travaille sur la ligne on repere les champs
	  						nombre[bi]=(char)ligne[k+bi];
							}
  						moy = moy + (tab2[j]*atof(nombre));
							bi = 0;
							for(bi = 0; bi < 3; bi++){												// avec ce tableau on travaille sur la ligne on repere les champs
	  							nombre[bi]='\0';
							}
  						k = k+4;
  					}
						else{
							if (is_abs (ligne[k],ligne [k+1],ligne[k+2])){        // cas absent
  							tab2[j] = 0.0;
  							k = k+4;
  						}
							else{
								if (ligne[k]==c){
  								k++;																//cas champ vide
  							}
  						}
  					}
  				}
  				j++;
  				count_champ++;
  		}
			else{
  			while(ligne[k]!=c &&  k<=count_ligne){
  				k++;
  			}
  			k++;
  			count_champ++;
  		}
  	}


  	for(int l=0; l<j;l++){
  		divise = divise + tab2[l];              // additionne les coefs
  	}

  	fputc(c,nv_fichier);
  	if(divise == 0){
  		fputs("abs",nv_fichier);
  	}
		else{
  		moy = moy/divise;
  		sprintf(moyenne,"%.2f",moy);
  		fputc(' ',nv_fichier);
  		fputs(moyenne,nv_fichier);
  	}

  	fputc('\n',nv_fichier);
   	j=0;
   	i=0;                                     	//reinitialisation des variables pour passer à lal ligne suivante
   	count_champ=1;
   	count_ligne=0;
   	moy=0;
   	divise=0;
   	moyenne[0]='\0'; moyenne[1]='\0';moyenne[2]='\0';moyenne[3]='\0';
   	tab2 = conversion2(s);

 		cop=fgetc(un);
 		if(cop==13|| cop==10){
 			cop=fgetc(un);
 		}
	}
	fclose(un);
	fclose(nv_fichier);
}



void moyenne_ponderee_aide_opt(){
	printf("%s","Option obligatoire ; -m\n Options facultatives ; -o -h\nLes champs sont indexes a partir de 1 (ne mettez pas de 0 dans vos formules)\nproduit un fichier qui reprend toutes les lignes de donnees du fichier en ajoutant a la fin\nde chaque ligne un nouveau champ numerique. La valeur du nouveau champ est une somme\n ponderee calculee selon la formule qui suit -m. La formule aura la forme c1*k1+:::+cj chaque ci est un numero de champ et chaque ki un coeffcient.");
}


int main(int argc, char *argv[])
{
    int c = 0;
    int mflg = 0;
		int hflg = 0;
    char* sfile = NULL;
    char *ofile = NULL;
	  int  errflg = 0;
    extern char *optarg;
    extern int optind;
	  extern int optopt;

    while ((c = getopt(argc, argv, "mo:s:h")) != -1) {
        switch(c) {
        case 'h':
            hflg++;
            break;
        case 'm':
            mflg++;
            break;
        case 's':
            sfile = optarg;
            break;
        case 'o':
            ofile = optarg;
            break;
		case ':':
			fprintf(stderr,	"Vous avez oubli� de preciser le param�tre d'une option.\n Veuillez consulter l'aide aux commandes avec -h \n");
			errflg++;
			break;
        case '?':
            fprintf(stderr,"Ceci n'est pas une option possible");
            errflg++;
        }
    }
    if(mflg == 0){
        fprintf(stderr, "L'option -m est obligatoire. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg != 0 ) {
        fprintf(stderr, "Options mal entrees. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg == 0 && hflg == 0 && ofile == NULL && sfile == NULL){
        while(optind < argc-1){
            if(estBienFormate(argv[argc -1]) == 1){
                moyenne_ponderePrint(argv[argc-1],argv[optind]);
                optind++;
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }
    if(ofile != NULL){
        while(optind < argc-1){
            if(estBienFormate(argv[optind]) == 1){
                moyenne_pondereFile(argv[argc-1],argv[optind],ofile);
                optind++;
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }

    if(hflg == 1){
       moyenne_ponderee_aide_opt;
    }
    return 0;
}
