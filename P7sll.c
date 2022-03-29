#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


typedef struct Node
{
	int data;
	struct Node* next;
} Node;

typedef struct SLL
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} SLL;

typedef struct 
{ 
    SLL* queue; //contnedor de la pila,en este caso es una lista enlazada
                //el top no es nesesario simplemente sera el fente del contenedor
}Stack;

SLL*   SLL_New();
void   SLL_Delete(       SLL** this );
void   SLL_Push_front(   SLL* this, int data );
void   SLL_Push_back(    SLL* this, int data );
void   SLL_Insert(       SLL* this, int data );
int    SLL_Get(          SLL* this );
void   SLL_Pop_front(    SLL* this );
size_t SLL_Len(          SLL* this );
bool   SLL_Is_empty(     SLL* this );
void   SLL_Make_empty(   SLL* this );
void   SLL_Cursor_front( SLL* this );
void   SLL_Cursor_back(  SLL* this );
void   SLL_Cursor_next(  SLL* this );
bool   SLL_Find_if(      SLL* this, int key );
bool   SLL_Find(         SLL* this, int key );



void Stack_Push( Stack* this, int _data );
int Stack_Pop( Stack* this );
void SLL_Print(SLL*this);



// newNode es una función privada, por eso su nombre está fuera 
// del patrón y además no tiene prototipo en el archivo de encabezados.
static Node* newNode( int data )   //revisado
{
	Node* n = (Node*) malloc( sizeof( Node ) );
	if( n ){
		n->data = data;
		n->next = NULL;
	}
	return n;
}

/**
 * @brief Crea una nueva lista SLL
 * @return Referencia a la nueva lista
 */
SLL* SLL_New()   //Revisado
{
	SLL* sll = (SLL*) malloc( sizeof( SLL ) );

	if( sll )
	{
		sll->first = sll->last = sll->cursor = NULL;
		sll->len=0;
	}

	return sll;
}

/**
 * @brief Destruye una lista SLL
 * @param this Referencia a un objeto SLL
 * @post La lista se destruyó y no debiera ser utilizado de nuevo
 */
void SLL_Delete( SLL** this )   //revisado
{
	assert( *this );

	SLL_Make_empty( *this );

	free( *this );

	*this = NULL;
   // primero borra todos los nodos

   // luego borra al propio objeto this

   // luego hace que this sea NULL
}

/**
 * @brief Indica si la lista está vacía
 * @param this Referencia a un objeto SLL
 * @return true si la lista está vacía; false en cualquier otro caso
 */
bool SLL_Is_empty( SLL* this )  // revisado
{
	return( this->len == 0 );
}

void SLL_Push_front( SLL* this, int data )   //revisado
{
	assert( this );

	Node* n = newNode( data );
	// caso de una lista no vacia
	if( this->first != NULL )
	{
		n->next = this->first;
		this->first = n;
	}
	//caso de una lista vacia
	else
	{
		this->first = this->last = this->cursor = n;
	}

	++this->len;
}

void SLL_Push_back( SLL* this, int data )   //revisado
{
	assert( this );

	Node* n = newNode( data );
	if( n )
    {
		if( SLL_Is_empty( this ) )  // si la lista esta vacia
        {
			this->first = this->last = this->cursor = n;
		}
		else
		{
			this->last->next = n;
			this->last = n;
		}
		++this->len;
	}
}

void SLL_Insert( SLL* this, int data )
{
	assert( this );
	assert( this->cursor );

	if( this->cursor == this->last )
	{
		SLL_Push_back( this , data );
	}
	else
	{
		Node* n = newNode( data );

		Node* tmp = this->cursor->next;

		this->cursor->next = n;

		n->next = tmp;

		++this->len;
	}
}

void SLL_Pop_front( SLL* this )
{
   assert( this->first );
   // error fatal si la lista está vacía

	Node* tmp = this->first->next;
	free( this->first );
	this->first = tmp;
	--this->len;
}

/**
 * @brief Devuelve una copia del elemento indicado por el cursor. El
 * comportamiento es indefinido si el cursor no apunta a una posición
 * válida.
 * @param this Referencia a un objeto SLL.
 * @return Una copia del elemento indicado por el cursor
 */
int SLL_Get( SLL* this )        //comprovar funcionamiento
{
   assert( this->first );
   // error fatal si la lista está vacía

   assert( this->cursor );
   // error fatal si el cursor no apunta a una posición válida

   int tmp = (this->cursor->data);

   return tmp; 

}

void SLL_Cursor_front( SLL* this )
{
	this->cursor = this->first;
}

