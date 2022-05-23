#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;
struct node *newNode( int );
struct node *ekle( struct node*, int );
struct node *search( int );
void inOrder( struct node* );

int main()
{
int secim, sayi, ara;

while( 1 ){	
	printf("1: Sayi ekle.\n"
	       "2: In-order traversal.\n"  
           "3: Sayi ara.\n"
		   "Secim: ");
	scanf( "%d", &secim );
	
	switch( secim ){		
		case 1:
			printf( "Bir sayi giriniz: " );
			scanf( "%d", &sayi);	
			ekle( root, sayi );
			break;
			
		case 2:
			inOrder( root );
			printf( "\n" );	
			break;
		
		case 3:
			printf( "Aranacak sayiyi giriniz: " );
			scanf( "%d", &ara );
			search( ara );
			break;
		 
		default:
			printf( "Yanlis secim! Tekrar deneyiniz.\n" );
			break;
	}	   
		        			
    printf( "\n" );	
   }

return 0;
}

struct node *newNode( int key )
{
    struct node *temp = ( struct node* )malloc( sizeof ( struct node ) );

    temp->data = key;
 	temp->left = NULL;
    temp->right = NULL;

 	if ( root == NULL )
        root = temp;
    else
        return temp;
}

struct node *ekle( struct node *node, int key )
{
	if( node == NULL )
	    return newNode( key );
	if( key < node->data )
	    node->left = ekle( node->left, key );
	else if( key > node->data )
	    node->right = ekle( node->right, key );
	    return node;	    
}

struct node *search( int aranan )
{
	struct node *current;
	current = root;
	
	while( current->data != aranan ){
	
	if ( current != NULL ){		
		printf( "%d--> ", current->data );
		 
		if( aranan < current->data )
		   current = current->left;
		else
		   current = current->right;  
	 }
	       	
	if( current == NULL){
		printf( "Boyle bir sayi yok!\n" );
		return NULL;
	 }
} 
 printf( " %d", current->data );
 return current;
}

void inOrder( struct node *root )
{
	if( root != NULL){		
		inOrder( root->left );
		printf( "%d ", root->data );
		inOrder( root->right );
	}
}
