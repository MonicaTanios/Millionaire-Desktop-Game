#pragma once
#include <string>

using namespace std;
class Question
{
	string question;         // Questions String
	string answersArray[4];  // Array That Carry The Value Of Each Answer Of The Four Answers Of The Question
	int rightAnswerIndex;    // Carry The Index Of The Right Answer

public:
	Question();
	Question(string, string, string, string, string);
	
	bool checkAnswer(int);   // Check Wthere The Answer He Has Chosen Is Right Or No
	void displayQuestion();  // Display The Question
	void removeTwoAnswers(); // Facility The Revome Two Answers 
	
	~Question();
};

