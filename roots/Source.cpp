#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
argc: counts the number of arguments
argv: an array of pointers to strings
COMMAND LINE : argc holds argv's size and argv holds pointers to strings
We can test machine epsilon by inputing its value inside a while condition.
Machine epsilon is found by to refering to the standard floating point formats and using the pow formula.

f(x) coeffs are    { 1 -6 4 12 1 4 }
argv[0] is file
argv[1]  1
argv[2] -6
argv[3]  4
argv[4]  12
argv[5] is a = 1
argv[6] is b = 4
*/

extern int size = __argc;//size is global variable

void bisection(char *argv[]);
void newton(char *argv[], double c);
float horner(double x, char *argv[], int size, char letter);

int main(int argc, char *argv[])

{

	printf("total size is %d\n\n", size);

	int i;
	int power = 0;
	for (i = 1; i < size - 2; i++)//i use this loop to see how many items i hae
	{
		printf("%6.2f is coeff %d \n", atof(argv[i]), i);//atof means turning array to float numbers
		power++;// this allows me to see the biggest exponent in the polynomial
	}
	printf("\n");
	printf("a = %.2f\n", atof(argv[size - 2]));
	printf("b = %.2f\n\n", atof(argv[size - 1]));

	printf("\n\nThe highest order is = %d\n\n", power - 1);

	int p = power;

	printf("F(x) = ");/*  print function and power is */

	while (power > 0)//this loop prints the function
	{
		for (i = 1; i <size - 2; i++)
		{
			if (atof(argv[i]) > 0)		printf(" + ");

			else if (atof(argv[i]) < 0)	printf(" - ");
			else
			{
				printf(" ");
			}

			printf("%6.2fx^%d  ", fabs(atof(argv[i])), --power);

		}
	}

	for (i = 1; i < size - 2; i++)// this loop lets polynomial go back to correct order
	{
		power++;
	}
	printf("\n\nF'(x) = ");
	while (power > 0)//this loop prints the derivative after getting correct power
	{
		for (i = 0; i <size - 2; i++)
		{
			if (atof(argv[i]) > 0)		printf(" + ");

			else if (atof(argv[i]) < 0)	printf(" - ");
			else
			{
				printf(" ");
			}
			//very tricky print statement, but just subtract 3 from the command arg when doing derivatives
			printf("%6.2fx^%d  ", (size - 3 - i)*fabs(atof(argv[i])), --power);

		}
	}
	printf("\n\n\nBISECTION\n___________");
	bisection(argv);//invoke this function which will invoke other functions
	system("pause");//makes it easier for YOU to read
}

void bisection(char *argv[])
{

	//this is my machine epsilon
	float e = 1.0f;

	do
	{
		e /= 2.0f;
	} while ((float)(1.0 + (e / 2.0)) != 1.0);
	//


	double c;

	double a = atof(argv[size - 2]);
	double fa;

	double b = atof(argv[size - 1]);
	double fb;

	double fc;

	int iterations = 0;

	printf("\n\nIterations \t\ta \t     F(a)\t\tb\t      F(b)  \t\tc\t\t F(c)\n");
	printf("----------------------------------------------------------------------------------------------------------\n");

	while (e <= fabs(b - a))
	{
		c = (a + b) / 2.0;
		fa = horner(a, argv, size, 'a');
		fb = horner(b, argv, size, 'a');
		fc = horner(c, argv, size, 'a');
		iterations++;

		printf("%d\t\t%10.2f\t%10.2f\t%10.2f\t%10.2f\t%10.2f\t%10.2f\n", iterations, a, fa, b, fb, c, fc);

		if (fc == 0)
		{
			break;
		}

		if (fa*fc<0) //b=c if NEGATIVE
		{
			b = c;
		}

		else if (fa*fc>0) //a=c if POSITIVE
		{
			a = c;
		}

	}
	printf("\n\nThe root is = %f\n\n", c);

	printf("\n\n\Newton\'s Method\n_______________\n");
	newton(argv, c);//invoking newton's method inside a function


	printf("\n\n\Horner\'s Algorithm\n__________________\n\n");
	float root = horner(c, argv, size, 'a');//invoking horner's alg to plug in the root
	printf("F(%f) = %f\n", c, root);
	float rootprime = horner(c, argv, size, 'd');//invoking horner's alg to get its root derivative
	printf("F'(%f) = %f\n\n", c, rootprime);


	return;
}



float horner(double x, char *argv[], int size, char letter)
{

	if (letter == 'a')// this loop allows the function to ADD
	{
		float sum = atof(argv[0]);

		for (int i = 1; i < size - 2; i++)
		{
			sum = sum*x + atof(argv[i]);
		}
		return sum;
	}
	if (letter == 'd')// this loop allow the function to do derivatives
	{
		float sum = atof(argv[0])*(size - 3)*pow(x, size - 3 - 1);

		for (int i = 1; i < size - 3; i++)
		{
			sum = sum + atof(argv[i])*(size - 3 - i)*pow(x, size - 3 - 1 - i);
		}
		return sum;
	}
}

void newton(char *argv[], double c)
{
	//machine epsilon
	float e = 1.0f;

	do
	{
		e /= 2.0f;
	} while ((float)(1.0 + (e / 2.0)) != 1.0);
	//

	double a = atof(argv[size - 2]);
	double b = atof(argv[size - 1]);

	double xn = (a + b) / 2.0;//start method with a+b/2
	double f;
	double df;
	double xn1 = 0;

	int iterations = 0;

	printf("\n\nIterations \t\txn \t     F(xn)\t    F'(xn)\t      xn+1\t\t\n");
	printf("--------------------------------------------------------------------------\n");

	for (int i = 0; i < 5; i++)
	{

		f = horner(xn, argv, size, 'a');	//plug in "xn"
		df = horner(xn, argv, size, 'd');	//derive function and plug in "xn"
		xn1 = xn - f / df;
		printf("%d\t\t%10.3f\t%10.3f\t%10.3f\t%10.3f\n", iterations, xn, f, df, xn1);
		if (xn == xn1)
		{
			break;
		}
		else if ((xn < a) | (b < xn))//error if the root is not inside interval [a,b]
		{
			printf("\nError! The root below does not exist in the interval [%.2f,%.2f]", a, b);
			break;
		}
		iterations++;
		xn = xn1;	//let xn= xn+1 and contine on the next Nth row
	}


	printf("\n\nThe root is = %f\n\n", xn1);

	return;
}

