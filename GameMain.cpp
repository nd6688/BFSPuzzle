// File: GameMain.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: Main function.
#include<iostream>
#include<vector>
#include <ctime>
#include "GameNode.cpp"
#include "GameNode1.cpp"
#include "Game1.cpp"
#include "Game.cpp"
#include "GameEngine.cpp"
using namespace std;
/*
 * Description: Main function
 */
int main()
{
    cout<<"\tWelcome\nWhich game would you like to play today?\n1. Water Jug\n2. Jump Peg"<<endl;
    int userChoice;
    cin>>userChoice;
    if(userChoice==1){
    clock_t begin = clock();
    int noOfJugs;
    cout<<"Enter the number of jugs: ";
    cin>>noOfJugs;
    vector<int> maxCapacity;
    vector<int> initialJug;
    int jugCapacity;
    int destinationQuantity;
    int maxJugSize=0;
    for(int i=0; i<noOfJugs; i++)
    {
        cout<<"Enter the capacity of water in jug "<<i+1<<": ";
        cin>>jugCapacity;
        maxCapacity.push_back(jugCapacity);
        initialJug.push_back(0);
        if(jugCapacity>maxJugSize)
            maxJugSize=jugCapacity;
    }
    cout<<"Enter the quantity of water required in any one of the jugs: ";
    cin>>destinationQuantity;
    while(true)
    {
        if(destinationQuantity>maxJugSize)
        {
            cout<<"Please enter valid quantity which is lesser than any of the jug quantity"<<endl;
            cout<<"New value: ";
            cin>>destinationQuantity;
        }
        else
            break;
    }
    Game game(noOfJugs,destinationQuantity,maxCapacity);
    GameNode Board(initialJug);
    GameEngine<Game, GameNode> gameEngine(game, Board);
    cout<<"The configurations are: "<<endl;
    cout<<"----------------------------------"<<endl;
    int solutionFound = gameEngine.processGame(initialJug);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    if(solutionFound<0)
        cout<<"Solution not available"<<endl;
    cout<<"\t***\tTime taken to get all configs: "<<elapsed_secs<< " seconds.\t****"<<endl;
    return 0;
    }
    else if(userChoice==2){
    clock_t begin = clock();
    int xSize;
    int ySize;
    int xHole;
    int yHole;
    cout<<"Enter size of board in length and width: ";
    cin>>xSize>>ySize;
    vector<vector<char> > board(xSize);
    for(int i=0; i<xSize; i++)
    {
        for(int j=0; j<ySize; j++)
        {
            board[i].push_back('+');
        }
    }
    cout<<"Enter the co-ordinates where you would like to place the hole: ";
    cin>>xHole>>yHole;
    board[xHole][yHole]='.';
    GameNode1 Board(board);
    Game1 game(xSize, ySize);
    GameEngine<Game1, GameNode1> gameEngine(game, Board);
    cout<<"The configurations are: "<<endl;
    vector<vector<char> >::iterator iter1;
    vector<char>::iterator iter2;
    for(iter1=board.begin(); iter1<board.end(); iter1++)
    {
        for(iter2=iter1->begin(); iter2<iter1->end(); iter2++)
        {
            cout<<*iter2<<" ";
        }
        cout<<endl;
    }
    cout<<"----------------------------------"<<endl;
    int solutionFound = gameEngine.processGame(Board);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    if(solutionFound<0)
        cout<<"Solution not available"<<endl;
    cout<<"\t***\tTime taken to get all configs: "<<elapsed_secs<< " seconds.\t****"<<endl;
    return 0;
    }
}
