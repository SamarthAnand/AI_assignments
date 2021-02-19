#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> board = {
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {2, 2, 1, 1, 1, 2, 2},
    {2, 2, 1, 1, 1, 2, 2}};
vector<vector<int>> goal = {
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {2, 2, 0, 0, 0, 2, 2},
    {2, 2, 0, 0, 0, 2, 2}};
map<vector<vector<int>>, bool> visited;
stack<int> steps;
void showboard()
{
    int n;
    for (int a = 0; a < 7; a++)
    {
        for (int b = 0; b < 7; b++)
        {
            n = board[a][b];
            if (n == 2)
                cout << " ";
            else
                cout << n;
        }
        cout << endl;
    }
}
bool isvalid(vector<vector<int>> temp_board, int row, int col, int dir)
{

    if (row >= 0 && row < 7 && col >= 0 && col < 7)
    {

        if (temp_board[row][col] == 1)
        {
            switch (dir)
            {
            case 1: //UP
                cout << " check up for" << row << " " << col << endl;
                if (row - 2 >= 0)
                {

                    if (temp_board[row - 1][col] == 1 && temp_board[row - 2][col] == 0)
                        return true;
                }
                break;
            case 2: //DOWN

                if (row + 2 < 7)
                {

                    if (temp_board[row + 1][col] == 1 && temp_board[row + 2][col] == 0)
                        return true;
                }
                break;
            case 3: //LEFT

                if (col - 2 >= 0)
                {

                    if (temp_board[row][col - 1] == 1 && temp_board[row][col - 2] == 0)
                        return true;
                }
                break;
            case 4: //RIGHT
                if (col + 2 < 7)
                {

                    if (temp_board[row][col + 1] == 1 && temp_board[row][col + 2] == 0)
                        return true;
                }
                break;
            default:
                return false;
                break;
            } //end switch
        }
        //end peg check
    }
    //end starting bounds check
    return false;
}

int nrpos = 0;
bool visit(vector<vector<int>> a)
{
    if (visited[a] == true)
        return true;
    else
        return false;
}
bool isGoal(vector<vector<int>> a) // checks for the goal state
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (a[i][j] != goal[i][j])
                return false;
        }
    }

    return true;
}
void jump(int a, int b, int dir)
{
    switch (dir)
    {
    case 1: //N
        //cout << "moving north" << endl;
        board[a][b] = 0;
        // cout << "moving north" << endl;
        board[a - 1][b] = 0;
        // cout << "moving north" << endl;
        board[a - 2][b] = 1;
        // cout<<" board after jumping is"<<endl;
        // showboard();
        break;
    case 2: //S
        cout << "moving south" << endl;
        board[a][b] = 0;
        board[a + 1][b] = 0;
        board[a + 2][b] = 1;
        break;
    case 4: //E
        cout << "moving east" << endl;
        board[a][b] = 0;
        board[a][b + 1] = 0;
        board[a][b + 2] = 1;
        break;
    case 3: //W
        //cout << "moving west" << endl;
        board[a][b] = 0;
        board[a][b - 1] = 0;
        board[a][b - 2] = 1;
        break;
    default:
        cout << "qwerty";
        break;
    }
}
bool findsolution()
{
    // cout << "Inside find solution" << endl;
    if (isGoal(board))
        return true;
    else
    {
        //cout << " goal not found;" << endl;
        for (int a = 0; a < 7; a++)
        {
            for (int b = 0; b < 7; b++)
            {
                for (int c = 1; c <= 4; c++)
                {
                    // cout << " checking for " << a << " " << b << " " << c << "  " << endl;
                    if (isvalid(board, a, b, c))
                    {
                        //cout << "this is valid:" << a << "  " << b << " " << c << endl;
                        vector<vector<int>> hold;
                        for (int i = 0; i < 7; i++)
                        {
                            vector<int> tempp;
                            for (int j = 0; j < 7; j++)
                            {
                                tempp.push_back(board[i][j]);
                            }
                            hold.push_back(tempp);
                        }
                        // cout<<" value before jumping  is"<<endl;
                        showboard();
                        // cout << "value copied" << endl;
                        jump(a, b, c);
                        //cout << " jumped" << endl;
                        steps.push(a);
                        steps.push(b);
                        steps.push(c);
                        cout << "Making move:" << endl;
                        showboard();
                        cout << "----------" << endl;

                        //  int Number = 0;
                        // string Result = ""; // string which will contain the result
                        //  for (int x = 0; x < 7; x++)
                        // {
                        //     for (int y = 0; y < 7; y++)
                        //     {

                        //         Number = board[x][y];

                        //         Result += to_string(Number);
                        //     }
                        // }
                        // Result += to_string(a);
                        // Result += to_string(b);
                        // Result += to_string(c);

                        // const char *cstr = Result.c_str();

                        // int wasnotbefore = 1;
                        if (visit(board))
                        {
                            // wasnotbefore = 0;
                            cout << "This state was before:" << endl;
                            showboard();
                            cout << "----------" << endl;
                        }

                        if (!visit(board))
                        {

                            visited[board] = true;
                            //  myhash.set(cstr, nrpos);
                            if (findsolution())
                                return true;
                            else
                            {
                                board.clear();
                                for (int i = 0; i < 7; i++)
                                {
                                    vector<int> tempp;
                                    for (int j = 0; j < 7; j++)
                                    {
                                        tempp.push_back(hold[i][j]);
                                    }
                                    board.push_back(tempp);
                                }
                                steps.pop();
                                steps.pop();
                                steps.pop();

                                cout << "Move step back:" << endl;
                                showboard();
                                cout << "----------" << endl;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }
}
int main()
{
    //vector<vector<int>> board;

    //showboard();
    findsolution();
    cout << "Final board:" << endl;
    showboard();

    int i = 0;
    int a, b, c;
    string cc = "";

    cout << "STEPS:" << endl
         << "Read from bottom to top" << endl
         << endl;
    while (!steps.empty())
    { //cout<<" printing steps"<<endl;
        c = steps.top();
        steps.pop();

        b = steps.top();
        steps.pop();

        a = steps.top();
        steps.pop();
        if (c == 1)
            cc = "N";
        if (c == 2)
            cc = "S";
        if (c == 3)
            cc = "E";
        if (c == 4)
            cc = "W";
        cout << a + 1 << b + 1 << " " << cc << " ";

        i++;
    }

    return 0;
}