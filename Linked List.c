#include <stdio.h>
#include <stdlib.h>

struct node{
	int veri;
	struct node* next;
};

struct node* start = NULL;
struct node* temp = NULL;

void menu( void );
void basaEkle( int );
void onuneEkle( int, int );
void sonaEkle( int );
void elemanSil( int, int );
void tersCevir( void );
void yazdir( void );

int main(){

int sayi, secim, onune, sec;

while( 1 ){	  
	menu();
	scanf( "%d", &secim );
	
	switch ( secim ){
		case 1:
			printf( "Eklenecek sayi: " );
			scanf( "%d", &sayi );
			basaEkle( sayi );
			yazdir();
			break;
		    
		case 2:
			printf( "Hangi sayinin onune ekleme yapmak istiyorsunuz?: " );
			scanf( "%d", &onune );
			printf( "Eklenecek sayi: " );
			scanf( "%d", &sayi );
			onuneEkle( onune, sayi );
			yazdir();
			break;
	
		case 3:	
			printf( "Eklenecek sayi: " );
			scanf( "%d", &sayi );
			sonaEkle( sayi );
			yazdir();
			break;
		 
		case 4:	
			printf( "Nereden eleman silmek istiyorsunuz?:" );
			scanf( "%d", &sec );
			printf( "Silinecek sayi: " );
			scanf( "%d", &sayi );
			elemanSil( sec, sayi );
			yazdir();
			break;
		 
		case 5:
		    tersCevir();
		    yazdir();
		    break;
		 			
		default:
			printf( "Yanlis secim. Tekrar deneyiniz.\n\n" );		
			break;
		}      		
}

return 0;
}

void menu( void ){
	printf( "Secim 1: Basa sayi ekle.\n"
	        "Secim 2: Araya sayi ekle.\n" 
	        "Secim 3: Sona sayi ekle.\n" 
	    	"Secim 4: Eleman sil.\n"
	    	"Secim 5: Ters cevir\n"
			"Seciminiz: " );     	
}

void basaEkle( int sayi ){
	struct node* basa = ( struct node* )malloc( sizeof(struct node) );
	basa->veri = sayi;
	
	if ( start == NULL ){
	    basa->next = NULL;
		start = basa;
	}
	else{
		temp = start;
		start = basa;
		basa->next = temp;
	}
}

void onuneEkle( int onune, int sayi ){
	struct node* onuneekle = ( struct node* )malloc( sizeof(struct node) );
	onuneekle->veri = sayi;
	temp = start;
	
	while( temp->next->veri != onune )	
		temp = temp->next;
	
	onuneekle->next = temp->next;
	temp->next = onuneekle;
}

void sonaEkle( int sayi ){
	struct node* sona = ( struct node* )malloc( sizeof(struct node) );
	temp = start;
	
	while( temp->next != NULL)
		temp = temp->next;
	
	temp->next = sona;
	sona->veri = sayi;
	sona->next = NULL;
}

void elemanSil( int sec, int sayi ){
	struct node* temp2 = ( struct node* )malloc( sizeof(struct node) );
	struct node* temp3 = ( struct node* )malloc( sizeof(struct node) );
	
	switch ( sec ){
		case 1:
			temp = start;
			
			if( temp->veri == sayi ){   	
			    temp = start->next;
			    free(start);
			    start = temp;
			}
			break;
		
		case 2:
			temp = start;
		
			while( temp->next->veri != sayi )
				temp = temp->next;
			
			temp2 = temp;
			temp3 = temp->next->next; 
			free( temp->next );
			temp2->next = temp3;
			break;
		 
		case 3:
			temp = start;
			
			while( temp->next->next != NULL )
			    temp = temp->next;
				
			if( temp->next->veri == sayi ){		
				free( temp->next ); 
				temp->next = NULL;
			}		  	
			break;
	   }	
}


void tersCevir( void ){
	struct node* current = start;
	struct node* prev = NULL ;
	
	while( current != NULL ){
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp; 
}  
	start = prev;   
}

void yazdir( void ){
	temp = start;
	
	printf( "Linked list: " );
	
	while( temp->next != NULL ){
		printf( "%d->", temp->veri );
	    temp = temp->next;
	   }   	
	   
	   printf( "%d->NULL", temp->veri );
	   printf( "\n\n" );
}

