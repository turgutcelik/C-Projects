#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node* next;
};

struct node* start = NULL;
struct node* temp;
struct node* top = NULL;

void menu();
void push( int );
void pop();
int peek();
void yazdir();

int main()
{
	int secim, num;
	
	while( 1 ){
		menu();
		scanf( "%d", &secim );
		
		switch( secim ){
		   case 1:
			   	printf( "Eklenecek sayiyi giriniz: " );
			   	scanf( "%d", &num );
			   	push( num );
			   	yazdir();
			   	break;
		   
		   case 2:
				pop();
		    	yazdir();
		    	break;
		   
		   case 3:
		        printf( "En ustteki deger: %d\n", peek() );
		        break;
		   
		   default: 
			    printf( "Yanlis secim!\n" );
				break;				
		}
		printf( "\n" );
	   }
	return 0;
}

void menu()
{
	printf("Secim 1: Push\n"
	       "Secim 2: Pop\n"
		   "Secim 3: Peek\n"
		   "Seciminiz: "); 	    
}

void push( int sayi )
{
	struct node*eklenecek = ( struct node* )malloc( sizeof( struct node ) );
	
	eklenecek->data = sayi;
	eklenecek->next = NULL;   
	
	if( top != NULL )
	    eklenecek->next = top;
	
	top = eklenecek;
}

void pop(){

	if( top == NULL )
	    printf( "Stack zaten bos!\n" );
	else{
		temp = top;
		top = temp->next;
		free( temp );
	   }
}

int peek(){
return top->data;
}

void yazdir(){
	struct node* q;
	q = top;
	
	while( q != NULL ){
	    printf( "%d<--", q->data );
	    q = q->next;
 }	

printf( "NULL\n" );	   	

}
