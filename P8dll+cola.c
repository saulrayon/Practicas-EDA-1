//estructura de datos double linked list
//lista enlazada doble ademas se utiliza como cola

#if 1  //para el archivo .h
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

typedef struct Node
{
	int datos;

	struct Node* next;
	struct Node* prev;
} Node;

typedef struct
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} DLL;


typedef struct 
{ 
    DLL* deq; 
} Deque;      //estructura cola


//funciones de la cola
Deque* Deque_New();
void Deque_Delete( Deque** this ); 
void Deque_Enqueue( Deque* this, int data ); 
void Deque_Enqueue_prio( Deque* this, int data ); 
int Deque_Dequeue( Deque* this ); 
int Deque_Dequeue_prio( Deque* this ); 
bool Deque_IsEmpty( Deque* this ); 
size_t Deque_Len( Deque* this );



//funciones de la lista doblemente enlazada
static Node* new_node( int x );
DLL* DLL_New();
void DLL_Delete( DLL** this );

int DLL_Front( DLL* this );
int DLL_Back( DLL* this );

void DLL_Push_front( DLL* this, int item );
void DLL_Push_back( DLL* this, int item );
void DLL_Insert( DLL* this, int item );

void DLL_Pop_front( DLL* this );
void DLL_Pop_back( DLL* this );

void DLL_Erase( DLL* this );
void DLL_Remove( DLL* this, int key );

void DLL_MakeEmpty( DLL* this );

bool DLL_Find( DLL* this, int key );

int  DLL_Cursor_Get( DLL* this );
void DLL_Cursor_front( DLL* this );
void DLL_Cursor_back( DLL* this );
void DLL_Cursor_next( DLL* this );
void DLL_Cursor_prev( DLL* this );
bool DLL_Cursor_end( DLL* this );

bool DLL_IsEmpty( DLL* this );
size_t DLL_Len( DLL* this );


void DLL_PrintStructure( DLL* this );

static Node* erase( DLL* list, Node* pos ); //Auxiliar para las avanzadas

// avanzadas:
void DLL_For_each( DLL* this, void (*p_fn)( int item ) );
Node* DLL_Find_if( DLL* this, bool (*p_fn)( int, int ), int key );
size_t DLL_Remove_if( DLL* this, bool (*cmp)( int x, int y ), int key );


#endif









#if 1  //para el archivo .c

//******************************************Cuerpos de la cola******************************************

Deque* Deque_New()
{
   Deque* cola_nueva = (Deque*)malloc(sizeof(Deque));//pide memoria para la cola

   if( cola_nueva != NULL )
   {
      cola_nueva->deq = DLL_New(); //pide memoria para el contenedor(DLL)

      if(cola_nueva->deq == NULL)
      {
         //no se encontro memoria para el contenedor
         // por lo tanto el objeto debe ser destru??do (sin 
         // contenedor no hay cola) 
         free( cola_nueva );
         cola_nueva = NULL; 
      }

   }
    
   return cola_nueva;
}

void Deque_Delete( Deque** this )
{
   assert( *this );    //error si la direccion no es valida

   // borramos primero el contenedor de la cola
   DLL_Delete( (*this)->deq );

   //borramos al objeto Deque
   free( *this );

   //Evitamos problemas futuros:
   *this = NULL;

}

void Deque_Enqueue( Deque* this, int data )
{
   //se pasa el contenedor a la funcion 
   DLL_Push_back( this->deq , data );
}

void Deque_Enqueue_prio( Deque* this, int data )
{
   DLL_Push_front( this->deq , data );
}

int Deque_Dequeue( Deque* this )
{
   DLL_Pop_front( this->deq );
}

int Deque_Dequeue_prio( Deque* this )
{
   DLL_Pop_back( this->deq );
}

bool Deque_IsEmpty( Deque* this ); 
size_t Deque_Len( Deque* this );





