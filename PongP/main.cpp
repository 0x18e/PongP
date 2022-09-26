#include "reqs.h"




struct Players {
    sf::RectangleShape Player1;
    bool pl1Up = false;
    bool pl1Down = false;

    sf::RectangleShape Player2;
    bool pl2Up = false;
    bool pl2Down = false;


    float plSpeed;
};
struct Ball {
    sf::CircleShape ball;
    float ballSpeedX = -400.f;
    float ballSpeedY = 250.f;
};


void Restart(Ball& ball, Players &players) {
    if (GameMode == 0 || GameMode == 1) {
        ball.ballSpeedY = 0.f;
    }
    ball.ball.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
    players.Player1.setPosition(sf::Vector2f(0, 0));
    players.Player2.setPosition(sf::Vector2f(WINDOW_WIDTH - 20, WINDOW_HEIGHT - 150));
}
void InitBall(Ball& ball) {
    ball.ball.setFillColor(sf::Color::White);
    ball.ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    ball.ball.setPointCount(7.f);
    ball.ball.setRadius(15.f);
    if (GameMode == 0 | GameMode == 1) {
        ball.ballSpeedY = 0.f;
    }
    else {
        ball.ballSpeedY = 400.f;
    }
}
void initPlayers(Players &players) {
    players.Player1.setFillColor(sf::Color::White);
    players.Player1.setSize(sf::Vector2f(20, 150));
    players.plSpeed = 1500.f;
    players.Player1.setOutlineColor(sf::Color::Cyan);

    players.Player2.setFillColor(sf::Color::White);
    players.Player2.setSize(sf::Vector2f(20, 150));
    //players.Player2.setPosition(sf::Vector2f(WINDOW_WIDTH-20, WINDOW_HEIGHT-(150*4))); //math is cool, this sets the players to be on equal height
    players.Player2.setPosition(sf::Vector2f(WINDOW_WIDTH - 20, WINDOW_HEIGHT - 150));
    

}
//ai
/*
if (ball is above paddle) {
    move paddle up
}
if (ball is below paddle) {
    move paddle down
}
*/
void AI(Ball &ball, Players &players, float dt) {
    //checks if its above padle
    if (GameMode == 1 || GameMode == 2) {
        if (ball.ball.getPosition().y + ball.ball.getGlobalBounds().height < players.Player2.getPosition().y + players.Player2.getGlobalBounds().height) {
            players.Player2.move(sf::Vector2f(0, -players.plSpeed) * dt);

        }
        if (ball.ball.getPosition().y > players.Player2.getPosition().y + players.Player2.getGlobalBounds().height) {

            players.Player2.move(sf::Vector2f(0, players.plSpeed) * dt);
        }
    }
    if (GameMode == 2) {
        if (ball.ball.getPosition().y + ball.ball.getGlobalBounds().height < players.Player1.getPosition().y + players.Player1.getGlobalBounds().height) {
            players.Player1.move(sf::Vector2f(0, -players.plSpeed) * dt);

        }
        if (ball.ball.getPosition().y > players.Player1.getPosition().y + players.Player1.getGlobalBounds().height) {

            players.Player1.move(sf::Vector2f(0, players.plSpeed) * dt);
        }
    }
}
void handleMovement(Players &players, float dt) {
    players.pl1Down = false;
    players.pl1Up = false;
    players.pl2Down = false;
    players.pl2Up = false;
    if (GameMode == 1 || GameMode == 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            players.Player1.move(sf::Vector2f(0, -players.plSpeed) * dt);
            players.pl1Up = true;
            players.pl1Down = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            players.Player1.move(sf::Vector2f(0, players.plSpeed) * dt);
            players.pl1Down = true;
            players.pl1Up = false;
        }

        //might have to add an else to make both booleans false
        if (GameMode == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                players.Player2.move(sf::Vector2f(0, -players.plSpeed) * dt);
                players.pl2Up = true;
                players.pl2Down = false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                players.Player2.move(sf::Vector2f(0, players.plSpeed) * dt);
                players.pl2Up = false;
                players.pl2Down = true;
            }
        }
    }
}
void checkCollision(Players &players) {
    //player1 screenCollision
    if (players.Player1.getPosition().y < 0.f) {
        players.Player1.setPosition(sf::Vector2f(0, 0));
    }
    if (players.Player1.getPosition().y + players.Player1.getGlobalBounds().height >= WINDOW_HEIGHT) {
        players.Player1.setPosition(sf::Vector2f(0, WINDOW_HEIGHT - players.Player1.getGlobalBounds().height));
    }
    //player2 screenCollision
    if (players.Player2.getPosition().y < 0.f) {
        players.Player2.setPosition(sf::Vector2f(players.Player2.getPosition().x, 0));
    }
    if (players.Player2.getPosition().y + players.Player2.getGlobalBounds().height > WINDOW_HEIGHT) {
        players.Player2.setPosition(sf::Vector2f(players.Player2.getPosition().x, WINDOW_HEIGHT - players.Player2.getGlobalBounds().height));
    }
}
void BallMovement(Ball& ball, float dt) {
    ball.ball.move(sf::Vector2f(ball.ballSpeedX, ball.ballSpeedY)*dt);
}
void Scoring(Ball &ball, sf::Font &font, sf::Text &text, Players &players, int &LEFT_SCORE, int &RIGHT_SCORE) {
    bool scored = false;
    if (ball.ball.getPosition().x <= 0) {
        RIGHT_SCORE += 1;
        Restart(ball, players);
        
    }
    if (ball.ball.getPosition().x >= WINDOW_WIDTH + 10) {
        LEFT_SCORE += 1;
        Restart(ball, players);
    }
   
    std::string c = std::to_string(LEFT_SCORE) + "V" + std::to_string(RIGHT_SCORE);
    text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, 10));
    text.setString(c);
}

