/********************************************************************************************
 * Name: Rachel Vanderlely
 * Date: October 4, 2022
 * Class:Algorithum Analysis
 * Project: Word Puzzle
 * This program prints out a word puzzle and allows users to search for a word going left, right
 * up or down in the puzzle and if found returns the colounm and row that the word can be found at. 
*********************************************************************************************/ 
#include <string>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#define MAXLENGTH 11

using std::cout;
using std::cin;
using std::string;
        
/****************************************************
 *                   Global Variables
*****************************************************/ 
        const int n = 11;	// Puzzle's dimension, n x n
        char found ='n';
        const char puzzle[n][n] = {
        {'P', 'H', 'K', 'A', 'S', 'C', 'H', 'A', 'O', 'R', 'Y'},
        {'R', 'K', 'E', 'B', 'I', 'H', 'W', 'Y', 'Q', 'A', 'N'},
        {'L', 'O', 'T', 'B', 'G', 'R', 'A', 'N', 'T', 'C', 'I'},
        {'E', 'R', 'T', 'A', 'M', 'I', 'A', 'N', 'E', 'H', 'T'},
        {'I', 'R', 'I', 'S', 'A', 'S', 'N', 'O', 'X', 'E', 'S'},
        {'R', 'A', 'S', 'I', 'V', 'T', 'D', 'S', 'T', 'L', 'E'},
        {'B', 'F', 'A', 'X', 'N', 'O', 'R', 'A', 'A', 'O', 'D'},
        {'A', 'U', 'R', 'E', 'I', 'P', 'O', 'J', 'V', 'G', 'O'},
        {'G', 'X', 'K', 'L', 'C', 'H', 'I', 'Z', 'T', 'L', 'O'},
        {'S', 'A', 'R', 'A', 'K', 'E', 'D', 'Y', 'L', 'A', 'N'},
        {'T', 'R', 'E', 'B', 'O', 'R', 'D', 'A', 'W', 'A', 'J'} };      

/****************************************************
 *                   Function Prototypes
*****************************************************/ 
void print_puzzle();                            //Prints the puzzle to be searched
void input(string &destination);                //Gets user input and returns input in all uppercase
int string_match(string pattern, string text);  //Searchs for a pattern within a text string
void lookLeftToRight(string pattern);           //Calls stringmatch function on all possible strings from left to right
void lookRightToLeft(string pattern);           //Calls stringmatch function on all possible strings from right to left
void lookTopToBottom(string pattern);           //Calls stringmatch function on all possible strings from top to bottom
void lookBottomToTop(string pattern);           //Calls stringmatch function on all possible strings from bottom to top
int flipindex(int flipme);                      //Flips the index for when searching the array backwards 

/****************************************************
 *                   Main Function
*****************************************************/ 
int main()
{
        string runagain = "Y";
        while(runagain == "Y" || runagain =="y")
        {
        string pattern = "";                    //Holds the pattern to search for 
        found = 'n';                            //Reset found flag to no
        print_puzzle();                         //Prints the entire puzzle that will be searched through
        input(pattern);                         //Get user input
        lookLeftToRight(pattern);               //Check all patterns left to right
        lookRightToLeft(pattern);               //Check all patterns right to left
        lookTopToBottom(pattern);               //Check all patterns top to bottom
        lookBottomToTop(pattern);               //Check all patterns bottom to top
        if (found == 'n'){
                cout<<"Not found.\n";
        }
        cout<<"Run again? Y/N: ";                //Ask user if want to run again
        cin>>runagain;                          //Get user input 
        }
        return 0;
}

/****************************************************
 *                    print_puzzle
This function prints the puzzle for searching.
*****************************************************/ 
void print_puzzle()
{
cout<<"\n";
cout<<"       0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10\n";
cout<<"+----+----------------------------------+\n";
        for (int i=0;i<11;i++) {                //Iterate through coloumns 
                cout<<"[";
                cout<<std::setw(3);
                cout<<i<<" ] ";
                for (int k=0;k<11;k++){         //Iterate through rows
                        cout<<puzzle[i][k]<<"  ";
                }
        cout<<"\n";
}
cout<<"+----+----------------------------------+\n";
}

/**********************************************************************************************
 *                                       input
This function takes in a string stored in "destinatinon" by referance and stores the users 
input in this string in uppercase.
***********************************************************************************************/ 
void input(string &destination)
{
cout<<"Enter a word to search for: ";
cin>>destination;
        for (int i = 0;i<destination.length();i++)
        {                        
        destination[i] = toupper(destination[i]);
        }
}