void SLL_Cursor_back( SLL* this )
{
	this->cursor = this->last;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 * @param this Referencia a un objeto SLL.
 * @return true si el cursor se pudo mover a la derecha; 
 *         false en caso contrario.
 * @post El cursor NO se mueve si a la entrada apuntaba a NULL.
 */
void SLL_Cursor_next( SLL* this )
{
	if( this->cursor != NULL )
	{
		this->cursor = this->cursor->next;
    }
}

/**
 * @brief Vacía la lista sin destruirla.
 * @param this Referencia a un objeto SLL.
 * @post La lista queda vacía.
 */
void SLL_Make_empty( SLL* this )
{
	while( this->first != NULL )
	{
		Node* tmp = this->first->next; //creamos un ap a nodo temporal y guardamos la direccion del sig
		free( this->first );          //devolvemos la memoria 
		this->first = tmp;           //first apunta al sig
	}

	this->first = this->last = this->cursor = NULL ;
	this->len = 0;
}

/**
 * @brief Busca si un elemento está en la lista.
 * @param this Referencia a un objeto SLL.
 * @param key El valor que estamos buscando.
 * @return true si se encontró una coincidencia; false en caso contrario.
 * @post Coloca al cursor en el nodo en el que se hubiera encontrado una
 * coincidencia
 */
bool SLL_Find_if( SLL* this, int key )
{
	bool found = false;
	
	if( !SLL_Is_empty( this ) )
	{

		for( Node* it = this->first; it->next != NULL && found == false ; it = it->next ){

			if( key == it->data )
			{
         // si el dato es compuesto, entonces esta instrucción deberá 
         // modificarse
				found = true;
			}
		}
	}
	return found;
}

bool SLL_Find( SLL* this, int key )  //comprovar
{
	bool found = false;
	
	if( !SLL_Is_empty( this ) )
	{

		for( Node* it = this->first; it->next != NULL && found == false ; it = it->next ){

			if( key == it->data )
			{
         // si el dato es compuesto, entonces esta instrucción deberá 
         // modificarse
				found = true;
				this->cursor = it;
			}
		}
	}
	return found;
}

/**
 * @brief Devuelve el número de elementos actualmente en la lista.
 * @param this Referencia a un objeto SLL.
 * @return El número de elementos actualmente en la lista.
 */
size_t SLL_Len( SLL* this )   // comprovar 
{
	return this->len;
}


void SLL_Print(SLL*this)
{
	SLL_Cursor_front(this);

	for (size_t i = 0 ; i < this->len ; i++)
	{
		size_t tmp = SLL_Get(this);

		printf("this->cursor:%p  data:%ld\n",this->cursor, tmp);

		SLL_Cursor_next(this);
	}
	
}


void Stack_Push( Stack* this, int data ) //inserta un elemento en el top o el frente del contenedor lista
{ 
	SLL_Push_front(this->queue, data);
     
} 

int Stack_Pop( Stack* this )  //obtiene el valor en el top y lo elimina del contenedor 
{ 
	SLL_Cursor_front(this->queue);   
    int tmp = SLL_Get(this->queue); 
	SLL_Pop_front(this->queue);
    return tmp; 
} 

#if 1

int main () // prueva de la pila con listas enlazadas
{
	Stack* pila = (Stack*)malloc(sizeof(Stack));

	pila->queue = SLL_New();

	Stack_Push(pila,2);
	Stack_Push(pila, 3);

	int tmp = Stack_Pop(pila);

	printf("%d\n", tmp);

	tmp = Stack_Pop(pila);

	printf("%d\n", tmp);


	SLL_Delete(&pila->queue);

	free(pila);

}

#endif



#if 0

int main()  //driver program para 4.1.2
{
	SLL* lista = SLL_New();

	//insertar 5 valores al fente
	for(size_t i = 0 ; i<5 ; ++i)
	{
		SLL_Push_front(lista , i);
	}

	//imprimir toda la lista
	printf("Primer Impresion:\n");
	SLL_Print(lista);
	
	//insertar 5 valores al fondo de la lista
	for(size_t i = 5 ; i<10 ; ++i)
	{
		SLL_Push_back(lista , i);
	}

	//volver a imprimir toda la lista
	printf("\nSegunda Impresion:\n");
	SLL_Print(lista);

	//insertar 5 valores en el medio de la lista
	SLL_Cursor_front(lista);
	for (size_t i = 0; i < 5; i++) //mover el cursor al medio de la lista
	{
		SLL_Cursor_next(lista);
	}
	for (size_t i = 12; i < 17; i++)//insertar 5 elementos en el medio
	{
		SLL_Insert(lista,i);
	}

	//imprimir lista
	printf("\ntercera Impresion:\n");
	SLL_Print(lista);
	
	//hacer pop a 12 valores
	for (size_t i = 0; i < 12; i++)
	{
		SLL_Pop_front(lista);
	}
	
	//imprimir lista
	printf("\nCuarta Impresion:\n");
	SLL_Print(lista);




	SLL_Delete(&lista);

}

#endif