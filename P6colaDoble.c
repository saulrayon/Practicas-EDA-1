#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DEBUG

#define TAM 10
#define REPETICIONES 20

typedef struct          //tipo de dato cola doble
{ 
    int* queue; /**!< Contenedor de la cola. Es un arreglo dinámico de reales. */ 
    size_t front; /**!< Índice al elemento más antiguo */ 
    size_t back; /**!< Índice al elemento más reciente */ 
    size_t len; /**!< Número actual de elementos en la cola */ 
    size_t capacity; /**!< Número máximo de elementos en la cola */ 
} DQueue;


DQueue* DQueue_New( size_t capacity ); 
void DQueue_Delete( DQueue** this ); 
void DQueue_Enqueue( DQueue* this, int val ); 
int DQueue_Dequeue( DQueue* this ); 
int DQueue_Peek( DQueue* this ); 
void DQueue_Enqueue_prio( DQueue* this, int val ); 
int DQueue_Dequeue_prio( DQueue* this ); 
int DQueue_Peek_prio( DQueue* this ); 
bool DQueue_IsEmpty( DQueue* this ); 
size_t DQueue_Len( DQueue* this ); 
size_t DQueue_Capacity( DQueue* this ); 
void DQueue_MakeEmpty( DQueue* this );

bool DQueue_IsFull( DQueue* this ); 



DQueue* DQueue_New( size_t capacity )
{
    DQueue* q = (DQueue*) malloc( sizeof( DQueue) ); // pide memoria para el objeto Queue 
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

void DQueue_Delete( DQueue** this )
{
    assert( *this );//si this es nulo dispara el assert 

    free( (*this)->queue ); // devuelve la memoria del arreglo 
    free( *this ); // devuelve la memoria del objeto 
    *this = NULL; // evitamos futuros problemas 
}

void DQueue_Enqueue_prio( DQueue* this, int val )
{
    if(this->front==0)
    {
        this->front=(this->capacity-1);
    }
    else
    {
        --this->front;
    }
    this->queue[this->front]=val;

    ++this->len;
}

void DQueue_Enqueue( DQueue* this, int val )
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

int DQueue_Dequeue( DQueue* this )
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

int DQueue_Dequeue_prio( DQueue* this )
{
    assert( this->len > 0 ); 
    // si len vale cero, entonces la pila esta vacia

    if(this->back==0)
    {
        this->back= (this->capacity-1);
    }
    else
    {
        --this->back;
    }
    --this->len;

    return this->queue[this->back];
}

int DQueue_Peek( DQueue* this )
{
    return this->queue[ this->front ];
} 

int DQueue_Peek_prio( DQueue* this )
{
    size_t tmp;
    if(this->back == 0)
    {
        tmp=(this->capacity-1);
    }
    else
    {
        tmp=(this->back-1);
    }
    return this->queue[ tmp ];
}

bool CQueue_IsEmpty( DQueue* this )
{
    return( this->len == 0 );
}

bool DQueue_IsFull( DQueue* this )
{
    return( this->len == this->capacity );
}

size_t DQueue_Len( DQueue* this )
{
    return this->len;
}

size_t DQueue_Capacity( DQueue* this )
{
    return this->capacity;
} 

void DQueue_MakeEmpty( DQueue* this )
{
    this->front = this->back = this->len = 0;
}





#if 1

int main()  // Driver program 5.2
{
    DQueue* fila = DQueue_New( TAM );

    for( size_t i = 0 ; i < REPETICIONES ; ++i)
    {
        int n = rand()% 11;

        for ( ; n>0 ; --n)
        {
            int val = rand()%100;

            if(DQueue_IsFull( fila ) != true)
            {
                int volado = rand()%100;

                if(volado>90)
                {
                DQueue_Enqueue_front( fila , val );
                printf("llego un VIP\n");
                }
                else
                {
                    DQueue_Enqueue_back( fila , val );
                }
            }
            else
            {
                printf("cola llena\n");
                break;
            }
        }   // vamos bien hasta aqui

        for(int m = rand()%11 ; m>0 ; --m )
        {
            if( CQueue_IsEmpty( fila ) != true)
            {
                int volado = rand()%100;

                if(volado>90)
                {
                    int val = DQueue_Dequeue_back( fila );
                    printf("Val= %d\n",val );
                    printf("se atendio a un VIP\n");
                }
                else
                {
                    int val = DQueue_Dequeue_front( fila );
                    printf("Val= %d\n",val );
                } 
            }
            else
            {
                printf("cola vacia\n");
                break;
            }
        }
        
    }
    DQueue_Delete(&fila);
}
#endif
