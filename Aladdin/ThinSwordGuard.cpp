#include "ThinSwordGuard.h"
#include "ResourceManager.h"


ThinSwordGuard::ThinSwordGuard()
{
}

ThinSwordGuard::ThinSwordGuard(float x, float y) : Enemy(x, y)
{
	this->_ID = EObject::THIN_SWORD_GUARD;
	this->_alive = true;
	this->_isActive = false;
	this->_vx = 0;
	this->_vy = 0;
	this->_turnRight = true;
	this->_moveSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
	this->_activeSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
	this->_attackSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
	this->_deadSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
	this->_hitSprite = new Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
}

void ThinSwordGuard::Attack()
{
	Enemy::Attack();
}


ThinSwordGuard::~ThinSwordGuard()
{

}
