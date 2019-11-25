#include "Question.h"
#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

Question::Question()
{

}

Question::Question(string _question, string _answerOne, string _answerTwo, string _answerThree, string _answerFour)
{
	question = _question;
	answersArray[0] = _answerOne;
	answersArray[1] = _answerTwo;
	answersArray[2] = _answerThree;
	answersArray[3] = _answerFour;
	for (int i = 0; i < 4; i++)
	{
		string tempAnswer = answersArray[i];
		if (tempAnswer[0] == '#')
		{
			rightAnswerIndex = i;
			tempAnswer.replace(0, 1, "");
			answersArray[i] = tempAnswer;
		}
	}
}

bool Question::checkAnswer(int choice)
{
	return (choice == rightAnswerIndex + 1);
}

void Question::displayQuestion() //handle right answer case
{
	cout << question << endl;
	cout << "1) " << setw(32) << left << answersArray[0] << "2) " << answersArray[1] << endl;
	cout << "3) " << setw(32) << left << answersArray[2] << "4) " << answersArray[3] << endl;
}

void Question::removeTwoAnswers()
{
	int removedAnswers = 0;
	for (int i = 0; i < 4; i++)
	{
		int removedIndex = rand()%3;
		if (removedIndex == rightAnswerIndex)
			continue;
		else
		{
			answersArray[removedIndex] = "";
			removedAnswers++;
		}
		if (removedAnswers == 2)
			break;
	}
	displayQuestion();
}

Question::~Question()
{
}
