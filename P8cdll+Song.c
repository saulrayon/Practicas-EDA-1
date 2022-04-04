//estructura de datos circular double linked list
//lista enlazada doble circular mas estructura Song


#if 1 // para el archivo .h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


typedef struct
{
  char name[25];  //nombre de la cancion
  char singer[25]; //cantante
  int duration;   //duracion de la cancion en segundos  
}Song;


typedef struct Node  //nodo de la CDLL modificado para guardar canciones
{
	Song cancion;

	struct Node* next;
	struct Node* prev;
} Node;

typedef struct  //CDLL modificada para que guarde canciones
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} CDLL;


// las de nuestra practica de hoy
static Node* new_node( Song x );
CDLL* CDLL_New();
void CDLL_Delete( CDLL** this );

int CDLL_Front( CDLL* this );
int CDLL_Back( CDLL* this );

void CDLL_Push_front( CDLL* this, int item );
void CDLL_Push_back( CDLL* this, int item );
void CDLL_Insert( CDLL* this, int item );

void CDLL_Pop_front( CDLL* this );
void CDLL_Pop_back( CDLL* this );

void CDLL_Erase( CDLL* this );
void CDLL_Remove( CDLL* this, int key );

void CDLL_MakeEmpty( CDLL* this );

bool CDLL_Find( CDLL* this, int key );

int  CDLL_Cursor_Get( CDLL* this );
void CDLL_Cursor_front( CDLL* this );
void CDLL_Cursor_back( CDLL* this );
void CDLL_Cursor_next( CDLL* this );
void CDLL_Cursor_prev( CDLL* this );
bool CDLL_Cursor_end( CDLL* this );

bool CDLL_IsEmpty( CDLL* this );
size_t CDLL_Len( CDLL* this );


void CDLL_PrintStructure( CDLL* this );

// avanzadas:
void CDLL_For_each( CDLL* this, void (*p_fn)( int item ) );
Node* CDLL_Find_if( CDLL* this, bool (*p_fn)( int, int ), int key );
size_t CDLL_Remove_if( CDLL* this, bool (*cmp)( int x, int y ), int key );


#endif



#if 1 //para el archivo .c


static Node* new_node( Song x ) //ya esta
{
   Node* n = (Node*) malloc( sizeof( Node ) );
   if( n != NULL )
   {
      n->cancion = x;
      n->next = NULL;
      n->prev = NULL;
   }

   return n;
}

/**
 * @brief Crea una lista doblemente enlazada
 *
 * @return Una referencia a la nueva lista
 * @post Una lista existente en el heap
 */
CDLL* CDLL_New() //ya esta
{
   CDLL* list = (CDLL*) malloc( sizeof( CDLL ) );
   if( list != NULL ){
      list->first = NULL;
      list->last = NULL;
      list->cursor = NULL;
      list->len = 0;
   }

   return list;
}

/**
 * @brief Destruye una lista.
 *
 * @param this Una lista.
 */
void CDLL_Delete( CDLL** this )  //ya esta
{
   assert( *this );    //*this es: la lista o su direccion

   // 1. Borramos todos los nodos:
   while( (*this)->len != 0 )
   {
      CDLL_Pop_back( *this );
   }

   // 2. Borramos al objeto DLL:
   free( *this );

   // 3. Evitamos problemas futuros:
   *this = NULL;

}

/**
 * @brief Devuelve una copia del elemento en el frente de la lista
 *
 * @param this Una lista
 *
 * @return La copia del elemento en el frente de la lista
 *
 * @pre La lista NO debe estar vacía
 */
int CDLL_Front( CDLL* this )  //ya esta
{
   assert( this->first != NULL );
   // ERR: no se puede leer de una lista vacía

   return this->first->datos;
}

/**
 * @brief Devuelve una copia del elemento en la parte trasera de la lista.
 *
 * @param this Una lista.
 *
 * @return La copia del elemento en la parte trasera de la lista.
 *
 * @pre La lista NO debe estar vacía
 */
Song CDLL_Back( CDLL* this )  //ya esta
{
   assert( this->last != NULL );
   // ERR: no se puede leer de una lista vacía

   return this->last->cancion;
}

