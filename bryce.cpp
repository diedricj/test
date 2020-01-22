#include <iostream>
#include <cstdlib>
using namespace std;

//This function calculates out cash total.
int total(int ones, int fives, int tens, int twenties, int fifties, int hundreds)
{
	return ones*1+fives*5+tens*10+twenties*20+fifties*50+hundreds*100;
}

//This function will add up how much of each denomination to deposit. Starting with
//highest denomination it will first check if we can remove all the excess bills above
//the minimum amounts for each denomination without going below $70 total. If we can it
//will add one to the deposit amount holder variable for that denomination and remove one
//from the denominations amount and recalculate the total. If depositing the bills would take
//us below $70 th function will tell the user to split that bill, and then adjust our variables
//to keep track of that split.
void skim(int &ones, int &fives, int &tens, int &twenties, int &fifties,
		 int &hundreds, int &dep_1, int &dep_5, int &dep_10, int &dep_20,
		 int &dep_50, int &dep_100)
{

	while(total(ones, fives, tens, twenties, fifties, hundreds) > 85)//Keeps looping until we get below the maximum cash total.
	{

		if(hundreds > 0)//Checking if we have excess hundreds.
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 100 < 70)//Making sure depositing excess hundreds will not
										   //take our cash total below $70.
			{
				cout << "Split a Hundred dollar bill into two fifites" << endl;
				hundreds--;
				fifties += 2;
			}
			else//If we are safe to deposit, this will add one bill to the
			    //deposit count for hundreds.
			{
				dep_100++;
				hundreds--;
			}
		}

		if(fifties > 0)
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 50 < 70)
			{
				cout << "Split a fifty dollar bill into two twenties and a ten" << endl;
				fifties--;
				twenties += 2;
				tens +=1;
			}
			else
			{
				dep_50++;
				fifties--;
			}
		}

		if(twenties > 2)
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 20 < 70)
			{
				cout << "Split a twenty dollar bill into two tens" << endl;
				twenties--;
				tens += 2;
			}
			else
			{
				dep_20++;
				twenties--;

			}
		}

		if(tens > 1)
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 10 < 70)
			{
				cout << "Split a ten dollar bill into two fives" << endl;
				tens--;
				fives += 2;
			}
			else
			{
				dep_10++;
				tens--;
			}

		}

		if(fives > 2)
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 5 < 70)
			{
				cout << "Split a five dollar bill into five ones" << endl;
				fives--;
				ones += 5;
			}
			else
			{
				dep_5++;
				fives--;
			}
		}

		if(ones > 5)
		{
			if(total(ones, fives, tens, twenties, fifties, hundreds) - 1 < 70)
			{
			dep_1++;
			ones--;
		  }
		}
	}
}



//This function returns true if all the minimum amounts for each denomination have
//been met, and false if they have not.
bool complete(int ones, int fives, int tens, int twenties, int fifties, int hundreds)
{
	if(ones < 5){
	   return false;
	}
	if(fives < 2){
	   return false;
	}
	if(tens < 1){
	   return false;
	}
	if(twenties < 2){
	   return false;
	}
	return true;

}

//This function takes a "split above" value and checks the next higher denominatons in
//order of least to greatest for excess bills. If we find an excess bill we instruct the
//cashier to split that bill at the bank in order to get change. We then adjust our
//variables to account for that split.
void split(int split_above, int &ones, int &fives, int &tens, int &twenties,
		   int &fifties, int &hundreds){
	if(split_above < 5)//If the split lacking denomination is smaller than tens.
	{
		if(fives > 2)//Checking for excess fives.
		{
			cout << "Split a 5 into five ones" << endl;
			fives--;
			ones += 5;
			return;
		}
	}

	if(split_above < 10)//If the lacking denomination is smaller than tens.
	{
		if(tens > 1)//Checking for excess tens.
		{
			cout << "Split a 10 into two fives" << endl;
			tens--;
			fives += 2;
			return;
		}
	}

	if(split_above < 20)//If the lacking denomination is smaller than twenties.
	{
		if(twenties > 2)//Checking for excess twenties.
		{
			cout << "Split a 20 into two tens" << endl;
			twenties--;
			tens += 2;
			return;
		}
	}

	if(fifties > 0)//Checking for excess fifties.
	{
		cout << "Split a 50 into two twenties and a ten" << endl;
		fifties--;
		twenties += 2;
		tens++;
	}

	if(hundreds > 0)//Checking for excess hundreds.
	{
		cout << "Split a 100 into five twenties" << endl;
		hundreds--;
		twenties += 5;
	}
}

