#include "Snake.cpp"
#include <chrono>
#include <ncurses.h>
using namespace std::chrono_literals;

int main()
{

  constexpr std::chrono::nanoseconds timestep(100ms);
  using clock = std::chrono::high_resolution_clock;

  std::chrono::nanoseconds lag(0ns);
  auto time_start = clock::now();
  
  int const width {24};
  int const height {24};
  
  int x{10};
  int y{10};
  initscr();
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
  WINDOW * win = newwin(height, width, 0, 0);

  Snake snake(5, 10, 10, win, height, width);
  int dx = 0;
  int dy = 1;
  int ch;
  bool cont = true;

  for(int i {0}; i<=height; ++i){
    move(i, width-1);
    addch('|');
    move(i, 0);
    addch('|');
  }
  move(height, 1);
  printw("----------------------");

  wrefresh(win);
  
  while(cont){
    
    auto delta_time = clock::now() - time_start;
    time_start = clock::now();
    lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

    
    ch = getch();
    switch (ch){
    case KEY_UP:
      dx = 0;
      dy = -1;
      break;
    case KEY_DOWN:
      dx = 0;
      dy = 1;
      break;
    case KEY_LEFT:
      dx = -1;
      dy = 0;
      break;
    case KEY_RIGHT:
      dx = 1;
      dy = 0;
      break;
    case KEY_BACKSPACE:
      cont = false;
      break;
    }
    while(lag >= timestep) {
      lag -= timestep;
      cont = snake.update();
      snake.move(dx, dy);
      snake.drawMe();
      wrefresh(win);
    }
   
  }
	  
  endwin();
  return 0;
}
