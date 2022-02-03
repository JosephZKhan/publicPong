#ifndef PONG_GAME_H
#define PONG_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event, float dt);
  void keyReleased(sf::Event event, float dt);

 private:

  bool on_title_screen = true;
  bool on_game_screen = false;
  bool on_game_over_screen = false;

  sf::RenderWindow& window;
  

  sf::Sprite middle_line;
  sf::Texture middle_line_texture;


  sf::Font font;

  sf::Text greeting_text;
  sf::Text begin_text;
  sf::Text game_over_text;
  sf::Text player_one_score_text;
  sf::Text player_two_score_text;


};

#endif // PONG_GAME_H
