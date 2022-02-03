#include "Game.h"
#include "Ball.h"
#include "Ball.cpp"
#include "Paddle.h"
#include "Paddle.cpp"
#include <iostream>

//initialise 1 ball object and 2 paddle objects

Ball ball_1;
Paddle paddle_1;
Paddle paddle_2;

//initialise game_window
Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

//initialise game objects
bool Game::init()
{
  //apply a texture to the ball_1 sprite and set its position to the middle of the screen
  ball_1.set_ball_texture("Data/Images/ball_3.png");
  ball_1.set_ball_sprite(window.getSize().x / 2, window.getSize().y / 2);

  //Load the paddle 1 texture, set its position
  paddle_1.set_paddle_texture("Data/Images/paddle_1.png");
  paddle_1.set_paddle_sprite(100, 350);

  //Load the paddle 2 texture, set its position
  paddle_2.set_paddle_texture("Data/Images/paddle_2.png");
  paddle_2.set_paddle_sprite(980, 350);


  //---INITIALISE FONT---
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  //---INITIALISE ALL TEXT---
  greeting_text.setString("WHACK-BAT 9000");
  greeting_text.setFont(font);
  greeting_text.setCharacterSize(70);
  greeting_text.setFillColor(sf::Color(255,0,0,255));
  greeting_text.setPosition(250, 100);

  begin_text.setString("            PRESS ENTER TO START.\nPRESS ESC TO CLOSE THE WINDOW ANYTIME.");
  begin_text.setFont(font);
  begin_text.setCharacterSize(30);
  begin_text.setFillColor(sf::Color(255,0,0,255));
  begin_text.setPosition(225, 400);

  player_one_score_text.setString("0");
  player_one_score_text.setFont(font);
  player_one_score_text.setCharacterSize(50);
  player_one_score_text.setFillColor(sf::Color(255,0,0,255));
  player_one_score_text.setPosition(100, 10);

  player_two_score_text.setString("0");
  player_two_score_text.setFont(font);
  player_two_score_text.setCharacterSize(50);
  player_two_score_text.setFillColor(sf::Color(0,255,255,255));
  player_two_score_text.setPosition(980, 10);

  game_over_text.setString("Neutral victory message");
  game_over_text.setFont(font);
  game_over_text.setCharacterSize(70);
  game_over_text.setFillColor(sf::Color(255,255,255,255));
  game_over_text.setPosition(200, 200);

  //Load the middle line texture, return error message if loading fails
  if (!middle_line_texture.loadFromFile("Data/Images/middle_line.png"))
  {
    std::cout << "middle line texture failed to load";
  }

  //Set the texture of middle line
  middle_line.setTexture(middle_line_texture);
  //Initialise middle line's position
  middle_line.setPosition((window.getSize().x / 2), 0);

  //return true to show initialisation was successful
  return true;
}

