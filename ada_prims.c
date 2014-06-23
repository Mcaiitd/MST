#include<stdio.h>
#include <stdlib.h>

struct node {
  int x;
  int y;
  struct node *next;
};
 
 struct check {
       int ap;
       int bcost;
       int bpar;
 };
 
 
 
 
// global declarations--give the value of n--no. of vertices.......
//USER PLEASE FILL THE VALUE OF IN FOLLOWING 5 VALUES...............
int n=6;
int heapmax=6;
struct node *adlist[6];
struct check *arr[6];
int heap[6]; 




int parent(int n)//function giving parent of point in heap
{
    if (n%2==1)
	return ((n-1)/2);
	else return (n/2);
}
int left(int n)//function giving left child of a point in heap
{
	return (n*2);
}
int right(int n)//function giving right child of a point in heap
{
	return ((n*2)+1);
}

void heapify(int a[])//heapify function--modifies the heap which can be wrong at root point
{
	int i =1,tempk,temp;
	while(i<=heapmax)
	{
		if(   (right(i) <= heapmax)  &&   ( arr[a[left(i)]]->bcost >= arr[a[right(i)]]->bcost)  )
		{
			if( arr[a[i]]->bcost <= arr[a[right(i)]]->bcost){break;}	
		
        	tempk = arr[a[i]]->ap;
			arr[a[i]]->ap = arr[a[right(i)]]->ap;
			arr[a[right(i)]]->ap = tempk;			
			temp=a[i];
			a[i]=a[right(i)];
			a[right(i)]=temp;
			
			i = right(i);	
			continue;
		}
		else if((left(i) <= heapmax))
		{        
            if(arr[a[i]]->bcost <= arr[a[left(i)]]->bcost){ break;}
		
        	tempk = arr[a[i]]->ap;
			arr[a[i]]->ap = arr[a[left(i)]]->ap;
			arr[a[left(i)]]->ap = tempk;

			temp=a[i];
			a[i]=a[left(i)];
			a[left(i)]=temp;
			
			i = left(i);
			continue;
		}
		else break;
	}
}

int getmin()//function to delete minimun of heap and calls the heapify function to modify heap
{
     int k;
     int i;
     k=heap[1];
     arr[heap[1]]->ap = 0;
     heap[1]=heap[heapmax];
     arr[heap[heapmax]]->ap=1;
     heapmax--;
     heapify(heap);

	return k;
}


void rectify(int a[], int i)//Function which rectifies the heap which is bad at ith point.
{
     int tempk,temp;
     while(i > 1)
     {
        if( arr[a[i]]->bcost >= arr[a[parent(i)]]->bcost) break;
		else
		{
			tempk = arr[i]->ap;
			arr[i]->ap = arr[a[parent(i)]]->ap;
			arr[a[parent(i)]]->ap = tempk;
			
			temp=a[i];
			a[i]=a[parent(i)];
			a[parent(i)]=temp;
			
			i = parent(i);
		}
    }
}
     
void addelem( struct node *l , int k , int k2 )//It is for user..creates an adjacency list
{
     struct node *base;
     struct node *p;
     base = malloc( sizeof(struct node) );
     base->next=0;
     base->x=k;
     base->y=k2;
     p=l;
     while (p->next!=0)
     { p = p->next; }
     
     p->next = base;
};



void main()//Starting of program
{
  
      int y3;//Used later for scanf value so that program does not terminate without showing answer.
      int i=1;
      while(  i<n+1  )//initiaises the adjacency list
      {
        adlist[i] = malloc( sizeof(struct node) );  
        adlist[i]->next=0;
        adlist[i]->x=i;
        adlist[i]->y=0;
        i=i+1;
      };
      
      
//For user---add all the edges by using function addelem
//   example --addelem(adlist[1] ,3, 65) - add the edge btwn node 1 and 3 of cost 65
addelem(adlist[1],2,100); 
addelem(adlist[1],4,200);
addelem(adlist[1],3,300);     
addelem(adlist[1],5,300);
addelem(adlist[2],1,100);  
addelem(adlist[2],3,100);  
addelem(adlist[2],4,700);  
addelem(adlist[2],6,600);
addelem(adlist[3],1,300);  
addelem(adlist[3],2,100);  
addelem(adlist[3],4,800);
addelem(adlist[4],1,200);  
addelem(adlist[4],2,700);  
addelem(adlist[4],3,800);  
addelem(adlist[4],5,100);
addelem(adlist[5],1,300);  
addelem(adlist[5],4,100);
addelem(adlist[6],2,600); 
 

  i=1;  // "arr" is array containing all information about all vertexes - "ap"->whether present in heap array or not , "bcost"->min cost , "bpar" is parent vertex
  while(i<=n)
  {
                        arr[i] = malloc (sizeof(struct check));
                        arr[i]->ap= i;
                        arr[i]->bcost = 10000;
                        arr[i]->bpar=0;
                        i++;
  };

  i=1;// it is the heap == "heap" array
  while(i<=n)
  {
             heap[i]=i;
             i++;
  }

int min ;
struct node *u;
while(heapmax!=0)//function which runs till heap does not get empty
{
                
             min  =  getmin(); //getmin func will heapify and at same time change the "ap" element in "arr".
             arr[min]->ap = 0;
             u=adlist[min];
             while(u->next!=0)//changes the minimum cost of all vertices which are adjacent to above minimum vertex
             {       
                 if (arr[u->next->x]->ap==0) {u=u->next;}
                 else
                 {
                     if(   u->next->y  <  arr[u->next->x]->bcost )
                     {
                           arr[u->next->x]->bcost = u->next->y;
                           arr[u->next->x]->bpar = min;
                           rectify(heap, arr[u->next->x]->ap  );//change the value in heap and construct the modified heap
                           u=u->next;
                           continue;
                     }
                     else
                     {
                         u=u->next;
                         continue;
                     }
                 }
             } 
}

printf("The parrent array is given as follows-:\n");
i=1;
while(i<=n)
{
        printf("%d ",arr[i]->bpar);//prints the parrent of all nodes.
           i++;
}


 
 
 
 
 scanf("%d",&y3);//So that the program does not terminate.

}
