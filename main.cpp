#include <SFML/Graphics.hpp>
#include "Snake.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(832, 704), "Snake");//size mus be multiple of 64
    window.setFramerateLimit(8);

    sf::Event event;
    srand(clock());

    sf::Font font;
    if(!font.loadFromFile("DejaVuSans.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Points: 0", font);
    text.setPosition(0, 0);

    Snake snake;

    sf::Texture appleT;
    appleT.loadFromFile("snake.png", sf::IntRect(128, 0, 64, 64));
    sf::Sprite apple;
    apple.setTexture(appleT);

    do {
        apple.setPosition((random() * 64) % window.getSize().x, (random() * 64) % window.getSize().y);
    } while(snake.intersects(apple.getGlobalBounds()));

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                snake.changeDirection(Snake::Left);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                snake.changeDirection(Snake::Right);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                snake.changeDirection(Snake::Up);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                snake.changeDirection(Snake::Down);
        }

        window.clear();
        window.draw(apple);
        window.draw(snake);
        if(snake.intersects(apple.getGlobalBounds())) {
            snake.setSize(snake.getSize() + 1);
            text.setString("Points: " + std::to_string(snake.getSize() - 2)); //two is default size of snake
            do {
                apple.setPosition((rand() * 64) % window.getSize().x, (rand() * 64) % window.getSize().y);
            } while(snake.intersects(apple.getGlobalBounds()));
        }

        if(snake.intersects(snake.getHeadBounds())) {
            text.setString("Game Over!");
            text.setCharacterSize(60);
            text.setPosition((window.getSize().x - text.getLocalBounds().width) / 2, (window.getSize().y - text.getLocalBounds().height) / 2);

            while(window.isOpen()) {
                while(window.pollEvent(event))
                    if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        window.close();
                window.draw(text);
                window.display();
            }
        }
        window.draw(text);
        window.display();
    }
    return 0;
}
