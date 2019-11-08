
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TADListaDL.h"

//DEFINICIÓN DE FUNCIONES

/***************************************************
Operaciones de construcción
***************************************************/
/*
void Initialize(lista *l)
Descripción: Inicializar lista (Iniciar una lista para su uso)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Initialize (lista *l) //YA
{
	l->frente=NULL;
	l->final=NULL;
	l->tamanio=0;
	return;
}


/*
void Destroy(lista *l)
Descripción: Destruir una lista (Recibe una lista l y la libera completamente)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve:
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
void Destroy (lista *l)
{
	//Apuntador auxiliar a nodo
	nodo *aux;

	//Mientras el apuntador del frente de la lista no sea "NULL"
	while(l->frente != NULL)
	{
		//Guardar la referencia el frente
		aux = l->frente;

		//El nuevo frente es el siguiente
		l->frente = l->frente->siguiente;

		//Liberar el antiguo frente de memoria
		free(aux);
	}

	//Colocar el final inicializado en "NULL"
	l->final = NULL;
	l->tamanio = 0;

	return;
}

/***************************************************
Operaciones de posicionamiento y busqueda
***************************************************/
/*
posicion Final(lista *l)
Descripción: Recibe una lista l y regresa la posición del final (Recibe una
lista l y retorna la posición del elemento al final de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posición del nodo que contiene al elemeto final de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
posicion Final (lista *l) //YA
{
	return l->final;
}

/*
posicion First(lista *l)
Descripción: Recibe una lista l y regresa la posición del frente (Recibe una
lista l y retorna la posición del elemento al frente de esta.)
Recibe: lista *l (Referencia a la lista "l" a operar)
Devuelve: posición del nodo que contiene al elemento del frente de la lista
Observaciones: El usuario a creado una lista y l tiene la referencia a ella,
si esto no ha pasado se ocasionara un error.
*/
posicion First (lista *l) //YA
{
	return l->frente;
}

/*
posicion Following(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve la posición del
elemento siguiente de p
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posición valida de la lista)
Devuelve: posición del nodo siguiente a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista,
si esto no ha pasado se ocasionara un error.
*/
posicion Following (lista *l,posicion p)//YA
{
	if(ValidatePosition(l,p))
	{
		return p->siguiente;
	}
	else
	{
		printf("ERROR: Función Following (p es invalida)");
		exit(1);
	}
}


/*
posicion Previous(lista *l, posicion p)
Descripción: Recibe una lista L, una posición P y devuelve la posición del
elemento anterior de P
Recibe: lista *l y posicion p (Referencia a la lista "l" a operar y posición valida de la lista)
Devuelve: posición del nodo anterior a la posicion dada
Observaciones: El usuario a creado una lista y l tiene la referencia a ella, p es una posicion valida de la lista, si esto no ha pasado se ocasionara un error.
*/
posicion Previous (lista *l,posicion p) //YA
{
	posicion anterior=NULL, aux;

	if(ValidatePosition(l,p)){
		return p->anterior;
	}else{
		printf("ERROR: Función Previous (p es invalida)");
		exit(1);
	}
}


/*
posicion Search(lista *l, elemento e)
Descripción: Recibe una lista l y un elemento e, regresa la posición que coincida exactamente con el elemento e.
Recibe: lista *l y un elemento e (Referencia a la lista "l" a operar y elemento a buscar en la lista)
Devuelve: posición del elemento en caso de ser encontrado, si no se encuentra se devuelve una posicion invalida
Observaciones: El usuario a creado una lista y l tiene la referencia a ella el elemento a buscar se compara directamente
a nivel de bytes.
*/
posicion Search (lista *l,elemento e) //YA
{
	posicion aux=l->frente;
	while(aux!=NULL)
	{
		if(memcmp(&aux->e,&e,sizeof(elemento))==0)
		{
			return aux;
		}
		aux=aux->siguiente;
	}
	return NULL;
}

/***************************************************
Operaciónes de consulta
/***************************************************/
/*
elemento Position(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve el elemento en dicha posición.
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar posicion valida en la lista)
Devuelve: Elemento en la posicion dada, si la posicion es invalida se genera error.
Observaciones: La lista l es no vacía y la posición p es una posición valida.
*/
elemento Position (lista *l,posicion p)//YA
{
	elemento e;
	if(ValidatePosition(l,p))
		return p->e;
	else
	{
		printf("\nERROR Position(): La posicion es invalida");
		exit(1);
	}
}

