#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
using namespace std;

template<typename T>
void printArray(T arr[50][50]) {
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (arr[i][j]) {
                cout << "\u2588" << " ";
            } else {
                cout << "0" << " ";
            }
        }
        cout << '\n';
    }
}

void fill_grid(bool grid[50][50],int num_cells) {
    srand(time(0));
    for (int i = 0; i < num_cells; ++i) {
        int row = rand() % 50;
        int col = rand() % 50;
        grid[row][col] = true;
    }
    
}

int count_neighbors(bool grid[50][50], int rpos, int cpos){
    int i, j, count = 0;
    for (i = rpos - 1; i <= rpos + 1; i++) {
        for (j = cpos - 1; j <= cpos + 1; j++) {
            if ((i == rpos && j == cpos) || (i < 0 || j < 0)
                || (i >= 50 || j >= 50)) {
                continue;
            }
            if (grid[i][j]) {
                count++;
            }
        }
    }
    return count;
}

void fill_count_grid(int ncount[50][50], bool board[50][50], int row, int col){
    for(int i = 0; i < row; i++){   
        for(int j = 0; j < col; j++){
            ncount[i][j] = count_neighbors(board,i,j);
        }
    }
}

void populate(bool board[50][50], int ncount[50][50], int row, int col){ 
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[i][j]){
                if(ncount[i][j] < 2 || ncount[i][j] > 3){
                    board[i][j] = false;
                }
            }
            else{ //board[i][j] ==  false
                if(ncount[i][j] == 3){
                    board[i][j] = true;
                }
            }
        }
    }
}

void turn(bool board[50][50], int ncount[50][50], int row, int col){
    string input;
    fill_count_grid(ncount,board,row,col);
    populate(board,ncount,row,col);
    printArray(board);
    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    cout<<'\n';
}

void run_conways(){
    const int row = 50;
    const int col = 50;
    bool board[50][50] = {false};
    int ncount[50][50] = {0};
    int num_cells;
    int num_of_turns;
    
    cout<<"The current board is size 50x50."<<'\n';
    cout<<"How many cells should initially be alive: ";
    cin>>num_cells;
    cout<<"How many rounds of the simulation should be perfromed: ";
    cin>>num_of_turns;
    cout<<'\n';

    fill_grid(board,num_cells);
    printArray(board);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cout<<'\n';

    for(int l = 0; l < num_of_turns; l++){
        turn(board,ncount,row,col);
    }

    cout<<"Simulation complete."<<'\n';
    int cells_alive;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[i][j]){
                cells_alive++;
            }
        }
    }
    cout<<to_string(cells_alive) + " of " + to_string(row*col) + " cells are alive."<<'\n';
}

int main(){
    run_conways();
    return 0;
}