/**
 * @brief Inserta un elemento en el frente de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void CDLL_Push_front( CDLL* this, int item )
{
   //error si this no existe
   assert( this ); 

	Node* n = newNode( item );

   //caso de una lista vacia
   if( this->first == NULL );
   {
      this->first = this->last = this->cursor = n;
   }
	else // caso de una lista no vacia
   {
      //guardamos el nodo previo al primero
      Node* tmp_Prev_first = this->first->prev;

      //conectamos a el nuevo nodo a la lista
      tmp_Prev_first->next = n;

      n->prev = tmp_Prev_first;

      n->next = this->first;

      this->first->prev = n;

      this->first = n;
   }

	++this->len;
}

/**
 * @brief Inserta un elemento en el fondo de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void CDLL_Push_back( CDLL* this, int item )
{
   //error si this no existe
   assert( this ); 

	Node* n = newNode( item );

   //caso de una lista vacia
   if( this->last == NULL );
   {
      this->first = this->last = this->cursor = n;
   }
	else // caso de una lista no vacia
   {
      //guardamos el nodo siguiente al ultimo
      Node* tmp_Next_last = this->last->next;

      //conectamos a el nuevo nodo a la lista
      tmp_Next_last->prev = n;

      n->next = tmp_Next_last;

      n->prev = this->last;

      this->last->next = n;

      this->last = n;
   }

	++this->len;
}


/**
 * @brief Inserta un elemento a la derecha del cursor
 *
 * @param lista Una referencia a la lista de trabajo
 * @param item El elemento a insertar
 *
 * @post Coloca al cursor en el nuevo nodo
 *
 */
//analizar el cazo donde hay solo un elemento y cambiar a insertar a la derecha
void CDLL_Insert( CDLL* this, Song item ) //insertar a la derecha del cursor
{
   //si la lista esta vacia crear el primer nodo
   if(this->cursor==NULL);
   {
        CDLL_Push_front( this , item );    
   }
   else // la lista no esta vacia
   {
        //guardamos el siguiente elemento donde de donde esta el cursor
        Node* tmp_Next_cursor = this->cursor->next;

        //creamos un nuevo nodo
        Node* n = new_node(item);

        //conectamos el nuevo nodo con sus hermanos
	    tmp_Next_cursor->prev = n;

        n->next = tmp_Next_cursor;

        n->prev = this->cursor;

        this->cursor->next = n; 

    
        ++this->len;

        //importante si se esta insertando al final de la lista se tiene
        // que actualizar el campo last
        if(this->cursor==this->last)
        {
            this->last = n;
        }
        //si se inserta al comienzo de la lista no hay problema por que se inserta a la derecha del cursor
   }
}


/**
 * @brief Elimina el elemento al frente de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */
void CDLL_Pop_front( CDLL* this )  //ya esta
{
   assert( this->len=0 );
   // error si la lista está vacía
    
   //guardamos el previo y el siguiente del primer elemento
	Node* tmp_Next_first = this->first->next; 

   Node* tmp_Prev_first = this->first->prev;

   //devolvemos memoria del primer elemento
	free( this->first );

   //ahora el primer elemento es:
   this->first = tmp_Next_first;

   //volver a unir la lista 
   tmp_Next_first->prev = tmp_Prev_first;

   tmp_Prev_first->next = tmp_Next_first;

	--this->len;
}

/**
 * @brief Elimina el elemento al fondo de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posición en la que estaba cuando entró la
 * función.
 */
void CDLL_Pop_back( CDLL* this ) //ya esta
{
   assert( this->len=0 );
   // error si la lista está vacía
    
   //guardamos el previo y el siguiente del ultimo elemento
	Node* tmp_Next_last = this->last->next; 

   Node* tmp_Prev_last = this->last->prev;

   //devolvemos memoria del ultimo elemento
	free( this->last );

   //ahora el ultimo elemento es:
   this->last = tmp_Prev_last;

   //volver a unir la lista 
   tmp_Prev_last->next = tmp_Next_last;

   tmp_Next_last->prev = tmp_Prev_last

	--this->len;

}

/**
 * @brief Elimina el elemento apuntado por el cursor.
 *
 * @param this Una lista.
 *
 */
void DLL_Erase( DLL* this )
{
}

/**
 * @brief Elimina el primer nodo que coincida con la llave.
 *
 * @param this Una lista
 * @param key  Valor buscado
 *
 */
void DLL_Remove( DLL* this, int key )
{
}

/**
 * @brief Elimina todos los elementos de la lista sin eliminar la lista.
 *
 * @param this Una lista
 */
void CDLL_MakeEmpty( CDLL* this )
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
 * @brief Busca un valor en la lista. Si lo encuentra coloca ahí al cursor.
 *
 * @param this Una lista.
 * @param key El valor que se está buscando.
 *
 * @post Si se encontró una coincidencia coloca al cursor en ese nodo; en caso contrario el cursor es NULL.
 *
 * @code
 * if( DLL_Find( list, x ) )
 * {
 *    y = DLL_Cursor_Get( list );
 *
 *    // ...
 * }
 * @endcode
 */
