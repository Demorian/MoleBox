/*
    Copyright (c) 2012 Paul Brown mafiamole@gmail.com

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef SFMLGAME_H
#define SFMLGAME_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "SFML_ContainerDefinitions.h"
/**
 * 
 * forward declarations
 *
 */
class SFMLGameComponent; 

/**
 * Typedef declarations for useful shorthands.
 * Those generic containers can be rather verbose
 */
typedef std::vector<SFMLGameComponent *> ComponentVector;

class SFMLGame
{
  
private:

  /**
   * SFML render window object.
   */
  sf::RenderWindow*	window;
  
protected:
  /**
   * Components container contains an list of components.
   */
  ComponentVector 	components;  
  /**
   * Method that is used to add a new game component to the game loop
   */
  void 			AddComponent	( SFMLGameComponent * component );
  /**
   * Method that returns the number of components already assigned to the game loop.
   */
  int 			ComponentCount	();
public:
  
  /**
   * The constructor requires the games window title to perform initalisation of the sf::RenderWindow object.
   */
			SFMLGame	( std::string windowName );
  /**
   * Deletes all components from memory.
   */
  virtual 		~SFMLGame	();
  /**
   * Method for obtaining the sf::RenderWindow instance in this class.
   * This is to allow components to draw to the window.
   */
  sf::RenderWindow * 	Window		();
  /**
   * Called once per loop.
   * The update function accepts events from the window poll event loop construct.
   * It also calls the update method of each component.
   */
  virtual void 		Update		( EventList *events );
  /**
   * Called once per loop.
   * This calls the Draw method of each component.
   */
  virtual void 		Draw 		();
  /**
   * Contains the game loop
   */
  virtual void 		Run		();

};

#endif // SFMLGAME_H