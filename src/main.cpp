/*
    This file is part of my_paint
    Copyright (C) 2014  Julien Thevenon ( julien_thevenon at yahoo.fr )

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
*/
#include "simple_gui.h"
#include <iostream>

#include <unistd.h>

void draw_line(simple_gui & p_gui, uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2,uint32_t p_color)
{
  if(y1 == y2)
    {
      for(uint32_t l_x = x1 ; l_x <= x2; ++l_x)
        {
          p_gui.setPixel(l_x,y1,p_color);
        }
    }
  else if(x1 == x2)
    {
      for(uint32_t l_y = y1 ; l_y <= y2; ++l_y)
        {
          p_gui.setPixel(x1,l_y,p_color);
        }
    }
  else
    {
      uint32_t l_delta_x = (x1 < x2 ? 1 : -1 );
      uint32_t l_delta_y = (y1 < y2 ? 1 : -1 );
      uint32_t l_x = x1;
      uint32_t l_y = y1;
      if(abs(x2-x1) == abs(y2-y1))
        {
          while(l_x != x2)
            {
              p_gui.setPixel(l_x,l_y,p_color);
              l_x += l_delta_x;
              l_y += l_delta_y;
            }
        }
      else
        {
          int32_t l_diff_x = x2 -x1;
          int32_t l_diff_y = y2 -y1;
          if(l_diff_x != 0)
            {
              if(l_diff_x > 0)
                {
                  if(l_diff_y != 0 )
                    {
                      if(l_diff_y > 0)
                        {
                          // vecteur oblique dans le 1er quadran
                          if(l_diff_x >= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 1er octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2;
                              l_diff_y = l_diff_y * 2; //positive cumulated_error
                              while((x1 = x1 + 1) != x2)  // déplacements horizontaux
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_y) < 0)
                                    {
                                      y1 = y1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 2nd octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ;
                              l_diff_x = l_diff_x * 2 ;  // positive cumulated_error
                              while((y1 = y1 + 1) != y2)  // vertical moves
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_x) < 0)
                                    {
                                      x1 = x1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                      else
                        { 
                          // l_diff_y < 0 (et l_diff_x > 0)
                          // vecteur oblique dans le 4e cadran
                          if(l_diff_x >= -l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 8e octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2 ;
                              l_diff_y = l_diff_y * 2 ;  // cumulated_error est positif
                              while((x1 = x1 + 1) != x2)// déplacements horizontaux
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_y) < 0)
                                    {
                                      y1 = y1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 7e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // negative cumulated_error
                              while((y1 = y1 - 1) != y2)  // vertical moves
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_x) > 0)
                                    {
                                      x1 = x1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                    }
                  else
                    {  // l_diff_y = 0 (et l_diff_x > 0)
                      
                      // vecteur horizontal vers la droite
                      while((x1 = x1 + 1) != x2)
                        {
                          p_gui.setPixel(x1,y1,p_color);
                        }
                      
                    }
                }
              else
                {
                  // l_diff_x < 0
                  if(l_diff_y != 0)
                    {
                      if(l_diff_y > 0)
                        {
                          // vecteur oblique dans le 2nd quadran
                          if(-l_diff_x >= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 4e octant
                              int32_t cumulated_error = l_diff_x ;
                              l_diff_x = cumulated_error * 2 ;
                              l_diff_y = l_diff_y * 2 ;  // negative cumulated_error
                              while((x1 = x1 - 1) != x2)  // déplacements horizontaux
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_y) >= 0)
                                    {
                                      y1 = y1 + 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 3e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // positive cumulated_error
                              while((y1 = y1 + 1) != y2)  // vertical moves
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error + l_diff_x) <= 0)
                                    {
                                      x1 = x1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
                        }
                      else
                        {
                          // l_diff_y < 0 (et l_diff_x < 0)
                          // vecteur oblique dans le 3e cadran
                          if(l_diff_x <= l_diff_y)
                            {
                              // vecteur diagonal ou oblique proche de l?horizontale, dans le 5e octant
                              int32_t cumulated_error = l_diff_x;
                              l_diff_x = cumulated_error * 2 ; 
                              l_diff_y = l_diff_y * 2 ;  // negative cumulated_error
                              while((x1 = x1 - 1) != x2)  // déplacements horizontaux
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_y) >= 0)
                                    {
                                      y1 = y1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_x ;
                                    }
                                }
                            }
                          else
                            {
                              // vecteur oblique proche de la verticale, dans le 6e octant
                              int32_t cumulated_error = l_diff_y;
                              l_diff_y = cumulated_error * 2 ; 
                              l_diff_x = l_diff_x * 2 ;  // negative cumulated_error
                              while((y1 = y1 - 1) != y2 )  // vertical moves
                                {
                                  p_gui.setPixel(x1,y1,p_color);
                                  if((cumulated_error = cumulated_error - l_diff_x) >= 0)
                                    {
                                      x1 = x1 - 1 ;  // diagonal move
                                      cumulated_error = cumulated_error + l_diff_y ;
                                    }
                                }
                            }
          
                        }
                    }
                  else
                    {
                      // l_diff_y = 0 (et l_diff_x < 0)
                      // vecteur horizontal vers la gauche
                      while((x1 = x1 - 1) != x2)
                        {
                          p_gui.setPixel(x1,y1,p_color);
                        }
                    }
                }
            }
          else
            {
              // l_diff_x = 0
              if(l_diff_y != 0)
                {
                  if(l_diff_y > 0)
                    {
                      // vecteur vertical croissant
                      while((y1 = y1 + 1) != y2)
                        {
                          p_gui.setPixel(x1,y1,p_color);
                        }
                    }
                  else
                    {
                      // l_diff_y < 0 (et l_diff_x = 0)
                      // vecteur vertical décroissant
                      while((y1 = y1 - 1) != y2)
                        { 
                          p_gui.setPixel(x1,y1,p_color);
                        }

                    }
                }
            }

        }
    }
}

int main(void)
{
  simple_gui l_gui;
  l_gui.createWindow(640,480);
  uint32_t l_red = l_gui.getColorCode(255,0,0);
  draw_line(l_gui,0,0,100,0,l_red);
  uint32_t l_blue = l_gui.getColorCode(0,0,255);
  draw_line(l_gui,45,25,45,75,l_blue);
  uint32_t l_green = l_gui.getColorCode(0,255,0);
  draw_line(l_gui,10,10,30,30,l_green);
  draw_line(l_gui,20,50,30,40,l_green);

  // First quadrant
  draw_line(l_gui,320,240,480,120,l_blue);
  draw_line(l_gui,320,240,480,80,l_red);
  draw_line(l_gui,320,240,440,80,l_blue);

  // Second quadrant
  draw_line(l_gui,320,240,160,120,l_blue);
  draw_line(l_gui,320,240,160,80,l_red);
  draw_line(l_gui,320,240,200,80,l_blue);

  // Third quadrant
  draw_line(l_gui,320,240,160,360,l_blue);
  draw_line(l_gui,320,240,160,400,l_red);
  draw_line(l_gui,320,240,200,400,l_blue);

  // Fourth quadrant
  draw_line(l_gui,320,240,480,360,l_blue);
  draw_line(l_gui,320,240,480,400,l_red);
  draw_line(l_gui,320,240,440,400,l_blue);

  l_gui.refresh();
  sleep(2);
  return 0;
}
