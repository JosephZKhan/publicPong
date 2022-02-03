//
// Created by Joseph Khan on 07/01/2021.
//

#ifndef PONGSFML_VECTOR_H
#define PONGSFML_VECTOR_H
#include <vector>

class Vector
{
 public:

  int get_random_number(int min, int max);

  float get_x();
  void reverse_x();

  float get_y();
  void set_y(float new_y);
  void reverse_y();
  void randomise_y();

 private:
  float x = -10;
  float y = 0;

};

#endif // PONGSFML_VECTOR_H
