/* -----------------------------------------------------------------------------
 *
 * File Name:  main.cpp
 * Author: Apurva Rai
 * Assignment:   EECS-560 Lab 8
 * Date: April 6, 2020
 *
 ---------------------------------------------------------------------------- */

#include <string>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct game
{

string name="";
int downloads=-1;

};

vector<game*> gameArray;
int gameArraySize = 0;

void reverseFromNewAddition()
{

  bool parity = 0;
  int temp = gameArraySize-1;

  for(int i = gameArraySize-1;i >= 0; i = floor(((float)(i)-1.0)/2.0))
  {

    if(((int)(floor(log2(((float)i)+1.0))))%2 == 0) parity = 0;
    else parity = 1;

    int parent = floor(((float)(i)-1.0)/2.0);

    if(parent < 0) break;

      if(parity)
      {

          if(gameArray[parent]->downloads < gameArray[temp]->downloads)
          {

            swap(gameArray[temp], gameArray[parent]);
            temp = parent;

          }

      }
      else
      {

          if(gameArray[parent]->downloads > gameArray[temp]->downloads)
          {

            swap(gameArray[temp], gameArray[parent]);
            temp = parent;

          }

      }

    if(floor(((float)(i))/2.0) == 0) break;

  }

}

bool addGame(game* d)
{

  if(gameArraySize == 0)
  {

    gameArray.resize(gameArraySize+1);
    gameArray[0] = d;
    gameArraySize++;
    return true;

  }

  for(int i = 0; i < gameArraySize; i++)
  {

    if((d->name == gameArray[i]->name)) return false;

  }

  int newParentIndex = floor(((float)(gameArraySize)-1.0)/2.0);
  int newChildIndex = 2*newParentIndex + (((gameArraySize-1)%2)+1);

  gameArray.resize(gameArraySize+1);
  gameArray[newChildIndex] = d;
  gameArraySize++;

  reverseFromNewAddition();

  return true;

}

void maxMinHeapify(int passer)
{

  bool parity = 0;
  int temp = passer;

  for(int i = passer;i >= 0; i = floor(((float)(i)-1.0)/2.0))
  {

    if(((int)(floor(log2(((float)i)+1.0))))%2 == 0) parity = 0;
    else parity = 1;

    int parent = floor(((float)(i)-1.0)/2.0);

    if(parent < 0) break;

      if(parity)
      {

          if(gameArray[parent]->downloads < gameArray[temp]->downloads)
          {

            swap(gameArray[temp], gameArray[parent]);
            temp = parent;

          }

      }
      else
      {

          if(gameArray[parent]->downloads > gameArray[temp]->downloads)
          {

            swap(gameArray[temp], gameArray[parent]);
            temp = parent;

          }

      }

    if(floor(((float)(i))/2.0) == 0) break;

  }

}

void maxMinHeapSort()
{

  for(int i = gameArraySize-1; i >= 0; i--)
  {

    maxMinHeapify(i);

  }


}

void deleteMaxGame()
{

  if(gameArraySize == 0) return;

  if(gameArraySize == 1)
  {

    delete gameArray[0];
    gameArray.resize(0);
    gameArraySize--;
    return;

  }

  if(gameArraySize == 2)
  {

    delete gameArray[0];
    gameArray[0] = gameArray[1];
    gameArray.resize(1);
    gameArraySize--;
    return;

  }

  if(gameArraySize == 3)
  {

    delete gameArray[0];
    gameArray[0] = (gameArray[1]->downloads > gameArray[2]->downloads) ? gameArray[1] : gameArray[2];
    if(gameArray[2]->downloads > gameArray[1]->downloads) gameArray[1] = gameArray[2];
    gameArray.resize(2);
    gameArraySize--;
    return;

  }

  delete gameArray[0];
  int tempI = 0, tempMax = gameArray[3]->downloads;

  for(int i = 3; i < gameArraySize;i++)
  {

    if(tempMax > gameArray[i]->downloads)
    {

      tempMax = gameArray[i]->downloads;
      tempI = i;

    }

  }

    gameArray[0] = gameArray[tempI];
    gameArray[tempI] = gameArray[gameArraySize-1];
    gameArraySize--;

    maxMinHeapSort();

}

