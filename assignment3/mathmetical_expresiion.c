#include<stdio.h>
#include<conio.h>

int main(){
    unsigned int  B,N,M;
    printf("Enter the value of B :");
   if (scanf("%u", &B) != 1) {
        printf("Invalid input for B.Please enter again\n");
        return 1;
    }

     printf("\nEnter the value of N :");
    if (scanf("%u", &N) != 1|| N<0) {
        printf("Invalid input for N.Please enter again\n");
        return 1;
    }
   
   printf("\nEnter the value of M :");
    if (scanf("%u", &M) != 1 || M<=1) {
        printf("Invalid input for M.Please enter again\n");
        return 1;
    }

    unsigned int result=1;

    for (int i = 0; i < N; i++)
    {
       result= (result*B)%M;
    }
    
    printf("\nResult= %u",result);
    

return 0;
}