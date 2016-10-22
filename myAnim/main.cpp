// Brian Malloy and Chris Malloy
// This example illustrates an approach to capturing 60 frames
// per second to form a smooth, efficient animation.
// The resulting frame rate of the generated movie exactly matches 
// the frame rate captured in the program below.
// By setting makeVideo to true on line 88, frame capture begins at
// the beginning of the program and ends when the animation completes.

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

const int XS = 10;
const int YS = 10;
const int SIDE = 32;

const unsigned int WIDTH = XS*SIDE;
const unsigned int HEIGHT = YS*SIDE;

const float INCR_X = 0.3;
// Approximately 60 frames per second: 60/1000
const unsigned int DT = 17u; // ***
const float GRAVITY = 10;
int timer = 0;

int field [XS][YS];

class Ball {
public:

  Ball() : X_VELOCITY(0), Y_VELOCITY(0), x(0), y(0), nextX(0), nextY(0), DIR(1), next(false) { }
  
  Ball (Ball *cry) : X_VELOCITY(cry->getXV()),
                     Y_VELOCITY(cry->getYV()),
                     x(cry->getX()), 
                     y(cry->getY()),
                     nextX(cry->nextX),
                     nextY(cry->nextY),
                     DIR(cry->getD()) { }
  
  float getX() { return x; }
  float getY() { return y; }
  
  float getXV() { return X_VELOCITY; }
  float getYV() { return Y_VELOCITY; }

  int getD() { return DIR; }
  
  void setDir(int in) { DIR = in; next = true; }
  
  void update () {
    if (next){
        if (DIR == 1){
            x += 32;
        } else if (DIR == 3){
            x -= 1;
        } else if (DIR == 2){
            y += 32;
        } else if (DIR == 0){
            y -= 32;
        }
    next = false;
    }
  }
  
  void bounceX (SDL_Surface *star) {
    if((x > WIDTH-star->w && DIR > 0) || (x < 0 && DIR < 0)){
      DIR *= -1;
      timer += 1;
    }
  }
  
  void bounceY (SDL_Surface *star) {
    if (y > HEIGHT-star->h) {
      Y_VELOCITY *= -1;
      y = HEIGHT-star->h;
    }
  }
  
private:
  float X_VELOCITY;
  float Y_VELOCITY;
  float x;
  float y;
  float nextX;
  float nextY;
  int DIR;
  bool next;
};

class Items {
public:
  Items () : wtf(NULL) {}
  Items (Ball *doom) : wtf(doom) {}
  
  Ball *getBall () { return wtf; }
  void setBall(Ball *no) {
    wtf = no;
  }
  
  void update() {
    wtf->update();
  }
  
  void setDir(int in) { wtf->setDir(in); }
private:
  Ball *wtf;
};

void init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw( std::string("Unable to initialize SDL: ")+ SDL_GetError());
  }
  atexit(SDL_Quit);
}

SDL_Surface* getImage(const std::string& filename, bool setColorKey) {
  SDL_Surface *temp = IMG_Load(filename.c_str());
  if (temp == NULL) {
    throw std::string("Unable to load image.")+SDL_GetError();
  }
  if ( setColorKey ) {
    Uint32 colorkey = SDL_MapRGB(temp->format, 255, 0, 255);
    SDL_SetColorKey(temp, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
  }
  SDL_Surface *image = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  return image;
}

void draw(SDL_Surface* image, SDL_Surface* screen, 
          float x = 0.0, float y = 0.0) {
  Uint16 w = image->w;
  Uint16 h = image->h;
  Sint16 xCoord = static_cast<Sint16>(x);
  Sint16 yCoord = static_cast<Sint16>(y);
  SDL_Rect src = { 0, 0, w, h };
  SDL_Rect dest = {xCoord, yCoord, 0, 0 };
  SDL_BlitSurface(image, &src, screen, &dest);
}

bool update(Items *in) {
  static unsigned int remainder = 0u; // ***
  static unsigned int currentTicks = 0u;
  static unsigned int prevTicks = SDL_GetTicks();
  currentTicks = SDL_GetTicks();
  unsigned int elapsedTicks = currentTicks - prevTicks + remainder; // ***
  Uint8 *keystate = SDL_GetKeyState(NULL);
  SDL_Event event;

  if( elapsedTicks < DT ) return false; // ***
  
  if (SDL_PollEvent(&event)){
    if (event.type == SDL_KEYDOWN){
        if (keystate[SDLK_d]){
            in->setDir(1);
        } else if (keystate[SDLK_a]){
            in->setDir(3);
        } else if (keystate[SDLK_s]){
            in->setDir(2);
        } else if (keystate[SDLK_w]){
            in->setDir(0);
        }
    }
  }
  
  in->update();
  
  prevTicks = currentTicks;
  remainder = elapsedTicks - DT; // ***

  return true; // ***
}

void makeField(){
    for (int i = 0; i < XS; i += 1){
        for (int j = 0; j < YS; j += 1){
            field[i][j] = 0;
        }
    }
}
int main() {
    makeField();

  try {
    init();
    SDL_Surface *screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_DOUBLEBUF);
    if (screen == NULL) {
      throw std::string("Unable to set video mode: ")+SDL_GetError();
    }
    SDL_Surface *sky = getImage("images/bkg.png", false);
    SDL_Surface *star = getImage("images/Ball.bmp", true);

    Ball *theBall = new Ball();
    Items *Manager = new Items(theBall);
    
    SDL_Event event;
    bool makeVideo = false;
    bool done = false;
    bool freshFrame = false; // ***
    
    while (!done) {
      while ( SDL_PollEvent(&event) ) {
        if (event.type == SDL_QUIT) done = true;
        if (event.type == SDL_KEYDOWN) {
          if (event.key.keysym.sym == SDLK_ESCAPE) done = true;
        }
      }
      
//      theBall->bounceY(star);
  //    theBall->bounceX(star);
      
      freshFrame = update(Manager);
      
      for (int i = 0; i < XS; i += 1){
        for (int j = 0; j < YS; j += 1){
          draw(sky, screen, i*SIDE, j*SIDE);
        }
      }
      
      draw(star, screen, theBall->getX(), theBall->getY());
      SDL_Flip(screen);
      
      if ( timer >= 2 ) { done = true; }
    }
    SDL_FreeSurface(sky);
    SDL_FreeSurface(star);
    
    delete theBall;
    delete Manager;
  }
  catch(const std::string& msg) { std::cout << msg << std::endl;  }
  catch(...) { std::cout << "oops" << std::endl;  }
}
