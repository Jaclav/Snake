#include "Snake.hpp"

Snake::Snake() {
    if(!mTexture.loadFromFile("snake.png"))
        exit(EXIT_FAILURE);

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

    segments.push_back(sf::Vector2f(384, 320));
}

void Snake::changeDirection(Direction side) {
    if((side == Up && mSide != Down) || (side == Down && mSide != Up) ||
            (side == Left && mSide != Right) || (side == Right && mSide != Left))
        mSide = side;

    return;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //rWARNING: last segment is head, first segment is tail
    //set position of new head
    switch(mSide) {
    case Left:
        segments.push_back(sf::Vector2f((segments.back().x <= 0 ? target.getSize().x - 64 : segments.back().x - 64), segments.back().y));
        break;
    case Right:
        segments.push_back(sf::Vector2f((segments.back().x >= target.getSize().x - 64 ? 0 : segments.back().x + 64), segments.back().y));
        break;
    case Up:
        segments.push_back(sf::Vector2f(segments.back().x, (segments.back().y <= 0 ? target.getSize().y - 64 : segments.back().y - 64)));
        break;
    case Down:
        segments.push_back(sf::Vector2f(segments.back().x, (segments.back().y >= target.getSize().y - 64 ? 0 : segments.back().y + 64)));
        break;
    }

    //delete tail
    if(segments.size() > mSize)
        segments.erase(segments.begin());

    //draw rest of body
    for(uint i = 0; i < segments.size() - 1; i++) {
        mSprite.setPosition(segments[i]);
        target.draw(mSprite, states);
    }

    //draw head
    mSprite.setPosition(segments.back());
    mSprite.setTextureRect(sf::IntRect(64, 0, 64, 64));
    switch(mSide) {
    case Left: {
        mSprite.setRotation(0);
        mSprite.setOrigin(0, 0);
    }
    break;
    case Right: {
        mSprite.setRotation(180);
        mSprite.setOrigin(64, 64);
    }
    break;
    case Up:
        mSprite.setRotation(90);
        mSprite.setOrigin(0, 64);
        break;
    case Down:
        mSprite.setRotation(-90);
        mSprite.setOrigin(64, 0);
        break;
    }
    target.draw(mSprite, states);
    mSprite.setRotation(0);
    mSprite.setOrigin(0, 0);
    mSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
}

bool Snake::intersects(sf::Rect<float> rect) {
    for(uint i = 0; i < segments.size() - 1; i++) { //thanks this snake's head is not intersecting with snake's body
        mSprite.setPosition(segments[i]);
        if(mSprite.getGlobalBounds().intersects(rect))
            return true;
    }
    return false;
}

uint Snake::getSize() {
    return mSize;
}

void Snake::setSize(uint size) {
    if(size > 0)
        mSize = size;
}

sf::Rect<float> Snake::getHeadBounds() {
    return sf::Rect<float>(*segments.end(), sf::Vector2f(64, 64));
}