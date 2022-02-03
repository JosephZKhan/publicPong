#include "Vector.h"
#include <math.h>

//function for generating random number
//for the purpose of randomising the ball's trajectory
int Vector::get_random_number(int min, int max)
{
  static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };
  return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

//accessor function for x
float Vector::get_x(){
  return x;
}

//reverse the direction of x
void Vector::reverse_x(){
  x = -x;
}

//accessor function for y
float Vector::get_y(){
  return y;
}

//mutator function for y
void Vector::set_y(float new_y){
  y = new_y;
}

//reverse the direction for y
void Vector::reverse_y(){
  y = -y;
}

//randomise the y component
void Vector::randomise_y(){
  //if the ball is moving down
  if (y > 0) {
    //set it on a random upwards angle
    y = (get_random_number(1, 10));
  }
  //if the ball is moving up
  else if (y < 0) {
    //set it on a random downwards angle
    y = (get_random_number(-10, -1));
  }
  //if the ball is moving straight ahead
  else {
    //set it on a random angle, upwards or downwards
    y = (get_random_number(-10, 10));
  }
}
