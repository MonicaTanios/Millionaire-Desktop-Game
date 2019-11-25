/**************************************** Millionaire Game PROJECT ****************************************/

/*
Please Follow The Following Notes :
1] Set cmd Layout Width To 100 (Right Click On The Title Bar Of The cmd
   Then Choose Properties > Layout > Screen Buffer Size > Width > 100).
*/

/*********** Included Libraries & Classes ************/
#include <algorithm>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <windows.h>
#include <mmsystem.h>

#include "Queue.cpp"
#include "Question.h"

#pragma comment(lib,"Winmm.lib")

using namespace std;

fstream CertifcateFile;
fstream ScoreboardFile;
fstream LevelFile;

/*************** Files Paths Declaration *****************/
char LevelOneFilePath  [] = "LEVEL-1.txt";
char LevelTwoFilePath  [] = "LEVEL-2.txt";
char LevelThreeFilePath[] = "LEVEL-3.txt";
char CertifcateFilePath[] = "Certifcate.doc";
char ScoreboardFilePath[] = "Scoreboard.csv";

/*************** Functions Prototype *****************/
void SplashScreen();                                // Disply The Logo & The Name Of Our Game
void GameCore();                                    // IS The Sequence , Logic And How The Game Is Going On The Right Way And Target 
int  CalculateScore(int, int&);                     // Calculates How Much The person Will Earn In The Game
void FillFromFile(Queue<Question>&, char path[]);   // Take The Questions Of Each Level And Fill The Object Of The Queue With
void CertifcateDisplay(string,int, bool);           // Display A Congratulatios Or Game Over Certifcate For The Palyer
void UploadScoreAndPlayerName(string, int);         // Upload Score And Name To File
void ListLastTenPlayers();                          // Display Last Ten Players Played
void ListTopScoredTenPlayers();                     // Display Top Ten Players 


/*************** Main Function *****************/
int main()
{
	//PlaySound("Theme_Main.wav", NULL, SND_ASYNC);
	//SplashScreen();

	while (true) {
	
		system("cls");

		cout << endl
			<< "  [1] Start\n"
			<< "  [2] Scoreboard\n"
			<< "  [3] Help\n"
			<< "  [0] Exit\n\n"
			<< "  Enter your choice: ";

		char choice = _getche();

		switch (choice) {

		case '1':
			system("cls");
			PlaySound("Theme_Main.wav", NULL, SND_ASYNC);
			GameCore();
			break;

		case '2':
			system("cls");
			cout << endl;
			ListTopScoredTenPlayers();
			cout << endl;
			ListLastTenPlayers();
			cout << endl << endl;
			system("pause");
			break;

		case '3':
			system("cls");
			cout << "Help Here\n";
			cout << endl << endl;
			system("pause");
			break;

		case '0':
			system("cls");
			PlaySound("Theme_Closing.wav", NULL, SND_ASYNC);
			SplashScreen();
			return 0;

		default:
			cout << "\n  Enter valid choice!" << endl;
			Sleep(500);
			break;
		}

	}

}

/*************** Functions Definition *****************/
void SplashScreen()
{
	
	vector<string> logo = { " __  __ _ _ _ _                   _                 ",
						    "|  \\/  (_) | (_)                 (_)               ",
						    "| \\  / |_| | |_  ___  _ __   __ _ _ _ __ ___       ",
						    "| |\\/| | | | | |/ _ \\| '_ \\ / _` | | '__/ _ \\   ",
						    "| |  | | | | | | (_) | | | | (_| | | | |  __/       ",
						    "|_|  |_|_|_|_|_|\\___/|_|_|_|\\__,_|_|_|  \\___|    ",
						    "                     / ____|                        ",
						    "                    | |  __  __ _ _ __ ___   ___    ",
						    "                    | | |_ |/ _` | '_ ` _ \\ / _ \\ ",
						    "                    | |__| | (_| | | | | | |  __/   ",
						    "                     \\_____|\\__,_|_| |_| |_|\\___|",
						    "                                                    ",
						    "                      B Y   M 3 L E S H Y - 2019    " };

	// Printing Splash Screen

	cout << endl << endl << endl;

	for (vector<string>::iterator it = logo.begin(); it != logo.end(); it++)
	{
		cout << string(25, ' ') << *it << endl;
		Sleep(400);
	}

	cout << endl << endl << endl;

	Sleep(5000);
	system("cls");

}

