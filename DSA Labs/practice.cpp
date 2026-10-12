// #include <iostream>

// using namespace std;
// class Place8QueensonBoard
// {
// private:
//     char board[8][9];
//     char queen;
//     char empty;
//     int currx,curry;
//     int rows,cols;
//     void PrintBoard(int i,int j)
//     {
//         if(board[i][j] == '\0')
//         {
//             cout << endl;
//             j = 0;
//             i++;
//         }
//         else if(i == 7 && board[i][j] == '\0')
//         {
//             cout << endl;
//             return;
//         }
//         else
//         {
//             cout << board[i][j] << ' ';
//             j++;
//         }
//         PrintBoard(i,j);
//     }
// public:
//     Place8QueensonBoard(char q = 'Q',char e = '0')
//     {
//         rows = cols = 8;
//         queen = q;
//         empty = e;
//         currx = curry = 0;

//         MakeBoard();
//     }
//     void MakeBoard()
//     {
//         if(currx < 7 && curry == 8)
//         {
//             board[currx][curry] = '\0';
//             curry = 0;
//             currx++;
//         }
//         else if(currx == 7 && curry == 8)
//         {
//             board[currx][curry] = '\0';
//             currx = curry = 0;
//             return;
//         }
//         else
//             curry++;
//         MakeBoard();
//     }
    
//     void Place_Queen_on_Index()
//     {
//         board[currx][curry] = queen;
//     }
//     void Replace_Queen_on_Index()
//     {
//         board[currx][curry] = empty;
//     }

//     bool CheckAvalability(int i ,int j,bool& flag)
//     {
//         if(i < 0 || i > rows - 1 || j < 0 || j > cols - 1)
//             flag = true;    
//         if(board[i][j] == queen)
//             flag = false;

//         if(!flag)
//             return false;

//         CheckAvalability(i,j + 1,flag);
//         CheckAvalability(i,j - 1,flag);
//         CheckAvalability(i + 1,j,flag);
//         CheckAvalability(i - 1,j,flag);
//         CheckAvalability(i + 1,j + 1,flag);
//         CheckAvalability(i - 1,j - 1,flag);
//     }
//     void Print()
//     {
//         PrintBoard(0,0);
//     }
    
// };

// void FabinachiSeries(int first,int second,int end)
// {
//     if(first == 0)
//         cout << 0 << ',' << 1;
//     else
//         cout << ',' << second;

//     if(second == end)
//         return;

//     int temp = second;
//     second += first;
//     first = temp;

//     FabinachiSeries(first,second,end);
// }

// void FabinachiSeries(int num)
// {
//     FabinachiSeries(0,1,num);
// }


// int main()
// {
//     FabinachiSeries(34);
//     cout << endl;
//     cout.put('s');
//     cout << endl;
//     int matrix[5][5] =
//     {
//         {1,2,3,4,5},
//         {6,7,8,9,10},
//         {11,12,13,14,15},
//         {16,17,18,19,20},
//         {21,22,23,24,25}
//     };
//     return 0;
// }

#include <iostream>
using namespace std;

#define MAX 100

// a) Left -> Right on a fixed row
void printRowLeftToRight(int matrix[][MAX], int row, int colStart, int colEnd)
{
    if (colStart > colEnd)          // base case: range finished
        return;
    cout << matrix[row][colStart] << " ";
    printRowLeftToRight(matrix, row, colStart + 1, colEnd);
}

// b) Top -> Bottom on a fixed column
void printColumnTopToBottom(int matrix[][MAX], int col, int rowStart, int rowEnd)
{
    if (rowStart > rowEnd)
        return;
    cout << matrix[rowStart][col] << " ";
    printColumnTopToBottom(matrix, col, rowStart + 1, rowEnd);
}

// c) Right -> Left on a fixed row (colStart is the larger index, moves down to colEnd)
void printRowRightToLeft(int matrix[][MAX], int row, int colStart, int colEnd)
{
    if (colStart < colEnd)
        return;
    cout << matrix[row][colStart] << " ";
    printRowRightToLeft(matrix, row, colStart - 1, colEnd);
}

// d) Bottom -> Top on a fixed column (rowStart is the larger index, moves up to rowEnd)
void printColumnBottomToTop(int matrix[][MAX], int col, int rowStart, int rowEnd)
{
    if (rowStart < rowEnd)
        return;
    cout << matrix[rowStart][col] << " ";
    printColumnBottomToTop(matrix, col, rowStart - 1, rowEnd);
}

// e) Spiral: peel one layer, then recurse on the inner matrix
void printSpiralRecursively(int matrix[][MAX], int top, int bottom, int left, int right)
{
    if (top > bottom || left > right)   // base case: nothing left
        return;

    // 1) top row, left -> right
    printRowLeftToRight(matrix, top, left, right);

    // 2) right column, top+1 -> bottom (top-right corner already printed)
    printColumnTopToBottom(matrix, right, top + 1, bottom);

    // 3) bottom row, right-1 -> left (only if it's a different row from top)
    if (top < bottom)
        printRowRightToLeft(matrix, bottom, right - 1, left);

    // 4) left column, bottom-1 -> top+1 (only if it's a different column from right)
    if (left < right)
        printColumnBottomToTop(matrix, left, bottom - 1, top + 1);

    // 5) shrink boundaries and repeat
    printSpiralRecursively(matrix, top + 1, bottom - 1, left + 1, right - 1);
}

int main()
{
    int matrix[MAX][MAX] = {
        { 1,  2,  3,  4},
        { 5,  6,  7,  8},
        { 9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    int rows = 4, cols = 4;
    printSpiralRecursively(matrix, 0, rows - 1, 0, cols - 1);
    cout << endl;
    return 0;
}