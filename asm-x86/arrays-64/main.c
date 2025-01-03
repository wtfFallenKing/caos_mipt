#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern void sum(size_t N, const int* A, const int* B, int* R);

int main()
{
    size_t N = 0;
    int* A = NULL;
    int* B = NULL;
    int* R = NULL;
    scanf("%"SCNd64, &N);
    A = calloc(N, sizeof(*A));
    B = calloc(N, sizeof(*B));
    R = calloc(N, sizeof(*R));
    size_t i = 0;
    for (i = 0; i < N; ++i) {
        scanf("%d", &(A[i]));
    }
    for (i = 0; i < N; ++i) {
        scanf("%d", &(B[i]));
    }
    sum(N, A, B, R);
    for (i = 0; i < N; ++i) {
        printf("%d ", R[i]);
    }
    printf("\n");
    free(A);
    free(B);
    free(R);
}
