#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "header/Tri.h"
#include "Aux.c"






void TriPrint(char* chiffre , char* fich){
  char* a_trier = Select(chiffre , fich);

  char sep = giveSep(fich);
  char* delim = &sep;

  int cpt_sep = nb_sep(a_trier,sep);
  int cpt_sep_entre = 0;

  char* array;
  array = strtok(a_trier,delim);

  char** strings = (char**)malloc(10*sizeof(char*));
  for(int i = 0 ;i < 10 ; i++){
    strings[i] = malloc(20* sizeof(char));
  }

  int idx = 0;
  int n = 0;
  while(array != NULL){
    for(n = 0 ; n < strlen(SansEspace(array)) ; n++){
      strings[idx][n] = SansEspace(array)[n];     //verifier '\0'
    }
    strings[idx][n] = '\0';
    array = strtok(NULL,delim);
    idx++;
  }

  /*
  for(int s = 0 ;s < idx  ; s++){
    printf("%s\n",strings[s]);
  }
  printf("%s","\n");
  */

  for(int j = 0 ; j < idx-1 ; j++){
    int indice_max = j;
    for(int z = j+1 ; z < idx ; z++){
      if( strcmp( strings[z], strings[indice_max] ) < 0){
        indice_max = z;
      }
    }
    echanger(&strings[indice_max],&strings[j]);
  }

  for(int t = 0 ;t < idx  ; t++){
    if(t != idx - 1){
      printf("%s%c",strings[t],sep);
      cpt_sep_entre++;
    }else{
      printf("%s",strings[t]);
      for(int r = 0 ; r < cpt_sep - cpt_sep_entre ; r++){
        printf("%c",sep);
      }
      break;
    }
  }
  free(strings);
}






void TriFile(char* chiffre , char* fich , char* srt){
  FILE* sortie = fopen(srt,"a");
  char* a_trier = Select(chiffre , fich);

  char sep = giveSep(fich);
  char* delim = &sep;

  int cpt_sep = nb_sep(a_trier,sep);
  int cpt_sep_entre = 0;

  char* array;
  array = strtok(a_trier,delim);

  char** strings = (char**)malloc(10*sizeof(char*));
  for(int i = 0 ;i < 10 ; i++){
    strings[i] = malloc(20* sizeof(char));
  }

  int idx = 0;
  int n = 0;
  while(array != NULL){
    for(n = 0 ; n < strlen(SansEspace(array)) ; n++){
      strings[idx][n] = SansEspace(array)[n];     //verifier '\0'
    }
    strings[idx][n] = '\0';
    array = strtok(NULL,delim);
    idx++;
  }

  /*
  for(int s = 0 ;s < idx  ; s++){
    printf("%s\n",strings[s]);
  }
  printf("%s","\n");
  */


  for(int j = 0 ; j < idx-1 ; j++){
    int indice_max = j;
    for(int z = j+1 ; z < idx ; z++){
      if( strcmp( strings[z], strings[indice_max] ) < 0){
        indice_max = z;
      }
    }
    echanger(&strings[indice_max],&strings[j]);
  }

  for(int t = 0 ;t < idx  ; t++){
    if(t != idx - 1){
      fprintf(sortie,"%s%c",strings[t],sep);
      cpt_sep_entre++;
    }else{
      fprintf(sortie,"%s",strings[t]);
      for(int r = 0 ; r < cpt_sep - cpt_sep_entre ; r++){
        fputc(sep,sortie);
      }
      break;
    }
  }
  free(strings);
  fclose(sortie);
}






void TriPrintNewSep(char* chiffre ,char* newsep ,char* fich){
  char* a_trier = Select(chiffre , fich);

  char sep = giveSep(fich);
  char* delim = &sep;

  int cpt_sep = nb_sep(a_trier,sep);
  int cpt_sep_entre = 0;

  char* array;
  array = strtok(a_trier,delim);

  char** strings = (char**)malloc(10*sizeof(char*));
  for(int i = 0 ;i < 10 ; i++){
    strings[i] = malloc(20* sizeof(char));
  }

  int idx = 0;
  int n = 0;
  while(array != NULL){
    for(n = 0 ; n < strlen(SansEspace(array)) ; n++){
      strings[idx][n] = SansEspace(array)[n];     //verifier '\0'
    }
    strings[idx][n] = '\0';
    array = strtok(NULL,delim);
    idx++;
  }

  /*
  for(int s = 0 ;s < idx  ; s++){
    printf("%s\n",strings[s]);
  }
  printf("%s","\n");
  */

  for(int j = 0 ; j < idx-1 ; j++){
    int indice_max = j;
    for(int z = j+1 ; z < idx ; z++){
      if( strcmp( strings[z], strings[indice_max] ) < 0){
        indice_max = z;
      }
    }
    echanger(&strings[indice_max],&strings[j]);
  }

  for(int t = 0 ;t < idx  ; t++){
    if(t != idx - 1){
      printf("%s%s",strings[t],newsep);
      cpt_sep_entre++;
    }else{
      printf("%s",strings[t]);
      for(int r = 0 ; r < cpt_sep - cpt_sep_entre ; r++){
        printf("%s",newsep);
      }
      break;
    }
  }
  free(strings);
}