bool DLL_Find( DLL* this, int key )
{
   for( this->cursor = this->first; 
        this->cursor != NULL; 
        this->cursor = this->cursor->next )
   {
      if( this->cursor->datos == key )
      {
         return true;
      }
   }
   return false;
}

/**
 * @brief Devuelve una copia del valor apuntado por el cursor
 *
 * @param this Una lista
 *
 * @return El valor apuntado por el cursor
 */
int DLL_Cursor_Get( DLL* this )
{
}

/**
 * @brief Coloca al cursor al inicio de la lista.
 *
 * @param this Una referencia a la lista de trabajo
 */
void CDLL_Cursor_front( CDLL* this )
{
   this->cursor = this->first;
}

/**
 * @brief Coloca al cursor al final de la lista.
 *
 * @param this Una referencia a la lista de trabajo
 */
void CDLL_Cursor_back( CDLL* this )
{
   this->cursor = this->back;
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 *
 * @param this Una lista.
 */
void CDLL_Cursor_next( CDLL* this )
{
   if( this->cursor != NULL )
	{
		this->cursor = this->cursor->next;
   }
}

/**
 * @brief Mueve al cursor al siguiente elemento a la izquierda.
 *
 * @param this Una lista.
 */
void CDLL_Cursor_prev( CDLL* this )
{
   if( this->cursor != NULL )
	{
		this->cursor = this->cursor->prev;
   }
}

bool CDLL_Cursor_end( CDLL* this )
{

}

/**
 * @brief Indica si la lista está vacía.
 *
 * @param this Referencia a una lista.
 *
 * @return true si la lista está vacía; false en caso contrario.
 */
bool CDLL_IsEmpty( CDLL* this )
{
   return this->first == NULL;
}

/**
 * @brief Devuelve el número actual de elementos en la lista.
 *
 * @param this Una lista.
 *
 * @return Devuelve el número actual de elementos en la lista.
 */
size_t CDLL_Len( CDLL* this )
{
   size_t tam = this->len;

   return tam;
}



/**
 * @brief Imprime la estructura de la lista. Es para uso de depuración, no es de uso general.
 *
 * @param this Una lista.
 */
void DLL_PrintStructure( DLL* this )
{
   if( DLL_IsEmpty( this ) )
   {
      fprintf( stderr, "Empty list. Nothing to show.\n" );
   } 
   else
   {
      fprintf( stderr, "\nNil->" );

      // usando un for en lugar de while (mi preferido):
      for( Node* it = this->first; it != NULL; it = it->next )
      {
         fprintf( stderr, "(%d)->", it->datos );
      } 
      fprintf( stderr, "Nil\n" );
   }
}


//----------------------------------------------------------------------
//                       Avanzadas: 
//----------------------------------------------------------------------

/**
 * @brief Recorre la lista y hace algo con cada uno de sus elementos
 *
 * @param lista Una lista
 * @param p_fn Función que procesa cada elemento de la lista
 */
void DLL_For_each( DLL* this, void (*p_fn)( int item ) )
{
   for( Node* it = this->first; it != NULL; it = it->next )
   {
      p_fn( it->datos );
   }
}

/**
 * @brief Busca si algún valor en la lista cumple con la función predicado
 *
 * @param this Una lista
 * @param p_fn Función predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la función quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la función podría ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, entonces devuelve verdadero; en caso contrario devuelve falso"
 * @param key El valor contra el que se está realizando la comparación.
 *
 * @return Un apuntador al nodo donde se haya encontrado la primer coincidencia. Devuelve NULL en caso de no haber encontrado ninguna
 */
Node* DLL_Find_if( DLL* this, bool (*cmp)( int, int ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede buscar nada en una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   while( it != NULL ){

      if( cmp( it->datos, key ) == true ) break;

      it = it->next;
   }

   return it;
}


/**
 * @brief Elimina todos los elementos que den positivo a la función predicado.
 *
 * @param this Una lista.
 * @param cmp Función predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la función quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la función podría ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, devuelve verdadero".
 * @param key El valor contra el que se está comparando.
 * @return El número de elementos encontrados y borrados.
 */
size_t DLL_Remove_if( DLL* this, bool (*cmp)( int x, int y ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede eliminar nada de una lista vacía

   Node* it = this->first;
   // |it| es la abreviación de "iterator", o  en español, "iterador"

   size_t elems = 0;

   while( it != NULL ){

      if( cmp( it->datos, key ) == true ) 
      {
         erase( this, it );
         ++elems;
      }

      it = it->next;
   }

   return elems;
}


#endif