void GameCore()
{
	/*************** Needed Variabels Declaration *****************/
	Queue <Question> Problem;
	string PlayerName;
	char Respond;
	int choice;
	int Help = 0;
	int NewHelp = 0;
	int playerScore;
	int totalQuestionsLeft = 15;
	bool fileIsLoaded = false;
	bool CheckAnswerReturn = true;

	
	do
	{
		playerScore = 0;

		cout << "Welcome To The Millionaire Game We Are extremly Happy And Humble That Your Are Playing Our Game, \n"
			 << "Hope You Enjoy The game And Win The Million Doller :):) .\n"
			 << "First Enter Your Name Then In Few Seconds The Game Starts , Get Redy... \n ";

		Sleep(10000);
		system("cls");

		cout << "Enter your Name : ";
		cin  >> PlayerName;
		system("cls");

		for (int Index = 0; Index < totalQuestionsLeft; Index++)
		{
			/*************** Filling From File Connditions *****************/
			if (Index == 0 || Index == 4 || Index == 9)
				fileIsLoaded = false;

			if (Index == 15 - totalQuestionsLeft && !fileIsLoaded)
			{
				Problem.Clear();
				FillFromFile(Problem, LevelOneFilePath);
				Problem.Shuffle();
				fileIsLoaded = true;

			}
			else if (Index == 5 && !fileIsLoaded)
			{
				Problem.Clear();
				FillFromFile(Problem, LevelTwoFilePath);
				Problem.Shuffle();
				fileIsLoaded = true;
			}
			else if (Index == 10 && !fileIsLoaded)
			{
				Problem.Clear();
				FillFromFile(Problem, LevelThreeFilePath);
				Problem.Shuffle();
				fileIsLoaded = true;
			}

			/*************** Frist level Conndition *****************/
			if (Index < 5)
			{
				Problem.FrontElement().displayQuestion();

				if (Help == 0)
				{
					cout << endl;
					cout << "To Remove Two Answers press 0 :)" << endl;
				}

				cin >> choice;
				while (choice < 0 || choice > 4)
				{
					cout << "Wrong Answer Enter In Range" << endl;
					cin >> choice;
				}
					
				if (choice == 0 && Help == 0)
				{
					system("cls");
					Problem.FrontElement().removeTwoAnswers();
					Help++;

					cin >> choice;
					while (choice < 0 || choice > 4)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				while (choice == 0 && Help == 1)
				{
					cout << "You Have Finshed Your Trails From This Type Of Trails  !!" << endl;
					cout << "Enter Your Choice Once More :):)" << endl;
					Sleep(1500);

					cin >> choice;
					while (choice < 0 || choice > 4)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				if (choice != 0)
				{
					if (!Problem.FrontElement().checkAnswer(choice))
					{
						cout << "!! Wrong Answer !!" << endl;
						cout << ":(:(:(:(:(:(:(:(:(" << endl;
						Sleep(1500);
						CheckAnswerReturn = false;
						break;
					}
					else
					{
						cout << ":):) Right Answer :):)" << endl;
						playerScore = CalculateScore(Index, playerScore);
						Problem.Dequeue();
						Sleep(1500);
						system("cls");
						continue;
					}
				}
			}

			/*************** Second level Conndition *****************/
			if (Index < 10)
			{
				if (Index == 5) 
				{
					cout << "Congratulatios," << endl
						 << "You Have Passed The First Part Of the Game And Here We Come to The Second & Middle Part Of The Game." << endl;
					Sleep(7000);
					system("cls");
				}

				Problem.FrontElement().displayQuestion();

				if (Help == 0)
				{
					cout << endl;
					cout << "To Remove Two Answers press 0 :)" << endl;
				}

				cin >> choice;
				while (choice < 0 || choice > 4)
				{
					cout << "Wrong Answer Enter In Range" << endl;
					cin >> choice;
				}

				if (choice == 0 && Help == 0)
				{
					system("cls");
					Problem.FrontElement().removeTwoAnswers();
					Help++;

					cin >> choice;
					while (choice < 0 || choice > 4)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				while (choice == 0 && Help == 1)
				{
					cout << "You Have Finshed Your Trails From This Type Of Trails !!" << endl;
					cout << "Enter Your Choice Once More :):)" << endl;
					Sleep(1500);
					
					cin >> choice;
					while (choice < 0 || choice > 4)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				if (choice != 0)
				{
					if (!Problem.FrontElement().checkAnswer(choice))
					{
						cout << "!! Wrong Answer !!" << endl;
						cout << ":(:(:(:(:(:(:(:(:(" << endl;
						Sleep(1500);
						CheckAnswerReturn = false;
						break;
					}
					else
					{
						cout << ":):) Right Answer :):)" << endl;
						playerScore = CalculateScore(Index, playerScore);
						Problem.Dequeue();
						Sleep(1500);
						system("cls");
						continue;
					}
				}
			}

			/*************** Third level Conndition *****************/
			if (Index < 15)
			{
				if (Index == 10)
				{
					cout << "Congratulatios," << endl
						 << "You Have Passed The Second Part Of the Game And Here We Come to The Third & Last Part Of The Game." << endl;
					Sleep(7000);
					system("cls");
				}

				Problem.FrontElement().displayQuestion();

				if (NewHelp == 0)
				{
					cout << endl;
					cout << "To Skip Question press 5 :)" << endl;
				}

				if (Help == 0)
				{
					cout << "To Remove Two Answers press 0 :)" << endl;
				}

				cin >> choice;
				while (choice < 0 || choice > 5)
				{
					cout << "Wrong Answer Enter In Range" << endl;
					cin >> choice;
				}

			RemoveTwoChoices:
				if (choice == 0 && Help == 0)
				{
					system("cls");
					Problem.FrontElement().removeTwoAnswers();
					Help++;
					
					cin >> choice;
					while (choice < 0 || choice > 5)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				while (choice == 0 && Help == 1)
				{
					cout << "You Have Finshed Your Trails From This Type Of Trails !!" << endl;
					cout << "Enter Your Choice Once More :):)" << endl;
					Sleep(1500);

					cin >> choice;
					while (choice < 0 || choice > 5)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				if (choice == 5 && NewHelp == 0)
				{
					system("cls");
					Problem.Dequeue();
					NewHelp++;
					Index -= 1;
					Problem.FrontElement().displayQuestion();
					cout << endl << "To Remove Two Answers press 0 :)" << endl;
					
					cin >> choice;
					while (choice < 0 || choice > 5)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}

					if (choice == 0)
						goto RemoveTwoChoices;
				}

				while (choice == 5 && NewHelp == 1)
				{
					cout << "You Have Finshed Your Trails From This Type Of Trails !!" << endl;
					cout << "Enter Your Choice Once More :):)" << endl;
					Sleep(1500);
					
					cin >> choice;
					while (choice < 0 || choice > 5)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}

					if (choice == 0)
						goto RemoveTwoChoices;
				}

				while ((choice == 5 || choice == 0) && NewHelp == 1 && Help == 1)
				{
					cout << "You Have Finshed Your Trails From The Two Types !!" << endl;
					cout << "Enter Your Choice Once More :):)" << endl;
					Sleep(1500);
					
					cin >> choice;
					while (choice < 0 || choice > 5)
					{
						cout << "Wrong Answer Enter In Range" << endl;
						cin >> choice;
					}
				}

				if (choice != 0 && choice != 5)
				{
					if (!Problem.FrontElement().checkAnswer(choice))
					{
						cout << "!! Wrong Answer !!" << endl;
						cout << ":(:(:(:(:(:(:(:(:(" << endl;
						CheckAnswerReturn = false;
						Sleep(1500);
						break;
					}
					else
					{
						cout << ":):) Right Answer :):)" << endl;
						playerScore = CalculateScore(Index, playerScore);
						Problem.Dequeue();
						Sleep(1500);
						system("cls");
						continue;
					}
				}
			}
		}
		/*************** Certificate Display Cheek *****************/
		if (CheckAnswerReturn == true)
			CertifcateDisplay(PlayerName, playerScore, CheckAnswerReturn);
		else
			CertifcateDisplay(PlayerName, playerScore, CheckAnswerReturn);
		
		/*************** Player Score And Name Upload *****************/
		UploadScoreAndPlayerName(PlayerName, playerScore);

		/*************** Another Game Check *****************/
		system("cls");
		cout << "Do You Want To Play Another Game ?? \n"
			 << "To Continue Press Y OR y ....";
		
		cin  >> Respond;
		system("cls");

	} while (Respond =='Y'|| Respond == 'y');
	
}

int CalculateScore(int NumberOfQuestion, int &TotalScore)
{
	switch (NumberOfQuestion)
	{
	case 0:
	case 1:
	case 2:
		TotalScore += 100;
		break;
	case 3:
		TotalScore += 200;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:TotalScore *= 2;
		break;
	case 11:TotalScore = (TotalScore * 2) - 3000;
		break;
	case 12:
	case 13:
	case 14:TotalScore *= 2;
		break;
	}

	cout << "Your Total Score is = " << TotalScore << "$ " << endl;
	
	return TotalScore;
}

void FillFromFile(Queue<Question> &Container, char path[]) 
{

	LevelFile.open(path, ios::in);

	while (!LevelFile.eof()) {

		string question;
		getline(LevelFile, question, '\n');
		string answerOne;
		getline(LevelFile, answerOne, '\n');
		string answerTwo;
		getline(LevelFile, answerTwo, '\n');
		string answerThree;
		getline(LevelFile, answerThree, '\n');
		string answerFour;
		getline(LevelFile, answerFour, '\n');

		// Ignore the empty line
		LevelFile.ignore();
		
		Container.Enqueue(Question(question, answerOne, answerTwo, answerThree, answerFour));
	}

	LevelFile.close();

}

void CertifcateDisplay(string Name, int Score, bool state)
{
	if (state == true)
	{
		cout << "   _____                            _         _       _   _                         " << endl
			 << "  / ____|                          | |       | |     | | (_)                        " << endl
			 << " | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __              " << endl
			 << " | |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\         " << endl
			 << " | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | |            " << endl
			 << "  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|   " << endl
			 << "                     __/ |                                                          " << endl
			 << "                    |___/                                                           " << endl
		     << endl << "Mr/Mrs: " << Name << " For Getting This Amazing Score " << Score << " $ "     << endl;
				

                       /************** Certifcate Export To Print ****************/
		CertifcateFile.open(CertifcateFilePath, ios::out);
		CertifcateFile << "   _____                            _         _       _   _                         " << endl
			           << "  / ____|                          | |       | |     | | (_)                        " << endl
			           << " | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __              " << endl
			           << " | |    / _ \\| '_ \\ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \\| '_ \\         " << endl
			           << " | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | |            " << endl
			           << "  \\_____\\___/|_| |_|\\__, |_|  \\__,_|\\__|\\__,_|_|\\__,_|\\__|_|\\___/|_| |_|   " << endl
			           << "                     __/ |                                                          " << endl
			           << "                    |___/                                                           " << endl
			           << "Mr/Mrs: " << Name << " For Getting This Amazing Score " << Score << " $ "             << endl
			           << "-------------------------------------------------------------------------"            << endl;

		CertifcateFile.close();

		cout << endl << "To print The Certifcate go to \"Certifcate.doc\" file." << endl;
	}
	else
	{
		system("cls");
		cout
			<< "   _____                         ____                       " << endl
			<< "  / ____|                       / __ \\                     " << endl
			<< " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __       " << endl
			<< " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__| " << endl
			<< " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |        " << endl
			<< "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   " << endl
	        ;
		cout << endl << "Mr/Mrs: " << Name << " We All Feel Deeply Sorry For This Socre " << Score << " $ " << endl
	   		 << "And We Hope That You Achive Your Gole The Next Time."                                      << endl;
	}

	Sleep(1500);
	cout << endl << endl;
	system("pause");
	system("cls");
}

void UploadScoreAndPlayerName(string Name, int Score)
{
	ScoreboardFile.open(ScoreboardFilePath, ios::out | ios::app);

	ScoreboardFile << Name  << ",";
	ScoreboardFile << Score << '\n';

	ScoreboardFile.close();
}

void ListLastTenPlayers()
{
	vector<pair<string, string>> players;

	ScoreboardFile.open(ScoreboardFilePath);

	while (!ScoreboardFile.eof(), ios::in)
	{
		string Name;
		getline(ScoreboardFile, Name, ',');
		if (Name == "") break;

		string Score;
		getline(ScoreboardFile, Score, '\n');

		players.push_back(make_pair(Name, Score));
	}

	ScoreboardFile.close();

	reverse(players.begin(), players.end());


	cout << "                [Recent Players]                 \n"
		 << "+-----------------------------------------------+\n"
		 << setw(30) << left << "| Name"
		 << setw(20) << right << "Score |\n"
		 << "+-----------------------------------------------+\n";


	for (int i = 0; i < 10; i++)
	{
		cout << "| "
			 << setw(25) << left << players[i].first
			 << setw(20) << right << players[i].second
			 << " |\n";
	}

	cout << "+-----------------------------------------------+\n";
}

void ListTopScoredTenPlayers()
{
	int Index = 0;

	ScoreboardFile.open(ScoreboardFilePath);
	while (!ScoreboardFile.eof(),ios::in) 
	{
		string Name;
		getline(ScoreboardFile, Name, ',');
		if (Name == "") break;

		string Score;
		getline(ScoreboardFile, Score, '\n');

		Index++;
	}
	ScoreboardFile.close();

	string *PlayerName  = new string[Index];
	int *PlayerScore    = new int[Index];

	ScoreboardFile.open(ScoreboardFilePath);
	for (int I = 0; I < Index; I++)
	{
		if (!ScoreboardFile.eof()) 
		{

			getline(ScoreboardFile, PlayerName[I], ',');
			if (PlayerName[I] == "") break;
			
			string Score;
			getline(ScoreboardFile, Score, '\n');
			PlayerScore[I] = stoi(Score);
		}
	}
	ScoreboardFile.close();

	for (int IndexOne = 0; IndexOne <Index; IndexOne++)
	{
		for (int IndexTwo = IndexOne+1; IndexTwo < Index; IndexTwo++)
		{
			if (PlayerScore[IndexTwo] > PlayerScore[IndexOne])
			{
				int PlayerScoreTemprory   = PlayerScore[IndexTwo];
				PlayerScore[IndexTwo]     = PlayerScore[IndexOne];
				PlayerScore[IndexOne]     = PlayerScoreTemprory;

				string PlayerNameTemprory = PlayerName[IndexTwo];
				PlayerName[IndexTwo]      = PlayerName[IndexOne];
				PlayerName[IndexOne]      = PlayerNameTemprory;
			}
		}

	}

	cout << "                  [Top Players]                  \n"
		 << "+-----------------------------------------------+\n"
		 << setw(30) << left  << "| Name"
		 << setw(20) << right << "Score |\n"
		 << "+-----------------------------------------------+\n";


	for (int J = 0; J < 10; J++)
	{
		cout << "| "  
			 << setw(25) << left  << PlayerName[J]
			 << setw(20) << right << PlayerScore[J] 
			 << " |\n";
	}

	cout << "+-----------------------------------------------+\n";

}