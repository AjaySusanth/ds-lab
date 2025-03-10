#include <stdio.h>

void readSparse(int sp[50][50],int r, int c) {
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++)
            scanf("%i",&sp[i][j]);
    }
}

void print(int sp[50][50],int r, int c) {
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++)
            printf("%i\t",sp[i][j]);
    }
    printf("\n");
}

void printTuple(int t[50][3],int n) {
    for(int i=0;i<n;i++) {
        for(int j=0;j<3;j++) {
            printf("%i\t",t[i][j]);
        }
    }
    printf("\n");
}

int tuple(int sp[50][50],int r,int c, int t[50][3]) {
    int k=1;
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++) {
            if(sp[i][j]!=0) {
                t[k][0] = i;
                t[k][1] = j;
                t[k][2] = sp[i][j];
                k++;
            }
        }
    }
    t[0][0] = r;
    t[0][1] = c;
    t[0][2] = k-1;
    return k;
}

int transpose(int t[50][3],int n,int trans[50][3]) {
    int k=1;
    for(int i=0;i<t[0][1];i++) {
        for(int j=1;j<=t[0][2];j++) {
            t[k][0] = t[j][1];
            t[k][1] = t[j][0];
            t[k][2] = t[j][2];
            k++;
        }
    }
    trans[0][0] = t[0][1];
    trans[0][1] = t[0][0];
    trans[0][2] = k-1;
    return k;
}

int Sum(int t1[][3],int t2[][3], int s[][3]) {
    int i=1,j=1,k=1;
    int e1 = t1[0][2];
    int e2 = t2[0][2];
    
    while(i<=e1 && j<=e2) {
        if(t1[i][0] == t2[j][0]) {
            if(t1[i][1] == t2[j][1]) {
                s[k][0] = t1[i][0];
                s[k][1] = t1[i][1];
                s[k][2] = t1[i][2] + t2[j][2];
                i++;j++;
                if(s[k][2]!=0) k++;
            }
        }
    }
}

int sparse(int t[][3],int sp[50][50]){
    int r = t[0][0];
    int c= t[0][1];
    int  k=1;
    
    for(int i=0;i<r;i++) {
        for(int j=0;j<c;j++){
            if(i == t[k][0] && j ==t[k][1]) {
                sp[i][j] = t[k][2];
                k++;
            }
            else
                sp[i][j] = 0;
        }
    }
}

