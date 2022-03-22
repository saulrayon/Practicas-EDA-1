#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DEBUG

#define SIZE_COLA 10
#define REPT 3

typedef struct // tipo de dato cola circular
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
    CQueue* q = (CQueue*) malloc( sizeof( CQueue) ); // pide memoria para el objeto Queue 
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
    assert( *p_this );//si this es nulo dispara el assert 

    free( (*p_this)->queue ); // devuelve la memoria del arreglo 
    free( *p_this ); // devuelve la memoria del objeto 
    *p_this = NULL; // evitamos futuros problemas 
} 

void CQueue_Enqueue( CQueue* this, int val )
{
    assert( this->len < this->capacity ); 
    // si el numero de elementos en cola es igual a capacity, entonces tenemos un problema
    #ifdef DEBUG
    fprintf( stderr, "Encolando en Back: %ld, len= %ld\n", this->back, this->len );
    #endif

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
    #ifdef DEBUG
    fprintf( stderr, "desencolando en front: %ld, len= %ld\n", this->front, this->len );
    #endif

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
    assert( this->len > 0);

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





#if 1

int main()  // Driver program 5.1
{
    CQueue* fila = CQueue_New( SIZE_COLA ); //SIZE_COLA = 10

    for( size_t i = 0 ; i < REPT ; ++i) //REPT numero de repeticiones: 3
    {
        int n = rand()% 11;

        for ( ; n>0 ; --n)
        {
            int val = rand()%100;

            if(CQueue_IsFull( fila ) != true)
            {
                CQueue_Enqueue( fila , val );
            }
            else
            {
                printf("<<<El contenedor de la cola se ha llenado>>>\n");
                break;
            }
        }

        for(int m = rand()%11 ; m>0 ; --m )
        {
            if( CQueue_IsEmpty( fila ) != true)
            {
                int val = CQueue_Dequeue( fila );
                printf("Val= %d\n",val );
            }
            else
            {
                printf("<<<La cola esta vacia>>>\n");
                break;
            }
        }
        
    }
    //devolver memoria dinamica
    CQueue_Delete(&fila);
}
#endif





