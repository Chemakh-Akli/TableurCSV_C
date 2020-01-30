#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "header/Aux.h"

char* SansEspace(char* s){
  char* a = malloc((strlen(s)+1)*sizeof(char));
  int j = 0;
  int i = 0;
  while(*(s+i)){
    if(*(s+i) != ' '){
      *(a+j) = *(s+i);
      j++;
    }
    i++;
  }
  return a;
}

int comptecomment(char* s){
  char c;
  int count =0;
  FILE * fich = fopen(s,"r");
  if(fich != NULL){
    while ((c=fgetc(fich)) != EOF ){
      if(c == '#'){
        count++;
      }
    }
    fclose(fich);
  }
  return count;
}

char giveSep(char* s){
    char c;
    char res = ';';
    int i = 0;
    FILE* fich = fopen(s,"r");
    if(fich != NULL){
        while( i < comptecomment(s) && (c = fgetc(fich)) != EOF ){
            if( c  == '\n' ){
                i++;
            }
        }
        char sep = fgetc(fich);
        char charsuiv = fgetc(fich);
        if(charsuiv == '\n'){
            res = sep;
        }
        fclose(fich);
    }
    return res;
}

/*
int comptechamp(char* s){
    char c;
    char sep = giveSep(s);
    int count = 0;
    int i = 0;
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
        while ((c = fgetc(fich)) != EOF ){
            if(c == sep){
                count++;
            }
        }
        fclose(fich);
    }
    return count;
}


int max(int a , int b){
  if(a > b){
    return a;
  }
  else{
    return b;
  }
}
*/

int comptechampLigne(char* s){
    char c;
    char sep = giveSep(s);
    int count = 0;
    int max = 0;
    int i = 0;
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
        while ((c = fgetc(fich)) != EOF ){
            if(c == '\n'){
                if(count > max){
                    max = count;
                }
                count = 0;
            }
            if(c == sep){
                count++;
            }
        }
        fclose(fich);
    }
    return max;
}

int compteligne(char* s){
    char c;
    char sep = giveSep(s);
    int count = 0;
    int i = 0;
    FILE* fich = fopen(s,"r");
    int nbcomment;
    if(sep == ';'){
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
        while ((c = fgetc(fich)) != EOF ){
            if(c == '\n'){
                count++;
            }
        }
        fclose(fich);
    }
    return count;
}

int estBienFormate(char* s){
    char sep = giveSep(s);
    int champlignemax = comptechampLigne(s);
    int count = 0;
    int diff;
    int i = 0;
    char c;
    FILE* fich = fopen(s,"r");
    int nbcomment;
    if(sep == ';'){
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
        diff = champlignemax - count;
        if(c == '\n'){
            if(diff != 0 ){
                return 0;
            }
            count = 0;
        }
        if(c == sep){
            count++;
        }
      }
      fclose(fich);
    }
    return 1;
}


char* Select(char* chiffre, char* s){
    char* res = malloc(1000*sizeof(char));
    int idx = 0;
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
          while((c = fgetc(fich)) != EOF &&  c != '\n' ){
            if(c == sep){
              end_print = 1;
            }
            if(end_print != 1){
              res[idx] = c;
              idx++;
            }
          }
          char charsuiv = fgetc(fich);
          if(charsuiv != EOF && charsuiv != '\n'){
            res[idx] = sep;
          }
          fseek(fich, -1L , SEEK_CUR);
          idx++;
          j++;
          end_print = 0;
          srch_champ = 0;
        }
      fclose(fich);
    }
    res[idx] = '\0';
    return res;
}

int isNote(char* note){
  double val;
  char* end;
  val = strtod(note ,&end);
  if(note == end){
    return 0;
  }
  else{
    if(val <= 20 && val >= 0 ){
      return 1;
    }
    else{
      return 0;
    }
  }
}




int nb_sep(char* txt , char sep){
  int cpt = 0;
  for(int i = 0 ; i < strlen(txt) ; i++){
    if(txt[i] == sep){
      cpt++;
    }
  }
  return cpt;
}

void echanger(char** a,char** b){
  char* tmp = *a;
  *a = *b;
  *b = tmp;
}
