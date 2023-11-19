#include <SFML/Graphics.hpp>
#include <math.h>
#define speed 15.f
#define meteorSpeed 10.f
#define bulletSpeed 15.f
class Player {
private:
    sf::Sprite* player;
    sf::Texture* texture;
    int life, frame;

public:
    Player();
    ~Player();
    void shoot(std::vector<sf::RectangleShape>& bullets, const sf::CircleShape& target);
    int getLife() const { return life; }
    void receiveDamage() { life--; }
    void moveLeft() { player->setPosition(player->getPosition() - sf::Vector2f(speed, 0.f)); }
    void moveRight() { player->setPosition(player->getPosition() + sf::Vector2f(speed, 0.f)); }
    void moveUp() { player->setPosition(player->getPosition() - sf::Vector2f(0.f, speed)); }
    void moveDown() { player->setPosition(player->getPosition() + sf::Vector2f(0.f, speed)); }
    sf::Sprite getPlayer() { return *player; }
    void changeTexture();
};

Player::Player() : life(3), texture(new sf::Texture), player(new sf::Sprite) {
    if (!texture->loadFromFile("ship.png")) throw std::runtime_error("Failed to load ship image");
    frame = 1;
    player->setTexture(*texture);
    player->setScale(0.2,0.2);
}

Player::~Player() {
    delete player;
    delete texture;
}

void Player::changeTexture() {
    if (frame == 1)
    {
        texture->loadFromFile("ship2.png");
        frame = 2;
    }
    else if (frame == 2)
    {
        texture->loadFromFile("ship3.png");
        frame = 3;
    }
    else if (frame == 3)
    {
        texture->loadFromFile("ship.png");
        frame = 1;
    }
}



class Meteor
{
protected:
    sf::Sprite* player;
    sf::Texture* texture;
    int life;
public:
    Meteor(int life, sf::Sprite* player, sf::Texture* texture):life(life), player(player), texture(texture){};
    void virtual move() = 0;
    int getLife() { return life; }
    void reciveDamange() {life--;}
    ~Meteor(){delete player; delete texture;};
    sf::Sprite getPlayer() {return *player;}
};

class fastMeteor : public Meteor
{
public:
    fastMeteor(float y);
    void move(){player->setPosition(player->getPosition() - sf::Vector2f(meteorSpeed, 0.f));};
    ~fastMeteor();
};

fastMeteor::fastMeteor(float y):Meteor(3, new sf::Sprite, new sf::Texture)
{
    if (!texture->loadFromFile("meteor.png")) throw std::runtime_error("Failed to load meteor image");
    player->setTexture(*texture);
    player->setScale(0.5,0.5);
    player->setPosition(sf::Vector2(750.f,y));
}

fastMeteor::~fastMeteor()
{
}



class slowMeteor : public Meteor
{
public:
    slowMeteor(float y);
    void move(){player->setPosition(player->getPosition() - sf::Vector2f(meteorSpeed/2, 0.f));};
    ~slowMeteor();
};
slowMeteor::slowMeteor(float y):Meteor(4, new sf::Sprite, new sf::Texture){
    if (!texture->loadFromFile("meteor.png")) throw std::runtime_error("Failed to load meteor image");
    player->setTexture(*texture);
    player->setScale(1,1);
    player->setPosition(sf::Vector2(750.f,y));
}

slowMeteor::~slowMeteor()
{
}


class Bullet
{
private:
    sf::Sprite* bullet;
    sf::Texture* texture;
public:
    Bullet(const float &x,const float &y);
    void move(){bullet->setPosition(bullet->getPosition() + sf::Vector2f(bulletSpeed, 0.f));}
    sf::Sprite getBullet() {return *bullet;}
    ~Bullet();
};

Bullet::Bullet(const float &x,const float &y):bullet(new sf::Sprite), texture(new sf::Texture)
{
    if(!texture->loadFromFile("laser.png")) throw std::runtime_error("Failed to load laser image");
    bullet->setTexture(*texture);
    bullet->setScale(0.1,0.1);
    bullet->setPosition(sf::Vector2f(x, y+20));
}

Bullet::~Bullet()
{
    delete bullet;
    delete texture;
}
