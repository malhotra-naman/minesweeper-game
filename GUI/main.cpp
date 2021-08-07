#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
using namespace std;
using namespace sf;

int rows = 9, cols = 9, mines = 10;
bool gameOver = false;
int w = 50;
int board[100][100];
int playBoard[100][100];
// Music music;

void initMines(){
  vector< pair< int, int > > positions;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            positions.push_back(make_pair(i, j));
        }
    }
    shuffle(positions.begin(), positions.end(), default_random_engine(time(0)));
    for(int i = 0; i < mines; i++){
        board[positions[i].first][positions[i].second] = 9;
    }
}

bool isValid(int x, int y){
  return ((x >= 0 && x < rows) && (y >= 0 && y < cols));
}

int neighborMines(int x, int y){
  int numMines = 0;
  for(int xOffset = -1; xOffset <= 1; xOffset++){
    for(int yOffset = -1; yOffset <= 1; yOffset++){
      int neighborX = x + xOffset;
      int neighborY = y + yOffset;
      if(isValid(neighborX, neighborY) && (board[neighborX][neighborY] == 9)){
        numMines++;
      }
    }
  }
  return numMines;
}

void initBoard(){
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      playBoard[i][j] = 10;
      board[i][j] = 0;
    }
  }
  initMines();
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(board[i][j] != 9){
        board[i][j] = neighborMines(i, j);
      }
    }
  }
}

void triggerPress(int x, int y){
  if(playBoard[x][y] != 10){
    return;
  }
  if(board[x][y] == 9){
    gameOver = true;
    return;
  }else{
    playBoard[x][y] = board[x][y];
    if(board[x][y] == 0){
      for(int xOffset = -1; xOffset <= 1; xOffset++){
        for(int yOffset = -1; yOffset <= 1; yOffset++){
          int neighborX = x + xOffset;
          int neighborY = y + yOffset;
          if(isValid(neighborX, neighborY)){
            triggerPress(neighborX, neighborY);
          }
        }
      }
    }
  }
}

void displayGameOver(bool hasWon, RenderWindow *app){
  app->close();
  if(hasWon){

    // music.stop();
    // music.openFromFile("./sounds/haswon.ogg");
    // music.play();

    RenderWindow gameDone(VideoMode(318, 212), "You Won!");
    Texture won;
    won.loadFromFile("./assets/hasWon.jpg");
    Sprite sWon(won);
    sWon.setPosition(0, 0);
    gameDone.draw(sWon);

    gameDone.display();

    Sleep(10000);

    exit(0);

  }else{

    // music.stop();
    // music.openFromFile("./sounds/gameover.ogg");
    // music.play();

    RenderWindow gameDone(VideoMode(480, 360), "You Lose!");
    Texture lose;
    lose.loadFromFile("./assets/hasLost.jpg");
    Sprite sLost(lose);
    sLost.setPosition(0, 0);
    gameDone.draw(sLost);

    gameDone.display();

    Sleep(8000);

    exit(0);

  }
  
  exit(0);

}

void isGameOver(RenderWindow *app){
  if(gameOver){
    displayGameOver(false, app);
    return;
  }
  int minesLeft;
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      if(playBoard[i][j] == 10 || playBoard[i][j] == 11){
        minesLeft++;
      }
    }
  }
  if(minesLeft == mines){
    gameOver = true;
    displayGameOver(true, app);
  }
  return;
}

