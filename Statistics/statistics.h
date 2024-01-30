#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <math.h>
using namespace std;
#define DEBUG 1

class Statistics
{
public:


	template<typename T>
	double P_AgivenB(std::set<T> A, std::set<T> B, std::set<T> S)
	{
		//Get P(AB)
		double p_AintersectB = P_AintersectB(A, B, S);

		//Get P(B)
		double p_B =P_A(B, S);

		//Get P(A/B)
		double p_AgivenB = p_AintersectB / p_B;


#ifdef DEBUG
		cout << "P(AB) = " << p_AintersectB << "\nP(B) = " << p_B << endl;
		cout << "P(A/B) = " << p_AgivenB << endl;
#endif

		return p_AgivenB;
	}

	template<typename T>
	double P_A(std::set<T> A, std::set<T> S)
	{
		//Magn of A / magn S
		double p_A = A.size() / (double)S.size();
		return p_A;
	}

	template<typename T>
	double P_AintersectB(std::set<T> A, std::set<T> B, std::set<T> S)
	{
		//Calculate |A intersect B|, |A union B|
		int intersectMagnitude = 0;
		int unionMagnitude = 0;
		for (T a : A)
		{

			//a is a member of our union; increment union magnitude
			unionMagnitude++;

			//B contains a; increment intersect magnitude, but NOT union, it was tallied above
			if (B.count(a))
			{
				intersectMagnitude++;
			}
		}

		//We've counted all members of A; what's left is the members in B not in A.
		//This is the same as the size of B minus the intersect magnitude of A and B
		unionMagnitude = unionMagnitude + (B.size() - intersectMagnitude);

#ifdef DEBUG
		cout << "|A + B| = " << unionMagnitude << "\n|AB| = " << intersectMagnitude << endl;
#endif
		//Intersect divided by S
		double p_AintersectB = intersectMagnitude / (double)S.size();
		return p_AintersectB;
	}

	template<typename T>
	double P_AunionB(std::set<T> A, std::set<T> B, std::set<T> S)
	{
		//Calculate |A intersect B|, |A union B|
		int intersectMagnitude = 0;
		int unionMagnitude = 0;
		for (T a : A)
		{

			//a is a member of our union; increment union magnitude
			unionMagnitude++;

			//B contains a; increment intersect magnitude, but NOT union, it was tallied above
			if (B.count(a))
			{
				intersectMagnitude++;
			}
		}
		//We've counted all members of A; what's left is the members in B not in A.
		//This is the same as the size of B minus the intersect magnitude of A and B
		unionMagnitude = unionMagnitude + (B.size() - intersectMagnitude);

		double p_AunionB = unionMagnitude / (double)S.size();
		return p_AunionB;
	}

	vector<double> Convert_PDFtoCDF(vector<double> pdf)
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


	double ExpectedValue_Nth(vector<double> pdf)
	{
		double sum = 0;
		for (int i = 0; i < pdf.size(); i++)
		{
			//kP(x=k)
			sum += i * pdf.at(i);
		}
		return sum;
	}

	double ExpectedValue_Nth(vector<double> pdf, int moment)
	{
		double sum = 0;
		for (int i = 0; i < pdf.size(); i++)
		{
			//kP(x=k)
			sum += pow(i, moment) * pdf.at(i);
		}
		return sum;
	}

	double Variance(vector<double> pdf)
	{
		//E[x]
		double e_x = ExpectedValue_Nth(pdf);

		//E[x^2]
		double e_x2 = ExpectedValue_Nth(pdf, 2);

		//E[x^2] - (E[x])^2
		double variance = e_x2 - (e_x * e_x);
		return variance;
	}

	double StandardDeviation(vector<double> pdf)
	{
		double variance = Variance(pdf);

		//stdev = sqrt(variance)
		//or, variance is stdev^2
		double stdev = sqrt(variance);
		return stdev;
	}

private:
};

