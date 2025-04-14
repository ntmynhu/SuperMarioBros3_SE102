#include "Background.h"
#include "Game.h"
void CBackground::Render() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float posX, posY;
            this->GetTileWorldPos(x, y, posX, posY);

            if (CGame::GetInstance()->IsInCam(posY, posX, posX, posY)) {
                int tileID = tileMap[y][x];
                if (tileID < 0) continue;

                int tileAssetID = base_asset_id + tileID;
                

                CSprites* s = CSprites::GetInstance();
                s->Get(tileAssetID)->Draw(posX, posY);

            }
        }
    }
}
void CBackground::GetTileBoundingBox(int x, int y, float& t, float& l, float& r, float& b) {
    float posX = x * TILE_WIDTH + this->x;
    float posY = y * TILE_HEIGHT + this->y;

    t = posX - TILE_WIDTH / 2;
    l = posY - TILE_HEIGHT / 2;
    r = l + TILE_WIDTH;
    b = t + TILE_HEIGHT;
}
void CBackground::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
    top = x - TILE_WIDTH / 2;
    left = y - TILE_HEIGHT / 2;
    right = left + TILE_WIDTH * width;
    bottom = top + TILE_HEIGHT * height;
}
void CBackground::GetTileWorldPos(int x, int y, float& posX, float& posY) {
    posX = x * TILE_WIDTH + this->x;
    posY = y * TILE_HEIGHT + this->y;
}