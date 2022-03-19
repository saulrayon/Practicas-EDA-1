#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DEBUG

#define TAM 10
#define REPETICIONES 20

typedef struct
{
  char name[40];  //nombre de la cancion
  char singer[40]; //cantante
  int year;       //año de la cancion
  int duration;   //duracion de la cancion en segundos  
}Song;


typedef struct // tipo de dato cola circular modificada para guardar canciones
{ 
    Song* queue; /**!< Contenedor de la cola. Es un arreglo dinámico de canciones. */ 
    size_t front; /**!< Índice al elemento más antiguo */ 
    size_t back; /**!< Índice al elemento más reciente */ 
    size_t len; /**!< Número actual de elementos en la cola */ 
    size_t capacity; /**!< Número máximo de elementos en la cola */ 
} CQueue;


CQueue* CQueue_New( size_t capacity ); 
void CQueue_Delete( CQueue** p_this ); 
void CQueue_Enqueue( CQueue* this, Song cancion ); 
Song CQueue_Dequeue( CQueue* this ); 
int CQueue_Peek( CQueue* this ); 
bool CQueue_IsEmpty( CQueue* this ); 
bool CQueue_IsFull( CQueue* this ); 
size_t CQueue_Len( CQueue* this ); 
size_t CQueue_Capacity( CQueue* this ); 
void CQueue_MakeEmpty( CQueue* this );

void print_song(const Song* this);

void print_song(const Song* this)
{
    printf("Nombre: %s \nCantante: %s \nAño: %d \nDuracion: %d\n\n",this->name,this->singer,this->year,this->duration);
}





CQueue* CQueue_New( size_t capacity )
{
    CQueue* q = (CQueue*) malloc( sizeof( CQueue) ); // pide memoria para el objeto Queue 
    if( NULL != q ) 
    { 
        q->queue = (Song *) malloc(sizeof( Song ) * capacity ); // pide memoria para el contenedor (arreglo) de la cola 
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

void CQueue_Enqueue( CQueue* this, Song cancion )
{
    assert( this->len < this->capacity ); 
    // si el numero de elementos en cola es igual a capacity, entonces tenemos un problema
    #ifdef DEBUG
    fprintf( stderr, "Encolando en Back: %ld, len= %ld\n", this->back, this->len );
    #endif

    this->queue[ this->back ] = cancion ;

    ++this->back; 

    if(this->back == this->capacity)
    {
        this->back=0;
    }

    ++this->len;

    
}

Song CQueue_Dequeue( CQueue* this )
{
    assert( this->len > 0 ); 
    // si len vale cero, entonces la pila esta vacia

    Song tmp = this->queue[ this->front ];
    #ifdef DEBUG
    fprintf( stderr, "desencolando en front: %ld, len= %ld\n", this->front, this->len );
    #endif

    ++this->front;

    if(this->front==this->capacity)
    {
        this->front=0;
    }

    --this->len;

    return (this->queue[ this->front-1 ]);
}

#if 1

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


#endif

int main()
{
    
}