#include <iostream>
#include <cmath>

// Function for the exact integral of f(x)
double f_inte(double x) {
    return pow(x, 4) / 4 + 10 * pow(x, 2) / 2 + x;
}

// Function to be integrated
double f(double x) {
    return pow(x, 3) + 10 * x + 1;
}

// Trapezoidal Rule for numerical integration
double trapezoidal(double (*f)(double), double lower_limit, double upper_limit, double intervals) {
    double step_size = (upper_limit - lower_limit) / intervals;
    double integration = f(lower_limit) + f(upper_limit);

    for (int i = 1; i <= intervals; i++) {
        double k = lower_limit + i * step_size;
        integration += 2 * f(k);
    }

    return (integration * step_size) / 2;
}

// Simpson's Rule for numerical integration
double simpsons(double (*f)(double), double lower_limit, double upper_limit, double intervals) {
    double step_size = (upper_limit - lower_limit) / intervals;
    double integration = f(lower_limit) + f(upper_limit);

    for (int i = 1; i < intervals; i++) {
        double k = lower_limit + i * step_size;

        if (i % 2 == 0) {
            integration += 2 * f(k);
        } else {
            integration += 4 * f(k);
        }
    }

    return (integration * step_size) / 3;
}

int main() {
    double lower_limit = 0.0;
    double upper_limit = 2.0;
    int intervals = 1000;

    // Exact area calculation using the integral function
    double exact_area = f_inte(upper_limit) - f_inte(lower_limit);
    printf("\nArea Under The Curve (Exact) = %.2f \n", exact_area);

    // Approximate area using the Trapezoidal Rule
    double area_trapezoidal = trapezoidal(f, lower_limit, upper_limit, intervals);
    printf("Area Under The Curve (Trapezoidal) = %.2f \n", area_trapezoidal);

    // Approximate area using Simpson's Rule
    double area_simpsons = simpsons(f, lower_limit, upper_limit, intervals);
    printf("Area Under The Curve (Simpson's) = %.2f\n\n", area_simpsons);

    // Error calculation
    double error_trap = fabs(area_trapezoidal - exact_area) / exact_area * 100;
    printf("Percentage Error (Trapezoidal Rule) = %.3f%%\n", error_trap);

    double error_simp = fabs(area_simpsons - exact_area) / exact_area * 100;
    printf("Percentage Error (Simpson's Rule) = %.3f%%\n\n", error_simp);

    return 0;
}
