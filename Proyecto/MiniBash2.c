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

int redireccion=0; //0 si el comando no tiene >
int tuberia=0; // 0 si el comano no tiene |
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

void analizarComando(char comando[]) {
  int i=0;
  while (i<strlen(comando)) {
      if(comando[i]=='>'){
          redireccion=1;
      }else{
        if(comando[i]=='|'){
          tuberia=1;
        }
      }
  }
}

void mandarRutaComandoaArchivo(){
	int copia=dup(1);
  int fd=open("resultado.txt",O_WRONLY | O_CREAT,0600);
	printf("COPIA %d FD %d",copia,fd);
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
  char c;
  char s[2];
  fd=open("resultado.txt",O_RDONLY);
  printf("fd %d\n",fd);
  if(fd!=-1){
	printf("ENTRA \n");
      while(read(fd,&c,sizeof(c)!=0)){
	printf("HOLA\n");
        s[0]=c;
        s[1]='\0';
        strcat(rutaComando,s);
	printf("%c H\n",c);
      }
      close(fd);
  }else{
    printf("\nEl archivo no existe\n");
  }
}

void castToPointer(char arr[][10],char *punteroCadena[],int n){
  int i=0;
  for(i=0;i<n;i++){
    punteroCadena[i]=malloc(10*sizeof(char));
    strcpy(punteroCadena[i],arr[i]);
  }
}

void ejecutarComando(int n, char comando[]){
  int i=0;
  char arr[n][10];
  char rutaComando[50];
  char *punteroCadena[n];
  limpiarCadena(rutaComando);
  separarParametros(comando,arr);
  strcpy(arr[n-1],"NULL");

  //vfork(): copia el proceso, continua en la copia y
  //y cuando termina su ejecución continua el proceso principal

  /*
    Vamos a sacar la ruta del comando principal
  */
  //imprimirArreglo(arr,n);
  if(!vfork()){
    mandarRutaComandoaArchivo();
    int execute=execl("/usr/bin/which","which",arr[0],NULL);
	//dup2(3,1);
	//close(3);
    perror("\nFallo en la ejecución de exec\n");
  }

  copiarRutaEjecutable(rutaComando);
  printf("%s\n",rutaComando );


/*
  if(tuberia==0 && redireccion==0){
    copiarRutaEjecutable(rutaComando);
    printf("Ruta comando %s\n",rutaComando);
      if(!vfork()){
        castToPointer(arr,punteroCadena,n);
        int i=0;
        for(i=0;i<n;i++){
          printf("hola\n");
          printf("%s\n",punteroCadena[i]);
        }
        int execute=execv(rutaComando,punteroCadena);
        perror("\nFallo en la ejecución\n");
      }
  }
*/

}

int main(){
  char comando[30];
  system("clear");
  limpiarCadena(comando);
  while(strcmp(comando, "exit")!=0){
    printf("\n");
    printf("mini-bash>");
    fgets(comando,30,stdin);
    tamanio=contarParametros(comando)+2;
    printf(" ");
    ejecutarComando(tamanio,comando);
  }
  return 0;
}
