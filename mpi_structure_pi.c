#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// x, y coordinates
typedef struct {
    double x;
    double y;
} Point;

//generate random points
void generate_points(Point *points, int num_points) {
    for (int i = 0; i < num_points; i++) {
        points[i].x = (double)rand() / RAND_MAX;
        points[i].y = (double)rand() / RAND_MAX;
    }
}

//count points inside the unit circle
int count_in_circle(Point *points, int num_points) {
    int count = 0;
    for (int i = 0; i < num_points; i++) {
        if ((points[i].x * points[i].x + points[i].y * points[i].y) <= 1.0) {
            count++;
        }
    }
    return count;
}

int main(int argc, char** argv) {
    int rank, size, total_points = 1000000, local_count, global_count;
    int points_per_process;
    Point *points = NULL;
    int *recv_counts = NULL;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //number of points per process
    points_per_process = total_points / size;
    Point *local_points = (Point*)malloc(points_per_process * sizeof(Point));

    if (rank == 0) {
        //generate points only on root process
        points = (Point*)malloc(total_points * sizeof(Point));
        recv_counts = (int*)malloc(size * sizeof(int));
        srand(time(NULL));
        generate_points(points, total_points);
    }

    // Scatter points to all processes
    MPI_Scatter(points, points_per_process * sizeof(Point), MPI_BYTE, 
                local_points, points_per_process * sizeof(Point), MPI_BYTE, 
                0, MPI_COMM_WORLD);

    // Each process counts points inside the unit circle
    local_count = count_in_circle(local_points, points_per_process);

    // Gather results from all processes
    MPI_Reduce(&local_count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // Root process calculates final value of Pi
    if (rank == 0) {
        double pi = (4.0 * global_count) / total_points;
        printf("Estimated Pi value: %f\n", pi);
        free(points);
        free(recv_counts);
    }

    free(local_points);
    MPI_Finalize();
    return 0;
}
