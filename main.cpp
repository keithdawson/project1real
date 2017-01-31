//============================================================================
// Name        : Project1.cpp
// Author      : Blake Mizzell
// Description : Word Counting and Matching using two files
//============================================================================

#include <iostream>
#include <fstream> //necessary for reading in txt file



using namespace std;

int convertCount(string inputFile)
{
	ifstream inFile;
	ofstream outFile;
	inFile.open(inputFile.c_str());
	outFile.open("clean.txt");
	string word; // variable used for test case
	int wordcount = 0;
	int outpos = 0;
	while (!inFile.eof()) //this loop will cycle through each word in input file
		{
		inFile >> word; //read word goes into temp variable
		for (unsigned int i = 0; i < word.size(); i++)
		{
			if (ispunct(word[i]))
			{
				word[i] = ' '; //delete punctuation
			}
			word[i] = tolower(word[i]);
		}

		//Section 2 - Short if statement to prevent
		//whitespace at beginning of cleaned
		//text file.
		if (outpos > 0) //if NOT first word in file
		{
			outFile << ' ' ;
			outFile << word; //insert whitespace
		}
		else
		{
			outFile << word; //no whitespace since beginning of file
		}
		outpos++;
		wordcount++;
		}
		inFile.close();
		outFile.close(); //always close file!
		cout<<"The number of words found in the file was "<<wordcount<<endl;
		return 0;
}

void uniqueCounter()
{
	ifstream cleanFile;
	cleanFile.open("clean.txt"); //opened cleaned file - avoiding punctuation issues.
	string word;
	string wordbank[10000]; //wordbank size for max string amount
	int uniquecount = 0;
	int wbposition = 0;
	int uniquecheck = 0;
	for (unsigned int I = 0; !cleanFile.eof();I ++ )
	{
		cleanFile>>word;
		wordbank[wbposition] = word;
		for (int j = 0; j < 10000; j++)
		{
			if (word == wordbank[j]) //iterate character by character in words
			{
				uniquecheck++;
			}
		}
		wbposition++;
		if (uniquecheck == 1) //if word only matches itself in the wordbank, this will equal 1. (UNIQUE!)
		{
			uniquecount++;
		}
		uniquecheck = 0;
	}
	cout<<"The number of distinct words found in the file was "<<uniquecount<<endl;
}

int inputMatcher(string testWord)
{
	//value from queryfile
	for (unsigned int i = 0; i < testWord.size(); i++)
	{
		testWord[i] = tolower(testWord[i]); //convert to lower-case for easiness
	}
	if (testWord == "^C"){ //Non-Necessary test case
		return 0;
	}
	ifstream cleanFile;
	cleanFile.open("clean.txt");
	string word;
	unsigned int fillup = 0; //re-initialize at ea. loocp
	int matching = 0; //re-initialize at ea. loop
	string matchbank[10000]; //10000 max string count
	int matchbankcount[10000] = {0};
	int mb = 0; // current index of matchbank


	for (unsigned int I = 0; !cleanFile.eof();I ++ )
	{
		cleanFile>>word; //temp variable "word"
		string tempword;
		tempword = word;
		if (word.size() == testWord.size()) //word cannot be a match if longer than testWord
		{
			int diff = 0;
			diff = (testWord.size() - word.size());
			for(int m = 0; m < diff; m++)
			{
				word += ' '; //append whitespace to make sizes match in the event that sizes differ
			}
			for (unsigned int k = 0; k < testWord.size(); k++)
			{
				if((word[k] == testWord[k])||(testWord[k] == '?')) //provide for '?' case
				{
					fillup++;
				}
				else {
					fillup = 0;
				}
			}
		}
		if (fillup == testWord.size()) //if fillup is reached, we have a match! (whitespace allows for a fillup)
		{
			for (int a = 0;a < (mb + 1); a++)
			{
				if (matchbank[a] == tempword)
				{
					matchbankcount[a]+=1; //if word already in bank, increment its associated count
					matching++;
				}
			}
			if (matching == 0)
			{
				matchbank[mb] = tempword;
				matchbankcount[mb] += 1;
				mb++;
			}
		}
		fillup = 0;
		matching = 0;

	}
	cout<< testWord<< " : ";
	for (int l = 0; l < mb; l++){
		if (l > 0) {
			for (unsigned int m = 0; m != testWord.length(); m++){
				cout << " ";
			}
			cout << "   ";
		}
		if (matchbankcount[l] > 1){
			cout<<"matches "<< matchbank[l]<< " " <<matchbankcount[l]<<" times"<< endl;
		}
		else if((matchbankcount[l]) == 1) {
			cout<<"matches "<< matchbank[l]<< " " <<matchbankcount[l]<<" time"<< endl;
		}
	}
	if (mb == 0) {
		cout<<"no match"<< endl;
	}
	cleanFile.close();
	return 0;
}

int queryRun(string queryFile){

	ifstream inFile;
	inFile.open(queryFile.c_str());
	string word; // variable used for checking
	cout << endl;
	for (int I = 0; !inFile.eof() ; I++) //this loop will cycle through each word in input file
	{
		inFile >> word; //read word goes into temp variable
		inputMatcher(word);
	}
	inFile.close();//always close file!
	return 0;
}




int main(int argc, char* argv[]) {
	convertCount(argv[1]);
	uniqueCounter();
	queryRun(argv[2]);
	return 0;
}