//*************************************Cuerpos de la doble lista enlazada*********************************
static Node* new_node( int x )
{
   Node* n = (Node*) malloc( sizeof( Node ) );
   if( n != NULL ){
      n->datos = x;
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
DLL* DLL_New()
{
}

/**
 * @brief Destruye una lista.
 *
 * @param this Una lista.
 */
void DLL_Delete( DLL** this )
{
}

/**
 * @brief Devuelve una copia del elemento en el frente de la lista
 *
 * @param this Una lista
 *
 * @return La copia del elemento en el frente de la lista
 *
 * @pre La lista NO debe estar vac??a
 */
int DLL_Front( DLL* this )
{
   assert( this->first != NULL );
   // ERR: no se puede leer de una lista vac??a

   return this->first->datos;
}

/**
 * @brief Devuelve una copia del elemento en la parte trasera de la lista.
 *
 * @param this Una lista.
 *
 * @return La copia del elemento en la parte trasera de la lista.
 *
 * @pre La lista NO debe estar vac??a
 */
int DLL_Back( DLL* this )
{
}

/**
 * @brief Inserta un elemento en el frente de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void DLL_Push_front( DLL* this, int item )
{
}

/**
 * @brief Inserta un elemento en el fondo de la lista.
 *
 * @param this Una lista.
 * @param item El elemento a insertar
 */
void DLL_Push_back( DLL* this, int item )
{
   Node* n = new_node( item );
   assert( n );

   if( this->first != NULL ){

      this->last->next = n;
      n->prev = this->last;
      this->last = n;
   } else{
      this->first = this->last = this->cursor = n;
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
void DLL_Insert( DLL* this, int item )
{
}

/**
 * @brief Elimina el elemento al frente de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posici??n en la que estaba cuando entr?? la
 * funci??n.
 */
void DLL_Pop_front( DLL* this )
{
}

/**
 * @brief Elimina el elemento al fondo de la lista.
 *
 * @param this Referencia a una lista.
 *
 * @post El cursor se mantiene en la posici??n en la que estaba cuando entr?? la
 * funci??n.
 */
void DLL_Pop_back( DLL* this )
{
   assert( this->len );
   // ERR: no se puede borrar nada de una lista vac??a

   if( this->last != this->first ) // tambi??n funciona: if( this->len > 1 ){...}
   { 
      Node* x = this->last->prev;
      free( this->last );
      x->next = NULL;
      this->last = x;
      --this->len;
   } else{
      free( this->last );
      this->first = this->last = this->cursor = NULL;
   }
}

/**
 * @brief Elimina el elemento apuntado por el cursor.
 *
 * @param this Una lista.
 *
 */
void DLL_Erase( DLL* this )
{
   assert( this->len=0 );
   // error si la lista est?? vac??a
    
   //guardamos el previo y el siguiente; del cursor
	Node* tmp_Next_cursor = this->cursor->next; 

   Node* tmp_Prev_cursor = this->cursor->prev;

   //devolvemos memoria del elemento apuntado por el cursor
	free( this->cursor );

   //ahora el cursor apunta a su siguente
   //si el cursor era el ultimo apuntara a NULL
   this->cursor = tmp_Next_cursor;

   
   if(this->cursor==NULL)//si el cursor era el ultimo de la lista (caso particular)
   {
      //se actualiza al nuevo ultimo
      this->last = tmp_Prev_cursor;

      this->last->next = NULL;
   }
   else if(tmp_Prev_cursor == NULL) //si el cursor era el primero de la lista (caso particular)
   {
      //se actualiza el nuevo primero
      this->first = tmp_Next_cursor;

      this->first->prev = NULL;
   }
   // si el cursor no era el ultimo se vuelve a unir la lista (caso general)
   else if(this->cursor != NULL )
   {
      //volver a unir la lista 
      tmp_Next_cursor->prev = tmp_Prev_cursor;

      tmp_Prev_cursor->next = tmp_Next_cursor;

   }

   --this->len;
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
   assert( this->len=0 );
   // error si la lista est?? vac??a

   DLL_Cursor_front(this);
   //recorremos la lista en busca de coincidencias con la llave
   for(size_t i = 0 ; i< this->len ; ++i)
   {
      if(this->cursor->datos== key) //al encontrar una coincidencia borramos el nodo y salimos del ciclo
      {
         DLL_Erase(this);
         break;
      }

      DLL_Cursor_next(this);
   }
}

/**
 * @brief Elimina todos los elementos de la lista sin eliminar la lista.
 *
 * @param this Una lista
 */
void DLL_MakeEmpty( DLL* this )
{
}

/**
 * @brief Busca un valor en la lista. Si lo encuentra coloca ah?? al cursor.
 *
 * @param this Una lista.
 * @param key El valor que se est?? buscando.
 *
 * @post Si se encontr?? una coincidencia coloca al cursor en ese nodo; en caso contrario el cursor es NULL.
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
void DLL_Cursor_front( DLL* this )
{
   this->cursor = this->first;
}

/**
 * @brief Coloca al cursor al final de la lista.
 *
 * @param this Una referencia a la lista de trabajo
 */
void DLL_Cursor_back( DLL* this )
{
}

/**
 * @brief Mueve al cursor al siguiente elemento a la derecha.
 *
 * @param this Una lista.
 */
void DLL_Cursor_next( DLL* this )
{
}

/**
 * @brief Mueve al cursor al siguiente elemento a la izquierda.
 *
 * @param this Una lista.
 */
void DLL_Cursor_prev( DLL* this )
{
   assert( this->cursor != NULL );

   Node* left = this->cursor->prev;
   this->cursor = left;
}

bool DLL_Cursor_end( DLL* this )
{

}

/**
 * @brief Indica si la lista est?? vac??a.
 *
 * @param this Referencia a una lista.
 *
 * @return true si la lista est?? vac??a; false en caso contrario.
 */
bool DLL_IsEmpty( DLL* this )
{
   return this->first == NULL;
}

/**
 * @brief Devuelve el n??mero actual de elementos en la lista.
 *
 * @param this Una lista.
 *
 * @return Devuelve el n??mero actual de elementos en la lista.
 */
size_t DLL_Len( DLL* this )
{
}

/**
 * @brief Imprime la estructura de la lista. Es para uso de depuraci??n, no es de uso general.
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









// Funci??n auxiliar.
//
// Elimina el nodo apuntado por |pos|. Esta funci??n es utilizada
// por DLL_Find_if()
//
// Devuelve el nodo a la derecha del nodo reci??n eliminado.
static Node* erase( DLL* list, Node* pos )
{

}
//----------------------------------------------------------------------
//                       Avanzadas: 
//----------------------------------------------------------------------

/**
 * @brief Recorre la lista y hace algo con cada uno de sus elementos
 *
 * @param lista Una lista
 * @param p_fn Funci??n que procesa cada elemento de la lista
 */
void DLL_For_each( DLL* this, void (*p_fn)( int item ) )
{
   for( Node* it = this->first; it != NULL; it = it->next )
   {
      p_fn( it->datos );
   }
}

/**
 * @brief Busca si alg??n valor en la lista cumple con la funci??n predicado
 *
 * @param this Una lista
 * @param p_fn Funci??n predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la funci??n quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la funci??n podr??a ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, entonces devuelve verdadero; en caso contrario devuelve falso"
 * @param key El valor contra el que se est?? realizando la comparaci??n.
 *
 * @return Un apuntador al nodo donde se haya encontrado la primer coincidencia. Devuelve NULL en caso de no haber encontrado ninguna
 */
Node* DLL_Find_if( DLL* this, bool (*cmp)( int, int ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede buscar nada en una lista vac??a

   Node* it = this->first;
   // |it| es la abreviaci??n de "iterator", o  en espa??ol, "iterador"

   while( it != NULL ){

      if( cmp( it->datos, key ) == true ) break;

      it = it->next;
   }

   return it;
}


/**
 * @brief Elimina todos los elementos que den positivo a la funci??n predicado.
 *
 * @param this Una lista.
 * @param cmp Funci??n predicado. El elemento |y| es proporcionado por el argumento |key|, mientras que el valor |x| se obtiene de la lista. Por ejemplo, si la funci??n quiere saber si el valor de la lista es menor que el valor del usuario (list_val < user_val), entonces la funci??n podr??a ser: less_than( list_val, user_val), la cual se lee en conjunto: "Si el valor de la lista |list_val| es menor que el valor del usuario |user_val|, devuelve verdadero".
 * @param key El valor contra el que se est?? comparando.
 * @return El n??mero de elementos encontrados y borrados.
 */
size_t DLL_Remove_if( DLL* this, bool (*cmp)( int x, int y ), int key )
{
   assert( DLL_IsEmpty( this ) == false );
   // ERR: no se puede eliminar nada de una lista vac??a

   Node* it = this->first;
   // |it| es la abreviaci??n de "iterator", o  en espa??ol, "iterador"

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






void Print( int item )
{
	printf( "%d\n", item );
}

// funci??n predicado:
bool less_than( int list_val, int user_val ){ return list_val < user_val; }


#endif
