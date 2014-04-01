// File: GameNode.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: Node class for the object structure.
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
class GameNode
{
public:
    vector<int> board;
    GameNode *parent;
    /* Name: Game()
     *
     * Description:	Default constructor
     *
     */
    GameNode()
    {
    }
    /* Name: Game()
     *
     * Description:	Parameterized constructor
     *
     */
    GameNode(vector<int> &board)
    {
        this->board=board;
        parent=NULL;
    }
};
