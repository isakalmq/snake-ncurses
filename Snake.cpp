#include <list>
#include <ncurses.h>
#include <random>

struct Point{
  int x;
  int y;
};

class Snake {
public:
  Snake(int const initLength, int const startX, int const startY, WINDOW * win, int h, int w){
    foodLocation = {14, 17};
    sizeX = w;
    sizeY = h;
    window = win; 
    length = initLength;
    segments = std::list<Point>();
    for(int i {0}; i< initLength; ++i){
      Point tempSeg {startX, startY - i};
      segments.push_back(tempSeg);
    }
  }
  ~Snake(){
  }
  //Moves the snake in the specified direction
  void move(int const dx, int const dy){
    lastx = segments.back().x;
    lasty = segments.back().y;
    segments.pop_back();
    Point newSeg {segments.front().x + dx, segments.front().y +dy};
    segments.push_front(newSeg);

    
  }
  bool update(){
    //wmove(window, 0,20);
    //wprintw(window, "IM");
    Point head = segments.front();
    if(head.x == foodLocation.x && head.y == foodLocation.y){
      Point newSeg {segments.back().x, segments.back().y};
      segments.push_back(newSeg);
      std::random_device rnd;
      foodLocation.x = (rnd() % 22)+1;
      foodLocation.y = (rnd() % 22)+1;
    }

    if((head.x <= 0)||(head.x >= sizeX)||(head.y <= 0)||(head.y >= sizeY)){
	return false;
    }
    bool first {true};
    for(Point const & seg : segments){
      if((seg.x == head.x) && (seg.y == head.y) && !first){
	return false;
      }
      first = false;
    }
    return true;
  }

  void drawMe() const{
    wmove(window, lasty, lastx);
    waddch(window, ' ');
    for(Point const & seg: segments){
      wmove(window, seg.y, seg.x);
      waddch(window, '@');
    }

    wmove(window, foodLocation.y, foodLocation.x);
    waddch(window, '*');

    wmove(window, 0,1);
    wprintw(window, "Points:---------------");
    wmove(window, 0,8);
    wprintw(window, "%d", segments.size());
  }
private:
  int sizeX;
  int sizeY;
  bool addSeg;
  int length;
  WINDOW * window;
  std::list<Point> segments;
  int lastx;
  int lasty;
  Point foodLocation;
};
