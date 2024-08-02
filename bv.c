#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 10
#define TOLERANCE 1e-7
#define MAX_ITERATIONS 1000

// Function to evaluate the polynomial at a given x
double evaluate_polynomial(double coeffs[], int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coeffs[i] * pow(x, degree - i);
    }
    return result;
}

// Birge-Vieta method for finding a root of a polynomial
double birge_vieta(double coeffs[], int degree, double initial_guess) {
    double b[MAX_DEGREE + 1], c[MAX_DEGREE + 1];
    double x = initial_guess;
    int iteration = 0;
    
    while (iteration < MAX_ITERATIONS) {
        b[0] = coeffs[0];
        for (int i = 1; i <= degree; i++) {
            b[i] = coeffs[i] + x * b[i - 1];
        }
        
        c[0] = b[0];
        for (int i = 1; i < degree; i++) {
            c[i] = b[i] + x * c[i - 1];
        }
        
        double fx = b[degree];
        double fpx = c[degree - 1];
        
        if (fabs(fx) < TOLERANCE) {
            return x; // Root found
        }
        
        x = x - fx / fpx;
        iteration++;
    }
    
    printf("Max iterations reached.\n");
    return x;
}

int main() {
    int degree = 3;
    double coeffs[] = {1, -6, 11, -6}; // Coefficients of the polynomial x^3 - 6x^2 + 11x - 6
    double initial_guess = 3.5;

    double root = birge_vieta(coeffs, degree, initial_guess);

    printf("Root: %lf\n", root);
    
    return 0;
}
