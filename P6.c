#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>


typedef struct 
{ 
    int* queue; /**!< Contenedor de la cola. Es un arreglo dinámico de reales. */ 
    size_t front; /**!< Índice al elemento más antiguo */ 
    size_t back; /**!< Índice al elemento más reciente */ 
    size_t len; /**!< Número actual de elementos en la cola */ 
    size_t capacity; /**!< Número máximo de elementos en la cola */ 
} CQueue;


CQueue* CQueue_New( size_t capacity ); 
void CQueue_Delete( CQueue** p_this ); 
void CQueue_Enqueue( CQueue* this, int val ); 
int CQueue_Dequeue( CQueue* this ); 
int CQueue_Peek( CQueue* this ); 
bool CQueue_IsEmpty( CQueue* this ); 
bool CQueue_IsFull( CQueue* this ); 
size_t CQueue_Len( CQueue* this ); 
size_t CQueue_Capacity( CQueue* this ); 
void CQueue_MakeEmpty( CQueue* this );





CQueue* CQueue_New( size_t capacity )
{
    Queue* q = (Queue*) malloc( sizeof( Queue) ); // pide memoria para el objeto Queue 
    if( NULL != q ) 
    { 
        q->queue = (int *) malloc(sizeof( int ) * capacity ); // pide memoria para el contenedor (arreglo) de la cola 
        if( NULL != q ) 
        {
            q->capacity = capacity;
            q->back = q->front = q->len = 0;
        } 
        else 
        { 
        // no se pudo asignar la memoria para el contenedor, 
        // por lo tanto el objeto debe ser destruído (sin 
        // contenedor no hay cola) 
        free( q );
        q = NULL; 
        } 
    } 
    return q;
} 

void CQueue_Delete( CQueue** p_this )
{
    assert( *this );//si this es nulo dispara el assert 

    free( (*this)->queue ); // devuelve la memoria del arreglo 
    free( *this ); // devuelve la memoria del objeto 
    *this = NULL; // evitamos futuros problemas 
} 

void CQueue_Enqueue( CQueue* this, int val )
{
    assert( this->len < this->capacity ); 
    // si el numero de elementos en cola es igual a capacity, entonces tenemos un problema
    fprintf( stderr, "Encolando en Back: %ld, len= %ld\n", this->back, this->len );

    this->queue[ this->back ] = val;

    ++this->back; 

    if(this->back == this->capacity)
    {
        this->back=0;
    }

    ++this->len;

    
}

int CQueue_Dequeue( CQueue* this )
{
    assert( this->len > 0 ); 
    // si len vale cero, entonces la pila esta vacia

    int tmp = this->queue[ this->front ];

    fprintf( stderr, "desencolando en front: %ld, len= %ld\n", this->front, this->len );

    ++this->front;

    if(this->front==this->capacity)
    {
        this->front=0;
    }

    --this->len;

    return tmp;
}

int CQueue_Peek( CQueue* this )
{
    return this->queue[ this->front ];
} 

bool CQueue_IsEmpty( CQueue* this )
{
    return( this->len == 0 );
}

bool CQueue_IsFull( CQueue* this )
{
    return( this->len == this->capacity );
}

size_t CQueue_Len( CQueue* this )
{
    return this->len;
}

size_t CQueue_Capacity( CQueue* this )
{
    return this->capacity;
} 

void CQueue_MakeEmpty( CQueue* this )
{
    this->front = this->back = this->len = 0;
}





