/*
Autores:
  Benitez Morales Manuel Emilio.
  Cristhian Rikardo Hernández Hernández
  Molina García José Ángel

  2CM8

Fecha: 28 de Noviembre 2019.
Descripción: PROYECTO FINAL, mini bash.
Entrada: Comandos similares al bash de UNIX como cadenas de caracteres.
Salida: Ejecución de las funciones de cada comando utilizando los temas vistos durante el curso.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void limpiarBuffer(){
  int c;
  while((c=getchar())!='\n' && c!=EOF);
}

void imprimirArreglo(char arr[][10],int n){
    int i=0;

    while(i<n){
        printf("%s\n",arr[i]);
      i++;
    }
}
void limpiarCadena(char cadena[]){
  int length=strlen(cadena);
  int i=0;

  while(i<length){
    cadena[i]='\0';
    i++;
  }
}

int contarParametros(char comando[]){
  int lenght=strlen(comando);
  int i=0,contador=0;

  while(i<lenght){
    if(comando[i]==' '){
      contador++;
    }
    i++;
  }
  return contador;

}

void separarParametros(char comando[],char arr[][10]){
    int lenght=strlen(comando);
    int i=0,indice=0;
    char cadena[50];
    char s[2];
    limpiarCadena(cadena);
    while(i<lenght){
      if(comando[i]==' ' || comando[i]=='\n' ){
        limpiarCadena(arr[i]);
        strcpy(arr[indice],cadena);
        indice++;
        limpiarCadena(cadena);
      }else{
        s[0]=comando[i]; s[1]='\0';
        strcat(cadena,s);
      }
      i++;
    }
}

void ejecutarComando(int n, char comando[]){
  int i=0;
  char arr[n][10];
  char rutaComando[50];
  limpiarCadena(rutaComando);
  separarParametros(comando,arr);
  //vfork(): copia el proceso, continua en la copia y
  //y cuando termina su ejecución continua el proceso principal
  if(!vfork()){
    int execute=execl("/usr/bin/which","which",arr[0],">","resultado",NULL);
    perror("\nFallo en la ejecución de exec\n");
  }
}

int main(){
  char comando[30];
  system("clear");
  limpiarCadena(comando);
  while(strcmp(comando, "exit")!=0){
    printf("\n");
    printf("mini-bash>");
    fgets(comando,30,stdin);
    int tamanio=contarParametros(comando)+2;
    printf(" ");
    ejecutarComando(tamanio,comando);
  }
  return 0;
}
