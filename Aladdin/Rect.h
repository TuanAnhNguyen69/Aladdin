#pragma once

#include <d3d9.h>

//Thay thế cho struct RECT, bởi vì xét va chạm bằng RECT viết rất nhiều hàm phức tạp
//Bổ sung thêm các hàm cần thiết khác
class CRECT
{
public:
	float _x, _y, _w, _h;
	
	CRECT(void);
	CRECT(RECT rect);
	CRECT(float _left, float _top, float _right, float _bottom);
	~CRECT(void);

	void Move(float x, float y);
};

