#include <stdio.h>
#include <mpi.h>

double func(double x) {
    return 2 * x * x + 2 * x + 1;
}

double Simpson(double local_a, double local_b, int local_n, double h) {
    if (local_n % 2 != 0) {
        if (local_n > 1) local_n--;
        else return 0;
    }

    double local_result = func(local_a) + func(local_b);

    for (int i = 1; i < local_n; i++) {
        double x = local_a + i * h;
        if (i % 2 == 0)
            local_result += 2 * func(x);
        else
            local_result += 4 * func(x);
    }

    local_result *= h / 3.0;
    return local_result;
}

int main(void) {
    int my_rank, comm_sz, n = 1024, local_n;
    double a = 0.0, b = 1.0, h, local_a, local_b;
    double local_int_simpson, total_int_simpson = 0.0;
    int source;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    h = (b - a) / n;
    local_n = n / comm_sz;

    local_a = a + my_rank * local_n * h;
    local_b = local_a + local_n * h;

    local_int_simpson = Simpson(local_a, local_b, local_n, h);

    if (my_rank != 0) {
        MPI_Send(&local_int_simpson, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total_int_simpson = local_int_simpson;

        for (source = 1; source < comm_sz; source++) {
            MPI_Recv(&local_int_simpson, 1, MPI_DOUBLE, source, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_int_simpson += local_int_simpson;
        }

        printf("With n = %d :\n", n);
        printf("Estimate value of f(x) Using Simpson's Rule   : %.15e\n", total_int_simpson);
    }

    MPI_Finalize();
    return 0;
}

