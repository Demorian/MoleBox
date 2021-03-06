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
#ifndef SFMLCONTENT_H
#define SFMLCONTENT_H

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "ContentTemplate.h"

/**
 * Template class to add sf::Texture as a loadable content.
 * 
 */
namespace MB {
  
  template <> class ContentContainer <sf::Texture> {
    
  private:
    /**
    *  Container for all sf::Texture in the game.
    */
    std::map< std::string , sf::Texture > textures;

  public:
    /**
    * Obtains a static instance of this class. A static instance ensures a single copy of it at run time.
    */
    static ContentContainer < sf::Texture >& I()
    {
      
      static ContentContainer < sf::Texture > instance;
      
      return instance;
      
    }
    /**
    * Used to load a sf::Texture from a given filesystem location.
    */
    const sf::Texture& Load(std::string reference)
    {

      if ( this->textures.find( reference ) == this->textures.end() )
      {
	
	sf::Texture texture;
	
	if ( !texture.loadFromFile( reference ) )
	  throw std::string ( "Unable to load texture: " + reference );
	
	this->textures.insert( std::pair< std::string , sf::Texture> ( reference , texture) );

	
      }
      
      return this->textures[reference];

      
    }
    
  };

  template <> class ContentContainer <sf::SoundBuffer> {
    
  private:
    /**
    *  Container for all sf::SoundBuffer's in the game.
    */
    std::map< std::string , sf::SoundBuffer > sounds;

  public:
    /**
    * Obtains a static instance of this class. A static instance ensures a single copy of it at run time.
    */
    static ContentContainer < sf::SoundBuffer >& I()
    {
      static ContentContainer < sf::SoundBuffer > instance;
      return instance;
    }
    /**
    * Used to load a sf::SoundBuffer from a given filesystem location.
    */
    const sf::SoundBuffer& Load(std::string reference)
    {

      if ( this->sounds.find(reference) == this->sounds.end() )
      {
	
	sf::SoundBuffer sound;
	
	if ( !sound.loadFromFile(reference) )
	  throw std::string ( "Unable to load " + reference );
	
	this->sounds.insert( std::pair< std::string , sf::SoundBuffer> ( reference , sound ) );
	
      }
      
      return this->sounds[reference];

    }
    
  };

  template <> class ContentContainer <sf::Music> {
    
  private:
    /**
    *  Container for all sf::Music in the game.
    */
    std::map< std::string , sf::Music *> music;

  public:
    
    ~ContentContainer < sf::Music > ()
    {
      std::map< std::string , sf::Music *>::iterator musicIterator;
      
      for ( musicIterator = music.begin(); musicIterator != music.end(); musicIterator++ )
      {
	delete ( *musicIterator ).second;
      }
      music.clear();

    }
    
    /**
    * Obtains a static instance of this class. A static instance ensures a single copy of it at run time.
    */
    static ContentContainer < sf::Music >& I()
    {
      
      static ContentContainer < sf::Music > instance;
      
      return instance;
      
    }
    
    /**
    * Used to load a sf::Music from a given filesystem location.
    */
    sf::Music* Load(std::string reference)
    {
      if ( this->music.find(reference) == this->music.end() )
      {
	
	this->music.insert( std::pair< std::string , sf::Music*> ( reference , new sf::Music() ) );
	
	if ( !this->music[reference]->openFromFile( reference ) )
	{
	  
	  this->music.erase( reference );
	  
	  throw std::string ( "Unable to load " + reference );
	  
	}

      }

      
      return this->music[reference];

    }
    
  };


  class SpriteBatch : public sf::Drawable, public std::vector<sf::Drawable *> {
    
  private:
    sf::RenderTarget* target;
    sf::RenderStates renderState;
    //sf::RenderTexture renderTexture;
    void initiate(sf::Vector2u size, sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);
  public:
    SpriteBatch(sf::Vector2u size, sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);  
    SpriteBatch(sf::RenderTarget* target, sf::RenderStates states = sf::RenderStates::Default);
    
    ~SpriteBatch();
    
    void SetRenderState(sf::RenderStates states = sf::RenderStates::Default);
    void Draw();
    void draw(sf::RenderTarget& target,const sf::RenderStates states = sf::RenderStates::Default) const;
  };
}
#endif