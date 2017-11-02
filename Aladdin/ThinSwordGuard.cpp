#include "ThinSwordGuard.h"
#include "ResourceManager.h"


ThinSwordGuard::ThinSwordGuard()
{
	this->_ID = EObject::THIN_SWORD_GUARD;
}

ThinSwordGuard::ThinSwordGuard(float x, float y) : Enemy(x, y)
{
	this->_moveSprite = Sprite(ResourceMng::GetInst()->GetTexture("image/aladdin.png"), 69, 74, 50);
}

void ThinSwordGuard::Attack()
{

	Enemy::Attack();
}


ThinSwordGuard::~ThinSwordGuard()
{

}
