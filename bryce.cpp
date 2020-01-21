#include <iostream>
#include <cstdlib>
using namespace std;

int total(int ones, int fives, int tens, int twenties, int fifties, int hundreds){
	return ones*1+fives*5+tens*10+twenties*20+fifties*50+hundreds*100;
}

int complete(int ones, int fives, int tens, int twenties, int fifties, int hundreds){
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

void split(int split_above, int &ones, int &fives, int &tens, int &twenties, int &fifties, int &hundreds){
	if(split_above < 5){
		if(fives > 2){
			cout << "Split a 5 into five ones" << endl;
			fives--;
			ones += 5;
			return;
		}
	}

	if(split_above < 10){
		if(tens > 1){
			cout << "Split a 10 into two fives" << endl;
			tens--;
			fives += 2;
			return;
		}
	}

	if(split_above < 20){
		if(twenties > 2){
			cout << "Split a 20 into two tens" << endl;
			twenties--;
			tens += 2;
			return;
		}
	}

	if(fifties > 0){
		cout << "Split a 50 into two twenties and a ten" << endl;
		fifties--;
		twenties += 2;
		tens++;
	}

	if(hundreds > 0){
		cout << "Split a 100 into five twenties" << endl;
		hundreds--;
		twenties += 5;
	}
}

void balance(int &ones, int &fives, int &tens, int &twenties, int &fifties, int &hundreds){
	if(ones < 5){
		split(1, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(fives < 2){
		split(5, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(tens < 1){
		split(10, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
	if(twenties < 2){
		split(20, ones, fives, tens, twenties, fifties, hundreds);
		return;
	}
}

void print(int ones, int fives, int tens, int twenties, int fifties, int hundreds){
	cout << "End of Day: " << endl
		 << "Ones: " << ones << endl
		 << "Fives: " << fives << endl
	   << "tens: " << tens << endl
		 << "twenties: " << twenties << endl
		 << "Fifties: " << fifties << endl
		 << "hundreds: " << hundreds << endl;
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

	int price = 0; //This will hold the randomly generated sale price.
	int sales_number = rand() % 20  +1; //This will hold the randomly generated number of sales.
	int i = 0; //For use in the sale simulation while loop.
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

	print(ones, fives, tens, twenties, fifties, hundreds);

	cout << "Total: " << total(ones, fives, tens, twenties, fifties, hundreds) << endl;

	ones = 0;
	fives = 2;
	tens = 1;
	twenties = 2;
	fifties = 1;
	hundreds = 0;

	while(!complete(ones, fives, tens, twenties, fifties, hundreds)){
	  balance(ones, fives, tens, twenties, fifties, hundreds);
  }

	print(ones, fives, tens, twenties, fifties, hundreds);
	/*
	if(total() < 70){
		cout << "Total was not met" << endl;
	}
	else if(complete){
		//while(skim)
	}
	else{
		while(!complete){

		}
	}
	*/

	return 0;

}
