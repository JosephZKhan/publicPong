//
// Created by Joseph Khan on 12/01/2021.
//

#ifndef PONGSFML_PADDLE_H
#define PONGSFML_PADDLE_H
#include <SFML/Graphics.hpp>

class Paddle
{
 public:
  sf::Sprite paddle_sprite;
  sf::Texture paddle_texture;

  void score_increase();

  int get_paddle_score();

  void set_paddle_texture(sf::String file_name);

  void set_paddle_sprite(int new_x, int new_y);

  void paddle_move(sf::Keyboard::Key up_key, sf::Keyboard::Key down_key);

  int get_paddle_x();
  int get_paddle_y();

  bool paddle_collide(int ball_x_pos, int ball_y_pos);

  void paddle_update_movement(float dt);

  void paddle_stop(sf::Keyboard::Key up_key, sf::Keyboard::Key down_key, sf::Event event);

  float get_movement_control();

 private:
  int score = 0;
  int paddle_speed = 800;

  int paddle_x;
  int paddle_y;

  float movement_control = 0.0f;

};

#endif // PONGSFML_PADDLE_H
