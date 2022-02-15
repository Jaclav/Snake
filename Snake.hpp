#ifndef SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Snake : public sf::Drawable {
public:
    enum Direction {Left, Right, Up, Down};

    Snake();
    void changeDirection(Direction side);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    bool intersects(sf::Rect<float> rect);

    uint getSize();
    void setSize(uint size);

	sf::Rect<float> getHeadBounds();

private:
    sf::Texture mTexture;
    mutable sf::Sprite mSprite;
    Direction mSide = Up;

    mutable std::vector<sf::Vector2f>segments;
    uint mSize = 2;//WARNING 1 is minimum
};

#endif//SNAKE_HPP