int main(int argc, char* argv[])
{

  	if(argc != 1)
  	{

  	std::cout<<"\nIncorrect number of parameters!\n\n";

  	}

  	else
  	{

      ifstream inputGames;

      inputGames.open("data.txt");

      if( !(inputGames.is_open()) )
      {

      cout<<"\nWrong file name.\n\n";
      throw(runtime_error("Invalid file name.") );

      }

        while(true)
        {

          string temp= "",name="",numString="";
      		int num=0,i=0;

          inputGames >> temp;

      		if(inputGames.eof()) break;

            while(temp[i]!= ',')
            {

              name+=temp[i];
              i++;

            }
            i++;
            while(temp[i]!= '\0')
            {

              numString+=temp[i];
              i++;

            }

          num = stoi(numString);

          game* newGame = new game;
          newGame->name = name;
          newGame->downloads = num;

          addGame(newGame);

        }

      }

      int option=0;

      while(option != 8)
      {

        //system("clear");
        cout << "\n\n.―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――\nPlease choose one of the following commands:\n\n1-  AddGame\n2-  DeleteMaxDownloadedGame\n3-  DeleteGame\n4-  PrintGamesAtMinimumLevels\n5-  PrintGamesAtMaximumLevels\n6-  TotalMinimumDownloadedGames\n7-  TotalMaximumDownloadedGames\n8-  Exit\n\n>Enter your choice:\n>";

        cin >> option;

        while(option > 8 || option < 1)
        {

          cout << "\nPlease select a valid option:\n";
          cin >> option;

        }

        if(option == 1)
        {

          game* newGame = new game;

          cout << ">Enter the name of the game you want to insert into the play store:\n>";
          cin >> newGame->name;
          cout << ">Enter the number of downloads for the game in thousands:\n>";
          cin >> newGame->downloads;
          if(addGame(newGame)) cout << ">Output: A new game was successfully added to the playstore.\n";
          else cout << ">Output: The game was not added to the playstore.\n";

   	    }
        else if(option == 2)
        {

          if(gameArraySize == 0)continue;
          else cout << ">Output: " << gameArray[0]->name << " game with " << gameArray[0]->downloads << "K downloads has been deleted successfully.\n";
          deleteMaxGame();

        }
        else if(option == 3)
        {

          if(gameArraySize == 0)continue;

          string tempName="";
          int tempDown=0;

          cout << ">Enter the name of the game you want to delet:\n>";
          cin >> tempName;
          cout << ">Enter the number of downloads of the game you want to delete:\n>";
          cin >> tempDown;

          if(tempName == gameArray[gameArraySize-1]->name && tempDown == gameArray[gameArraySize-1]->downloads)
          {

            gameArraySize--;
            delete gameArray[gameArraySize];
            gameArray.resize(gameArraySize);
            cout << ">Output: " << tempName << " game with " << tempDown << "K downloads has been deleted successfully.\n";
            continue;

          }

          int i = -1;
          for(i = 0; i < gameArraySize; i++)
          {

              if(tempName == gameArray[i]->name && tempDown == gameArray[i]->downloads) break;

          }

          if(i != gameArraySize)
          {

            delete gameArray[i];
            gameArray[i] = gameArray[gameArraySize-1];
            gameArraySize--;
            gameArray.resize(gameArraySize);
            maxMinHeapSort();
            cout << ">Output: " << tempName << " game with " << tempDown << "K downloads has been deleted successfully.\n";
            continue;

          }

          cout << ">Output: " << tempName << " game with " << tempDown << "K downloads was not deleted.\n";

        }
        else if(option == 4)
        {

          cout << ">Output";

          for(int i =0;i < gameArraySize;i++)
          {

            if(((int)(floor(log2(((float)i)+1.0))))%2 == 1) cout << ", " << gameArray[i]->name;

          }

          cout << "\n";

        }
        else if(option == 5)
        {

          cout << ">Output";

          for(int i =0;i < gameArraySize;i++)
          {

            if(((int)(floor(log2(((float)i)+1.0))))%2 == 0) cout << ", " << gameArray[i]->name;

          }

          cout << "\n";

        }
        else if(option == 6)
        {

          int total = 0;

          for(int i =0;i < gameArraySize;i++)
          {

            if(((int)(floor(log2(((float)i)+1.0))))%2 == 1) total+=gameArray[i]->downloads;

          }

          cout << ">Output: " << total << "\n";

        }
        else if(option == 7)
        {

          int total = 0;

          for(int i =0;i < gameArraySize;i++)
          {

            if(((int)(floor(log2(((float)i)+1.0))))%2 == 0) total+=gameArray[i]->downloads;

          }

          cout << ">Output: " << total << "\n";

        }

      }

    for(int i = 0; i < gameArraySize; i++) delete gameArray[i];

    cout << ">Output: Bye!!!\n";

    return(0);
}
