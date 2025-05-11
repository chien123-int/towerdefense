#include "Enemy.h"
#include <iostream>

// Dùng ?? t?o và ?i?u khi?n các ??i t??ng k? ??ch trong trò ch?i.
Enemy::Enemy(int x, int y, int width, int height, int groundHeight, bool isRunning)
    : speed(8), currentFrame(0), frameSpeed(4), isRunning(isRunning), groundHeight(groundHeight) {
    enemyRect = { x, y, width, height };

    if (isRunning) {
        frameWidth = width;
        frameHeight = height;
        totalFrames = 4;
        speed = 10;
     
    }
    else {
        frameWidth = width;
        frameHeight = height;
        totalFrames = 4;
    }
}

void Enemy::setTexture(SDL_Texture* texture) {
    enemyTexture = texture;
}

void Enemy::update() {
    static int dem = 0;
    enemyRect.x -= speed;
    static bool check = true;
    if (check){
        enemyRect.y += 2;
        
        dem++;
        if (dem == 120) {
            check = false;
            dem = 0;
        }
    }
    else {
        dem++;
        enemyRect.y -= 2;
        if (dem == 120) {
            check = true;
            dem = 0;
        }
        
    }
    currentFrame++;

    if (currentFrame >= totalFrames * frameSpeed) {
        currentFrame = 0;

    }
}

void Enemy::draw(SDL_Renderer* renderer) const {
    if (!enemyTexture) {
        std::cerr << "No texture set for enemy!" << std::endl;
        return;
    }

    SDL_Rect srcRect = { (currentFrame / frameSpeed) * frameWidth, 0, frameWidth, frameHeight };
    SDL_RenderCopy(renderer, enemyTexture, &srcRect, &enemyRect);
}

SDL_Rect Enemy::getRect() const {
    return enemyRect;
}
