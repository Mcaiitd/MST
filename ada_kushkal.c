#include<stdio.h>

#include <stdlib.h>

struct node {
  int x;
  int y;
  struct node *next;
};

struct edging {
       int cost;
       int e1;
       int e2;
       };

struct output {//output is of this structure
       int edge1;
       int edge2;
       };

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
     
     }
     
void swap(struct edging *x,struct edging *y)//swaps the two elements given of structure edging

{

   int temp1,temp2,temp3;
   temp1 = x->cost;
   x->cost = y->cost;
   y->cost = temp1;
   
   temp2 = x->e1;
   x->e1 = y->e1;
   y->e1 = temp2;
   
   temp3 = x->e2;
   x->e2 = y->e2;
   y->e2 = temp3;   
}
int choose_pivot(int i,int j )//returns pivot point
{
   return((i+j) /2);
}
 
void quicksort(struct edging *list[],int m,int n)//sorts the edges in increasing order..order is O(nlogn)
{
   int key,i,j,k;
   if( m < n)
   {
      k = choose_pivot(m,n);
      swap(list[m],list[k]);
      key = list[m]->cost;
      i = m+1;
      j = n;
      while(i <= j)
      {
         while((i <= n) && (list[i]->cost <= key))
                i++;
         while((j >= m) && (list[j]->cost > key))
                j--;
         if( i < j)
                swap(list[i],list[j]);
      }
      // swap two elements
      swap(list[m],list[j]);
      // recursively sort the lesser list
      quicksort(list,m,j-1);
      quicksort(list,j+1,n);
   }
}


main()
{
      int y3;//Used later for scanf value so that program does not terminate without showing answer.
      int n;//No. of vertices
      printf("Enter value of n-->the no. of nodes");
      scanf("%d",&n);
    
      struct node *adlist[n];//array of adjacency list
      struct output *ans[n];//"ans" array will finally contain the answer
      ans[0] = malloc( sizeof(struct node) ); //initialising.. 
      ans[0]->edge1=0;
      ans[0]->edge2=0;
      
      int i=1;
      while(  i<n+1  )//initialises the adlist and ans array
      {
        adlist[i] = malloc( sizeof(struct node) );  
        adlist[i]->next=0;
        adlist[i]->x=i;
        adlist[i]->y=0;
        
        ans[i] = malloc( sizeof(struct node) );  
      
        ans[i]->edge1=0;
        ans[i]->edge2=0;
        
        i=i+1;
      }
      
//For user---add all the edges by using function addelem
//   example --addelem(adlist[1] ,5, 65) - creates edge btwn 1 and 5 node of cost 65
addelem(adlist[1],2,16);
addelem(adlist[2],1,16);
addelem(adlist[1],5,15);
addelem(adlist[5],1,15);
addelem(adlist[1],6,7);
addelem(adlist[6],1,7);
addelem(adlist[1],3,14);
addelem(adlist[3],1,14);
addelem(adlist[2],4,1);
addelem(adlist[4],2,1);
addelem(adlist[4],5,9);
addelem(adlist[5],4,9);
addelem(adlist[3],4,4);
addelem(adlist[4],3,4);
addelem(adlist[5],6,2);
addelem(adlist[6],5,2);
addelem(adlist[4],6,3);
addelem(adlist[6],4,3);
 
           


 int h = n*n;
 int u=1;
 struct edging *edges[h];//array which contains all the edges.

 i=1;
 struct node *p;
 for(i=1;i<=n;i++)//put all edges in "edges" array
 {
                  
                  p=adlist[i];
                  while(p->next!=0)
                  {
                        edges[u] = malloc (sizeof(struct edging));
                        edges[u]->cost= p->next->y;
                        edges[u]->e1 = i;
                        edges[u]->e2= p->next->x;
                        u++;
                        p=p->next;
                  }
} 

int imp = u-1; //(Total no. of edges * 2 )
 
// sort the array 'edges' w.r.t first element.
quicksort( edges,1,imp);

int Par[n];//Parent array 
i=1;
for(i=1;i<=n;i++)//initialises--initially there are n trees..
{
                 Par[i]=-1;
}

i=0;
int ec=1;
int j1,j2,j3;
int t1,t2;
while(i!=n-1)//Takes the most minimum edge from "edges" array and see if it could be added such that a cycle is not created..
{
           j1=edges[ec]->cost;
           j2=edges[ec]->e1;
           j3=edges[ec]->e2;
           
           t1=j2;
           t2=j3;  
           while(Par[t1]!=-1)
           {
                             t1=Par[t1];
           }
           while(Par[t2]!=-1)
           {
                             t2=Par[t2];
           }
           
           if (t1==t2)
           { ec++;  continue; }
           else {
                //put union of edges over here             
                ans[i]->edge1=j2;//filling the answer edge (component 1 of that edge).
                ans[i]->edge2=j3;//filling the answer edge (component 2).

                Par[j2]=j3;
                Par[t1]=t2;            
                i++;  ec++;   }
}

i=0;
printf("The edges in MST are-:");
while(i<n-1)//Printing the "ans" array which contains edges of MST
{
           printf("\n%d-%d",ans[i]->edge1 , ans[i]->edge2);
           i++;
}
    





   scanf("%d",&y3);//So that the program does not terminate.
  
}     
