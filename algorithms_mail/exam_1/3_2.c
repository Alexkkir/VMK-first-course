#include <stdio.h>
#include <stdlib.h>


int comp (const int *i, const int *j)
{
return *i - *j;
}

int main(void) {
    int n=0;
    scanf("%d",&n);
    int *starts,*ends;
    int abc = 100;
    starts=(int*) calloc(n , (sizeof(int)+1));
    ends=(int*) calloc(n , (sizeof(int)+1));

    int index1=0,index2=0;
    for (int i=0;i<n;i++){
        int t1,t2,t3,p1,p2,p3;
        scanf("%d:%d:%d %d:%d:%d",&t1,&t2,&t3,&p1,&p2,&p3);
        t1=t1 * 3600+t2 * 60+t3;
        p1=p1 * 3600+p2 * 60+p3;
        starts[index1]=t1;
        index1++;
        ends[index2]=p1;
        index2++;
    }

    qsort(starts,n,sizeof(int), (int(*) (const void *, const void *)) comp);
    qsort(ends,n,sizeof(int), (int(*) (const void *, const void *)) comp);
    int max=0;
    int sum=0;
    index1=index2=0;
    while (index1<n){
        if (starts[index1]<=ends[index2]){
            sum++;
            index1++;
        } else{
            sum-=1;
            index2++;
        }
        if (sum>max){
            max=sum;
        }
    }

    printf("%d",max);
    return 0;
}