/*
boolean ValidatePosition(lista *l, posicion p)
Descripción: Recibe una lista l, una posición p y devuelve TRUE si la posición es una posición p valida en la lista l y FALSE en caso contrario.
Recibe: lista *l y una posicion p(Referencia a la lista "l" a operar y una posicion)
Devuelve: Booleano
Observaciones:
*/
boolean ValidatePosition (lista *l,posicion p)
{
	posicion aux;
	aux=l->frente;
	while(aux!=NULL)
	{
		if(aux==p) //**************
			return TRUE;
		aux=aux->siguiente;
	}
	return FALSE;
}

/*
elemento Element(lista *l, int n)
Descripción: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
Recibe: lista *l y una entero
Devuelve: elemento
Observaciones: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
*/
elemento Element(lista *l, int n) //YA
{
	elemento r;
	nodo *aux;
	int i;
	//Si el elemento solicitado esta entre 1 y el tamaño de la lista
	if (n>0&&n<=Size(l))
	{
		//Obtener el elemento en la posición n
		aux=l->frente;
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		r=aux->e;
	}
	else
	{
		printf("\nERROR (Element): Se intenta acceder a elemento %d inexistente",n);
		exit(1);
	}
	return r;
}

/*
posicion ElementPosition(lista *l, int n)
Descripción: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve la posicion del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
Recibe: lista *l y una entero
Devuelve: posicion
Observaciones: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
*/
posicion ElementPosition(lista *l, int n)//YA
{
	posicion aux=NULL;
	int i;
	//Si el elemento solicitado esta entre 1 y el tamaño de la lista
	if (n>0&&n<=Size(l))
	{
		//Obtener el elemento en la posición n
		aux=l->frente;
		for(i=2;i<=n;i++)
			aux=aux->siguiente;
		return aux;
	}
	else
	{
		printf("\nERROR (ElementPosition): Se intenta acceder a posicion %d inexistente",n);
		exit(1);
	}
	return aux;
}

/*
int Size(lista * l);
Descripción: Recibe una lista y devuelve el número de elemento que se encuentran en esta.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: int (Tamaño de la lista)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
int Size (lista *l)
{
	return l->tamanio;
}

/*
int Size(lista * l);
Descripción: Recibe una lista l y devuelve TRUE en caso de que la lista este vacía y FALSE en caso contrario.
Recibe: lista *l (Referencia a la lista "l")
Devuelve: boolean (TRUE o FALSE)
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada.
*/
boolean Empty (lista *l)
{
	return (l->tamanio==0) ? TRUE:FALSE;
}
/***************************************************
Operaciones de modificación
****************************************************/

/*
void  InsertarDespues(lista *l, posicion p,elemento e)
Descripción: Recibe una lista ,una posicion p y un elemento e, el cual inserta en un nodo creade despu�s de p
Recibe: lista *l, posicion p,elemento e
Devuelve:
Observaciones: La pila debe estar inicializada
*/
void InsertarDespues(lista *l, posicion p,elemento e){ //YA
	posicion aux;
	aux=malloc(sizeof(nodo));

	if(aux==NULL){
		printf("\nERROR (InsertarDespues): No se puede crear un nuevo nodo");
		exit(1);
	}
	//Introducir a e en el nuevo nodo
	aux->e=e;
	aux->anterior=p;

	//Si  est� vacia  la lista
	if(p->siguiente==NULL){
		aux->siguiente=NULL; //Ahora el nuevo elemento aux ser� el ultimo y apunta a NULL
		l->final=aux;
	}else{ //Si p hace referencia a cualquier otro elemento de la lista
		aux->siguiente=p->siguiente; // el nodo que p tenia como siguiente ahora ser� el siguiente de aux
		p->siguiente->anterior=aux;
	}
	p->siguiente=aux; //aux ahora ser� el nodo siguiente de p
	l->tamanio++;
}

