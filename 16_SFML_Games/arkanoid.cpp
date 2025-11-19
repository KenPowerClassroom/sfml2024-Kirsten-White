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
    int const WIDTH_OF_BLOCK = 43;
    int const HEIGHT_OF_BLOCK = 20;

    Sprite block[MAX_NUMBER_OF_BLOCKS];

    int const MAX_ROW = 10;
    int const MAX_COLUMN = 10;

    int numberOfCurrentBlock=0;
    for (int currentColumn = 1; currentColumn <= MAX_ROW; currentColumn++)
    {
        for (int currentRow = 1; currentRow <= MAX_COLUMN; currentRow++)
        {
            block[numberOfCurrentBlock].setTexture(textureBlock);
            block[numberOfCurrentBlock].setPosition(currentColumn * WIDTH_OF_BLOCK, currentRow * HEIGHT_OF_BLOCK);
            numberOfCurrentBlock++;
        }
    }

    float xBallSpeed=6, yBallSpeed=5;
    float x=300, y=300;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    x+=xBallSpeed;
    for (int i=0;i< numberOfCurrentBlock;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); xBallSpeed=-xBallSpeed;}

    y+=yBallSpeed;
    for (int i=0;i< numberOfCurrentBlock;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) ) 
             {block[i].setPosition(-100,0); yBallSpeed=-yBallSpeed;}

    if (x<0 || x>520)  xBallSpeed=-xBallSpeed;
    if (y<0 || y>450)  yBallSpeed=-yBallSpeed;

    if (Keyboard::isKeyPressed(Keyboard::Right)) spritePaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) spritePaddle.move(-6,0);

    if ( FloatRect(x,y,12,12).intersects(spritePaddle.getGlobalBounds()) ) yBallSpeed=-(rand()%5+2);

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