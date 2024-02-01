#include "statistics.h"
#include <cmath>

vector<double> Statistics::Convert_PDFtoCDF(vector<double> pdf)
{
	//Summation of inputs must add to one
	//We use a vector because *order matters*
	std::vector<double> cdf;
	double sum = 0;

	//We use the iterator for debugging only
	int iter = 0;
	for (double i : pdf)
	{
		//Keep current count
		sum += i;
		//Push the new count to the back
		cdf.push_back(sum);

#ifdef DEBUG
		cout << "F(" << iter << ") = " << sum << endl;
#endif

		//Debug
		iter++;
	}
	//Invalid pdf - should sum to 1
	if (cdf.back() != 1)
	{
		cout << "PDF was invalid: final sum was " << cdf.back() << endl;
		return {};
	}

	//Fin
	return cdf;
}


double Statistics::ExpectedValue_Nth(vector<double> pdf)
{
	double sum = 0;
	for (int i = 0; i < pdf.size(); i++)
	{
		//kP(x=k)
		sum += i * pdf.at(i);
	}
	return sum;
}

double Statistics::ExpectedValue_Nth(vector<double> pdf, int moment)
{
	double sum = 0;
	for (int i = 0; i < pdf.size(); i++)
	{
		//kP(x=k)
		sum += pow(i, moment) * pdf.at(i);
	}
	return sum;
}

double Statistics::Variance(vector<double> pdf)
{
	//E[x]
	double e_x = ExpectedValue_Nth(pdf);

	//E[x^2]
	double e_x2 = ExpectedValue_Nth(pdf, 2);

	//E[x^2] - (E[x])^2
	double variance = e_x2 - (e_x * e_x);
	return variance;
}

double Statistics::StandardDeviation(vector<double> pdf)
{
	double variance = Variance(pdf);

	//stdev = sqrt(variance)
	//or, variance is stdev^2
	double stdev = sqrt(variance);
	return stdev;
}

double Statistics::GeometricDistribution(int k, double p)
{
	//Plug into geometric distribution with k trials and probability p
	double p_k = pow((1 - p), k-1) * p;
	return p_k;
}

double Statistics::BinomialDistribution(int n, int k, double p)
{
	if (n < k)
	{
		cout << "Malformed input: n < k" << endl;
		return -1;
	}
	double combination = Combination(n, k);
	double pr_m = combination * pow(p, k) * pow(1 - p, n - k);
	return pr_m;
}

/// <summary>
/// Returns n choose k
/// </summary>
/// <param name="n">things taken</param>
/// <param name="k">at a time.</param>
/// <returns>n choose k</returns>
double Statistics::Combination(int n, int k)
{
	//We will inevitably need these variables to be doubles;
	//but floating point math is slower than integer math.
	
	//n! only up to n-k
	int numerator = 1;
	for (int i = n; i > n - k; i--)
	{
		numerator *= n;
	}

	int denominator = 1;
	//calculate k!
	for (int i = k; i > 0; i--)
	{
		denominator *= i;
	}
	double sum = numerator / (double)denominator;
	return sum;

}

/// <summary>
/// Takes an integer n and returns n!.
/// </summary>
/// <param name="n">An integer</param>
/// <returns>Factorial of n.</returns>
int Statistics::Factorial(int n)
{
	int sum = 1;
	for (int i = n; i > 0; i--) sum *= i;
	return sum;
}

/// <summary>
/// Poisson is the limit of the binomial theorem as the number of trials approaches infinity. 
/// Because the binomial theorem gets more accurate as n gets larger, Poisson takes the limit at infinity of n.
/// This function just plugs in user arguments into the equation.
/// </summary>
/// <param name="lambda">Traffic per unit time.</param>
/// <param name="k">k objects pass per unit time.</param>
/// <returns>The probability that less than k objects pass per unit time.</returns>
double Statistics::PoissonProcess(double lambda, int k)
{
	int k_fact = Factorial(k);
	double pr_m = (pow(lambda, k) / k_fact)*(std::exp(lambda*-1));
	return pr_m;
}