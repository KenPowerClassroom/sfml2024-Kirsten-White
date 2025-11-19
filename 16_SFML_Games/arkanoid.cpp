#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int arkanoid()
{
    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    Texture textureBlock,textureBackground,textureBall,texturePaddle;
    textureBlock.loadFromFile("images/arkanoid/block01.png");
    textureBackground.loadFromFile("images/arkanoid/background.jpg");
    textureBall.loadFromFile("images/arkanoid/ball.png");
    texturePaddle.loadFromFile("images/arkanoid/paddle.png");

    Sprite spriteBackground(textureBackground), spriteBall(textureBall), spritePaddle(texturePaddle);
    spritePaddle.setPosition(300,440);

    int const MAX_NUMBER_OF_BLOCKS = 100;

    Sprite block[MAX_NUMBER_OF_BLOCKS];

    int const MAX_ROW = 10;
    int const MAX_COLUMN = 10;

    int numberOfCurrentBlock=0;
    for (int currentRow = 1; currentRow <= MAX_ROW; currentRow++)
    {
        for (int currentColumn = 1; currentColumn <= MAX_COLUMN; currentColumn++)
        {
            block[numberOfCurrentBlock].setTexture(textureBlock);
            block[numberOfCurrentBlock].setPosition(currentRow * 43, currentColumn * 20);
            numberOfCurrentBlock++;
        }
    }

    float dx=6, dy=5;
    float x=300, y=300;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    x+=dx;
    for (int i=0;i< numberOfCurrentBlock;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dx=-dx;}

    y+=dy;
    for (int i=0;i< numberOfCurrentBlock;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); dy=-dy;}

    if (x<0 || x>520)  dx=-dx;
    if (y<0 || y>450)  dy=-dy;

    if (Keyboard::isKeyPressed(Keyboard::Right)) spritePaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) spritePaddle.move(-6,0);

    if ( FloatRect(x,y,12,12).intersects(spritePaddle.getGlobalBounds()) ) dy=-(rand()%5+2);

    spriteBall.setPosition(x,y);

    app.clear();
    app.draw(spriteBackground);
    app.draw(spriteBall);
    app.draw(spritePaddle);

    for (int i = 0; i < numberOfCurrentBlock; i++)
    {
        app.draw(block[i]);
    }

    app.display();
    }

  return 0;
}