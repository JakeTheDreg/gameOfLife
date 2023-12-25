//These are the rules of a game. Let it be played upon an infinite two-dimensional grid of flowers.

//Rule One. A living flower with less than two living neighbors is cut off. It dies.

//Rule Two. A living flower with two or three living neighbors is connected. It lives.

//Rule Three. A living flower with more than three living neighbors is starved and overcrowded. It dies.

//Rule Four. A dead flower with exactly three living neighbors is reborn. It springs back to life.

//The only play permitted in the game is the arrangement of the initial flowers.

#include <iostream>
#include <string>
#include <random>
#include "./board.hpp"

#define height          100
#define width           200

using std::cin, std::cout, std::endl;
std::default_random_engine generator;

void display(bool flowers[][width]){
    std::string displayString;
    for(size_t row = 0; row < height; row++){
        for(size_t column = 0; column < width; column++){
            if(flowers[row][column]){
                displayString += '%';
            }
            else{
                displayString += ' ';
            }
        }
        displayString += '\n';
    }
    for(size_t i = 0; i < width; i++){
        displayString += '-';
    }
    displayString += '\n';
    std::cout << displayString << std::endl;
}

void initFlowers(bool flowers[][width]){
    std::uniform_int_distribution<int> distribution(0, 17);

    for(size_t row = 0; row < height; row++){
        for(size_t column = 0; column < width; column++){
            flowers[row][column] = (distribution(generator) == 1);
        }
    }
}

std::pair<int, int> getNeighbors(bool flowers[][width], size_t pos_y, size_t pos_x){
    std::pair<int, int> neighbors(0, 0);
    for(size_t row = pos_y - 1; row < pos_y + 2; row++){
        for(size_t column = pos_x - 1; column < pos_x + 2; column++){
            if(column >= 0 && row >= 0 && column < width && row < height){
                if(flowers[row][column] == true) neighbors.first++;
                else neighbors.second++;
            }
        }
    }
    return neighbors;
}

void turn(bool flowers[][width]){
    for(size_t row = 0; row < height; row++){
        for(size_t column = 0; column < width; column++){
            std::pair<int, int> neighbors = getNeighbors(flowers, row, column);
            if(flowers[row][column] == false){
                if(neighbors.first == 3) flowers[row][column] = true;
            }
            else{
                if(neighbors.first < 2) flowers[row][column] = false;
                else if(neighbors.first > 3) flowers[row][column] = false;
            }
        }
    }
    display(flowers);
}

int main(){
    bool flowers[height][width];
    initFlowers(flowers);
    cout << "Welcome to the flower game!" << endl;
    cout << "Press enter to start the next turn" << endl;
    cout << "Enter x to end the game" << endl;
    std::string input;
    cin >> input;
    while(input != "x"){
        turn(flowers);
        cin >> input;
    }
    return 0;
}