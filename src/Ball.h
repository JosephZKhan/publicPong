//
// Created by Joseph Khan on 11/01/2021.
//

#ifndef PONGSFML_BALL_H
#define PONGSFML_BALL_H
#include <SFML/Graphics.hpp>



class Ball
{

 public:

  sf::Sprite ball_sprite;
  sf::Texture ball_texture;

  void set_ball_texture(sf::String file_name);

  void set_ball_sprite(int new_x, int new_y);

  float get_speed();

  void spawn();

  void speed_up();

  void get_ball_texture();

  bool ball_reach_left();
  bool ball_reach_right();


 private:




  float speed = 50;

};

#endif // PONGSFML_BALL_H
