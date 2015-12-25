#ifdef _MSVC
#  define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define STEP					1000.0
#define MAX_FIRST_PAY  			1500000.0
#define MAX_DELTA_FIRST_PAY		100000.0

#define INIT_WEB_PRICE 	2800000.0
#define MAX_WEB_PRICE 	3400000.0

#define ORIG_VALUE		490000.0
#define NET_INCOME 		3190000.0

#define AGENCY 			(3690000.0 * 0.007 + 600 - 200)

#define LOAN(web_price)			((web_price) * 0.7)
#define DECORATE(web_price)		((web_price) * 0.1)

#define DEED_TAX(web_price)		((web_price) * 0.03)
#define PERS_TAX(web_price)		(((web_price) - ORIG_VALUE - DECORATE(web_price)) * 0.2)

int purchase() {
	double min_web_price = MAX_WEB_PRICE;

	double deed_tax;
	double pers_tax;
	double loan;
	double net_first_pay;
	double first_pay;
	double total_price;
	double total_expense;

	double delta_first_pay;
	double web_price;

	for (delta_first_pay = 1000.0; delta_first_pay <= MAX_DELTA_FIRST_PAY; delta_first_pay += STEP) {
		for (web_price = INIT_WEB_PRICE; web_price <= MAX_WEB_PRICE; web_price += STEP) {
			deed_tax = DEED_TAX(web_price);
			pers_tax = PERS_TAX(web_price);
			loan = LOAN(web_price);
			net_first_pay = NET_INCOME - loan + pers_tax;
			first_pay = net_first_pay + deed_tax + AGENCY;

			if (fabs(first_pay - MAX_FIRST_PAY) <= delta_first_pay && web_price < min_web_price)
				min_web_price = web_price;
		}
	}

	if (MAX_WEB_PRICE <= min_web_price) {
		printf("Can not find minimal web price\n");
		return -1;
	}

	web_price = min_web_price;

	deed_tax = DEED_TAX(web_price);
	pers_tax = PERS_TAX(web_price);
	loan = LOAN(web_price);
	net_first_pay = NET_INCOME - loan + pers_tax;
	first_pay = net_first_pay + deed_tax + AGENCY;
	total_price = NET_INCOME + pers_tax;
	total_expense = total_price + deed_tax + AGENCY;

	printf("=====================================================\n");
	printf("total_price %.3f\tweb_price %.3f\tloan %.3f\n", total_price / 10000.0, web_price / 10000.0, loan / 10000.0);
	printf("net_first_pay %.3f\n", net_first_pay / 10000.0);
	printf("\n");
	printf("pers_tax %.3f\n", pers_tax / 10000.0);
	printf("deed_tax %.3f\n", deed_tax / 10000.0);
	printf("agency %.3f\n", AGENCY / 10000.0);
	printf("\n");
	printf("first_pay %.3f\n", first_pay / 10000.0);
	printf("total_expense %.3f\n", total_expense / 10000.0);
	printf("\n");
	printf("net_income %.3f\n", NET_INCOME / 10000.0);
	printf("\n");

	return 0;
}
