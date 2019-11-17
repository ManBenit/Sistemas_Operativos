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
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "TADListaDL.h"

void ejecutarComandoTuberias(lista *comando);
void ejecutarComando(char comando[]);
int rdPipe=0;
int limpiar=0;
char txtPipe[100];
void limpiarBuffer(){
  int c;
  while((c=getchar())!='\n' && c!=EOF);
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

int contarRedireccion(char comando[]){
  int i=0;
  int contador=0;
  int longitud=strlen(comando);
    while (i<longitud) {
      if(comando[i]=='>'){
          contador++;
      }
      i++;
    }
    return contador;
}
int contarIngreso(char comando[]){
  int i=0;
  int contador=0;
  int longitud=strlen(comando);
    while (i<longitud) {
      if(comando[i]=='<'){
          contador++;
      }
      i++;
    }
    return contador;

}
int contarTuberia(char comando[]){
  int i=0;
  int contador=0;
  int longitud=strlen(comando);
    while (i<longitud) {
      if(comando[i]=='|'){
          contador++;
      }
      i++;
    }
  return contador;
}

void sobreescribirArchivo(char archivoP[]){
  FILE *archivo;
  archivo=fopen(archivoP,"w+");
  fputs(" ",archivo);
  fclose(archivo);
}
void ejecutarDub(char archivo[]){
  int stdout_save=dup(STDOUT_FILENO);
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
  //sleep(1);
}

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


void separarIngreso(lista *l,lista *copia){
  posicion p;
  elemento e;
  int i=0;
  p=First(l);
  for (i = 1;ValidatePosition(l,p); i++) {
    e=Position(l,p);
    if(strcmp(e.c,"<")!=0){
      if(strcmp(e.c,">")==0){
        break;
      }else{
        InsertaAlFinal(copia,e);
      }
    }
    p=Following(l,p);
  }
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

void imprimeLista( lista *l){
  posicion p;
  elemento e;
  int i=0;

  p=First(l);

  for(i=1;ValidatePosition(l,p);i++){
    e=Position(l,p);
    printf("\nElemento[%d]->%s\n",i,e.c);
    p=Following(l,p);
  }
}

void imprimePuntero(char *Pointer[], int tamP){
  int i=0;

  for(i=0;i<tamP;i++){
    printf("%s\n",Pointer[i]);
  }
}

void ejecutarDubTuberia(){
  sobreescribirArchivo("tuberia.txt");
  int fd=open("tuberia.txt",O_WRONLY | O_CREAT,0600);
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
  //sleep(1);

}
 void imprimirCad(char cad[]) {
  int i=0;
  while (cad[i]!='\0') {
    printf("%c->%d\n",cad[i],cad[i]);
    i++;
  }
}
void ejecutarComandoTuberias(lista *comando) {
  posicion p;
  elemento e;
  char comand[100];
  limpiarCadena(comand);
  int i=0;
  int contador=0; // la vamos a ir incrementando cada que se encuentre una pipe
  p=First(comando);
  for(i=1;ValidatePosition(comando,p);i++){
    e=Position(comando,p);
    if(strcmp(e.c,"|")==0){
      contador++;
      if(contador==1){
        strcat(comand,"> tuberia.txt\n");
        ejecutarComando(comand);
      }else{
        if(contador>1){
            strcat(comand,"< tuberia.txt > tuberia2.txt\n"); //lee el archivo
	          //imprimirCad(comand);
		        ejecutarComando(comand);
            ejecutarComando("cp tuberia2.txt tuberia.txt\n");
        }
      }
      limpiarCadena(comand);
    }else{
      strcat(e.c," ");
      strcat(comand,e.c);
    }
    p=Following(comando,p);
  }
    strcat(comand,"< tuberia.txt\n"); //ejecuta el comando final de la tuberia
    if(rdPipe==1){
      ejecutarDub(txtPipe);
    }
    ejecutarComando(comand);
}

void listaToCommand(char cadena[],lista *l){
  posicion p;
  elemento e;
  int i=0;

  p=First(l);

  for(i=1;ValidatePosition(l,p);i++){
    e=Position(l,p);
    if(i==1){
      strcat(cadena,e.c);
    }else{
      strcat(cadena," ");
      strcat(cadena,e.c);
    }
    p=Following(l,p);
  }
  strcat(cadena,"\n");
}

void ejecutarComando(char comando[]){
  sleep(1);
  int redireccion=contarRedireccion(comando); //0 si el comando no tiene >
  int tuberia=contarTuberia(comando); // 0 si el comano no tiene |
  int ingreso=contarIngreso(comando); // 0 si el comando no tiene <
  lista comandoSeparado;
  Initialize(&comandoSeparado);
  separarParametros(comando,&comandoSeparado);
  //imprimeLista(&comandoSeparado);
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
        perror("\nFallo en la ejecución\n");

      }

    }else{
        if (tuberia==0 && redireccion==0 && ingreso==1) {
              if(!vfork()){
                  lista redireccionar;
                  Initialize(&redireccionar);
                  separarIngreso(&comandoSeparado,&redireccionar);
                  int tamPointer=Size(&redireccionar)+1;
                  char *punteroCadena[tamPointer];
                  listaToPointer(&redireccionar,punteroCadena);
                  posicion p=First(&redireccionar);
                  elemento e=Position(&redireccionar,p);
                  int execute=execvp(e.c,punteroCadena);
                  perror("\nFallo en la ejecución\n");

              }
          }else{
              //comando < archivo > archivo
            if (tuberia==0 && redireccion==1 && ingreso==1) {
                  if(!vfork()){
                      lista redireccionar;
                      Initialize(&redireccionar);
                      separarIngreso(&comandoSeparado,&redireccionar);
                      posicion aux=Final(&comandoSeparado);
                      elemento k=Position(&comandoSeparado,aux);
                      elemento rd;
                      limpiarCadena(rd.c);
                      strcpy(rd.c,">");
                      InsertaAlFinal(&redireccionar,rd);
                      InsertaAlFinal(&redireccionar,k);
                      char comandoNUevo[100];
                      limpiarCadena(comandoNUevo);
                      listaToCommand(comandoNUevo,&redireccionar);
                      ejecutarComando(comandoNUevo);
                  }
              }else{
                if (tuberia>0 && redireccion==0) {
                    ejecutarComandoTuberias(&comandoSeparado);
                }else{
                  if (tuberia>0 && redireccion==1) {
                    if(!vfork()){
                      lista redireccionar;
                      Initialize(&redireccionar);
                      int pos =separarRedireccion(&comandoSeparado,&redireccionar);
                      int tamPointer=Size(&redireccionar)+1;
                      char *punteroCadena[tamPointer];
                      listaToPointer(&redireccionar,punteroCadena);
                      posicion v=ElementPosition(&comandoSeparado,pos);
                      elemento e= Position (&comandoSeparado, v);
                      rdPipe=1;
                      strcpy(txtPipe,e.c);
                      ejecutarComandoTuberias(&redireccionar);
                    }
                  }
                }
              }
          }
    }
  }
}

int main(){
  rdPipe=0;
  char comando[100];
  system("clear");
  limpiarCadena(txtPipe);
  limpiarCadena(comando);
  printf("\n");
  printf("mini-bash>");
  while(1){
    int stdout_save=dup(STDOUT_FILENO);
    fgets(comando,100,stdin);
    if (strcmp(comando,"exit\n")==0) {
      printf("\nConsola terminada\n");
      exit(0);
    }
    ejecutarComando(comando);
    dup2(stdout_save,STDOUT_FILENO);
    sleep(1);
    printf("\nEjecución teminada\n");
    printf("\nmini-bash>");
    rdPipe=0;
    limpiarCadena(txtPipe);
    limpiarCadena(comando);
  }
  return 0;
}