//This function will check for denominations that are below the minimum amount(or "lacking").
//If it finds a denomination to be lacking, it will call the split function with the proper
//"split above" value. The split above value.
//The split above value will instruct the split function which denominations to start looking
//for abovein order to find change. As if you are short a ten, we dont want to check for excess
//fives to split, for you can not get a ten in change from a five.
void balance(int &ones, int &fives, int &tens, int &twenties, int &fifties, int &hundreds)
{
	if(ones < 5)
	{
		split(1, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(fives < 2)
	{
		split(5, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(tens < 1)
	{
		split(10, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(twenties < 2)
	{
		split(20, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
}

void print(int ones, int fives, int tens, int twenties, int fifties, int hundreds)
{
	cout << "Ones: " << ones << endl
		 << "Fives: " << fives << endl
	   << "tens: " << tens << endl
		 << "twenties: " << twenties << endl
		 << "Fifties: " << fifties << endl
		 << "hundreds: " << hundreds << endl;
}

void simulate(int &ones, int &fives, int &tens, int &twenties, int &fifties, int &hundreds, int price, int sales_number, int i){
	price = 0; //This will hold the randomly generated sale price.
	sales_number = rand() % 20  +1; //This will hold the randomly generated number of sales.
	i = 0; //For use in the sale simulation while loop.
	 //This will hold the total amount of money in the register.

	//Asking the user to input start of day denomination totals.
	cout << "Please enter the amout of 1's in the register" << endl;
	cin >> ones;
	cout << "Please enter the amout of 5's in the register" << endl;
	cin >> fives;
	cout << "Please enter the amout of 10's in the register" << endl;
	cin  >> tens;
	cout << "Please enter the amout of 20's in the register" << endl;
	cin >> twenties;
	cout << "Please enter the amout of 50's in the register" << endl;
	cin >> fifties;
	cout << "Please enter the amout of 100's in the register" << endl;
	cin >> hundreds;

	cout << "Sales Number: " << sales_number << endl;

	while(i < sales_number)
	{

	//Using the modular arithmetic this loop will first generate a random price,
	//and then (assuming exact change) calculate the new totals of each denomination
	//after each purchase. After each succesive loop we increase the counter until
	//'i' until it is equal to the number of generated daily sales. This is all to
	//simulate a days worth of transactions.

		price = rand() % 100 +1;
		cout << "Price" << i << ": " << price << endl;
		hundreds += price/100;
		price = price%100;

		fifties += price/50;
		price = price%50;

		twenties += price/20;
		price = price%20;

		tens += price/10;
		price = price%10;

		fives += price/5;
		price = price%5;

		ones += price/1;
		price = price;

		++i;
	}
}

int main()
{
	srand(time(0));
	//These variables will keep track of how many bills of each denomination is
	//in the register at any given moment.
	int ones = 0;
	int fives = 0;
	int tens = 0;
	int twenties = 0;
	int fifties = 0;
	int hundreds = 0;

	//These variables will keep track of how any of each denomination needs
	//to be deposited at end of day.
	int dep_1 = 0;
	int dep_5 = 0;
	int dep_10 = 0;
	int dep_20 = 0;
	int dep_50 = 0;
	int dep_100 = 0;

	int price, i, sales_number;

  simulate(ones, fives, tens, twenties, fifties, hundreds, price, sales_number, i);

	cout << "Total: " << total(ones, fives, tens, twenties, fifties, hundreds) << endl;

	print(ones, fives, tens, twenties, fifties, hundreds);

	if(total(ones, fives, tens, twenties, fifties, hundreds) < 70)
	{
		cout << "Total was not met" << endl;
	}
	else if(complete(ones, fives, tens, twenties, fifties, hundreds))
	{
		skim(ones, fives, tens, twenties, fifties, hundreds, dep_1,
				   dep_5, dep_10, dep_20, dep_50, dep_100);
	}
	else
	{
		while(!complete(ones, fives, tens, twenties, fifties, hundreds))
		{
			balance(ones, fives, tens, twenties, fifties, hundreds);
		}
		skim(ones, fives, tens, twenties, fifties, hundreds, dep_1,
				   dep_5, dep_10, dep_20, dep_50, dep_100);
	}

	cout << "Deposit " << dep_1  << " ones" << endl;
	cout << "Deposit " << dep_5  << " fives" << endl;
	cout << "Deposit " << dep_10  << " tens" << endl;
	cout << "Deposit " << dep_20  << " twenties" << endl;
	cout << "Deposit " << dep_50  << " fifties" << endl;
	cout << "Deposit " << dep_100  << " hundreds" << endl;

	cout << "Total left after deposits: "
			 << total(ones, fives, tens, twenties, fifties, hundreds)
			 << endl;
  cout << endl << "Bills left for next day are: " << endl;
	print(ones, fives, tens, twenties, fifties, hundreds);


	return 0;

}
