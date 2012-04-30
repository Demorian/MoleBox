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


#include "testcomponent.h"
#include <iostream>

TestComponent::TestComponent(SFMLGame* game): SFMLGameComponent(game)
{
  texture 	= Content< sf::Texture >::Load( "test.png" );
  sprite 	= sf::Sprite(texture);
  music		= Content< sf::Music >::Open( "menu.ogg" );
  musicPaused  = true;

  sound		= sf::Sound(Content< sf::SoundBuffer >::Load( "mouthpop.wav" ));
}

TestComponent::~TestComponent()
{
  music->stop();

}

void TestComponent::Update(EventList* events)
{
    SFMLGameComponent::Update(events);
    EventList::iterator found = events->find(sf::Event::KeyReleased);
    if (found != events->end())
    {
      if ((*found).second.key.code == sf::Keyboard::Space)
      {
	  
	  if (musicPaused) {
	    music->play();
	    musicPaused = false;
	    std::cout << "Music playing" << std::endl;
	  }
	  else {
	    music->pause();
	    musicPaused = true;
	    std::cout << "Music paused" << std::endl;

	  }
      }
      
    }
    found = events->find(sf::Event::KeyPressed);
    if (found != events->end())
    {
      if ( ( (*found).second.key.code == sf::Keyboard::Return ) )
      {
	sound.play();
      } 
    }
}

void TestComponent::Draw()
{

    this->game->Window()->draw(sprite);
    
    SFMLGameComponent::Draw();
    
}

