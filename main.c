#include <stdlib.h>
#include <stdio.h>

// Declare dynamic arrays/vectors and global variables
int numResources = 0;
int numProcesses = 0;
int* resource;
int* available;
int** maxclaim;
int** allocated;
int** need;
char* titles[] = {"Resources", "Available", "Max Claim", "Allocated", "Need"};

void prtVector(int *vector, char *title) {
    int size = sizeof(vector) / sizeof(vector[0]);
    printf("\n%s: \n", title);
    printf("\t");
    for(int i = 0; i < size; i++) {
        printf("r%d\t", i);
    }
    printf("\n\t");
    for(int i = 0; i < size; i++) {
        printf("%d\t", vector[i]);
    }
    return;
}

// TODO: Finish up option 1
void enterGraph() {

    printf("\nEnter number of resources: ");
    scanf("%d", &numResources);
    while (getchar() != '\n');
    
    resource = calloc(numResources, sizeof(int));
    if (resource == NULL) {
        fprintf(stderr, "Fail array allocation!");
        return;
    }
    available = calloc(numResources, sizeof(int));
    if (available == NULL) {
        fprintf(stderr, "Fail array allocation!");
        return;
    }

    printf("\nEnter number of units for resources (r%d to r%d): ", 0, numResources-1);
    for(int i = 0; i < numResources; i++) {
        scanf("%d", &resource[i]);
    }
    while (getchar() != '\n');

    prtVector(resource, titles[0]);
    free(resource);
    free(available);
    return;
}

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
                enterGraph();
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
