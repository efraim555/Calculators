#include <iostream>
#include <cmath>
#include <iomanip>
#include "divisor.h"
#include "multiplier.h"
#include "globals.h"

using namespace std;

int main(int argc, char* argv[])
{
	double principal = 0.0;
	double humanInterest = 0.0;
	int yearsOfLoan = 0.0;

	
	if (argc == 1)
	{
		/*cout << "argc: " << argc << endl;
		cout << "argv[0]: " << argv[0] << endl;

		for (int i = 0; i < argc; i++)
		{
			cout << "argv[" << i << "]: " << argv[i] << endl;
		}*/

		cout << "Enter the principal amount: ";
		cin >> principal;

		cout << "Enter the interest rate: ";
		cin >> humanInterest;

		cout << "Enter the years of loan: ";
		cin >> yearsOfLoan;
	} else {
		principal = atof(argv[1]);;
		humanInterest = atof(argv[2]);
		yearsOfLoan = atoi(argv[3]);
	}

	cout << "Loan Principal: " << principal << endl;
	cout << "Interest Rate: " << humanInterest << "%" << endl;
	cout << "Time Period: " << yearsOfLoan << " years" << endl;

	double interest = divisor(humanInterest, gPercentDenominator);

	double monthInterest = divisor(interest, gMonthsInYear);
	long monthsOfLoan = multiplier(yearsOfLoan,gMonthsInYear);

	double payment = 0.0;
	payment = principal *(monthInterest /
		(1 - (pow((double)1 + monthInterest, (double)-monthsOfLoan))));

	cout << "Monthly Payment: " << setiosflags(ios::fixed) //keep decimal point in particuar precision
		<< setprecision(2) << payment << endl;

	double currInterestPayment = 0.0;
	double currPrincipalPayment = 0.0;
	double currBalance = 0.0;
	long currLoanMonth = 1;
	currBalance = principal;

	while (currLoanMonth <= monthsOfLoan){

		gAmortizeMonth amortMonth;
		currInterestPayment = currBalance * monthInterest;

		currPrincipalPayment = payment - currInterestPayment;
		currBalance = currBalance - currPrincipalPayment;

		amortMonth.year = 1;
		amortMonth.yearMonth = 1;
		amortMonth.loanMonth = currLoanMonth;
		amortMonth.payment = payment;
		amortMonth.pureInterest = currInterestPayment;
		amortMonth.paidDownPrincipal = currPrincipalPayment;
		amortMonth.principalBalance = currBalance;
		

		cout << "Current Month: " << amortMonth.loanMonth
			<< " Current Interest: " << amortMonth.pureInterest
			<< " Current Principal: " << amortMonth.paidDownPrincipal
			<< " Balance: " << amortMonth.principalBalance
			<< endl;
		
		currLoanMonth++;
	}

	cout << "Loan complete"<< endl;
	system("pause");
	return 0;
}
