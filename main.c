#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int choice;
    do
    {
        printf("\n\nBanker's Algorithm\n");
        printf("------------------");
        printf("\n1) Enter claim graph");
        printf("\n2) Request resource");
        printf("\n3) Release resource");
        printf("\n4) Determine safe sequence");
        printf("\n5) Quit program\n");
        printf("\nEnter selection: ");
        scanf("%d", &choice);
        while (getchar() != '\n');
        switch (choice) {
            case 1:
                printf("\nClaim graph");
                break;
            case 2:
                printf("\nRequest resource");
                break;
            case 3:
                printf("\nRelease resource");
                break;
            case 4:
                printf("\nDetermine safe sequence");
                break;
            case 5:
                printf("\nQuitting program");
                break;
            default:
                printf("\nINVALID Input, try again");
                break;
        }
    } while (choice != 5);
    
    return 0;
}
