#include <iostream>
#include <vector>
#include <cstdlib>	

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif


char grid[10][10];
char snake_symbol='X';
char snake_head_symbol='~';
char empty_symbol='.';
char food_symbol='@';

void printGrid(){

    system(CLEAR_SCREEN);

    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < 10; ++j){
        std::cout << grid[i][j]<<"  ";
    }
    std::cout << "\n";
    }
}


class Snake{
  public:
  int snake_length;
  int* food_location;
  std::vector<std::pair<int, int>> snake_body;

  void apply_snake(){
    grid[snake_body[0].second][snake_body[0].first]=snake_head_symbol;
    for (int i=1; i<snake_length;i++){
      grid[snake_body[i].second][snake_body[i].first]=snake_symbol;
    }
  }


  Snake(){
    snake_length = 1;
    snake_body.insert(snake_body.begin(),{rand()%10,rand()%10});
    apply_snake();
  }
  



  bool snake_move( char direction){
    bool ate_food = false;
    int dx = 0, dy = 0;
    switch (direction) {
            case 'w': dy = -1; break;
            case 's': dy = 1; break;
            case 'a': dx = -1; break;
            case 'd': dx = 1; break;
    }
    int temp1=(snake_body[0].first + dx)%10;
    int temp2=(snake_body[0].second + dy)%10;
    snake_body.insert(snake_body.begin(),{temp1 != -1 ? temp1 : 9, temp2 != -1 ? temp2 : 9});
  
    if (grid[snake_body[0].second][snake_body[0].first]==food_symbol){
      snake_length++;
      ate_food=true;
    }

    else {
      grid[snake_body.back().second][snake_body.back().first]=empty_symbol;
      snake_body.pop_back();
    }

    for (int i=1; i<snake_length;i++){
      if (snake_body[i]==snake_body[0]){
        std::cout<<"Game Over\nScore: "<<snake_length;
        exit(1);
      }
    }

    apply_snake();

  return ate_food;

  }

};



void placeFood (Snake yilan){
    int food_location[2] = {-1,-1};

      while (food_location[0]==-1){
      
      food_location[0]=rand()%10;
      food_location[1]=rand()%10;


      for (int i=0; i<yilan.snake_length;i++){

        if (food_location[0] == yilan.snake_body[i].first && food_location[1] == yilan.snake_body[i].second ) {
          food_location[0]=-1;
          break;
        }      
      }
    }
    grid[food_location[1]][food_location[0]]=food_symbol;


};





int main() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        grid[i][j] = empty_symbol;
    }
  }
  char input;
  Snake yilan;
  placeFood(yilan);
  printGrid();

  while (1){
    std::cin>>input;
    if (yilan.snake_move(input)){
      placeFood(yilan);
    } 
    
    printGrid();
  }
  std::cout<<"";
  return 0;
}