#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DEBUG

typedef struct Node
{
	int data;
	struct Node* next;
} Node;

typedef struct CLL
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} CLL;

CLL*   CLL_New();
void   CLL_Delete(       CLL** this );
void   CLL_Push_front(   CLL* this, int data );
void   CLL_Push_back(    CLL* this, int data );
void   CLL_Insert(       CLL* this, int data );
int    CLL_Get(          CLL* this );
void   CLL_Pop_front(    CLL* this );
size_t CLL_Len(          CLL* this );
bool   CLL_Is_empty(     CLL* this );
void   CLL_Make_empty(   CLL* this );
void   CLL_Cursor_front( CLL* this );
void   CLL_Cursor_back(  CLL* this );
void   CLL_Cursor_next(  CLL* this );
bool   CLL_Find_if(      CLL* this, int key );
bool   CLL_Find(         CLL* this, int key );

void SLL_Print(CLL*this);


static Node* newNode( int data )
{
	Node* n = (Node*) malloc( sizeof( Node ) );
	if( n ){
		n->data = data;
		n->next = NULL ;
	}
	return n;
}

/**
 * @brief Crea una nueva lista CLL
 * @return Referencia a la nueva lista
 */
CLL* CLL_New()
{
	CLL* cll = (CLL*) malloc( sizeof( CLL ) );

	if( cll )
	{
		cll->first = cll->last = cll->cursor = NULL;
		cll->len=0;
	}

	return cll;
}

/**
 * @brief Destruye una lista CLL
 * @param this Referencia a un objeto CLL
 * @post La lista se destruyó y no debiera ser utilizado de nuevo
 */
void CLL_Delete( CLL** this )
{
	assert( *this );

	CLL_Make_empty( *this );

	free( *this );

	*this = NULL;
   // primero borra todos los nodos

   // luego borra al propio objeto this

   // luego hace que this sea NULL
}

/**
 * @brief Indica si la lista está vacía
 * @param this Referencia a un objeto CLL
 * @return true si la lista está vacía; false en cualquier otro caso
 */
bool CLL_Is_empty( CLL* this )
{
	return( this->len == 0 );
}

void CLL_Push_front( CLL* this, int data )
{
	assert( this );

	Node* n = newNode( data );

	n->next = this->first;

	this->first = n;

	++this->len;
}

void CLL_Push_back( CLL* this, int data )
{
	Node* n = newNode( data );
	
	if(n)
	{
		if( CLL_Is_empty( this ) )  // si la lista esta vacia
        {
			this->first = this->last = this->cursor = n;
		}
		else
		{
			this->last->next = n;

			this->last = n;

			n->next=this->first;
		}
		++this->len;
	}
	
}

void CLL_Insert( CLL* this, int data )
{
	assert( this );
	assert( this->cursor );

	if( this->cursor == this->last )
	{
		CLL_Push_back( this , data );
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

void CLL_Pop_front( CLL* this )
{
   assert( this->first );
   // error fatal si la lista está vacía

	Node* tmp = this->first->next;
	free( this->first );
	this->first = tmp;
	--this->len;

	this->last->next=this->first;
}

/**
 * @brief Devuelve una copia del elemento indicado por el cursor. El
 * comportamiento es indefinido si el cursor no apunta a una posición
 * válida.
 * @param this Referencia a un objeto CLL.
 * @return Una copia del elemento indicado por el cursor
 */
int CLL_Get( CLL* this )
{
   assert( this->first );
   // error fatal si la lista está vacía

   assert( this->cursor );
   // error fatal si el cursor no apunta a una posición válida

   int tmp = (this->cursor->data);

   return tmp; 

}

void CLL_Cursor_front( CLL* this )
{
	this->cursor = this->first;
}

void CLL_Cursor_back( CLL* this )
{
	this->cursor = this->last;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 * @param this Referencia a un objeto CLL.
 * @return true si el cursor se pudo mover a la derecha; 
 *         false en caso contrario.
 * @post El cursor NO se mueve si a la entrada apuntaba a NULL.
 */
void CLL_Cursor_next( CLL* this )
{
	if( this->cursor != NULL ){
		this->cursor = this->cursor->next;
   }
}

/**
 * @brief Vacía la lista sin destruirla.
 * @param this Referencia a un objeto CLL.
 * @post La lista queda vacía.
 */
void CLL_Make_empty( CLL* this )
{
	for(size_t i=0 ; i<this->len;++i)
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
 * @param this Referencia a un objeto CLL.
 * @param key El valor que estamos buscando.
 * @return true si se encontró una coincidencia; false en caso contrario.
 * @post Coloca al cursor en el nodo en el que se hubiera encontrado una
 * coincidencia
 */

#if 1
bool CLL_Find_if( CLL* this, int key )
{
	bool found = false;
	
	if( !CLL_Is_empty( this ) ){ //si la cosa no esta vacia

		Node* it = this->first;

		for( size_t i = 0 ; i< this->len && found == false ; i++ ){

			if( key == it->data )
			{
				found = true;

				return found;
			}
			it=it->next;
		}
	}
	return found;
}

bool CLL_Find( CLL* this, int key, int* data )
{
	bool found = false;
	
	if( !CLL_Is_empty( this ) ){ //si la cosa no esta vacia

		Node* it = this->first;

		for( size_t i = 0 ; i< this->len && found == false ; i++ ){

			if( key == it->data )
			{
				found = true;

				this->cursor=it;

				return found;
			}
			it=it->next;
		}
	}
	return found;
}

/**
 * @brief Devuelve el número de elementos actualmente en la lista.
 * @param this Referencia a un objeto CLL.
 * @return El número de elementos actualmente en la lista.
 */
size_t CLL_Len( CLL* this )
{

}
#endif

void CLL_Print(CLL*this)
{
	CLL_Cursor_front(this);

	for (size_t i = 0 ; i < this->len ; i++)
	{
		size_t tmp = CLL_Get(this);

		printf("this->cursor:%p  data:%ld\n",this->cursor, tmp);

		CLL_Cursor_next(this);
	}
	
}

int main()  //para probar push back y pop front
{
	CLL* lista = CLL_New();

	CLL_Push_back(lista,1);
	CLL_Push_back(lista,2);
	CLL_Push_back(lista,3);
	CLL_Push_back(lista,4);
	CLL_Push_back(lista,5);

	//imprime la lista de forma vertical
	printf("Primer impresion \n");
	CLL_Print(lista);

	CLL_Pop_front(lista);
	CLL_Pop_front(lista);
	CLL_Pop_front(lista);

	printf("\nSegunda impresion \n");
	CLL_Print(lista);

	CLL_Delete(&lista);

}