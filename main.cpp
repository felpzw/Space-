#include "SFML/Game.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>


#define winX 800
#define winY 600

using namespace std;


void spawnEnemy(vector<Meteor*> &Enemys)
{
    if (Enemys.size() < 5)
    {   
        if (rand() % 2 == 0) Enemys.push_back(new fastMeteor(rand() % winY));
        else Enemys.push_back(new slowMeteor(rand() % winY));
    }
    
}

bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());
}

void deleteEnemyAtIndex(vector<Meteor*>& Enemys, size_t index) {
    if (index < Enemys.size()) {
        delete Enemys[index];
        Enemys.erase(Enemys.begin() + index);
    }
}

void deleteBulletAtIndex(vector<Bullet*>& Bullets, size_t index) {
    if (index < Bullets.size()) {
        delete Bullets[index];
        Bullets.erase(Bullets.begin() + index);
    }
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "PROG II - GAME");
    window.setFramerateLimit(30);
    int Points = 0;
    Player player;
    vector<Meteor*> Enemys;
    vector<Bullet*> Bullets;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::A && player.getPlayer().getPosition().x >= 0) {
                    player.moveLeft();
                } else if (event.key.code == sf::Keyboard::D && player.getPlayer().getPosition().x <= winX) {
                    player.moveRight();
                }
                if (event.key.code == sf::Keyboard::W && player.getPlayer().getPosition().y >= 0) {
                    player.moveUp();
                } else if (event.key.code == sf::Keyboard::S && player.getPlayer().getPosition().y <= winY) {
                    player.moveDown();
                }
                if (event.key.code == sf::Keyboard::J && Bullets.size() < 5) {
                    Bullets.push_back(new Bullet(player.getPlayer().getPosition().x, player.getPlayer().getPosition().y));

                }
            }                   
        }

        if (rand() % 1000 <= 30) spawnEnemy(Enemys);

        for (size_t i = 0; i < Bullets.size(); i++)
        {   bool found = false;
            for (size_t z = 0; z < Enemys.size(); z++)
            {
                if (checkCollision(Bullets[i]->getBullet(), Enemys[z]->getPlayer())) {
                    Enemys[z]->reciveDamange();
                    found = true;
                    break;
                }
            }
            if (found) {
                deleteBulletAtIndex(Bullets, i);
                break;
            }
        }

        for (size_t i = 0; i < Bullets.size(); i++)
        {
            if (Bullets[i]->getBullet().getPosition().x > winX)
            {
                deleteBulletAtIndex(Bullets, i);
                break;
            }
            
        }
        
        for (size_t i = 0; i < Enemys.size(); i++)
        {
            if (Enemys[i]->getLife() < 0)
            {
                deleteEnemyAtIndex(Enemys, i);
                Points++;
                break;
            }
        }
        

        for (size_t i = 0; i < Enemys.size(); i++)
        {
            if (checkCollision(Enemys[i]->getPlayer(), player.getPlayer())) {
            player.receiveDamage();
            cout << "Life: " << player.getLife() << endl;
            deleteEnemyAtIndex(Enemys, i);
            break;
            }
            else if (Enemys[i]->getPlayer().getPosition().x <=0) {
                deleteEnemyAtIndex(Enemys, i);
                break;
            }
            
        }
        
        if (player.getLife() <= 0) window.close();
        
        player.changeTexture();
        window.clear();
        for (auto &Bullet : Bullets)
        {
            Bullet->move();
            window.draw(Bullet->getBullet());
        }
        
        for (auto &Enemy : Enemys)
        {   
            Enemy->move();
            window.draw(Enemy->getPlayer());
        }
        window.draw(player.getPlayer());
        window.display();

    }
    cout << "END GAME" << endl << "Points: " << Points << endl;
    for (auto &Enemy : Enemys)
        {   
            delete Enemy;
        }
    for (auto &Bullet : Bullets)
    {
        delete Bullet;
    }
    
    return 0;
}