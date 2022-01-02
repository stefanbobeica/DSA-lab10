#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    float pi;
    float gi;
} obiect;

obiect *create(FILE *input, int n)
{
    obiect *ret;
    ret = (obiect *)malloc(n * sizeof(obiect));
    for (int i = 0; i < n; i++)
        fscanf(input, "%f %f",  &ret[i].pi, &ret[i].gi);

    return ret;
}

void afisare(FILE *output, int n, obiect *o)
{
    for (int i = 0; i < n; i++)
        fprintf(output, "%f %f %f\n", o[i].pi, o[i].gi,o[i].pi/o[i].gi);
}

void swap( obiect *x, obiect *y)
{
    obiect aux;
    aux =*x;
    *x=*y;
    *y= aux;

}


int partition(obiect *arr, int low, int high)
{
    obiect pivot;
    pivot=arr[high];

    int i=low-1;
    for(int j = low; j < high; j++)
    {
        if((arr[j].pi/arr[j].gi) <= (pivot.pi/pivot.gi))
        {
            i++;

            swap(arr+i,arr+j);
        }
    }
    swap(arr+i+1,arr+high);
    return (i+1);
}


void quicksort(obiect *arr, int low, int high)
{
    int q;
    if(low<high)
    {
        q=partition(arr,low,high);


        quicksort(arr,low,(q-1));
        quicksort(arr,(q+1),high);
    }
}
obiect *rucsac( obiect *o,int n,float G,int *l)
{
    //sortez in main
    float currG=0;
    obiect *ruc;
    float aux=0;
    ruc=(obiect*)malloc(n*sizeof(obiect));
    int i=0;
    float prev;
    for(int i=0; i<n; i++)
    {
        aux=aux+o[i].gi;
    }
    if(aux<G)
    {
        *l=n;
        printf("SACUL NU A FOST UMPLUT");
        return o;

    }
    while(currG<G)
    {
        ruc[i]=o[n-i-1];
        prev=currG;
        currG=currG+o[n-i-1].gi;

        i++;

    }
    if(currG>G)
    {
        ruc[i-1].pi=((G-prev)*ruc[i-1].pi)/ruc[i-1].gi;
        ruc[i-1].gi=G-prev;
    }
    *l=i;
    float valoare;
    for(int i=0; i<*l; i++)
        valoare=valoare+ruc[i].pi;
    printf("Valorea maxima este: %f",valoare);
    return ruc;
}

int main()
{
    FILE *input, *output;//in output sunt elemenetele pi,gi si raportul lor.

    //input = fopen("data1.txt", "r+");
    input=fopen("data2.txt","r+");
    output = fopen("output.txt", "w+");
    obiect *o,*r;
    int n,*l;
    float G;
    fscanf(input,"%d",&n);
    o=create(input,n);
    printf("Dati greutatea= ");
    scanf("%f",&G);
    quicksort(o,0,n-1);
    obiect *ruc;
    ruc=rucsac(o,n,G,&l);

    afisare(output,l,ruc);
    fclose(input);
    fclose(output);
}
