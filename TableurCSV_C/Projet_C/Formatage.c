#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "header/Formatage.h"
#include "Aux.c"




void formatage(char* s){
    char sep = giveSep(s);
    int champlignemax = comptechampLigne(s);
    int count = 0;
    int diff;
    int i = 0;
    char c;
    FILE* fich = fopen(s,"r");
    int nbcomment;
    if(giveSep(s) == ';'){
        nbcomment = comptecomment(s);
    }
    else{
        nbcomment = comptecomment(s) + 1;
    }
    if(fich != NULL){
      while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
          i++;
        }
      }
      while ((c=fgetc(fich)) != EOF ){
        if(c == '\n'){
            diff = champlignemax - count;
            for(int j = 0; j<diff; j++){
                printf("%c",sep);
            }
            count =0;
        }
        if(c == sep){
            count++;
        }
        printf("%c",c);

      }
      diff = champlignemax - count;
      for(int j = 0; j<diff; j++){
        printf("%c",sep);
      }
      fclose(fich);
    }
}







void formatageFile(char* n,char* s){
    FILE* sortie = fopen(n,"a");
    char sep = giveSep(s);
    int champlignemax = comptechampLigne(s);
    int count = 0;
    int diff;
    int i = 0;
    char c;
    FILE * fich = fopen(s,"r");
    int nbcomment;
    if(giveSep(s) == ';'){
        nbcomment = comptecomment(s);
    }
    else{
        nbcomment = comptecomment(s) + 1;
    }
    if(fich != NULL){
      while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
          i++;
        }
      }
      while ((c=fgetc(fich)) != EOF ){
        if(c == '\n'){
            diff = champlignemax - count;
            for(int j = 0; j<diff; j++){
                fputc(sep,sortie);
            }
            count =0;
        }
        if(c == sep){
            count++;
        }
        fputc(c,sortie);
      }
      diff = champlignemax - count;
      for(int j = 0; j<diff; j++){
        fputc(sep,sortie);
      }
      fclose(fich);
    }
    fclose(sortie);
}





void formatagePrintNewSep(char* newsep,char* s){
    char sep = giveSep(s);
    int champlignemax = comptechampLigne(s);
    int count = 0;
    int diff;
    int i = 0;
    char c;
    FILE * fich = fopen(s,"r");
    int nbcomment;
    if(giveSep(s) == ';'){
        nbcomment = comptecomment(s);
    }
    else{
        nbcomment = comptecomment(s) + 1;
    }
    if(fich != NULL){
      while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
          i++;
        }
      }
      while ((c=fgetc(fich)) != EOF ){
        if(c == '\n'){
            diff = champlignemax - count;
            for(int j = 0; j<diff; j++){
                printf("%s",newsep);
            }
            count =0;
        }
        if(c == sep){
            printf("%s",newsep);
            count++;
        }
        else{
        printf("%c",c);
        }
      }
      diff = champlignemax - count;
      for(int j = 0; j<diff; j++){
        printf("%s",newsep);
      }
      fclose(fich);
    }
}


void formatageAideOpt(){
  printf("%s","Option obligatoire; Aucune\nOption facultative ; -o -s,-h\nLa commande DOIT prendre en argument UN fichier");
}





int main(int argc, char *argv[])
{

    int c = 0;
    int hflg = 0;
    char* sfile = NULL;
    char* ofile = NULL;
	int  errflg = 0;
    extern char *optarg;
    extern int optind;
	extern int optopt;

    while ((c = getopt(argc, argv, "o:s:h")) != -1) {
        switch(c) {
        case 'h':
            hflg++;
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

    if(errflg != 0 ) {
        fprintf(stderr, "Options mal entrees. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }



    if(errflg == 0 && hflg == 0 && ofile == NULL && sfile == NULL){
        formatage(argv[optind]);
    }

    if(ofile != NULL){
        formatageFile(ofile,argv[optind]);

    }

    if(sfile != NULL){
        formatagePrintNewSep(sfile,argv[optind]);
    }

    if(hflg == 1){
        formatageAideOpt();
    }

}
