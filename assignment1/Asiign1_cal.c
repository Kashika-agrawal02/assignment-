#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

int operation(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;

    case '/':
        if (b == 0)
        {

            printf("Error : Division by zero. \n");
           exit(EXIT_FAILURE);
         
        }
        return a / b;
    }
    return 0;
}

int evaluateExpression(char *exp)
{
    int values[MAX_SIZE], valueTop = -1;
    char operator[MAX_SIZE], operatorTop = -1;

    for (int i = 0; i < strlen(exp); i++)
    {

        if (isspace(exp[i]))
        {
            continue;
        }

        if (isdigit(exp[i]))
        {

            int value = 0;

            while (i < strlen(exp) && isdigit(exp[i]))
            {
                value = value * 10 + (exp[i] - '0');
                i++;
            }
            i--;
            values[++valueTop] = value;
        }

        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {

            while (operatorTop >= 0 && precedence(exp[i]) <= precedence(operator[operatorTop]))
            {
                int b = values[valueTop--];
                int a = values[valueTop--];
                char op = operator[operatorTop--];
                values[++valueTop] = operation(a, b, op);
            }
            operator[++operatorTop] = exp[i];
        }

        else
        {
            printf("Error:Invalid expression.\n");
            exit(EXIT_FAILURE);
        }
    }

    while (operatorTop >= 0)
    {
        int b = values[valueTop--];
        int a = values[valueTop--];
        char op = operator[operatorTop--];
        values[++valueTop] = operation(a, b, op);
    }
    return values[valueTop];
}

int isValidExpression(char *input)
{
    for (int i = 0; input[i]; i++)
    {
        if (!isdigit(input[i]) && !isspace(input[i]) && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/')
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char input[MAX_SIZE];
    printf("Enter a mathematical expresion: ");
    fgets(input, MAX_SIZE, stdin);

    input[strcspn(input, "\n")] = '\0';

    if (!isValidExpression(input))
    {
        printf("Error : Invalid expression.\n");
        return 1;
    }

    int result = evaluateExpression(input);
    printf("Result: %d\n", result);

    return 0;
}