void startGame(){
  srand(time(0));
  RenderWindow app(VideoMode(rows*w, cols*w), "Minesweeper");

  Texture t0;
  t0.loadFromFile("./assets/modern_tiles/MINESWEEPER_0.png");
  Sprite s0(t0);
  Texture t1;
  t1.loadFromFile("./assets/modern_tiles/MINESWEEPER_1.png");
  Sprite s1(t1);
  Texture t2;
  t2.loadFromFile("./assets/modern_tiles/MINESWEEPER_2.png");
  Sprite s2(t2);
  Texture t3;
  t3.loadFromFile("./assets/modern_tiles/MINESWEEPER_3.png");
  Sprite s3(t3);
  Texture t4;
  t4.loadFromFile("./assets/modern_tiles/MINESWEEPER_4.png");
  Sprite s4(t4);
  Texture t5;
  t5.loadFromFile("./assets/modern_tiles/MINESWEEPER_5.png");
  Sprite s5(t5);
  Texture t6;
  t6.loadFromFile("./assets/modern_tiles/MINESWEEPER_6.png");
  Sprite s6(t6);
  Texture t7;
  t7.loadFromFile("./assets/modern_tiles/MINESWEEPER_7.png");
  Sprite s7(t7);
  Texture t8;
  t8.loadFromFile("./assets/modern_tiles/MINESWEEPER_8.png");
  Sprite s8(t8);
  Texture t9;
  t9.loadFromFile("./assets/modern_tiles/MINESWEEPER_M.png");
  Sprite s9(t9);
  Texture t10;
  t10.loadFromFile("./assets/modern_tiles/MINESWEEPER_X.png");
  Sprite s10(t10);
  Texture t11;
  t11.loadFromFile("./assets/modern_tiles/MINESWEEPER_F.png");
  Sprite s11(t11);

  initBoard();

  while (app.isOpen()){
    Vector2i pos = Mouse::getPosition(app);
    int x = pos.x/w;
    int y = pos.y/w;
    Event evt;
    while (app.pollEvent(evt)){
      if (evt.type == Event::Closed){
        app.close();
      }
      if (evt.type == Event::MouseButtonPressed){
        if (evt.key.code == Mouse::Left){
          triggerPress(x, y);
        }
        else if (evt.key.code == Mouse::Right){
          if(playBoard[x][y] == 10){
            playBoard[x][y] = 11;
          }else if(playBoard[x][y] == 11){
            playBoard[x][y] = 10;
          }
        }
      }
    }
    app.clear(Color::White);

    for (int i = 0; i < rows; i++){
      for (int j = 0; j < cols; j++){
        if(gameOver){
          playBoard[i][j] = board[i][j];
        }
        float dim = w/216.0;
        switch(playBoard[i][j]){
          case 0:
            s0.setScale(Vector2f(dim, dim));
            s0.setPosition(i*w, j*w);
            app.draw(s0);
            break;
          case 1:
            s1.setScale(Vector2f(dim, dim));
            s1.setPosition(i*w, j*w);
            app.draw(s1);
            break;
          case 2:
            s2.setScale(Vector2f(dim, dim));
            s2.setPosition(i*w, j*w);
            app.draw(s2);
            break;
          case 3:
            s3.setScale(Vector2f(dim, dim));
            s3.setPosition(i*w, j*w);
            app.draw(s3);
            break;
          case 4:
            s4.setScale(Vector2f(dim, dim));
            s4.setPosition(i*w, j*w);
            app.draw(s4);
            break;
          case 5:
            s5.setScale(Vector2f(dim, dim));
            s5.setPosition(i*w, j*w);
            app.draw(s5);
            break;
          case 6:
            s6.setScale(Vector2f(dim, dim));
            s6.setPosition(i*w, j*w);
            app.draw(s6);
            break;
          case 7:
            s7.setScale(Vector2f(dim, dim));
            s7.setPosition(i*w, j*w);
            app.draw(s7);
            break;
          case 8:
            s8.setScale(Vector2f(dim, dim));
            s8.setPosition(i*w, j*w);
            app.draw(s8);
            break;
          case 9: 
            s9.setScale(Vector2f(dim, dim));
            s9.setPosition(i*w, j*w);
            app.draw(s9);
            break;
          case 10:
            s10.setScale(Vector2f(dim, dim));
            s10.setPosition(i*w, j*w);
            app.draw(s10);
            break;
          case 11:
            s11.setScale(Vector2f(dim, dim));
            s11.setPosition(i*w, j*w);
            app.draw(s11);
            break;
        } 
      }
    }
    app.display();

    isGameOver(&app);

    // if(gameOver){
    //   app.close();
    //   exit(0);
    // }
  }

}

int main(){
  
  // Music music;
  // if (!music.openFromFile("./sounds/bgmusic.ogg")) return -1; // error
  // music.play();

  cout << "Welcome to Minesweeper! :) - By NAMAN MALHOTRA\n";
  int difficultyLevel;
  cout << "Choose a Difficulty Level! :O\n";
  cout << "Press 1 - For Beginners!\n";
  cout << "Press 2 - For Experienced!\n";
  cout << "Press 3 - For Veterans!\n";
  cin >> difficultyLevel;

  switch(difficultyLevel){
    case 1:
      rows = 9;
      cols = 9;
      mines = 10;
      startGame(); 
      break;
    case 2:
      rows = 16;
      cols = 16;
      mines = 40;
      startGame(); 
      break;
    case 3:
      rows = 16;
      cols = 30;
      mines = 99;
      w = 32;
      startGame(); 
      break;
  }

  return 0;
}
