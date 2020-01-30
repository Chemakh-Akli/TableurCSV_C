#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "header/Union.h"
#include "Aux.c"




// pas d'option

void unionPrint(char* n){
  char c;
  int i = 0;
  FILE* fich = fopen(n,"r");
  int nbcomment;
  if(giveSep(n) == ';'){
    nbcomment = comptecomment(n);
  }
  else{
    nbcomment = comptecomment(n)+1;
  }
  if(fich != NULL){
    while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
            i++;
        }
    }
    while ((c=fgetc(fich)) != EOF ){
      printf("%c",c);
    }
    fclose(fich);
  }
}




// -o

void unionFile(char* s ,char* n ){
  FILE* concatene = fopen(s,"a");
  FILE* fich;
  int c;
  int i = 0;
  fich = fopen(n,"r");
  int nbcomment;
  if(giveSep(n) == ';'){
    nbcomment = comptecomment(n);
  }
  else{
    nbcomment = comptecomment(n)+1;
  }
  if(fich != NULL){
    while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
            i++;
        }
    }
    while ((c=fgetc(fich)) != EOF ){
      fputc(c,concatene);
    }
    fclose(fich);
  }
  fclose(concatene);
}





//-s

void unionPrintNewSep(char* sep ,char* n){
  FILE * fich;
  char oldsep = giveSep(n);
  int i = 0;
  char c;
  fich = fopen(n,"r");
  int nbcomment;
  if(oldsep == ';'){
    nbcomment = comptecomment(n);
  }
  else{
    nbcomment = comptecomment(n) + 1;
  }
  if(fich != NULL){
    while( i < nbcomment && (c = fgetc(fich)) != EOF ){
        if( c  == '\n' ){
            i++;
        }
    }
    while ((c = fgetc(fich)) != EOF ){
      if(c == oldsep){
        printf("%s",sep);
      }
      else{
        printf("%c",c);
      }
    }
    printf("%s","\n");
    fclose(fich);
  }
}




// -h

void unionAideOpt(){
  printf("%s","Option obligatoire; Aucune\nOption facultative ; -o -s,-h\n");
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
			fprintf(stderr,	"Vous avez oublie de preciser le parametre d'une option.\n Veuillez consulter l'aide aux commandes avec -h \n");
			errflg++;
			break;
        case '?':
            fprintf(stderr,"Ceci n'est pas une option possible");
            errflg++;
        }
    }


    int nbchamp = comptechampLigne(argv[optind]);

    if (errflg != 0 ) {
        fprintf(stderr, "Options mal entrees. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg == 0 && hflg == 0 && ofile == NULL && sfile == NULL){
        while(optind < argc){
            if(estBienFormate(argv[optind]) == 1){
                if(comptechampLigne(argv[optind]) == nbchamp ){
                    unionPrint(argv[optind]);
                    optind++;
                }
                else{
                    fprintf(stderr,"Les lignes n'ont pas le meme nombre de champ\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }
    if(ofile != NULL){
        while(optind < argc){
            if(estBienFormate(argv[optind]) == 1){
                if(comptechampLigne(argv[optind]) == nbchamp ){
                    unionFile(ofile,argv[optind]);
                    optind++;
                }
                else{
                    fprintf(stderr,"Les lignes n'ont pas le meme nombre de champ\n");
                    exit(2);
                }
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }
    if(sfile != NULL){
        for(int i = optind ; i < argc ; i++){
             if(estBienFormate(argv[optind]) == 1){
                if(comptechampLigne(argv[optind]) == nbchamp ){
                    unionPrintNewSep(sfile ,argv[i]);
                }
                else{
                    fprintf(stderr,"Les lignes n'ont pas le meme nombre de champ\n");
                    exit(2);
                }
             }
             else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
             }
        }
    }
    if(hflg == 1){
        unionAideOpt();
    }

}
