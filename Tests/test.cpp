#include <gtest/gtest.h>
#include "../include/arkanoid.cpp"

// A simple mock of the Sprite class to isolate the test from the actual SFML graphics
class MockSprite : public sf::Sprite {
public:
	void setPosition(float x, float y) override {
		position = { x, y };
	}

	sf::Vector2f getPosition() const override {
		return position;
	}

	void setTexture(const sf::Texture&) override {}

	// Override the function for testing the collision
	sf::FloatRect getGlobalBounds() const override {
		return { position.x, position.y, 6.f, 6.f }; // Ball size for testing
	}

private:
	sf::Vector2f position;
};

// Test case for checking collision with blocks
TEST(GameTest, CheckCollisionBallWithBlock) {
	// Setup
	float ballX = 50.f, ballY = 50.f;
	float ballSpeed = 5.f;

	const int MAX_BLOCKS = 10;
	MockSprite blocks[MAX_BLOCKS];

	// Setup mock blocks
	for (int i = 0; i < MAX_BLOCKS; ++i) {
		blocks[i].setPosition(50.f + i * 10.f, 50.f); // Place blocks in a row
	}

	// Ball hits the first block
	blocks[0].setPosition(50.f, 50.f); // Collision should happen at position 50,50
	checkCollision(ballX, ballY, ballSpeed, blocks, MAX_BLOCKS);

	// Assert that ball's speed is reversed
	EXPECT_EQ(ballSpeed, -5.f);  // Ball speed should be negative after collision

	// Assert block "removed" (position set to REMOVE_BLOCK)
	EXPECT_EQ(blocks[0].getPosition().x, -100.f); // Block's X position should be REMOVE_BLOCK value
}

TEST(GameTest, CheckNoCollision) {
	float ballX = 200.f, ballY = 200.f;
	float ballSpeed = 5.f;

	const int MAX_BLOCKS = 10;
	MockSprite blocks[MAX_BLOCKS];

	// Setup blocks further from the ball (no collision expected)
	for (int i = 0; i < MAX_BLOCKS; ++i) {
		blocks[i].setPosition(500.f + i * 10.f, 500.f);
	}

	// Ball moves without hitting any block
	checkCollision(ballX, ballY, ballSpeed, blocks, MAX_BLOCKS);

	// Assert ball speed has not changed
	EXPECT_EQ(ballSpeed, 5.f);  // Ball speed should remain positive

	// Assert no block was "removed"
	for (int i = 0; i < MAX_BLOCKS; ++i) {
		EXPECT_NE(blocks[i].getPosition().x, -100.f);
	}
}

TEST(GameTest, BallAndPaddleCollision) {
	float ballX = 250.f, ballY = 400.f;
	float ballSpeedY = 5.f;
	sf::Sprite spritePaddle;

	// Set up paddle
	spritePaddle.setPosition(200.f, 440.f); // Paddle at the bottom

	// Simulate ball colliding with paddle (set ball position to touch the paddle)
	if (sf::FloatRect(ballX, ballY, 12.f, 12.f).intersects(spritePaddle.getGlobalBounds())) {
		ballSpeedY = -(rand() % 5 + 2);  // Random speed between 2 and 6
	}

	// Check if ball's vertical speed is reversed (since it hit the paddle)
	EXPECT_LT(ballSpeedY, 0.f);  // The ball should go up after hitting the paddle
}

TEST(GameTest, BallPositionAndSpeedUpdate) {
	float ballX = 300.f, ballY = 300.f;
	float xBallSpeed = 6.f, yBallSpeed = 5.f;
	int screenWidth = 520, screenHeight = 450;

	// Simulate ball movement
	ballX += xBallSpeed;
	ballY += yBallSpeed;

	// Simulate wall collision (ball should reverse speed when it hits the screen border)
	if (ballX < 0 || ballX > screenWidth) {
		xBallSpeed = -xBallSpeed;
	}
	if (ballY < 0 || ballY > screenHeight) {
		yBallSpeed = -yBallSpeed;
	}

	// Assert that ball is updated correctly
	EXPECT_EQ(ballX, 306.f);  // 300 + 6
	EXPECT_EQ(ballY, 305.f);  // 300 + 5

	// Check if the ball would bounce off the walls correctly
	EXPECT_EQ(xBallSpeed, 6.f);  // Should be positive as no collision with left/right wall
	EXPECT_EQ(yBallSpeed, 5.f);  // Should be positive as no collision with top/bottom wall
}

TEST(GameTest, BlockPositioning) {
	const int MAX_ROW = 10;
	const int MAX_COLUMN = 10;
	const int WIDTH_OF_BLOCK = 43;
	const int HEIGHT_OF_BLOCK = 20;

	MockSprite blocks[MAX_ROW * MAX_COLUMN];

	int blockIndex = 0;
	for (int column = 1; column <= MAX_ROW; ++column) {
		for (int row = 1; row <= MAX_COLUMN; ++row) {
			blocks[blockIndex].setPosition(column * WIDTH_OF_BLOCK, row * HEIGHT_OF_BLOCK);
			blockIndex++;
		}
	}

	// Check the position of the first block
	EXPECT_EQ(blocks[0].getPosition().x, 43.f);  // First column, first row
	EXPECT_EQ(blocks[0].getPosition().y, 20.f);

	// Check the position of the last block
	EXPECT_EQ(blocks[MAX_ROW * MAX_COLUMN - 1].getPosition().x, 430.f);  // Last column, last row
	EXPECT_EQ(blocks[MAX_ROW * MAX_COLUMN - 1].getPosition().y, 200.f);
}