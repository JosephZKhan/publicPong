//
// Created by Joseph Khan on 12/01/2021.
//

#include "Paddle.h"
#include <iostream>

#include <SFML/Graphics.hpp>

//increment the player's score by 1
void Paddle::score_increase(){
  score += 1;
}

void Paddle::set_paddle_texture(sf::String file_name)
{
  // Load the paddle texture, return error message if loading fails
  if (!paddle_texture.loadFromFile(file_name))
  {
    std::cout << "Error - Missing file";
  }
  // Set the texture of the paddle
  paddle_sprite.setTexture(paddle_texture);
}

//accessor function for paddle_x
int Paddle::get_paddle_x(){
  return paddle_x;
}

//accessor function for paddle_y
int Paddle::get_paddle_y(){
  return paddle_y;
}

//set the position of the paddle_sprite on screen
void Paddle::set_paddle_sprite(int new_x, int new_y){
  paddle_sprite.setPosition(new_x, new_y);
}

//accessor function for score
int Paddle::get_paddle_score(){
  return score;
}

//function handling key-operated paddle movement
void Paddle::paddle_move(sf::Keyboard::Key up_key, sf::Keyboard::Key down_key){

  //set movement_control to -1 if the player presses the down key
  if (sf::Keyboard::isKeyPressed(up_key)) {
    movement_control = -1.0f;
  }

  //set movement_control to 1 if the player presses the down key
  if (sf::Keyboard::isKeyPressed(down_key)) {
    movement_control = 1.0f;
  }
}

//function returning true if the ball hits a paddle
bool Paddle::paddle_collide(int ball_x_pos, int ball_y_pos){
  //if the ball's y coordinate is within the vertical bounds of the paddle
  if (ball_y_pos >= paddle_sprite.getPosition().y and ball_y_pos <= (paddle_sprite.getPosition().y + paddle_sprite.getGlobalBounds().height))
  {
    //and the ball's x coordinate is within the horizontal bounds of the paddle
    if (ball_x_pos > paddle_sprite.getPosition().x and ball_x_pos < (paddle_sprite.getPosition().x) + paddle_sprite.getGlobalBounds().width)
    {
      //return true
      return true;
    }
  }
  //otherwise return false
  else {
    return false;
  }
}

//function that changes the paddle's position onscreen
void Paddle::paddle_update_movement(float dt){
  //move the paddle sprite using paddle_speed and the movement_control variable as altered above
  paddle_sprite.move(0, movement_control * paddle_speed * dt);
}

//function that stops the paddle from moving if the keys have been released
void Paddle::paddle_stop(sf::Keyboard::Key up_key, sf::Keyboard::Key down_key, sf::Event event){
    if(event.key.code == up_key and movement_control != 1.0f){
      movement_control = 0.0f;
    }
    else if(event.key.code == down_key and movement_control != -1.0f){
      movement_control = 0.0f;
    }
}

//accessor function for movement_control
float Paddle::get_movement_control(){
  return movement_control;
}