#pragma once
#include "GameObject.h"
#include <vector>

using namespace std;

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

class CBackground : 
    public CGameObject {
protected:
    int width, height;
    int base_asset_id;

    vector<vector<int>> tileMap; // 2D grid of tile IDs

    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 0; }
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void GetTileBoundingBox(int x, int y, float& t, float& l, float& r, float& b);
    void GetTileWorldPos(int x, int y, float& posX, float& posY);
public:
    CBackground(float x, float y, int w, int h, int base_asset_id) : CGameObject(x, y) {
        this->width = w;
        this->height = h;
        this->base_asset_id = base_asset_id;
        tileMap.resize(height, vector<int>(width, -1)); // init with tile ID -1
    };
    int GetHeight() { return height; }
    int GetWidth() { return width; }
    void SetTile(int x, int y, int tileID) {
        if (y < 0 || y >= tileMap.size()) return;
        if (x < 0 || x >= tileMap[y].size()) return;
        tileMap[y][x] = tileID;
    };
};