#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

void checkCollision(float& xPositionBall, float& yPositionBall, float& BallSpeed, Sprite* block, int const MAX_NUMBER_OF_BLOCKS)
{
    int const HALF_BALL_SIZE = 3;
    int const BALL_SIZE = 6;

    int const REMOVE_BLOCK = -100;
    for (int checkBlockCollisionWithBall = 0; checkBlockCollisionWithBall < MAX_NUMBER_OF_BLOCKS; checkBlockCollisionWithBall++)
    {
        FloatRect ballShape = FloatRect(xPositionBall + HALF_BALL_SIZE, yPositionBall + HALF_BALL_SIZE, BALL_SIZE, BALL_SIZE);
        if (ballShape.intersects(block[checkBlockCollisionWithBall].getGlobalBounds()))
        {
            block[checkBlockCollisionWithBall].setPosition(REMOVE_BLOCK, 0); BallSpeed = -BallSpeed;
        }
    }
}

void draw(RenderWindow& app, Sprite& spriteBackground, Sprite& spriteBall, Sprite& spritePaddle, Sprite* block, int const& MAX_NUMBER_OF_BLOCKS)
{
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

int arkanoid()
{
    srand(time(0));

    int const MAX_WIDTH_SCREEN = 520;
    int const MAX_HEIGHT_SCREEN = 450;

    RenderWindow app(VideoMode(MAX_WIDTH_SCREEN, MAX_HEIGHT_SCREEN), "Arkanoid!");
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

    if (xPositionBall < 0 || xPositionBall > MAX_WIDTH_SCREEN)
    {
        xBallSpeed = -xBallSpeed;
    }
    if (yPositionBall < 0 || yPositionBall > MAX_HEIGHT_SCREEN)
    {
        yBallSpeed = -yBallSpeed;
    }

    int const PADDLE_SPEED = 6;

    if (Keyboard::isKeyPressed(Keyboard::Right))
    {
        spritePaddle.move(PADDLE_SPEED, 0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        spritePaddle.move(-PADDLE_SPEED, 0);
    }

    int const HEIGHT_OF_BALL = 12;

    if (FloatRect(xPositionBall, yPositionBall, HEIGHT_OF_BALL, HEIGHT_OF_BALL).intersects(spritePaddle.getGlobalBounds()))
    {
        yBallSpeed = -(rand() % 5 + 2); //Number between 2 and 6
    }

    spriteBall.setPosition(xPositionBall,yPositionBall);

    draw(app, spriteBackground, spriteBall, spritePaddle, block, MAX_NUMBER_OF_BLOCKS);
    }

  return 0;
}
