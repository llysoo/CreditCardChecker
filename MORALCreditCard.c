/***************************************************************************************
This is to certify that this project is my own work, based on my personal efforts
in studying and applying the concepts learned. I have constructed the
functions and their respective algorithms and corresponding code by myself.
The program was run, tested, and debugged by my own efforts. I further
certify that I have not copied in part or whole or otherwise plagiarized the
work of other students and/or persons.
											Gwyneth Allyson M. Moral, DLSU ID# 12278254
***************************************************************************************/

/*
Description: The program displays the bill of the owner of the credit card.
			 It calculates the purchases, payments, points, balance, and
		     generates the credit card bill every end of a billing cycle. 
Programmed by: Gwyneth Allyson M. Moral <S16>
Last modified: 07/30/2023
Version: 1.0
[Acknowledgements: stdlib.h 
				   Sample credit card statement Payment Information Date: 12/30/XX Payment Due Date: 1/23/XX. (n.d.).Retrieved July 27, 2023.
				   McElroy, D. (2021, February 19). Credit Card Payoff in C, C++ and Java.
*/

#include <stdio.h>
#include <stdlib.h>

/* Function to clear the terminal*/
void displayClear() {
     system("cls");
}

/* Function to display the menu and get user 
choice from the menu that they want to see or do
Precondition: user select an integer from 1-7 only
@param choice the input choice of user
@return the interger choice of user
*/
int getUserChoice() {
    int choice;
    printf("\nPossible Actions\n");
    printf("1-Add Purchase\n");
    printf("2-View Previous Statement\n");
    printf("3-Make Payment\n");
    printf("4-View Reward Points\n");
    printf("5-Use Reward Points\n");
    printf("6-End Billing Cycle\n");
    printf("7-Exit\n");
    printf("Enter Action You want to do: ");
    scanf("%d", &choice);
    return choice;
}

/* Function to compute the reward points of the credit card 
Precondition: purchases are non-negative
@paramm amountPurchases is the amount of the purachase
@return the number of reward points
*/
int calculateRewardPoints(float amountPurchases) {
    return (amountPurchases / 30);
}

/* Function to compute twice the credit card limit 
Precondition: number entered is positive
@paramm creditLimit is the limit entered by the user
@return twice the number of the limit
*/
float calculateTwiceLimit(float creditLimit) {
    return creditLimit * 2;
}

/* Function to compute the outstanding balance 
Precondition: numbers are positive
@paramm previousBalance is the total amount due of the previous billing cycle
@paramm fPurchases is the total amount of purchases made during the current billing cycle
@paramm previousBalance is the total amount due of the previous billing cycle
@return the amount of the outstanding balance
*/
float calculateOutstandingBalance(float previousBalance, float fPurchases, float paymentsCredits) {
    return previousBalance + fPurchases - paymentsCredits;
}

/* Function to compute the total amount due 
Precondition: numbers are positive
@paramm outstandingBalance is the current amount owed at a point in time
@paramm financeCharges is the total of overlimit fee and unpaid balance fee
@paramm latePayment is the charge for not paying at least the minimum amount
due of the previous billing cycle.
@return the total amount due of the current bill
*/
float calculateTotalAmountDue(float outstandingBalance, float financeCharges, float latePayment) {
    return outstandingBalance + financeCharges + latePayment;
}

/*Function to compute the total credit points 
Precondition: numbers are positive
@paramm prevPointsBal is the total previous points.
@paramm currentPointsEarn is the points earned during the current billing cycle
@paramm pointsUsed is the points used during the current billing cycle
@return the total credit points
*/
int calculateTotalCreditPoints(int prevPointsBal, int currentPointsEarn, int pointsUsed) {
    return prevPointsBal + currentPointsEarn - pointsUsed;
}

/* Function to handle purchase transaction or option 1 
Precondition: numbers are positive and valid
@paramm purchases is the amount of purchases entered
@paramm currentPointsEarn is the points earned during the current cycle
@paramm creditLimit is the limit of the credit card
@param purchaseAmount is the amount of purchase entered
*/
void processPurchase(float* fPurchases, int* currentPointsEarn, float creditLimit) {
    float purchaseAmount;
    int purchaseLoop=0;
    
	while(!purchaseLoop){
		printf("\nPlease Enter Amount of the Purchase: ");
    	scanf("%f", &purchaseAmount);
    	displayClear();
    		// Check if the purchase is greater than 2 times the limit
    	if (purchaseAmount >= calculateTwiceLimit(creditLimit)) {
        	printf("-----Transaction Denied. Credit Limit exceeded-----\n");
        	printf("----------------TRY AGAIN-----------------\n");
    	} else if (purchaseAmount > 0) {
        	// Check if the amount entered is non-negative
        	*fPurchases += purchaseAmount;
        	*currentPointsEarn += calculateRewardPoints(purchaseAmount);
        	printf("-----Amount of Purchase Successfully Added-----\n");
        	purchaseLoop=1;
    	} else {
        	printf("-----Invalid Amount. Please enter a non-negative number-----\n");
        	printf("--------------------------TRY AGAIN--------------------------\n");
    	}
	}
}

