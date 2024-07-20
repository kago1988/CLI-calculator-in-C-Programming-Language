//
//  main.c
//  cli-calculator
//
//  Created by Andreas Kagoshima on 20.07.24.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPR_LEN 100

double evaluateExpression(const char* expression);
double parseTerm(const char** expr);
double parseFactor(const char** expr);
double parseNumber(const char** expr);

int main(void);

int main(void) {
    char expression[MAX_EXPR_LEN];

    printf("Enter an expression: ");
    if (fgets(expression, MAX_EXPR_LEN, stdin) == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    // Evaluate the expression and print the result
    double result = evaluateExpression(expression);
    printf("Result: %lf\n", result);

    return 0;
}

double evaluateExpression(const char* expression) {
    const char* expr = expression;
    return parseTerm(&expr);
}

double parseTerm(const char** expr) {
    double result = parseFactor(expr);

    while (**expr) {
        if (**expr == '+') {
            (*expr)++;
            result += parseFactor(expr);
        } else if (**expr == '-') {
            (*expr)++;
            result -= parseFactor(expr);
        } else {
            break;
        }
    }

    return result;
}

double parseFactor(const char** expr) {
    double result = parseNumber(expr);

    while (**expr) {
        if (**expr == '*') {
            (*expr)++;
            result *= parseNumber(expr);
        } else if (**expr == '/') {
            (*expr)++;
            result /= parseNumber(expr);
        } else {
            break;
        }
    }

    return result;
}

double parseNumber(const char** expr) {
    while (isspace(**expr)) (*expr)++;  // Skip whitespace

    double result = 0.0;

    if (**expr == '(') {
        (*expr)++;  // Skip '('
        result = parseTerm(expr);
        (*expr)++;  // Skip ')'
    } else {
        char* end;
        result = strtod(*expr, &end);
        *expr = end;
    }

    return result;
}
