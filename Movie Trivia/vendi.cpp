#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <windows.h>
using namespace std;



bool exists_check(string name)
{
	ifstream infile;
	name = name + ".txt";
	infile.open(name.c_str());
	if(infile.fail())
	{
		return true;
	}
	else
	{
		infile.close();
		return false;
	}
}

void update_account(string user_name,string password,int balance, int amounts[], int prices[], string products[],int n)
{
	int it = 0;
	ofstream wfile,inv;
	string file = user_name + ".txt";
	string inventory_file = "inventory.txt";
	string temp = "temp.txt";
	string sample,input;
	remove(file.c_str());
	remove(inventory_file.c_str());
	//updating the user information...
	wfile.open(file.c_str());
	wfile<<user_name;
	wfile<<"\n";
	wfile<<password;
	wfile<<"\n";
	wfile<<balance;
	wfile.close();
	//Updating the inventory....
	inv.open(inventory_file.c_str());
	inv<<"Product";
	inv<<"\t\t\t";
	inv<<"Price";
	inv<<"\t\t\t";
	inv<<"Amount";
	inv<<"\n";
	while(it < n)
	{
		inv<<products[it];
		inv<<"\t\t\t";
		inv<<prices[it];
		inv<<"\t\t\t";
		inv<<amounts[it];
		inv<<"\n";
		it++;
	}
	inv.close();




}

void vendi_main(string products[],int amounts[],int prices[],int n)
{
	ifstream rfile;
	ofstream wfile;
	bool already;
	string dec,user_name,password,file_name,dec2;
	int balance,number,recharge;
	cout<<"Are you a new user?  (yes or no)"<<endl;
	cin>>dec;
	while(dec != "yes" && dec != "no")
	{
		cout<<"Error: Wrong Input"<<endl;
		cout<<"Enter (yes) or (no) again:";cin>>dec;

	}
	if(dec == "yes")
	{
		balance = 100;
		cout<<"Enter desired username: ";
		cin>>user_name;
		cout<<endl;
		cout<<"Enter your password: ";
		cin>>password;
		cout<<endl;
		already = exists_check(user_name);
		while(!already)
		{
			cout<<"User already exists..."<<endl;
			cout<<"Enter new username: ";cin>>user_name;
			cout<<"Enter new password: ";cin>>password;
			cout<<endl;
			already = exists_check(user_name);
		}
		file_name = user_name + ".txt";
		wfile.open(file_name.c_str());
		wfile<<user_name;
		wfile<<"\n";
		wfile<<password;
		wfile<<"\n";
		wfile<<balance;
		wfile.close();
	}
	else
	{
		string test_pass,test_user,st_balance;
		cout<<"Enter your username: ";
		cin>>user_name;
		cout<<endl;
		cout<<"Enter your password: ";
		cin>>password;
		cout<<endl;
		file_name = user_name + ".txt";
		rfile.open(file_name.c_str());
		if(rfile.fail())
		{
			cout<<"You're not an existing user..."<<endl;
			cout<<"Quitting Vendi.. Run again."<<endl;
			exit(0);
		}
		getline(rfile,test_user);
		getline(rfile,test_pass);
		getline(rfile,st_balance);
		balance = atoi(st_balance.c_str());
		if (user_name == test_user && password == test_pass)
		{
			cout<<"Welcome to Vendi..."<<endl;
		}
		else
		{
			cout<<"Incorrect credentials... Quitting.."<<endl;
			exit(0);
		}
		rfile.close();

	}
	while(1)
	{
		system("CLS");
		system("color 9F");
		Sleep(900);
		cout<<"If you want to see the menu press 97....."<<endl;
		cout<<"If you want to exit press 98..."<<endl;
		cout<<"If you want to recharge your account press 99..."<<endl;
		cin>>number;
		if(number == 97)
		{
			system("CLS");
			system("color DF");
			cout<<"Here's the list of items you can purchase..."<<endl;
			for(int i=0; i<n;i++)
			{
				cout<<i<<": "<<products[i]<<"\t"<<"Price: "<<prices[i]<<endl;
			}
			cout<<"Enter the number of product you want to purchase: "<<endl;
			cout<<"You can still enter 98 to exit and 99 to recharge..."<<endl;
			cin>>number;
		}
		
		while(number >= n && number != 99 && number != 98)
		{
			cout<<"Error: incorrect number entered..."<<endl;
			Sleep(900);
			continue;

		}
		if(number == 98)
		{
			cout<<"Thank you for using vendi.. Your details have been updated !"<<endl;
			break;
		}
		if(number == 99)
		{
			cout<<"Enter the amount you want to recharge: ";cin>>recharge;
			balance = balance + recharge;
			cout<<"You have successfully recharged your account.."<<endl;
			Sleep(1000);
			continue;
		}
		if(balance >= prices[number] && amounts[number] > 0)
		{
			cout<<"You've successfully bought: "<<products[number]<<endl;
			balance = balance - prices[number];
			amounts[number] = amounts[number] - 1;
			cout<<"Please collect your item from below...."<<endl;
			Sleep(1000);
		}
		else
		{
			if(amounts[number] <= 0)
			{
				cout<<"The item is out of stock... Sorry!"<<endl;
				cout<<"Please consider purchasing anything else..."<<endl;
				Sleep(1000);
				continue;
			}
			cout<<"Insufficient balance...Please recharge your account to purchase this."<<endl;
			cout<<"Would you like to buy anything else? ";cin>>dec2;
			if(dec2 == "no")
			{
				cout<<"Thank you for using vendi.."<<endl;
				break;
			}
			if(dec2 =="yes")
			{
				continue;
			}
		}
	}
	update_account(user_name,password,balance,amounts,prices,products,n);
}

void file_read(string name)
{
	bool T = true; //To check if the int obtained while reading is either a price or amount of product...
	int counter = 0; //To count number of products in inventory
    ifstream infile,testfile;
    testfile.open(name.c_str());
    string tester; //random string to read the file so that can obtain counter.
    while(getline(testfile,tester))
    {
    	counter++;
    }
    counter = counter-1;
    testfile.close();
    infile.open(name.c_str());
    string garbage,input;
    string concat = ""; //String to get Product names...
    string products[counter]; //Products array for all the inventory products..
    int k = 0;
    int prices[counter]; //Array for prices of products..
    int amounts[counter]; //Array containing quantity of products..
    getline(infile,garbage);
    while(getline(infile,input))
    {
        istringstream st(input);
        string sample;
        int price,amount,found;
        while(st >> sample)
        {
            if(stringstream(sample) >> found)
                {
                	if(sample == "300ml" || sample == "7up" || sample =="7up300ml")
                	{
                		concat = concat + sample;
                		continue;
                	}
                	if(T)
                	{
                		price = found;
                		T = false;
                		continue;
                	}
                	else
                	{
                		amount = found;
                		T = true;
                		continue;
                	}
                }
            concat = concat + sample; 

        }
        products[k] = concat;
        prices[k] = price;
        amounts[k] = amount;
        k++;
        concat = "";

    }
    infile.close();
    vendi_main(products,amounts,prices,counter);


}

int main()
{
	//Here I am giving the program my inventory file so that It can take data from it..
	//Reading the inventory file and storing the data in corresponding arrays....
    string inv = "inventory.txt";
	file_read(inv);

	return 0;
}