/* Function to display the previous balance and previous amount due of the bill or option 2
Precondition: numbers are equal to previous balance and previous minimum amount 
@paramm previousBalance is the total amount due of the previous billing cycle
@paramm prevMinAmountDue is the minimum amount due of the previous billing cycle
*/
void displayPreviousStatement(float previousBalance, float prevMinAmountDue) {
	displayClear();
	printf("-----------------------------------------------\n");
    printf("Previous Balance: %.2f\n", previousBalance);
    printf("Previous Minimum Amount Due: %.2f\n", prevMinAmountDue);
    printf("-----------------------------------------------\n");
}

/* Function to handle payment transaction or option 3
Precondition: numbers are positive
@paramm paymentsCredits is the valid amount of payment entered
@paramm paymentAmount to take in the amount of payment entered
*/
void processPayment(float* paymentsCredits) {
    float paymentAmount;
    int paymentLoop=0;
    
    while(!paymentLoop){
		printf("\nPlease Input Amount of Payment: ");
    	scanf("%f", &paymentAmount);
    	displayClear();
		//checks if payment value is valid
    	if (paymentAmount >= 0) {
        	*paymentsCredits += paymentAmount;
        	printf("-----Amount of Payment Successfully Added-----\n");
        	paymentLoop=1;
    	} else {
        	printf("-----Invalid Amount. Please enter a non-negative number-----\n");
        	printf("--------------------------TRY AGAIN--------------------------\n");
    	}
	}
}

/* Function to display reward points earned during the current billing cycle or option 4
Precondition: numbers are 0 or greater
@paramm billCycle is the number of current billing cycle
@paramm totalCreditPoints presents all the credit points earned
*/
void displayRewardPoints(int billCycle, int totalCreditPoints) {
	displayClear();
	printf("--------------------------------------------------\n");
    printf("Total Reward Points Earned in Billing Cycle %d: %d\n", billCycle, totalCreditPoints);
	printf("--------------------------------------------------\n");
}

/* Function to handle reward redemption or 5
Precondition: numbers are positive
@paramm pointsUsed used points of user in the current bill cycle
@paramm paymentsCredits is the valid amount of payment entered
@param totalCreditPoints is the total points earned
@param rewardChoice choice of user for reward
*/
void processRewardRedemption(int* pointsUsed, float* paymentsCredits, int* totalCreditPoints) {
    int rewardChoice;
    int rewardLoop=0;
    displayClear();
    if (*totalCreditPoints >= 1000) {
    	while(!rewardLoop){
        	printf("\nAvailable Rewards to Claim:\n");
        	printf("[1] Php 100 eGift voucher for 1000 pts\n");
        	printf("[2] Php 100 credits for 1000 pts\n");
        	printf("[3] Cancel\n");
        	printf("Please Choose an Action: ");
        	scanf("%d", &rewardChoice);
        	displayClear();

        	switch (rewardChoice) {
            	case 1: {
                	*pointsUsed += 1000;
                	printf("----------------------------------------------------------------\n");
                	printf("The eGift voucher code was sent to your registered mobile number\n");
                	printf("----------------------------------------------------------------\n");
					rewardLoop=1;
                	break;
           		}
            	case 2: {
                	*pointsUsed += 1000;
                	*paymentsCredits += 100;
                	printf("-------------------------------------\n");
                	printf("Php 100 was Added to Payments/Credits\n");
                	printf("-------------------------------------\n");
                	rewardLoop=1;
                	break;
            	}
            	case 3: {
            		rewardLoop=1;
                	break;
            	}
            	default: {
                	printf("-----Invalid Choice. Please choose from above-----\n");
        			printf("-------------------TRY AGAIN-------------------\n");
                	break;
            	}
        	}
		}
    } else {
    	printf("-------------------------------------------------\n");
        printf("There are not enough points to claim any rewards.\n");
        printf("-------------------------------------------------\n");

	}
}


