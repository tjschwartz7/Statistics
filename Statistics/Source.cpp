#include "statistics.h"
#include <string>


int main()
{
	Statistics st;

	set<string> S = { "HH", "HT", "TH", "TT" };
	set<string> A = { "HH"};
	set<string> B = { "HH", "HT", "TH"};
	cout << "P(A/B) = " << st.P_AgivenB<string>(A, B, S) << endl;
	cout << "P(A+B) = " << st.P_AunionB<string>(A, B, S) << endl;
	cout << "P(AB) = " << st.P_AintersectB<string>(A, B, S) << endl;
	cout << "P(A) = " << st.P_A<string>(A, S) << endl;
	cout << "P(B) = " << st.P_A<string>(B, S) << endl;

	cout << "A and B are independent: " << st.IsIndependent(A, B, S) << endl;
	cout << "A and B are mutually exclusive: " << st.IsMutuallyExclusive(A, B) << endl;

	vector<double> pdf = { .05, .4, .3, .2, .05 };
	st.Convert_PDFtoCDF(pdf);

	cout << "E[x] = " << st.ExpectedValue_Nth(pdf) << endl;
	cout << "E[x^2] = " << st.ExpectedValue_Nth(pdf, 2) << endl;
	cout << "Var = " << st.Variance(pdf) << endl;
	cout << "Stdev = " << st.StandardDeviation(pdf) << endl;

	cout << "Geometric probability = " << st.GeometricDistribution(2, .25) << endl;
	cout << "Binomial probability = " << st.BinomialDistribution(5, 3, .50) << endl;

}