/*
void  InsertarAntes(lista *l, posicion p,elemento e)
Descripción: Recibe una lista ,una posicion p y un elemento e, el cual inserta en un nodo creado antes de p
Recibe: lista *l, posicion p,elemento e
Devuelve:
Observaciones: La pila debe estar inicializada
*/
void InsertarAntes(lista *l, posicion p,elemento e){
	posicion aux;
	aux=malloc(sizeof(nodo));

	if(aux==NULL){
		printf("\nERROR (InsertarAntes): No se puede crear un nuevo nodo");
		exit(1);
	}

	aux->e=e;
	aux->siguiente=p;

	if(p->anterior==NULL){//si el nodo anterior es nulo (como cuando solo hay un elemento en la lista o la pila est� vacia)
		aux->anterior=NULL;
		l->frente=aux;
	}else{
		aux->anterior=p->anterior;
		p->anterior->siguiente=aux;
	}
	p->anterior = aux ;
	l->tamanio++;
}

/*
void  InsertaAlInicio(lista *l,elemento e)
Descripción: Recibe una lista  y un elemento e, el cual inserta en un nodo creado antes de como frente
				sila pila esta vacia o modificando el nodo frente si la lista ya cuenta con elementos
Recibe: lista *l, posicion p,elemento e
Devuelve:
Observaciones: La pila debe estar inicializada
*/

void InsertaAlInicio(lista *l,elemento e){
	posicion aux;
	aux=malloc(sizeof(nodo));


	if(aux==NULL){
		printf("\nERROR (InsertaAlInicio): No se puede crear un nuevo nodo");
		exit(1);
	}

	if(l->frente==NULL){ //SI LA LISTA ESTA VACIA
		aux->e=e;
		l->frente=aux;
		l->final=aux;
		aux->anterior=NULL;
		aux->siguiente=NULL;
		l->tamanio++;
	}else{
		InsertarAntes(l,l->frente,e);
	}
}

/*
void  InsertaAlInicio(lista *l,elemento e)
Descripción: Recibe una lista  y un elemento e, el cual inserta en un nodo creado antes de como frente
				sila pila esta vacia o modificando el nodo final si la lista ya cuenta con elementos
Recibe: lista *l, posicion p,elemento e
Devuelve:
Observaciones: La pila debe estar inicializada
*/

void InsertaAlFinal(lista *l,elemento e){
	if(l->final==NULL){//si la lista esta vacia
		InsertaAlInicio(l,e);
	} else{
		InsertarDespues(l,l->final,e);
	}
}

/*
void Remove (lista *l,posicion p);
Descripción: Recibe una lista l y una posición p, el elemento en la posición p será removido.
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a eliminar en la lista)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Remove (lista *l,posicion p)// YA
{
	posicion aux;
	//Si p es valida
	if(ValidatePosition(l,p))
	{
		if(p->anterior==NULL){
			l->frente=p->siguiente;
		}else{
			p->anterior->siguiente=p->siguiente;
		}

		if(p->siguiente==NULL){
			l->final=p->anterior;
		}else{
			p->siguiente->anterior=p->anterior;
		}
		free(p);
		l->tamanio--;
	}
	else
	{
		printf("\nERROR: Remove p es invalida");
		exit(1);
	}

	return;
}


/*
void Replace (lista *l,posicion p, elemento e);
Descripción: Recibe una lista l, una posición p y un elemento e, el elemento en la posición p será sustituido por e
Recibe: lista *l (Referencia a la lista "l"), posicion p (posicion a remplazar en la lista), elemento e (elemento que remplazara al existente en p)
Devuelve:
Observaciones: El usuario a creado una lista,la lista fue correctamente inicializada, la posicion p es valida.
*/
void Replace (lista *l,posicion p, elemento e)// YA
{
	//Si la posicion p existe
	if(ValidatePosition(l,p))
	{
		p->e=e; //Remplazar a e
	}
	else{
		printf("\nERROR: Replace : No se puede remplazar una posicion invalida");
		exit(1);
	}
	return;
}

/********************************************************************************
//Función para usarse en depuración, la cuál imprime las direcciones de
//memoria de los nodos y su apuntador a siguiente
********************************************************************************/
void VerLigasLista(lista *l)
{
	posicion aux;
	aux=l->frente;
	printf("\n*************************************************************");
	while(aux!=NULL)
	{
		printf("\nPosicion=%p\tSiguiente=%p",aux,aux->siguiente);
		aux=aux->siguiente;
	}
	printf("\n*************************************************************");

	return;
}
