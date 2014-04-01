// File: GameNode1.cpp, v 1 2013/12/08 17:00:00
// Author: 
// Contributors: 
// Description: Node class for the object structure.
#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;
class GameNode1
{
public:
    vector<vector<char> > board;
    GameNode1 *parent;
    /* Name: Game()
     *
     * Description:	Default constructor
     *
     */
    GameNode1()
    {
    }
    /* Name: Game()
     *
     * Description:	Parameterized constructor
     *
     */
    GameNode1(vector<vector<char> > &board)
    {
        this->board=board;
        parent=NULL;
    }
};