void TriPrintNum(char* chiffre , char* fich){
  char* a_trier = Select(chiffre , fich);

  char sep = giveSep(fich);
  char* delim = &sep;

  int cpt_sep = nb_sep(a_trier,sep);
  int cpt_sep_entre = 0;

  char* array;
  array = strtok(a_trier,delim);


  char** strings = (char**)malloc(10*sizeof(char*));
  for(int i = 0 ;i < 10 ; i++){
    strings[i] = malloc(10* sizeof(char));
  }

//  printf("\n%s\n","Le tableau a ete initialise");

  int idx = 0;
  int n = 0;
  while(array != NULL){
   if(strcmp(SansEspace(array),"abs") != 0 && isNote(SansEspace(array)) == 0){
      perror("Le fichier (ou le champ) choisi n'est pas compatible avec l'option n \nVerifiez que votre ficher ne contient que des valeurs numeriques");
      exit(2);
    }
    for(n = 0 ; n < strlen(SansEspace(array)) ; n++){
      strings[idx][n] = SansEspace(array)[n];     //verifier '\0'
    }
    strings[idx][n] = '\0';
    array = strtok(NULL,delim);
    idx++;
  }


  for(int s = 0 ;s < idx  ; s++){
    printf("%s\n",strings[s]);
  }
  printf("%s\n\n","Le tableau a ete spite (sans tri)");

  for(int j = 0 ; j < idx-1 ; j++){
    int indice_max = j;
    for(int z = j+1 ; z < idx ; z++){
      if( atof(strings[z]) > atof(strings[indice_max]) ){
        indice_max = z;
      }
    }
    echanger(&strings[indice_max],&strings[j]);
  }

//  printf("\n%s\n","Le tri a ete effectue");

  for(int t = 0 ;t < idx  ; t++){
    if(t != idx - 1){
      printf("%s%c",strings[t],sep);
      cpt_sep_entre++;
    }else{
      printf("%s",strings[t]);
      for(int r = 0 ; r < cpt_sep - cpt_sep_entre ; r++){
        printf("%c",sep);
      }
      break;
    }
  }

  printf("\n%s\n","Notes triees");

  free(strings);

}




void TriAideOpt(){
  printf("%s\n","Option obligatoire; un nombre positif \nOption facultative ; -o -s -h -n\n");
  printf("%s", "Pour trier des notes sans l'option -n il est fortement coseillé de faire en sorte que les chiffre soit de meme taille");
}







int main(int argc, char *argv[])
{
    //TriPrintNum("1" , "fich1.csm");
    int c = 0;
    int hflg = 0;
    int cflg = 0;
    int nflg = 0;
    char* sfile = NULL;
    char *ofile = NULL;
	  int  errflg = 0;
    extern char *optarg;
    extern int optind;
	  extern int optopt;

    while ((c = getopt(argc, argv, "n:o:s:h")) != -1) {
        switch(c) {
        case 'h':
            hflg++;
            break;
        case 'n':
            nflg++;
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

    if(errflg != 0 ) {
        fprintf(stderr, "Options mal entrees. Veuillez consulter l'aide aux commandes avec -h \n ");
        exit(2);
    }
    if(errflg == 0 && hflg == 0 && ofile == NULL && sfile == NULL && nflg == 0) {
            if(estBienFormate(argv[argc-1]) == 1){
              if(isNote(argv[argc-2]) == 1){
                TriPrint(argv[argc-2], argv[argc-1]);
              }
              else{
                fprintf(stderr,"Veuillez choisir un champ valable");
              }
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }

    }
    if(ofile != NULL){
            if(estBienFormate(argv[argc-1]) == 1){
              if(isNote(argv[optind]) == 1){
                TriFile(argv[optind],argv[argc-1],ofile);
              }
              else{
                fprintf(stderr,"Veuillez choisir un champ valable");
              }
                optind++;
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }

    }
    if(sfile != NULL){
            if(estBienFormate(argv[argc-1]) == 1){
              if(isNote(argv[argc-2]) == 1){
                TriPrintNewSep(argv[argc - 2],sfile, argv[argc-1]);
              }
              else{
                fprintf(stderr,"Veuillez choisir un champ valable");
              }
            }
            else{
                fprintf(stderr,"Fichier mal formate\n");
                exit(2);
            }

    }
    if(nflg == 1){
      if(estBienFormate(argv[argc-1]) == 1){
        if(isNote(argv[argc-2]) == 1){
          printf("%s\n",argv[argc - 2]);
          printf("%s\n\n",argv[argc - 1]);
          TriPrintNum(argv[argc - 2], argv[argc-1]);
        }
        else{
          fprintf(stderr,"Veuillez choisir un champ valable");
        }
      }
      else{
          fprintf(stderr,"Fichier mal formate\n");
          exit(2);
      }
    }

    if(hflg == 1){
       TriAideOpt();
    }
    return 0;
}
