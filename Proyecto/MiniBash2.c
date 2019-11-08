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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "TADListaDL.h"

int redireccion=0; //0 si el comando no tiene >
int tuberia=0; // 0 si el comano no tiene |
int ingreso=0; // 0 si el comando no tiene <
int tamanio=0; //cantidad de elementos del arreglo para ejecutar exec

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

void separarParametros(char comando[],char arr[][100]){
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

void analizarComando(char comando[]) {
  int i=0;
  while (i<strlen(comando)) {
      if(comando[i]=='>'){
          redireccion++;;
      }else{
        if(comando[i]=='|'){
          tuberia++;
        }else{
          if(comando[i]=='<'){
            ingreso++;
          }
        }
      }
  }
}
void sobreescribirArchivo(){
  FILE *archivo;
  archivo=fopen("resultado.txt","w+");
  fputs(" ",archivo);
  fclose(archivo);
}
void mandarRutaComandoaArchivo(char archivo[]){
  sobreescribirArchivo();
  int fd=open(archivo,O_WRONLY | O_CREAT,0600);
  if(fd==-1){
    perror("\nfallo en open\n");
    exit(-1);
  }
  //lo mandamos a salida standar
  if(dup2(fd,1)==-1){
    perror("fallo en dup2");
    exit(-1);
  }

  if(close(fd)==-1){
    perror("fallo en close");
    exit(-1);
  }

}

void copiarRutaEjecutable(char rutaComando[]){
  int fd;
  int numberBytes;
  char c;
  char s[2];
  char cadena[50];
  limpiarCadena(cadena);
  fd=open("resultado.txt",O_RDONLY);
  if(fd!=-1){
      while((numberBytes=read(fd,&cadena,sizeof(char)))>0){
        strcat(rutaComando,cadena);
      }
      close(fd);
  }else{
    printf("\nEl archivo no existe\n");
  }
}

/*
  int separarRedireccion(char arr[][100],lista *l){

  si arr contiene n cadenas, devuelve la posion en la que existe
  almacenada el caracter >
  char arr[][100]-> contiene el comando separado en posiciones
  lista *l-> donde copiaremos el comando hasta antes de '>

  NOTA: esta funcion sólo considera una redicrreciones

  Devuelve: posicion de >
*/

int separarRedireccion(char arr[][100],lista *l){
  int i=0,retorno=0;
  while(i<tamanio){
      if(strcmp(arr[i],">")==0){
        retorno=i;
        break;
      }else{
        elemento e;
        limpiarCadena(e.c);
        strcpy(e.c,arr[i]);
        InsertaAlFinal(l,e);
      }
      i++;
  }
  return retorno;
}

void castToPointer(char arr[][100],char *punteroCadena[],int n){
  int i=0;
  for(i=0;i<n;i++){
    int memoria=strlen(arr[i])+1;
    punteroCadena[i]=malloc(memoria*sizeof(char));
    strcpy(punteroCadena[i],arr[i]);
  }
}

void listaToPointer(lista *l,char *punteroCadena[]){
  int i=0;
  posicion p;
  elemento e;
  p=First(l);
  for (i = 1;ValidatePosition(l,p); i++) {
    e=Position(l,p);
    strcpy(punteroCadena[i-1],e.c);
    p=Following(l,p);
  }
}

void ejecutarComando(char comando[]){
  int i=0;
  char arr[tamanio][100];//almacena el comando separado
  char rutaComando[50];
  limpiarCadena(rutaComando);
  separarParametros(comando,arr);
  strcpy(arr[tamanio-1],"\0");

  //vfork(): copia el proceso, continua en la copia y
  //y cuando termina su ejecución continua el proceso principal

  //comando simple
  if(tuberia==0 && redireccion==0 && ingreso==0){
      if(!vfork()){
        char *punteroCadena[tamanio];
        castToPointer(arr,punteroCadena,tamanio);
        punteroCadena[tamanio-1]=NULL;
        int execute=execvp(arr[0],punteroCadena);
        perror("\nFallo en la ejecución\n");
      }
      sleep(2);
      system("clear");
  }else{
        //comando simple>redireccion
    if (tuberia==0 && redireccion==1 && ingreso==1) {

      if(!vfork()){
        lista miLista;
        Initialize(&miLista);
        int pos=separarRedireccion(arr,&miLista)+1;
        char *punteroCadena[Size(&miLista)];
        listaToPointer(&miLista,punteroCadena);
        mandarRutaComandoaArchivo(arr[pos]);
        int execute=execvp(arr[0],punteroCadena);
      }
      sleep(2);
      system("clear");
    }
  }

}

int main(){
  char comando[100];
  system("clear");
  limpiarCadena(comando);
  while(strcmp(comando, "exit")!=0){
    printf("\n");
    printf("mini-bash>");
    fgets(comando,100,stdin);
    tamanio=contarParametros(comando)+2;
    ejecutarComando(comando);
  }
  return 0;
}
