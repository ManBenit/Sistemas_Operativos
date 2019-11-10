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


void separarParametros(char comando[],lista *l){
    int lenght=strlen(comando);
    int i=0,indice=0;
    char cadena[50];
    char s[2];
    elemento e;
    limpiarCadena(cadena);
    while(i<lenght){
      if(comando[i]==' ' || comando[i]=='\n' ){
        limpiarCadena(e.c);
        strcpy(e.c,cadena);
        InsertaAlFinal(l,e);
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
  int longitud=strlen(comando);
  while (i<longitud) {
      if(comando[i]=='>'){
          redireccion++;
      }else{
        if(comando[i]=='|'){
          tuberia++;
        }else{
          if(comando[i]=='<'){
            ingreso++;
          }
        }
      }
      i++;
  }
}
void sobreescribirArchivo(char archivoP[]){
  FILE *archivo;
  archivo=fopen(archivoP,"w+");
  fputs(" ",archivo);
  fclose(archivo);
}
void ejecutarDub(char archivo[]){
  sobreescribirArchivo(archivo);
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

int separarRedireccion(lista *l,lista *copia){
  posicion p;
  elemento e;
  int i=0;
  int retorno=0;
  p=First(l);
  for (i = 1;ValidatePosition(l,p); i++) {
    e=Position(l,p);
    if(strcmp(e.c,">")==0){
      retorno=i;
      break;
    }else{
      InsertaAlFinal(copia,e);
    }
    p=Following(l,p);

  }

  return retorno+1;
}



void listaToPointer(lista *l,char *punteroCadena[]){
  int i=0,j=0;
  int nElementos=Size(l)+1;
  posicion p;
  elemento e;
  p=First(l);

  for (j = 0; j < nElementos; j++) {
    punteroCadena[j]=malloc(100*sizeof(char));
  }

  for (i = 1;ValidatePosition(l,p); i++) {
    e=Position(l,p);
    strcpy(punteroCadena[i-1],e.c);
    p=Following(l,p);
  }
  punteroCadena[nElementos-1]=NULL;
}

void ejecutarComando(char comando[]){
  lista comandoSeparado;
  Initialize(&comandoSeparado);
  separarParametros(comando,&comandoSeparado);

  //vfork(): copia el proceso, continua en la copia y
  //y cuando termina su ejecución continua el proceso principal
  //comando simple
  if(tuberia==0 && redireccion==0 && ingreso==0){
      if(!vfork()){
        int tamPointer=Size(&comandoSeparado)+1;
        char *punteroCadena[tamPointer];
        listaToPointer(&comandoSeparado,punteroCadena);
        posicion p=First(&comandoSeparado);
        elemento e=Position(&comandoSeparado,p);
        int execute=execvp(e.c,punteroCadena);
        perror("\nFallo en la ejecución\n");
      }
  }else{
        //comando simple>redireccion
    if (tuberia==0 && redireccion==1 && ingreso==0) {

      if(!vfork()){
        lista redireccionar;
        Initialize(&redireccionar);
        int pos =separarRedireccion(&comandoSeparado,&redireccionar);
        int tamPointer=Size(&redireccionar)+1;
        char *punteroCadena[tamPointer];
        listaToPointer(&redireccionar,punteroCadena);
        posicion v=ElementPosition(&comandoSeparado,pos);
        elemento e= Position (&comandoSeparado, v);
        posicion p=First(&comandoSeparado);
        elemento e2=Position(&comandoSeparado,p);
        ejecutarDub(e.c);
        int execute=execvp(e2.c,punteroCadena);
      }
      printf("redireccion exitosa\n");

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
    analizarComando(comando);
    ejecutarComando(comando);
    tuberia=0;
    redireccion=0;
    ingreso=0;
  }
  return 0;
}