void Game::update(float dt)
{
  //if the player is on the game screen
  if (on_game_screen)
  {

    //unless the paddle tries moving up while at the top of the screen
    if(!(paddle_1.get_movement_control() == -1.0f and paddle_1.paddle_sprite.getPosition().y <= 0))
    {
      //or down while at the bottom
      if(!(paddle_1.get_movement_control() == 1.0f and paddle_1.paddle_sprite.getPosition().y + paddle_1.paddle_sprite.getGlobalBounds().height >= 720)) {
        //move the paddle every frame - regardless of whether or not the position actually changes
        //this is how smoother movement is achieved
        paddle_1.paddle_update_movement(dt);
      }
    }

    //same as above, for paddle 2
    if(!(paddle_2.get_movement_control() == -1.0f and paddle_2.paddle_sprite.getPosition().y <= 0))
    {
      if(!(paddle_2.get_movement_control() == 1.0f and paddle_2.paddle_sprite.getPosition().y + paddle_2.paddle_sprite.getGlobalBounds().height >= 720)) {
        paddle_2.paddle_update_movement(dt);
      }
    }

    //if the ball reaches the top or bottom of the screen
    if (((ball_1.ball_sprite.getPosition().y) <= 0) or (ball_1.ball_sprite.getPosition().y + ball_1.ball_sprite.getGlobalBounds().height >= window.getSize().y))
    {
      //reverse the y component of the direction vector
      //changing the ball's vertical direction so it bounces up or down
      ball_1_direction.reverse_y();
    }

    //get the ball's current x and y coordinates
    //for collision with paddles below
    int current_ball_x = ball_1.ball_sprite.getPosition().x;
    int current_ball_y = ball_1.ball_sprite.getPosition().y;

    //if the paddle_collide function returns true for paddle_1
    if (paddle_1.paddle_collide(current_ball_x, current_ball_y) == true)
    {
      //reverse the ball's horizontal movement
      ball_1_direction.reverse_x();

      //alter the ball's texture making it red
      ball_1.set_ball_texture("Data/Images/ball_1.png");

      //increase the ball's speed
      ball_1.speed_up();

      //randomly change the ball's vertical movement
      ball_1_direction.randomise_y();
    }

    //if the paddle_collide function returns true for paddle_2
    if (paddle_2.paddle_collide(current_ball_x, current_ball_y) == true)
    {
      //reverse the ball's horizontal movement
      ball_1_direction.reverse_x();

      //alter the ball's texture making it red
      ball_1.set_ball_texture("Data/Images/ball_2.png");

      //increase the ball's speed
      ball_1.speed_up();

      //randomly change the ball's vertical movement
      ball_1_direction.randomise_y();
    }


    //if the ball reaches the left of the screen
    //meaning paddle 2 has scored a point
    if (ball_1.ball_reach_left() == true)
    {
      //increase player two score
      paddle_2.score_increase();

      //if player two's score reaches 10:
      if (paddle_2.get_paddle_score() == 10)
      {
        //set the game over text to congratulate player 2
        game_over_text.setString("CONGRATULATIONS! \nPLAYER 2 WINS! \nPRESS ESCAPE TO QUIT.");
        game_over_text.setFillColor(sf::Color(0,255,255,255));
        //and move the player to the game over screen
        on_game_screen = false;
        on_game_over_screen = true;
      }

      //if the player's score remains less than 10
      else
      {
        //update the score display
        std::string player_two_score_string = std::to_string(paddle_2.get_paddle_score());
        player_two_score_text.setString(player_two_score_string);

        //change the colour of the middle line to the colour of the player who just scored
        if (!middle_line_texture.loadFromFile("Data/Images/middle_line_2.png"))
        {
          std::cout << "middle line texture failed to load";
        }

        // Set the texture of middle line
        middle_line.setTexture(middle_line_texture);

        //respawn the ball
        ball_1.spawn();
      }
    }

    //if the ball reaches the right side of the screen
    //meaning paddle 2 has scored a point
    //(the following is the same as above, but in the case of player 1 scoring)
    if (ball_1.ball_reach_right() == true)
    {
      paddle_1.score_increase();

      if (paddle_1.get_paddle_score() >= 10)
      {
        game_over_text.setString("CONGRATULATIONS! \nPLAYER 1 WINS! \nPRESS ESCAPE TO QUIT.");
        game_over_text.setFillColor(sf::Color(255,0,0,255));
        on_game_screen = false;
        on_game_over_screen = true;
      }

      else
      {
        std::string player_one_score_string = std::to_string(paddle_1.get_paddle_score());
        player_one_score_text.setString(player_one_score_string);

        if (!middle_line_texture.loadFromFile("Data/Images/middle_line_1.png"))
        {
          std::cout << "middle line texture failed to load";
        }

        middle_line.setTexture(middle_line_texture);

        ball_1.spawn();
      }
    }

    //finally, update the ball's position with the above changes in mind
    ball_1.ball_sprite.move(ball_1_direction.get_x() * ball_1.get_speed() * dt, ball_1_direction.get_y() * ball_1.get_speed() * dt);
  }
}

void Game::render()
{
  //if the player is on the title screen
  if (on_title_screen) {
    //draw the title screen content to the screen
    window.draw(greeting_text);
    window.draw(begin_text);
  }

  //if the game has ended
  if (on_game_over_screen) {
    //draw the game over text to screen
    window.draw(game_over_text);
  }

  //if the player is playing the game
  if (on_game_screen) {
    //draw the ball and paddles to the screen
    window.draw(middle_line);
    window.draw(ball_1.ball_sprite);
    window.draw(paddle_1.paddle_sprite);
    window.draw(paddle_2.paddle_sprite);
    window.draw(player_one_score_text);
    window.draw(player_two_score_text);
  }
}

void Game::keyPressed(sf::Event event, float dt)
{
  // if the player presses enter on the title screen
  if (event.key.code == sf::Keyboard::Enter and on_title_screen)
  {
    // exit the title screen to begin the game
    on_title_screen = false;
    on_game_screen  = true;
  }


  // if the player presses the Escape key at any time
  if (event.key.code == sf::Keyboard::Escape)
  {
    // close the window
    window.close();
  }

  // if the player has exited the title screen
  if (on_game_screen)
  {
    //paddle_move function handles movement of the paddles. taking in the keys passed in as up and down keys
    paddle_1.paddle_move(sf::Keyboard::W, sf::Keyboard::S);
    paddle_2.paddle_move(sf::Keyboard::Up, sf::Keyboard::Down);
  }
}

//if a key has been released
void Game::keyReleased(sf::Event event, float dt){
  //stop the paddles using the paddle_stop function
  paddle_1.paddle_stop(sf::Keyboard::W, sf::Keyboard::S, event);
  paddle_2.paddle_stop(sf::Keyboard::Up, sf::Keyboard::Down, event);
}
