// File: GameEngine.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: BFS for solving puzzles.
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
template <typename E, typename F>
class GameEngine
{
private:
    E game;
    queue<F> vectorQueue;
    F* currentBoard;
    vector<F*> configurationList;
public:
    /* Name: GameEngine()
     *
     * Description:	Default constructor
     */
    GameEngine()
    {
    }
    /* Name: GameEngine()
     *
     * Description:	Parameterized constructor
     */
    GameEngine(E game, F &currentBoard)
    {
        this->game=game;
        this->currentBoard=&currentBoard;
    }
    /* Name: processGame()
     *
     * Description:	BFS algorithm for solving puzzles
     *
     * Argument: board   instance of type F
     *
     * Return:    int    if solution is found return 0, else -1
     *
     */
    int processGame(F board)
    {
        vectorQueue.push(board);
        currentBoard=new F(vectorQueue.front());
        vectorQueue.pop();
        while(true)
        {
            configurationList.erase(configurationList.begin(), configurationList.end());
            configurationList=game.getNextConfiguration(&(*currentBoard));
            int size=configurationList.size();
            for(int i=0; i<size; i++)
            {
                vectorQueue.push(*configurationList[i]);
                if(game.checkWin(configurationList[i]))
                {
                    game.print(configurationList[i]);
                    return 0;
                }
            }
            if(vectorQueue.empty())
            {
                break;
            }
            currentBoard=new F(vectorQueue.front());
            vectorQueue.pop();
        }
        game.print(currentBoard);
        return -1;
    }

};
