//
// Created by Joseph Khan on 11/01/2021.
//
#include "Ball.h"
#include "Vector.h"
#include "Vector.cpp"
#include <iostream>

//instantiate a Vector object determining the ball's movement
Vector ball_1_direction;

void Ball::set_ball_texture(sf::String file_name)
{
  //Load the ball texture, return error message if loading fails
  if(!ball_texture.loadFromFile(file_name))
  {
    std::cout << "Error - Missing file";
  }

  //Set the texture of the ball
  ball_sprite.setTexture(ball_texture);
}

//respawn function
void Ball::spawn()
{
  //reset the ball's speed to 50
  speed = 50;
  //set the y component of the directional vector to 0
  //meaning the ball will always respawn going in a straight line
  ball_1_direction.set_y(0);
  //reverse the ball vector's x component
  //so that a player won't have multiple losses in immediate succession
  ball_1_direction.reverse_x();
  //move the ball to the centre of the screen
  ball_sprite.setPosition(540, 360);
  //reset the ball's texture to a neutral white
  set_ball_texture("Data/Images/ball_3.png");



}

void Ball::speed_up()
{
  // increase the speed by 4 unless it reaches the speed cap of 100
  if (speed <= 100)
    {
      speed += 4;
    }
}

//accessor function for speed
float Ball::get_speed(){
  return speed;
}

//set position of the ball_sprite
void Ball::set_ball_sprite(int new_x, int new_y){
  ball_sprite.setPosition(new_x, new_y);
}

//return true if the ball has reached the left of the screen
//determining if player 2 has scored a point
bool Ball::ball_reach_left(){
  if (ball_sprite.getPosition().x <= 0){
    return true;
  }
  else {
    return false;
  }
}
//return true if the ball has reached the right of the screen
//determining if player 1 has scored a point
bool Ball::ball_reach_right(){
  if (ball_sprite.getPosition().x + ball_sprite.getGlobalBounds().width >= 1080){
    return true;
  }
  else {
    return false;
  }
}