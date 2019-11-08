#ifndef __TADLista_H
#define __TADLista_H

#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;

typedef struct elemento
{
	char c[100];
}elemento;

//Estructura de un NODO DOBLEMENTE LIGADO
typedef struct nodo
{
	elemento e;
	//Realación con el siguiente nodo
	struct nodo *siguiente;
	struct nodo *anterior; //AGREGAMOS UN NODO ANTERIOR
} nodo;

//Se define una posicion como un apuntador a nodo
typedef nodo* posicion;

//Estructura de una lista
typedef struct lista
{
	int tamanio;
	posicion frente;
	posicion final;
}lista;

//Efecto: Recibe una lista l y la inicializa para su trabajo normal.
void Initialize (lista *l);

//Efecto: Recibe una lista l y la libera completamente
void Destroy (lista *l);	//Maykaren Gomez Chávez, Alejandro Hernández Rodríguez.

//Efecto: Recibe una lista l y retorna la posición del elemento al final de esta.
posicion Final (lista *l);//Ramírez García Ana Rubí y Moreno Tinoco Aldo

//Efecto: Recibe una lista l y devuelve la posición del elemento al inicio de esta.
posicion First (lista *l);//Ramírez García Ana Rubí y Moreno Tinoco Aldo

//Efecto: Recibe una lista l, una posición p y devuelve la posición del elemento siguiente de p.
posicion Following (lista *l,posicion p);//Brandon GD

//Efecto: Recibe una lista l, una posición p y devuelve la posición del elemento anterior a p.
//Requerimientos: La lista l es no vacía y la posición p es una posición valida.
posicion Previous (lista *l,posicion p);

//Efecto: Recibe una lista l y un elemento e, devuelve la posición del elemento que coincida exactamente con e.
posicion Search (lista *l,elemento e);

//Efecto: Recibe una lista l, una posición p y devuelve el elemento en dicha posición.
//Requerimientos: La lista l es no vacía y la posición p es una posición valida.
elemento Position (lista *l,posicion p);

//Efecto: Recibe una lista l, una posición p y devuelve TRUE si la posición es una posición p valida en la lista l y FALSE en caso contrario.
boolean ValidatePosition (lista *l,posicion p);

//Efecto: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve la posición del elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
//Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se retorna una posición invalida.
posicion ElementPosition(lista *l, int n);

//Efecto: Recibe una lista y un índice (entre 1 y el tamaño de la lista) y devuelve el elemento que se encuentra en la lista en ese índice partiendo del frente de este =1 hacia atrás.
//Excepción: Si la cola esta vacía o el índice se encuentra fuera del tamaño de la lista se produce error.
elemento Element(lista *l, int n);

//Efecto: Recibe una lista l y devuelve el tamaño de la lista.
int Size (lista *l);

//Efecto: Recibe una lista l y devuelve TRUE en caso de que la lista este vacía y FALSE en caso contrario
boolean Empty (lista *l);

//Efecto: Recibe una lista l y una posición p, el elemento en la posición p será removido.
//Requerimientos: La lista l es no vacía y la posición p es una posición valida.
void Remove (lista *l,posicion p);

//Efecto: Recibe una lista l, una posición p y un elemento e, el elemento en la posición p será sustituido por e
//Requerimientos: La lista l es no vacía y la posición p es una posición valida.
void Replace (lista *l,posicion p, elemento e);

//Efecto: recibe una lista l, una posicion p y un elemento e que se inserta en una posici�n p-1
//Requerimientos: la lista l ya ha sido inicializada
void InsertarAntes(lista *l,posicion p,elemento e);

//Efecto: recibe una lista l, una posicion p y un elemento e que se inserta en una posici�n p+1
//Requerimientos: la lista l ya ha sido inicializada
void InsertarDespues(lista *l,posicion p,elemento e);

//Efecto: recibe una lista l y un elemento e que se inserta en AL INICIO DE LA LISTA
//Requerimientos: la lista l ya ha sido inicializada
void InsertaAlInicio(lista *l, elemento e);

//Efecto: recibe una lista l y un elemento e que se inserta en AL FINAL DE LA LISTA
//Requerimientos: la lista l ya ha sido inicializada
void InsertaAlFinal(lista *l, elemento e);
//Función para usarse en depuración, la cuál imprime las direcciones de
//memoria de los nodos y su apuntador a siguiente
void VerLigasLista(lista *l);
#endif    // __TADLista_H
