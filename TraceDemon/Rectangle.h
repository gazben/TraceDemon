#ifndef Rectangle_h__
#define Rectangle_h__

#include "Vector3D.h"

struct Coordinate2D{
  int x;
  int y;
};

struct Rect{
  Coordinate2D UpRigh, UpLeft, DownRight, DownLeft;

  Rect(){
  }

  Rect(int DownLeft_x, int DownLeft_y, int width, int height){
    DownLeft.x = DownLeft_x;				
    DownLeft.y = DownLeft_y;
    DownRight.x = DownLeft_x + width;		
    DownRight.y = DownLeft_y;
    UpRigh.x = DownLeft_x + width;			
    UpRigh.y = DownLeft_y + height;
    UpLeft.x = DownLeft_x;					
    UpLeft.y = DownLeft_y + height;
  }

  Rect(Coordinate2D _DownLeft, Coordinate2D _UpRight){
    DownLeft = _DownLeft;
    UpRigh = _UpRight;
    DownRight.x = UpRigh.x;
    DownRight.y = DownLeft.y;
    UpLeft.x = DownLeft.x;
    UpLeft.y = UpRigh.y;
  }

  Rect(Rect& inRectangle){
    this->UpRigh = inRectangle.UpRigh;	
    this->DownRight = inRectangle.DownRight;
    this->DownLeft = inRectangle.DownLeft;	
    this->UpLeft = inRectangle.UpLeft;
  }

  Rect& operator = (const Rect& inRectangle){
    this->UpRigh = inRectangle.UpRigh;	
    this->DownRight = inRectangle.DownRight;
    this->DownLeft = inRectangle.DownLeft;	
    this->UpLeft = inRectangle.UpLeft;

    return *this;
  }

  void setCorners(int DownLeft_x, int DownLeft_y, int width, int height){
    DownLeft.x = DownLeft_x;				
    DownLeft.y = DownLeft_y;
    DownRight.x = DownLeft_x + width;		
    DownRight.y = DownLeft_y;
    UpRigh.x = DownLeft_x + width;			
    UpRigh.y = DownLeft_y + height;
    UpLeft.x = DownLeft_x;					
    UpLeft.y = DownLeft_y + height;
  }

  bool Contains(int x, int y){							//returns true if the rectangle contains the ginven point
    return ((x > this->UpLeft.x &&
      x < this->UpRigh.x) &&
      (y > this->DownLeft.y &&
      y < this->UpRigh.y));
  }

  void Move(int delta_x, int delta_y){					//Moves the rectangle with the relative positions
    UpLeft.x += delta_x;			
    UpLeft.y += delta_y;
    UpRigh.x += delta_x;			
    UpRigh.y += delta_y;
    DownRight.x += delta_x;			
    DownRight.y += delta_y;
    DownLeft.x += delta_x;			
    DownLeft.y += delta_y;
  }

  void SetPosition(int DownLeft_x, int DownLeft_y){			//Sets the rectangles position to the given Topleft coordinate
    float delta_x = DownLeft_x - this->DownLeft.x;
    float delta_y = DownLeft_y - this->DownLeft.y;

    this->Move(delta_x, delta_y);
  }
};
#endif // Rectangle_h__