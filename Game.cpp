// File: Game.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: Problem class for Water Jug.
#include<iostream>
#include<vector>
#include<set>
#include<stack>
using namespace std;
class Game
{
private:
    vector<GameNode*> possibleMoves;
    vector<GameNode*> allConfigs;
    int noOfJugs;
    int targetAmount;
    vector<int> maxCapacity;
    set<vector<int> > checkSet;
    stack<vector<int> > printStack;
public:
    /* Name: Game()
     *
     * Description:	Default constructor
     */
    Game()
    {
    }
    /* Name: Game()
     *
     * Description:	Parameterized constructor
     */
    Game(int noOfJugs, int targetAmount, vector<int> maxCapacity)
    {
        this->noOfJugs=noOfJugs;
        this->targetAmount=targetAmount;
        this->maxCapacity=maxCapacity;
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
    bool checkWin(GameNode *boardObj)
    {
        vector<int> board;
        board=boardObj->board;
        for(int i=0; i<noOfJugs; i++)
        {
            if(board[i]==targetAmount)
            {
                return true;
            }
        }
        return false;
    }
    /* Name: getNextConfiguration()
     *
     * Description:	returns the list of all new possible configuration
     *              from given configuration.
     *
     * Argument: boardObj   object of type GameNode11
     *
     * Return:    vector<GameNode*>    list of all configurations generated.
     *
     */
    vector<GameNode*> getNextConfiguration(GameNode* boardObj)
    {
        possibleMoves.erase(possibleMoves.begin(), possibleMoves.end());
        fillBucket(boardObj);
        emptyBucket(boardObj);
        transferBucketContents(boardObj);
        return possibleMoves;
    }
    /* Name: fillBucket()
     *
     * Description:	fills the bucket
     *
     * Argument: boardObj             object of type GameNode
     *
     */
    void fillBucket(GameNode *boardObj)
    {
        vector<int> config;
        config=boardObj->board;
        vector<int> tempConfig;
        for(int i=0; i<noOfJugs; i++)
        {
            tempConfig=config;
            if(tempConfig[i]!=maxCapacity[i])
            {
                tempConfig[i]=maxCapacity[i];
                GameNode *newBoard= new GameNode(tempConfig);
                vector<GameNode*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObj->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<int> >::iterator searchIter;
                searchIter=checkSet.find(tempConfig);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(tempConfig);
                    possibleMoves.push_back(newBoard);
                }
                config=boardObj->board;
            }
        }
    }
    /* Name: emptyBucket()
     *
     * Description:	empties the bucket
     *
     * Argument: boardObj             object of type GameNode
     *
     */
    void emptyBucket(GameNode *boardObj)
    {
        vector<int> config;
        config=boardObj->board;
        vector<int> tempConfig;
        for(int i=0; i<noOfJugs; i++)
        {
            tempConfig=config;
            if(tempConfig[i]!=0)
            {
                tempConfig[i]=0;
                GameNode *newBoard= new GameNode(tempConfig);
                vector<GameNode*>::iterator searchVector;
                for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                {
                    if((*searchVector)->board==boardObj->board)
                    {
                        newBoard->parent=*searchVector;
                    }
                }
                allConfigs.push_back(newBoard);
                set<vector<int> >::iterator searchIter;
                searchIter=checkSet.find(tempConfig);
                if(searchIter==checkSet.end())
                {
                    checkSet.insert(tempConfig);
                    possibleMoves.push_back(newBoard);
                }
                config=boardObj->board;
            }
        }
    }
    /* Name: transferBucketContents()
     *
     * Description:	transfer buckets from one bucket to another
     *
     * Argument: boardObj             object of type GameNode
     *
     */
    void transferBucketContents(GameNode *boardObj)
    {
        vector<int> config;
        config=boardObj->board;
        vector<int> tempConfig;
        for(int i=0; i<noOfJugs; i++)
        {
            for(int j=0; j<noOfJugs; j++)
            {
                tempConfig=config;
                if(i!=j)
                {
                    if(tempConfig[j]!=maxCapacity[j] && tempConfig[i]!=0)
                    {
                        int temp=maxCapacity[j]-tempConfig[j];
                        if(tempConfig[i]>=temp)
                        {
                            tempConfig[j]=maxCapacity[j];
                            tempConfig[i]=tempConfig[i]-temp;
                        }
                        else
                        {
                            tempConfig[j]=tempConfig[j]+tempConfig[i];
                            tempConfig[i]=0;
                        }
                        GameNode *newBoard= new GameNode(tempConfig);
                        vector<GameNode*>::iterator searchVector;
                        for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
                        {
                            if((*searchVector)->board==boardObj->board)
                            {
                                newBoard->parent=*searchVector;
                            }
                        }
                        allConfigs.push_back(newBoard);
                        set<vector<int> >::iterator searchIter;
                        searchIter=checkSet.find(tempConfig);
                        if(searchIter==checkSet.end())
                        {
                            checkSet.insert(tempConfig);
                            possibleMoves.push_back(newBoard);
                        }
                        config=boardObj->board;
                    }
                }
            }
        }
    }
    /* Name: print()
     *
     * Description:	prints the solution
     *
     * Argument: boardObj             object of type GameNode
     *
     */
    void print(GameNode *boardObj)
    {
        vector<int> board;
        board=boardObj->board;
        vector<GameNode*>::iterator searchVector;
        GameNode *printNode;
        for(searchVector=allConfigs.begin(); searchVector<allConfigs.end(); searchVector++)
        {
            if((*searchVector)->board==boardObj->board)
            {
                printNode=*searchVector;
            }
        }
        vector<int>::iterator iter1;
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
                cout<<*iter1<<" ";
            }
            cout<<endl;
        }
        cout<<"----------------------------------"<<endl;
    }

};
