#include <stdio.h>
#include <stdlib.h>

int source,destination, V,E,G[20][20],Q[20],f=-1,r=-1,visited[20];

void DFS(int i) {
    visited[i] = 1;
    printf("%i->",i);
    for(int j=1;j<=V+1;j++) {
        if(G[i][j] == 1 && visited[j] == 0)
            DFS(j);
    }
}

void enqueue(int item) {
    if(f==-1 && r==-1) {
        f=r=0;
        Q[r] = item;
    }
    else {
        r++;
        Q[r] = item;
    }
}

int dequeue() {
    int item;
    if(f==-1 && r==-1) {
        printf("Queue empty\n");
        return -1;
    }
    else if(f==r) {
        Q[f] = item;
        f=r=-1;
    }
    else {
        f++;
        Q[f] = item;
    }
    return item;
}

void BFS(int s) {
    int i;
    visited[s] = 1;
    printf("%i->",s);
    enqueue(s);
    while(f!=-1) {
        s = dequeue();
        for(int i=1;i<=V+1;i++) {
            if(G[s][i] == 1 && visited[i]==0) {
                printf("%i->",i);
                visited[i]=1;
                enqueue(i);
            }
        }
    }
    
}


int DFSPathExist(int source,int destination) {
    if(source == destination) return 1;
    visited[source] = 1;
    for(int i=1;i<=V+1;i++) {
        if(G[source][i] == 1 && visited[i] == 0) {
            if(DFSPathExist(i,destination))
                return 1;
        }
    }
    return 0;
}


int BFSPathExists(int src, int dest) {
    enqueue(src);
    visited[src] = 1;

    while (f != -1) {
        int node = dequeue();
        if (node == dest) return 1;
        for (int i = 1; i <= V; i++) {
            if (G[node][i] == 1 && !visited[i]) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    return 0;
}

int noOfProvinces() {
    int count=0;
    for(int i=0;i<=V;i++) {
        if(visited[i] == 0) {
            count++;
            DFS(i);
        }
    }
    return count;
}


int main() {
    int v1,v2,opt;
    printf("Enter the no.of vertices\n");
    scanf("%i",&V);
    for(int i=1;i<=V+1;i++) {
        for(int j=1;j<=V+1;j++) {
            G[i][j] = 0;
        }
    }
    
    printf("Enter the no.of edges\n");
    scanf("%i",&E);
    
    for(int i=1;i<=E;i++) {
        printf("Enter the edges in V1 V2 format\n");
        scanf("%i %i",&v1,&v2);
        G[v1][v2] = 1;
        G[v2][v1] = 1;

    }
     printf("Adj matrix\n");
    for(int i=1;i<=V+1;i++) {
        for(int j=1;j<=V+1;j++) {
            printf("%i\t",G[i][j]);
        }
        printf("\n");
    }
    
    for(int i=1;i<=V+1;i++)
        visited[i] =0;
    
    printf("Enter the source\n");
    scanf("%i",&source);
    
    printf("DFS\n");
    DFS(source);
    printf("\n");
    
    for(int i=1;i<=V+1;i++)
        visited[i] =0;
    
    printf("BFS\n");
    BFS(source);
    
    printf("Provinces: %i",noOfProvinces());
    
    // printf("Enter the source\n");
    // scanf("%i",&source);
    
    // printf("Enter the destination\n");
    // scanf("%i",&destination);
    
    // if(DFSPathExist(source,destination))
    //     printf("Exist\n");
    // else 
    //     printf("Not Exist\n");
}