sf::Font LoadFont() {
    sf::Font font;
    bool success = true;
    if (!font.loadFromFile("font/ARCADECLASSIC.TTF")) {
        LOG("error loading font");
        success = false;
    }
    else {
        LOG("loaded font successfully");
        success = true;
    }
    return font;
    
}
void BallCollision(Ball &ball, Players &players) {
    //screencollision

    if (ball.ball.getPosition().y < 0) {
        LOG("hit TOP");
        ball.ball.setPosition(sf::Vector2f(ball.ball.getPosition().x, ball.ball.getPosition().y + 10));
        ball.ballSpeedY = -ball.ballSpeedY;
    }
    if (ball.ball.getPosition().y + ball.ball.getGlobalBounds().height > WINDOW_HEIGHT) {
        ball.ball.setPosition(sf::Vector2f(ball.ball.getPosition().x, ball.ball.getPosition().y - 10));
        ball.ballSpeedY = -ball.ballSpeedY;
    }

    //if collided with player1
    if (ball.ball.getGlobalBounds().intersects(players.Player1.getGlobalBounds()) && players.pl1Up == true) {
        LOG("hit player 1");
        ball.ballSpeedX = -ball.ballSpeedX;
        ball.ballSpeedY = -1000.f;
    }
    else if (ball.ball.getGlobalBounds().intersects(players.Player1.getGlobalBounds()) && players.pl1Down == true) {
        LOG("hit player 1");
        ball.ballSpeedX = -ball.ballSpeedX;
        ball.ballSpeedY = 1000.f;
    }
    else if (ball.ball.getGlobalBounds().intersects(players.Player1.getGlobalBounds())) {
        LOG("hit player 1X");
        ball.ballSpeedX = -ball.ballSpeedX;
    }
    
    //if collided with player2 
    if (ball.ball.getGlobalBounds().intersects(players.Player2.getGlobalBounds()) && players.pl2Up == true) {
        LOG("hit player 2");
        ball.ballSpeedX = -ball.ballSpeedX;
        ball.ballSpeedY = -1000.f;
    }
    else if (ball.ball.getGlobalBounds().intersects(players.Player2.getGlobalBounds()) && players.pl2Down == true) {
        LOG("hit player 2d");
        ball.ballSpeedX = -ball.ballSpeedX;
        ball.ballSpeedY = 1000.f;
    }
    else if (ball.ball.getGlobalBounds().intersects(players.Player2.getGlobalBounds())) {
        LOG("hit player 2X");
        ball.ballSpeedX = -ball.ballSpeedX;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2-PlayerPong");
    Players players;
    Ball ball;
    sf::Text text;
    initPlayers(players);
    InitBall(ball);
    sf::Font fontloaded = LoadFont();
    text.setFont(fontloaded);
    sf::Clock clock;
    int left_Score = 0;
    int right_Score = 0;
    sf::Text text2;
    text2.setFont(fontloaded);
    //text2.setString("lol");
    text2.setPosition(WINDOW_WIDTH / 5, WINDOW_HEIGHT / 2);
    text2.setCharacterSize(55);
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Scoring(ball, fontloaded, text, players, left_Score, right_Score);
        BallCollision(ball, players);
        BallMovement(ball, dt);
        AI(ball, players, dt);
        handleMovement(players, dt);
        checkCollision(players);
        window.clear();
        window.draw(text);
        window.draw(text2);
        window.draw(ball.ball);
        window.draw(players.Player1);
        window.draw(players.Player2);
        window.display();
    }

    return 0;
}