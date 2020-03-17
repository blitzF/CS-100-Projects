#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>
#include <windows.h>
using namespace std;

void print_scores(int mode)
{
    string sfile = "scores.txt";
    string lines;
    ifstream ifile;
    ifile.open(sfile.c_str());
    if(mode == 1)
    {
        cout<<"Players"<<"\t\t"<<"Scores"<<endl;
        while(getline(ifile,lines))
        {
            cout<<lines<<endl;
        }
    }
    else if(mode == 2)
    {
        string highest_user,h_found,word;
        int highest_score = 0,pre = 0;
        while (getline(ifile,lines))
        {
            istringstream st(lines);
            while(st >> word)
            {
                if(stringstream(word) >> pre)
                {
                    if(highest_score <= pre)
                    {
                        highest_score = pre;
                        h_found = highest_user;
                    }

                }
                highest_user = word;

            }
        }
        cout<<"User with highest score is: "<<h_found<<endl;
        cout<<"Their score is: "<<highest_score<<endl;
        
    }
    else
    {
        cout<<"invalid mode..."<<endl;
        cout<<"exiting"<<endl;
        exit(0);
    }
    

}

bool Right_Answer(int right_answer, int user_answer)
{
    if(right_answer == user_answer)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

void trivia(string name, string username)
{
    bool checker;
    int new_decision;
    int counter = 0, i = 0, score = 0;
    int answer_index,input_answer;
    string random,question,optionA,optionB,optionC,ansIndex;
    ifstream infile,testfile;
    testfile.open(name.c_str());
    while(getline(testfile,random))
    {
    	counter++;
    }
    counter = counter/5;

    testfile.close();
    infile.open(name.c_str());
    while(i < counter)
    {
        system("color 9F");
        getline(infile,question);
        getline(infile,optionA);
        getline(infile,optionB);
        getline(infile,optionC);
        getline(infile,ansIndex);
        cout<<"**********************************************************************"<<endl;
        cout<<"Question: "<<question<<endl;
        cout<<"Option-1: "<<optionA<<endl;
        cout<<"Option-2: "<<optionB<<endl;
        cout<<"Option-3: "<<optionC<<endl;
        cout<<"**********************************************************************"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<"Enter 1 for Option-1"<<endl;
        cout<<"Enter 2 for Option-2"<<endl;
        cout<<"Enter 3 for Option-3"<<endl;
        cout<<"-----------------------------------------------------------------------"<<endl;
        answer_index = stoi(ansIndex);
        cin>>input_answer;
        input_answer = input_answer - 1;
        checker = Right_Answer(answer_index,input_answer);
        if(checker == true)
        {
            cout<<endl;
            cout<<"Congratulations!!! Right Answer..."<<endl;
            score = score+5;
            cout<<"Your Score is: "<<score<<endl;
            cout<<"oooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"<<endl;
            Sleep(1500);
            system("CLS");
        }
        else
        {
            //
            ofstream wfile;
            string file = "scores.txt";
            testfile.open(file.c_str());
            if(testfile.fail())
            {
                wfile.open(file.c_str());
            }
            else
            {
                testfile.close();
                wfile.open(file.c_str(), std::ios_base::app);
                wfile<<"\n";
            }
            
            wfile<<username;
            wfile<<"\t\t";
            wfile<<score;
            wfile.close();
            //
            system("color C0");
            cout<<endl;
            cout<<"Bad Luck!! Your answer is Wrong..."<<endl;
            cout<<"Your score is: "<<score<<endl;
            cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
            infile.close();
            cout<<endl;
            cout<<"Enter 1 to play again..."<<endl;
            cout<<"Enter 2 to see all scores"<<endl;
            cout<<"Enter 3 to exit"<<endl;
            cin>>new_decision;
            if(new_decision == 1)
            {
                system("CLS");
                trivia(name,username);
            }
            else if(new_decision == 2)
            {
                system("CLS");
                print_scores(1);
                break;
            }
            else if(new_decision == 3)
            {
                cout<<"Thank you for playing Movie Trivia with US !!"<<endl;
                break;
                exit(0);

            }
            else
            {
                break;
                cout<<"Invalid Input!!"<<endl;
                cout<<"Exiting"<<endl;
                exit(0);
            }
            
            
        }
        i++;
        if(i==counter)
        {
            cout<<"WOW!! You have won this Movie Trivia....."<<endl;
        }
        

    }
}

int Welcome(string *username)
{
    system("CLS");
    system("color DF");
    string userr;
    int user;
    cout<<"*************************************************"<<endl;
    cout<<"Welcome to Movie Trivia"<<endl;
    cout<<"*************************************************"<<endl;
    cout<<endl;
    cout<<"Please Enter Your Name:  "; cin>>userr;
    
    *username = userr;
    system("CLS");
    cout<<"*************************************************"<<endl;
    cout<<"Enter 1 for Bollywood"<<endl;
    cout<<"Enter 2 for Hollywood"<<endl;
    cout<<"Enter 3 to see scores of all players.."<<endl;
    cout<<"Enter 4 to see highest score.."<<endl;
    cout<<"*************************************************"<<endl;
    cin >> user;
    if(user == 1)
    {
        return 0;
    }
    else if(user == 2)
    {
        return 1;
    }
    else if(user == 3)
    {
        return 2;
    }
    else if(user == 4)
    {
        return 3;
    }
    else
    {
        return 4;
    }
    


}

int main()
{
    string username;
    string bollywood = "bollywood.txt";
    string hollywood = "hollywood.txt";
    int decision = Welcome(&username);
    if(decision == 0)
    {
        system("CLS");
        trivia(bollywood,username);
    }
    else if (decision == 1)
    {
        system("CLS");
        trivia(hollywood,username);
    }
    else if(decision == 2)
    {
        system("CLS");
        print_scores(1);
    }
    else if(decision == 3)
    {
        system("CLS");
        print_scores(2);
    }
    else
    {
        cout<<"Invalid User Input"<<endl;
        cout<<"Exiting"<<endl;
        exit(0);
    }

}