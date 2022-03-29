#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


typedef struct
{
    int barcode;
    char name[25];
    float price;
}Product;

typedef struct Node
{
	Product* data;
	struct Node* next;
} Node;

typedef struct SLL
{
	Node* first;
	Node* last;
	Node* cursor;
	size_t len;
} SLL;



SLL*   SLL_New();
void   SLL_Delete(       SLL** this );
void   SLL_Push_front(   SLL* this, Product* data );
void   SLL_Push_back(    SLL* this, Product* data );
void   SLL_Insert(       SLL* this, Product* data );
Product*  SLL_Get(          SLL* this );
void   SLL_Pop_front(    SLL* this );
size_t SLL_Len(          SLL* this );
bool   SLL_Is_empty(     SLL* this );
void   SLL_Make_empty(   SLL* this );
void   SLL_Cursor_front( SLL* this );
void   SLL_Cursor_back(  SLL* this );
void   SLL_Cursor_next(  SLL* this );
bool   SLL_Find_if(      SLL* this, int key );
bool   SLL_Find(         SLL* this, int key );

Product* Product_New( int barcode, char* name, float price );

// newNode es una función privada, por eso su nombre está fuera 
// del patrón y además no tiene prototipo en el archivo de encabezados.
static Node* newNode( Product* data )  
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
SLL* SLL_New()  
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
void SLL_Delete( SLL** this ) 
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

void SLL_Push_front( SLL* this, Product* data )   //revisado
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

void SLL_Push_back( SLL* this, Product* data )   //revisado
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

void SLL_Insert( SLL* this, Product* data )
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
Product* SLL_Get( SLL* this )        //comprovar funcionamiento
{
   assert( this->first );
   // error fatal si la lista está vacía

   assert( this->cursor );
   // error fatal si el cursor no apunta a una posición válida

   Product* tmp = (this->cursor->data);

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
#if 0
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
#endif
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
		Product* tmp = SLL_Get(this);

		printf("Barcode: %d, Name: %s, Price: $%0.2f\n\n",tmp->barcode,tmp->name,tmp->price);

		SLL_Cursor_next(this);
	}
	
}

Product* Product_New( int barcode, char* name, float price )
{
    Product*p = (Product*)malloc(sizeof(Product));
    if(NULL != p)
    {
    p->barcode = barcode;
    
    strncpy( p->name,name,25 );

    p->price = price;
    }
    return p;
}


#if 1

int main()
{
	//se crean tres productos nuevos
	Product* P1 = Product_New( 100 , "leche", 25 );
	Product* P2 = Product_New( 200 , "Huevos", 20 );
	Product* P3 = Product_New( 300 , "papas", 15 );

	SLL* listaProductos = SLL_New();

	//insertar productos en la lista 
	SLL_Push_front(listaProductos, P1 );
	SLL_Push_front(listaProductos, P2 );
	SLL_Push_front(listaProductos, P3 );

	SLL_Print(listaProductos);

	//calcular el total a pagar
	float total = 0;
	SLL_Cursor_front(listaProductos);
	for(size_t i=0 ; i<listaProductos->len ; ++i)
	{
		Product* tmp = SLL_Get(listaProductos);

		total += tmp->price; 
		SLL_Cursor_next(listaProductos);
	}
	printf("Total a pagar: %0.2f\n", total);



   SLL_Delete(&listaProductos);

}

#endif


#if 0

int main()
{
	Product* Product_New( int barcode, char* name, float price )
{
    Product*p = (Product*)malloc(sizeof(Product));
    if(NULL != p)
    {
    p->barcode = barcode;
    
    strncpy( p->name,name,MAX_LEN );

    p->price = price;
    }
    return p;
}
}

#endif

#if 0

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