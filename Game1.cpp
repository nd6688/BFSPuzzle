// File: Game1.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: Problem class for Jump Peg game.
#include<iostream>
#include<vector>
#include <set>
#include<stack>
using namespace std;
class Game1
{
private:
    vector<GameNode1*> possibleMoves;
    vector<GameNode1*> allConfigs;
    stack<vector<vector<char> > > printStack;
    bool configGenerated;
    int xSize;
    int ySize;
    set<vector<vector<char> > > checkSet;
public:
    /* Name: Game1()
     *
     * Description:	Default constructor
     */
    Game1() {}
    /* Name: Game1()
     *
     * Description:	Parameterized constructor
     */
    Game1(int xSize, int ySize)
    {
        this->xSize=xSize;
        this->ySize=ySize;
        this->configGenerated=false;
    }
    /* Name: checkWin()
     *
     * Description:	Check if the game is won.
     *
     * Argument: boardObj   object of type GameNode1
     *
     * Return:    bool    true if the game is won, else false
     *
     */
    bool checkWin(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        vector<vector<char> >::iterator iter1;
        vector<char>::iterator iter2;
        int count=0;
        for(iter1=board.begin(); iter1<board.end(); iter1++)
        {
            for(iter2=iter1->begin(); iter2<iter1->end(); iter2++)
            {
                if(*iter2=='+')
                    count++;
            }
        }
        if(count<2)
            return true;
        else
            return false;
    }
    /* Name: getNextConfiguration()
     *
     * Description:	returns the list of all new possible configuration
     *              from given configuration.
     *
     * Argument: boardObj   object of type GameNode11
     *
     * Return:    vector<GameNode1*>    list of all configurations generated.
     *
     */
    vector<GameNode1*> getNextConfiguration(GameNode1* boardObj)
    {
        possibleMoves.erase(possibleMoves.begin(), possibleMoves.end());
        checkUp(boardObj);
        checkDown(boardObj);
        checkLeft(boardObj);
        checkRight(boardObj);
        return possibleMoves;
    }
    /* Name: checkUp()
     *
     * Description:	generates new configuration where two pegs are
     *              available above a hole
     *
     * Argument: boardObj   object of type GameNode1
     *
     */
    void checkUp(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        for(int i=2; i<xSize; i++)
        {
            for(int j=0; j<ySize; j++)
            {
                if(board[i][j]=='.'&&board[i-1][j]=='+'&&board[i-2][j]=='+')
                {
                    board[i][j]='+';
                    board[i-1][j]='.';
                    board[i-2][j]='.';
                    GameNode1 *newBoard= new GameNode1(board);
                    vector<GameNode1*>::iterator searchVector;
                    for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                    {
                        if((*searchVector)->board==boardObj->board)
                        {
                            newBoard->parent=*searchVector;
                        }
                    }
                    allConfigs.push_back(newBoard);
                    set<vector<vector<char> > >::iterator searchIter;
                    searchIter=checkSet.find(board);
                    if(searchIter==checkSet.end())
                    {
                        checkSet.insert(board);
                        possibleMoves.push_back(newBoard);
                        checkMultipleJump(newBoard, boardObj, i, j);
                    }
                    board=boardObj->board;
                }
            }
        }
    }
    /* Name: checkDown()
     *
     * Description:	generates new configuration where two pegs are
     *              available below a hole
     *
     * Argument: boardObj   object of type GameNode1
     *
     */
    void checkDown(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        for(int i=0; i<xSize-2; i++)
        {
            for(int j=0; j<ySize; j++)
            {
                if(board[i][j]=='.'&&board[i+1][j]=='+'&&board[i+2][j]=='+')
                {
                    board[i][j]='+';
                    board[i+1][j]='.';
                    board[i+2][j]='.';
                    GameNode1 *newBoard= new GameNode1(board);
                    vector<GameNode1*>::iterator searchVector;
                    for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                    {
                        if((*searchVector)->board==boardObj->board)
                        {
                            newBoard->parent=*searchVector;
                        }
                    }
                    allConfigs.push_back(newBoard);
                    set<vector<vector<char> > >::iterator searchIter;
                    searchIter=checkSet.find(board);
                    if(searchIter==checkSet.end())
                    {
                        checkSet.insert(board);
                        possibleMoves.push_back(newBoard);
                        checkMultipleJump(newBoard, boardObj, i, j);
                    }
                    board=boardObj->board;
                }
            }
        }
    }
    /* Name: checkLeft()
     *
     * Description:	generates new configuration where two pegs are
     *              available on left of a hole
     *
     * Argument: boardObj   object of type GameNode1
     *
     */
    void checkLeft(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        for(int i=0; i<xSize; i++)
        {
            for(int j=2; j<ySize; j++)
            {
                if(board[i][j]=='.'&&board[i][j-1]=='+'&&board[i][j-2]=='+')
                {
                    board[i][j]='+';
                    board[i][j-1]='.';
                    board[i][j-2]='.';
                    GameNode1 *newBoard= new GameNode1(board);
                    vector<GameNode1*>::iterator searchVector;
                    for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                    {
                        if((*searchVector)->board==boardObj->board)
                        {
                            newBoard->parent=*searchVector;
                        }
                    }
                    allConfigs.push_back(newBoard);
                    set<vector<vector<char> > >::iterator searchIter;
                    searchIter=checkSet.find(board);
                    if(searchIter==checkSet.end())
                    {
                        checkSet.insert(board);
                        possibleMoves.push_back(newBoard);
                        checkMultipleJump(newBoard, boardObj, i, j);
                    }
                    board=boardObj->board;
                }
            }
        }
    }
    /* Name: checkRight()
     *
     * Description:	generates new configuration where two pegs are
     *              available on right of a hole
     *
     * Argument: boardObj   object of type GameNode1
     *
     */
    void checkRight(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        for(int i=0; i<xSize; i++)
        {
            for(int j=0; j<ySize-2; j++)
            {
                if(board[i][j]=='.' && board[i][j+1]=='+' && board[i][j+2]=='+')
                {
                    board[i][j]='+';
                    board[i][j+1]='.';
                    board[i][j+2]='.';
                    GameNode1 *newBoard= new GameNode1(board);
                    vector<GameNode1*>::iterator searchVector;
                    for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                    {
                        if((*searchVector)->board==boardObj->board)
                        {
                            newBoard->parent=*searchVector;
                        }
                    }
                    allConfigs.push_back(newBoard);
                    set<vector<vector<char> > >::iterator searchIter;
                    searchIter=checkSet.find(board);
                    if(searchIter==checkSet.end())
                    {
                        checkSet.insert(board);
                        possibleMoves.push_back(newBoard);
                        checkMultipleJump(newBoard, boardObj, i, j);
                    }
                    board=boardObj->board;
                }
            }
        }
    }
    /* Name: checkMultipleJump()
     *
     * Description:	generates multiple jumps if possible
     *
     * Argument: boardObj             object of type GameNode1
     *           boardObjForParent    parent board
     *           i                    row of board
     *           j                    column of board
     *
     */
    void checkMultipleJump(GameNode1 *boardObj, GameNode1 *boardObjForParent, int i, int j)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        //Right
        if(i<xSize && j<ySize-2)
        {
            if(board[i][j]=='+' && board[i][j+1]=='+' && board[i][j+2]=='.')
            {
                board[i][j]='.';
                board[i][j+1]='.';
                board[i][j+2]='+';
                GameNode1 *newBoard= new GameNode1(board);
                vector<GameNode1*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObjForParent->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<vector<char> > >::iterator searchIter;
                searchIter=checkSet.find(board);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(board);
                    possibleMoves.push_back(newBoard);
                    checkMultipleJump(newBoard, boardObjForParent, i, j+2);
                }
                board=boardObj->board;
            }
        }
        //Left
        if(i<xSize && j>1 && j<ySize)
        {
            if(board[i][j]=='+'&&board[i][j-1]=='+'&&board[i][j-2]=='.')
            {
                board[i][j]='.';
                board[i][j-1]='.';
                board[i][j-2]='+';
                GameNode1 *newBoard= new GameNode1(board);
                vector<GameNode1*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObjForParent->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<vector<char> > >::iterator searchIter;
                searchIter=checkSet.find(board);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(board);
                    possibleMoves.push_back(newBoard);
                    checkMultipleJump(newBoard, boardObjForParent, i, j-2);
                }
                board=boardObj->board;
            }
        }
        //Down
        if(i<xSize-2 && j<ySize)
        {
            if(board[i][j]=='+'&&board[i+1][j]=='+'&&board[i+2][j]=='.')
            {
                board[i][j]='.';
                board[i+1][j]='.';
                board[i+2][j]='+';
                GameNode1 *newBoard= new GameNode1(board);
                vector<GameNode1*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObjForParent->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<vector<char> > >::iterator searchIter;
                searchIter=checkSet.find(board);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(board);
                    possibleMoves.push_back(newBoard);
                    checkMultipleJump(newBoard, boardObjForParent, i+2, j);
                }
                board=boardObj->board;
            }
        }
        //Up
        if(i>1 && i<xSize && j<ySize)
        {
            if(board[i][j]=='+'&&board[i-1][j]=='+'&&board[i-2][j]=='.')
            {
                board[i][j]='.';
                board[i-1][j]='.';
                board[i-2][j]='+';
                GameNode1 *newBoard= new GameNode1(board);
                vector<GameNode1*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObjForParent->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<vector<char> > >::iterator searchIter;
                searchIter=checkSet.find(board);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(board);
                    possibleMoves.push_back(newBoard);
                    checkMultipleJump(newBoard, boardObjForParent, i-2, j);
                }
                board=boardObj->board;
            }
        }
    }
    /* Name: print()
     *
     * Description:	prints the solution
     *
     * Argument: boardObj             object of type GameNode1
     *
     */
    void print(GameNode1 *boardObj)
    {
        vector<vector<char> > board;
        board=boardObj->board;
        vector<GameNode1*>::iterator searchVector;
        GameNode1 *printNode;
        for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
        {
            if((*searchVector)->board==boardObj->board)
            {
                printNode=*searchVector;
            }
        }
        vector<vector<char> >::iterator iter1;
        vector<char>::iterator iter2;
        do
        {
            board=printNode->board;
            printStack.push(board);
            printNode=printNode->parent;
        }
        while(printNode!=NULL);
        while(!printStack.empty())
        {
            board=printStack.top();
            printStack.pop();
            for(iter1=board.begin(); iter1<board.end(); iter1++)
            {
                for(iter2=iter1->begin(); iter2<iter1->end(); iter2++)
                {
                    cout<<*iter2<<" ";
                }
                cout<<endl;
            }
            cout<<"----------------------------------"<<endl;
        }
    }
};
