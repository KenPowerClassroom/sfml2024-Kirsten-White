#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

void checkCollision(float& xPositionBall, float& yPositionBall, float& BallSpeed, Sprite*block, int const MAX_NUMBER_OF_BLOCKS)
{
    for (int checkBlockCollisionWithBall = 0; checkBlockCollisionWithBall < MAX_NUMBER_OF_BLOCKS; checkBlockCollisionWithBall++)
    {
        if (FloatRect(xPositionBall + 3, yPositionBall + 3, 6, 6).intersects(block[checkBlockCollisionWithBall].getGlobalBounds()))
        {
            block[checkBlockCollisionWithBall].setPosition(-100, 0); BallSpeed = -BallSpeed;
        }
    }
}

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
    float xPositionBall=300, yPositionBall=300;

    while (app.isOpen())
    {
       Event gameOpened;
       while (app.pollEvent(gameOpened))
       {
           if (gameOpened.type == Event::Closed)
           {
               app.close();
           }
       }

    xPositionBall+=xBallSpeed;
    checkCollision(xPositionBall, yPositionBall, xBallSpeed, block, MAX_NUMBER_OF_BLOCKS);
    yPositionBall+=yBallSpeed;
    checkCollision(xPositionBall, yPositionBall, yBallSpeed, block, MAX_NUMBER_OF_BLOCKS);

    if (xPositionBall<0 || xPositionBall>520)  xBallSpeed=-xBallSpeed;
    if (yPositionBall<0 || yPositionBall>450)  yBallSpeed=-yBallSpeed;

    if (Keyboard::isKeyPressed(Keyboard::Right)) spritePaddle.move(6,0);
    if (Keyboard::isKeyPressed(Keyboard::Left)) spritePaddle.move(-6,0);

    if ( FloatRect(xPositionBall,yPositionBall,12,12).intersects(spritePaddle.getGlobalBounds()) ) yBallSpeed=-(rand()%5+2);

    spriteBall.setPosition(xPositionBall,yPositionBall);

    app.clear();
    app.draw(spriteBackground);
    app.draw(spriteBall);
    app.draw(spritePaddle);

    for (int currentBlock = 0; currentBlock < MAX_NUMBER_OF_BLOCKS; currentBlock++)
    {
        app.draw(block[currentBlock]);
    }

    app.display();
    }

  return 0;
}
