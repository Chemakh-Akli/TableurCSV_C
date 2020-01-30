#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "header/Select.h"
#include "Aux.c"


void SelectPrint(char* chiffre, char* s){
    int n = atoi(chiffre);
    int nbchamp = comptechampLigne(s);
    if(n < 0 || n > nbchamp){
        perror("L'index du champs a selectionner ne peut pas etre negatif ou superieur au nombre de champs disponibles");
    }
    char sep = giveSep(s);
    int srch_champ = 0;
    char c;
    int i = 0;
    int j = 0;
    int end_print = 0;
    FILE * fich = fopen(s,"r");
    int nbcomment;
    int nbLigne = compteligne(s);
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
      while(j < nbLigne){
        while ((c = fgetc(fich)) != EOF && srch_champ != n ){
            if(c == sep){
              srch_champ++;
            }
          }
          fseek(fich, -1L , SEEK_CUR);
          while((c = fgetc(fich)) != EOF /* && c != sep */&&  c != '\n' ){
            if(c == sep){
              end_print = 1;
            }
            if(end_print != 1){
              printf("%c",c);
            }
          }
          char charsuiv = fgetc(fich);
          if(charsuiv != EOF && charsuiv != '\n'){
            printf("%c",sep);
          }
          fseek(fich, -1L , SEEK_CUR);
          j++;
          end_print = 0;
          srch_champ = 0;
        }
      printf("%s","\n");
      fclose(fich);
    }
}




void SelectFile(char* chiffre,char* srt, char* s){
    FILE* sortie = fopen(srt,"a");
    int n = atoi(chiffre);
    int nbchamp = comptechampLigne(s);
    if(n < 0 || n > nbchamp){
        perror("L'index du champs a selectionner ne peut pas etre negatif ou superieur au nombre de champs disponibles");
    }
    char sep = giveSep(s);
    int srch_champ = 0;
    char c;
    int i = 0;
    int j = 0;
    int end_print = 0;
    int nbLigne = compteligne(s);
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
      while(j < nbLigne){
        while ((c = fgetc(fich)) != EOF && srch_champ != n ){
          if(c == sep){
            srch_champ++;
          }
        }
        fseek(fich, -1L , SEEK_CUR);
        while((c = fgetc(fich)) != EOF /* && c != sep */&&  c != '\n' ){
          if(c == sep){
            end_print = 1;
          }
          if(end_print != 1){
            fputc(c,sortie);
          }
        }
        char charsuiv = fgetc(fich);
        if(charsuiv != EOF && charsuiv != '\n'){
          fputc(sep,sortie);
        }
        fseek(fich, -1L , SEEK_CUR);
        j++;
        end_print = 0;
        srch_champ = 0;
      }
      fputc('\n',sortie);
      fclose(fich);
    }
    fclose(sortie);
}



void SelectNewSepPrint(char* chiffre,char* newsep, char* s){
  int n = atoi(chiffre);
  int nbchamp = comptechampLigne(s);
  if(n < 0 || n > nbchamp){
      perror("L'index du champs a selectionner ne peut pas etre negatif ou superieur au nombre de champs disponibles");
  }
  char sep = giveSep(s);
  int srch_champ = 0;
  char c;
  int i = 0;
  int j = 0;
  int end_print = 0;
  FILE * fich = fopen(s,"r");
  int nbcomment;
  int nbLigne = compteligne(s);
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
    while(j < nbLigne){
      while ((c = fgetc(fich)) != EOF && srch_champ != n ){
          if(c == sep){
            srch_champ++;
          }
        }
        fseek(fich, -1L , SEEK_CUR);
        while((c = fgetc(fich)) != EOF /* && c != sep */&&  c != '\n' ){
          if(c == sep){
            end_print = 1;
          }
          if(end_print != 1){
            printf("%c",c);
          }
        }
        char charsuiv = fgetc(fich);
        if(charsuiv != EOF && charsuiv != '\n'){
          printf("%s",newsep);
        }
        fseek(fich, -1L , SEEK_CUR);
        j++;
        end_print = 0;
        srch_champ = 0;
      }
    printf("%s","\n");
    fclose(fich);
  }
}

void SelectAideOpt(){
  printf("%s","Option obligatoire; l\nOption facultative ; -o -s,-h + un fichier \n");
}



int main(int argc, char *argv[])
{
    int c = 0;
    int hflg = 0;
    int lflg = 0;
    char* sfile = NULL;
    char *ofile = NULL;
	  int  errflg = 0;
    extern char *optarg;
    extern int optind;
	  extern int optopt;

    while ((c = getopt(argc, argv, "lo:s:h")) != -1) {
        switch(c) {
        case 'h':
            hflg++;
            break;
        case 'l':
            lflg++;
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
    if(lflg == 0){
        fprintf(stderr, "L'option -l est obligatoire. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg != 0 ) {
        fprintf(stderr, "Options mal entrees. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg == 0 && hflg == 0 && ofile == NULL && sfile == NULL){
        while(optind < argc-1){
            if(estBienFormate(argv[argc -1]) == 1){
                SelectPrint(argv[optind], argv[argc-1]);
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
                SelectFile(argv[optind],ofile, argv[argc-1]);
                optind++;
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }
    if(sfile != NULL){
        while(optind < argc-1){
            if(estBienFormate(argv[optind]) == 1){
                SelectNewSepPrint(argv[optind],sfile, argv[argc-1]);
                optind++;
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }
        }
    }

    if(hflg == 1){
       SelectAideOpt();
    }
    return 0;
}
