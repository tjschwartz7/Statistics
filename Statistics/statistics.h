#pragma once
#include "includes.h"
#define DEBUG 1

class Statistics
{
public:


	vector<double> Convert_PDFtoCDF(vector<double> pdf);
	double ExpectedValue_Nth(vector<double> pdf);
	double ExpectedValue_Nth(vector<double> pdf, int moment);
	double Variance(vector<double> pdf);
	double StandardDeviation(vector<double> pdf);
	double GeometricDistribution(int k, double p);
	double BinomialDistribution(int n, int k, double p);
	double Combination(int n, int k);
	int Factorial(int n);
	double PoissonProcess(double lambda, int k);


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

	template<typename T>
	bool IsIndependent(std::set<T> A, std::set<T> B, std::set<T> S)
	{
		double p_AunionB = P_AunionB(A, B, S);
		double p_A = P_A(A, S);
		double p_B = P_A(B, S);
		double p_AB = p_A * p_B;
		bool isIndependent = p_AunionB == p_AB;
		return isIndependent;
	}

	template<typename T>
	bool IsMutuallyExclusive(std::set<T> A, std::set<T> B)
	{
		std::set<T> temp;
		//Perform the intersect; if magnitude is zero, its mutually exclusive
		//For each item in relation
		for (T a : A)
		{
			//If B does not contain item
			if (B.count(a))
			{
				temp.emplace(a);
			}
		}

		//If A is empty, then A and B had nothing in common
		//Hence, it must be mutually exclusive.
		bool isMutuallyExclusive = (temp.size() == 0);
		return isMutuallyExclusive;
	}

	

private:
};