/**********************************************************************************************
 *                                      string_match
This function takes in a string and a pattern and checks if the pattern is contained inside of 
the string. If the pattern is contained in the string the function returns the index of the pattern
inside of the string. If the pattern is not contained inside of the string the function returns -1. 
***********************************************************************************************/ 
int string_match(string pattern, string text)
{
        int pattern_len = pattern.length();             //Pattern length
        int text_len = text.length();                   //Text length
        int stop_index = text_len - pattern_len + 1;    //Stop index m-n+1               

        for (int i = 0; i < stop_index;i++)
        {
            int j=0;                            //iterates through pattern
            int k = i;                          //iterates through text

            while (text[k] == pattern[j] && j < pattern_len)
             {                                  //Incriment both k and j while the text and 
                j++;                            //pattern match and end of pattern not yet 
                k++;                            //reached
             }                               

            //if the pattern was found
            if (j == pattern_len )
            {
                found = 'y';                    //Set flag to yes
                return i;                       //return the beggining index of found pattern
            }  
        }
        return -1;                              //If not found return -1
}

/**********************************************************************************************
                void lookLeftToRight 
This function loads one row of the puzzle from left to right into the text string. 
Then, calls the stringMatching function to find the input word in the text; prints the position of 
the word in the puzzle(row/column number). Repeats each row of the puzzle.
***********************************************************************************************/ 
void lookLeftToRight(string pattern)
{
string text;                    //To hold the string to search
for (int i=0;i<11;i++)          //Iterate through the rows 

{
        text = "";              //Reset the text to null
        int foundindex =-1;     //reset the found index to -1

        int k = 0;              
        for (k=0;k<11;k++)      //Iterate through the cols 
        {
                text = text + puzzle[i][k];
        }
        foundindex = string_match(pattern,text); //check each row for pattern
        if (foundindex != -1)                   //If the pattern was found print it 
        {
                cout<<pattern<<" found at ["<<i<<"]["<<foundindex<<"]. L->R\n\n";
        }
}
}

/**********************************************************************************************
                void lookRightToLeft 
This functino loads one row of the puzzle from left to right into the text array. 
Then, calls the stringMatching function to find the input word in the text; prints the position of 
the word in the puzzle(row/column number). Repeats the above for each row of the puzzle.
***********************************************************************************************/ 
void lookRightToLeft(string pattern)
{
string text;                    //To hold the string to search
int index_flipper;
for (int i=0;i<11;i++)          //Iterate through the rows 
{
        text = "";              //Reset the text to null
        int foundindex =-1;     //reset the found index to -1

        int k = 0;              //Iterate through the cols 
        for (k=10;k>=0;k--)
        {
                text = text + puzzle[i][k];
        }
        foundindex = string_match(pattern,text); //check each row for pattern
        foundindex= flipindex(foundindex);       //Flip the index since your searching backwards 
        if (foundindex != -1)
        {
                cout<<pattern<<" found at ["<<i<<"]["<<foundindex<<"]. R->L\n\n";
        }
}
}

/**********************************************************************************************
                void lookTopToBottom 
This functino loads one row of the puzzle from left to right into the text array. 
Then, calls the stringMatching function to find the input word in the text; prints the position of 
the word in the puzzle(row/column number). Repeats the above for each row of the puzzle.
***********************************************************************************************/ 
void lookTopToBottom(string pattern)
{
string text;                    //To hold the string to search
for (int i=0;i<11;i++)          //Iterate through the cols
{
        text = "";              //Reset the text to null
        int foundindex =-1;     //reset the found index to -1

        //Iterate through the rows 
        int k = 0;
        for (k=0;k<11;k++)
        {
                text = text + puzzle[k][i];
        }
        foundindex = string_match(pattern,text); //check each row for pattern
        if (foundindex != -1)                    //If pattern found then print
        {
                cout<<pattern<<" found at ["<<foundindex<<"]["<<i<<"]. T->B\n\n";
        }
}
}

/**********************************************************************************************
                void lookBottomToTop
This functino loads one row of the puzzle from left to right into the text array. 
Then, calls the stringMatching function to find the input word in the text; prints the position of 
the word in the puzzle(row/column number). Repeats the above for each row of the puzzle.
***********************************************************************************************/ 
void lookBottomToTop(string pattern)
{
        string text;                    //To hold the string to search

        for (int i=0;i<11;i++)          //Iterate through the rows 
        {
                text = "";              //Reset the text to null
                int foundindex =-1;     //reset the found index to -1

                int k = 0;              //Iterate through the cols
                for (k=10;k>=0;k--)
                {
                        text = text + puzzle[k][i];
                }
                foundindex = string_match(pattern,text); //check each row for pattern
                foundindex = flipindex(foundindex);     // If found then pring index
                if (foundindex != -1)
                {
                        cout<<pattern<<" found at ["<<foundindex<<"]["<<i<<"]. B->T\n\n";
                }
        }
}

/**********************************************************************************************
                int flipindexs
This function takes in an index and flips it. THERES GOTTA BE BETTER WAY 
***********************************************************************************************/ 
int flipindex(int flipme)
{
        if (flipme != -1)
        {
        flipme= 10 - flipme;
        }
return flipme;
}
