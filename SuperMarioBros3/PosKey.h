#pragma once

class PosKey {
public:
	int keyCode;
	float x;
	float y;
	PosKey() {
		keyCode = -1;
		x = -1;
		y = -1;
	}
	PosKey(int keyCode, float x, float y) {
		this->keyCode = keyCode;
		this->x = x;
		this->y = y;
	}
};