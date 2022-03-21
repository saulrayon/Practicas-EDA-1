#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#define DEBUG

#define TAM 40
#define REPETICIONES 20

typedef struct
{
  char name[TAM];  //nombre de la cancion
  char singer[TAM]; //cantante
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
void song_Ctor( Song* this, char* name, char* singer, int year, int duration );

void print_song(const Song* this)
{
    printf("Nombre: %s \nCantante: %s \nAño: %d \nDuracion: %d\n\n",this->name,this->singer,this->year,this->duration);
}

void song_Ctor( Song* this, char* name, char* singer, int year, int duration )
{
    strncpy( this->name,name,TAM ); //(destino,fuente,cuantos)
    strncpy( this->singer,singer,TAM );
    this->year = year;
    this->duration = duration;
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

void CQueue_Enqueue( CQueue* this, Song cancion ) //modificado para que cresca
{
    
    #ifdef DEBUG
    fprintf( stderr, "Encolando en Back: %ld, len= %ld\n", this->back, this->len+1 );
    #endif

    /*Si se llega a la capaciad maxima de la cola*/
    if (this->len== this->capacity) 
    {
        this->queue = (Song *) realloc(this->queue , sizeof( Song ) * (this->capacity*2) ); 

        if( NULL != this ) 
        {
            this->capacity *= 2;
            #ifdef DEBUG
            printf("new capacity=%ld\n",this->capacity);
            #endif
        } 
        else 
        { 
        // no se pudo asignar la memoria para el contenedor, 
        // por lo tanto el objeto debe ser destruído (sin 
        // contenedor no hay cola) 

        fprintf( stderr, "Fallo al reasignar memoria" );

        free( this );
        this = NULL; 

        exit(1);
        } 
        
    }
    
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

    Song tmp = (this->queue[ this->front ]);
    #ifdef DEBUG
    fprintf( stderr, "desencolando en front: %ld, len= %ld\n", this->front, this->len-1 );
    #endif

    ++this->front;

    if(this->front==this->capacity)
    {
        this->front=0;
    }

    --this->len;

    return tmp;
}

#if 0

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
    Song cancion1;
    song_Ctor(&cancion1,"cancion1","cantante1",1,1);

    Song cancion2;
    song_Ctor(&cancion2,"cancion2","cantante2",2,2);

    Song cancion3;
    song_Ctor(&cancion3,"cancion3","cantante3",3,3);

    print_song(&cancion1);
    print_song(&cancion2);
    print_song(&cancion3);

    CQueue* lista = CQueue_New( 2 );

    CQueue_Enqueue(lista, cancion3);
    CQueue_Enqueue(lista, cancion2);
    CQueue_Enqueue(lista, cancion1);

    for (size_t i = 3; i >0; i--)
    {
        Song tmp=CQueue_Dequeue(lista);
        print_song(&tmp);
    }
    
    

    CQueue_Delete(&lista);
    
}
