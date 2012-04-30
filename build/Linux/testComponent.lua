logoPosition = 0
direction    = 1

function init()
  Sprites.Load("Test","ufpdfLogo.png")
  Sounds.Load("mouthpop.wav")
  Sprites.Move("Test",10,10)
end

function update(events)
 --Sounds.Play("mouthpop.wav")-- o yea!
  delta = 0.2 * direction  
  logoPosition = (logoPosition * direction) + delta
  if logoPosition > 15 then
    direction = -1
    Sounds.Play("mouthpop.wav")
  end
  if logoPosition < 1 then
    
    direction = 1
  end

  Sprites.Move("Test",logoPosition,logoPosition)
  
end

function draw()
  Sprites.Draw("Test")
end 