/*This function displays the generated credit card bill
Precondition: values are presented correctly
@paramm billCycle is the current billing cycle number
@paramm previousBalance is the balance from the previous billing cycle
@paramm paymentsCredits is the amount made during the current billing cycle
@param fPurchases is the purchased amount during the current billing cycle
@param financeCharges is the total of overlimit fee and unpaid balance fee
@param latePayment is the  charge for not paying at least the minimum amount due of the previous billing cycle.
@param TotalAmountDue is the total of the outstanding balance, finance charges, and late charges
@param minAmountDue is the portion of the total amount due and is the minimum amount that should be paid within the next billing cycle
@param prevPointsBal is the total of the previous points
@param currentPointsEarn is the points accumulated during the current bill cycle
@param pointsUsed points is the used during the current billing cycle
@param totalCreditPoints is the total of previous and current points minus the used points
*/
void generateCardBill(int billCycle, float previousBalance, float paymentsCredits, float fPurchases,
    float financeCharges, float latePayment, float TotalAmountDue, float minAmountDue,
    int prevPointsBal, int currentPointsEarn, int pointsUsed, int totalCreditPoints) {
	
	displayClear();
    printf("---- Credit Card Bill ----\n");
    printf("---- Billing Cycle %d ----\n\n", billCycle);
    printf("-------------------------------------------\n");
    printf("Previous Balance: %.2f\n", previousBalance);
    printf("(-)Payments / Credits: %.2f\n", paymentsCredits);
    printf("(+)Purchases: %.2f\n", fPurchases);
    printf("(+)Finance Charges: %.2f\n", financeCharges);
    printf("(+)Late Payment Charges: %.2f\n", latePayment);
    printf("-------------------------------------------\n");
    printf("Total Amount Due: %.2f\n", TotalAmountDue);
    printf("Minimum  Amount Due: %.2f\n", minAmountDue);
    printf("-------------------------------------------\n");
    printf("Previous Cards Points Balance: %d\n", prevPointsBal);
    printf("(+)Current Points Earned: %d\n", currentPointsEarn);
    printf("(-)Points Used: %d\n", pointsUsed);
    printf("Total Credit Points: %d\n", totalCreditPoints);
    printf("-------------------------------------------\n\n");
}


/* Function to handle the end of the billing cycle or 6
Precondition: values are computed correctly
@paramm billCycle is the current billing cycle number
@paramm previousBalance is the balance from the previous billing cycle
@paramm paymentsCredits is the amount made during the current billing cycle
@param fPurchases is the purchased amount during the current billing cycle
@param financeCharges is the total of overlimit fee and unpaid balance fee
@param latePayment is the  charge for not paying at least the minimum amount due of the previous billing cycle.
@param totalAmountDue is the total of the outstanding balance, finance charges, and late charges
@param minAmountDue is the portion of the total amount due and is the minimum amount that should be paid within the next billing cycle
@param prevPointsBal is the total of the previous points
@param currentPointsEarn is the points accumulated during the current bill cycle
@param pointsUsed points is the used during the current billing cycle
@param totalCreditPoints is the total of previous and current points minus the used points
@param creditLimit is the credit limit set by user
@param outstandingBalance is the current amount owed at a point in time
@param prevMinAmountDue is the minimum amount due of the previous billing cycle
*/
void endBillingCycle(int billCycle, float* previousBalance, float* paymentsCredits,
                     float* fPurchases, float* financeCharges, float* latePayment,
                     float* totalAmountDue, float* minAmountDue, int* prevPointsBal,
                     int* currentPointsEarn, int* pointsUsed, int* totalCreditPoints,
                     float creditLimit) {

	//calculate the outstanding balance
    float outstandingBalance = calculateOutstandingBalance(*previousBalance, *fPurchases, *paymentsCredits);
	
	*financeCharges=0;
	 
    //checks and computes how much the finance charge 
    if (outstandingBalance > creditLimit)
        *financeCharges += 500;
    else if (*paymentsCredits < *previousBalance)
        *financeCharges += (*previousBalance - *paymentsCredits) * 0.03;

    
    float prevMinAmountDue = *minAmountDue;
    float unpaidBalance = *minAmountDue -*paymentsCredits;
    
    //checks and computes how much the late payment
    if (prevMinAmountDue >= *paymentsCredits) {
        if (prevMinAmountDue  < 850.0) {
            *latePayment = unpaidBalance ;
        }else {
            *latePayment = 850.0;
        }
    }else
    	*latePayment=0;
    	
    //computes the total amount due
    *totalAmountDue = calculateTotalAmountDue(outstandingBalance, *financeCharges, *latePayment);

    //checks and computes how much the minimum amount due 
    if (*totalAmountDue <= 850.00) {
        *minAmountDue = *totalAmountDue;
    }else {
        *minAmountDue = *totalAmountDue * 0.0357;
        if (*minAmountDue < 850.00) {
            *minAmountDue = 850.00;
        }
    }

    //computes the total credit points
    *totalCreditPoints = calculateTotalCreditPoints(*prevPointsBal, *currentPointsEarn, *pointsUsed);

	//calls function to print bill
    generateCardBill(billCycle, *previousBalance, *paymentsCredits, *fPurchases,
                     *financeCharges, *latePayment, *totalAmountDue, *minAmountDue,
                     *prevPointsBal, *currentPointsEarn, *pointsUsed, *totalCreditPoints);
}


