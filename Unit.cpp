#include "Unit.h"

#include "Game.h"


const float Unit::speed = 5.0f;
const float Unit::size = 0.4f;




Unit::Unit(SDL_Renderer* renderer, Vector2D setPos) :
	pos(setPos) {
	texture = TextureLoader::loadTexture(renderer, "Unit.bmp");

}



void Unit::update(float dT, Level& level, std::vector<Unit>& listUnits) {
	//xac dinh khoang cach den muc tieu tu vi tri hien tai cua don vi
	float distanceToTarget = (level.getTargetPos() - pos).magnitude();

	//xac dinh khoang cach de di chuyen khung hinh
	float distanceMove = speed * dT;
	if (distanceMove > distanceToTarget)
		distanceMove = distanceToTarget;

	
	Vector2D directionNormal(level.getFlowNormal((int)pos.x, (int)pos.y));
	Vector2D posAdd = directionNormal * distanceMove;

	
	bool moveOk = true;
	for (int count = 0; count < listUnits.size() && moveOk; count++) {
		auto& unitSelected = listUnits[count];
		if (&unitSelected != this && unitSelected.checkOverlap(pos, size)) {
			

			Vector2D directionToOther = (unitSelected.pos - pos);
			

			if (directionToOther.magnitude() > 0.01f) {
				


				Vector2D normalToOther(directionToOther.normalize());
				float angleBtw = abs(normalToOther.angleBetween(directionNormal));
				if (angleBtw < 3.14159265359f / 4.0f)
					
					moveOk = false;
			}
		}
	}

	if (moveOk) {
		

		const float spacing = 0.35f;
		int x = (int)(pos.x + posAdd.x + copysign(spacing, posAdd.x));
		int y = (int)(pos.y);
		if (posAdd.x != 0.0f && level.isTileWall(x, y) == false)
			pos.x += posAdd.x;

		
		x = (int)(pos.x);
		y = (int)(pos.y + posAdd.y + copysign(spacing, posAdd.y));
		if (posAdd.y != 0.0f && level.isTileWall(x, y) == false)
			pos.y += posAdd.y;
	}
}



void Unit::draw(SDL_Renderer* renderer, int tileSize) {
	if (renderer != nullptr) {
		


		SDL_Rect rect = {
			(int)((pos.x - size / 2) * tileSize),
			(int)((pos.y - size / 2) * tileSize),
			(int)(size * tileSize),
			(int)(size * tileSize) };
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
}



bool Unit::checkOverlap(Vector2D posOther, float sizeOther) {
	return (posOther - pos).magnitude() <= (sizeOther + size) / 2.0f;
}
