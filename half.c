// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    return 0.0;
}

//*COMPLETED INTO:

// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill_amount, float tax_percent, int tip_percent);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{

    //Calculate taxed bill
    float taxed = (bill * tax) / 100;

    //Convert int tip into float tip decimal
    float tip_decimal = ((float) tip / 100);

    //Calculate tip
    float tip_total = (bill + taxed) * tip_decimal;

    //Calculate total owe
    float totalBill = (bill + taxed + tip_total);

    //Calculate and return half owed
    float halfBill = totalBill / 2;
    return halfBill;
}
