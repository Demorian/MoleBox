/*
    Copyright (c) 2012 Paul Brown <email>

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


#include "keyboard.h"
#include <iostream>

using namespace MB;

Keyboard::Keyboard(sf::Keyboard::Key key)
{
  this->key = key;
  this->keyDown = false;//sf::Keyboard::isKeyPressed(key);
  this->keyPressed = this->keyDown;
  std::cout <<"initiate! " << this->keyDown << std::endl;
}

Keyboard::~Keyboard()
{

}


void Keyboard::Update()
{
  bool keyPressedGrab = sf::Keyboard::isKeyPressed(key);
  
  if ( this->keyPressed != keyPressedGrab )
  {
    
    this->keyPressed = keyPressedGrab;
    
    this->keyDown = !this->keyDown;
    
  }
}

bool Keyboard::IsActive()
{
    return sf::Keyboard::isKeyPressed(key);
}

bool Keyboard::HasChanged()
{
    return this->keyDown;
}