int main() {
    int userChoice, billCycle = 1;
    int none_Payment_Made = 0; // Add back the variable none_Payment_Made
    int creditLoop=1;
    int cycleStop = 0; //to start overall loop
    float creditLimit, previousBalance = 0.0, totalAmountDue = 0.0, minAmountDue = 0.0, prevMinAmountDue = 0.0;
    float paymentsCredits = 0.0, fPurchases = 0.0, financeCharges = 0.0, latePayment = 0.0;
    int prevPointsBal = 0, currentPointsEarn = 0, pointsUsed = 0, totalCreditPoints = 0;
   

    // Prompt the user for the credit card limit
    do {
        printf("Please input the credit card limit: ");
        scanf("%f", &creditLimit);
        if (creditLimit > 0) {
            displayClear();
            printf("---------------------------------\n");
            printf("-----Credit Card Limit Added-----\n");
            printf("---------------------------------\n");
            creditLoop=0;
        } else {
            displayClear();
            printf("-----------------------------------------------\n");
            printf("Credit Limit Invalid. Enter a Positive Value.\n");
            printf("-----------------------------------------------\n\n");
        }
    } while(creditLoop==1);

    // Main loop
    while (!cycleStop) {
        userChoice = getUserChoice();

        switch (userChoice) {
            case 1: {
                processPurchase(&fPurchases, &currentPointsEarn, creditLimit);
                break;
            }
            case 2: {
                prevMinAmountDue = minAmountDue;
                previousBalance = totalAmountDue;
                displayPreviousStatement(previousBalance, prevMinAmountDue);
                break;
            }
            case 3: {
                processPayment(&paymentsCredits);
                break;
            }
            case 4: {
                displayRewardPoints(billCycle, totalCreditPoints);
                break;
            }
            case 5: {
                processRewardRedemption(&pointsUsed, &paymentsCredits, &totalCreditPoints);
                break;
            }
             case 6: {
               	endBillingCycle(billCycle, &previousBalance, &paymentsCredits, &fPurchases,
                                &financeCharges, &latePayment, &totalAmountDue, &minAmountDue,
                                &prevPointsBal, &currentPointsEarn, &pointsUsed, &totalCreditPoints,
                                creditLimit);
    				
                //checks for consecutive billing cycle without payment
				if (minAmountDue > 0 && paymentsCredits == 0) {
        			none_Payment_Made++;
        			if (none_Payment_Made == 4) {
        				printf("-----------------------------------------------------\n");
            			printf("\nYour credit card has been canceled\n");
            			printf("Demandable Amount Due: PHP %.2f\n", totalAmountDue);
            			printf("Penalty Due: PHP %.2f\n", totalAmountDue * 0.25);
            			printf("\n-----------------------------------------------------\n");
            			cycleStop=1; }
				}else 
					none_Payment_Made=0;
    			
    			//signals start of new bill cycle
    			if(cycleStop==0){
    				printf("\n\n-----Next Billing Cycle-----\n");
					printf("----started successfully----\n");
    			}
    		
            	// Reset values
    			previousBalance = totalAmountDue;
    			prevPointsBal = totalCreditPoints;
    			currentPointsEarn = 0;
    			pointsUsed = 0;
    			fPurchases = 0;
    			paymentsCredits = 0;
    			
    			//updates the bill cycle number
                billCycle++; 
                
                // Checks for every 12 billing cycles
    			if (billCycle % 12 == 0)
        			fPurchases += 2000;
                break;
            }
            case 7: {
            	printf("-----------------------------------------------------\n");
            	printf("------Terminating Credit Card Billing Generator------\n");
            	printf("-----------------------------------------------------\n");
                cycleStop = 1; // Terminate the overall loop
                break;
            }
            default: {
            	printf("-------------------------------\n");
                printf("Invalid Input. Please try again\n");
                printf("-------------------------------\n");
                break;
            }
        }
    }

    return 0;
}
