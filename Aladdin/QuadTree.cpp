#include "QuadTree.h"
#include "Global.h"

//init static member

QuadTreeNode* QuadTree::_rootNode = NULL;
CRECT QuadTree::_bound = CRECT(0, 0, 0, 0);


QuadTree::QuadTree(CRECT bound)
{
	_bound = bound;
	_rootNode = new QuadTreeNode();
	_rootNode->_bound = bound;
}

QuadTree::~QuadTree(void)
{
	if(_rootNode != NULL)
	{
		delete _rootNode;
		_rootNode = NULL;
	}
}

void QuadTree::Insert (MyObject* obj)
{
	_rootNode->Insert(obj);
}

void QuadTree::UpdateRender(CRECT camera, Aladdin* mario, int time)
{
#pragma region create rect camera
	CRECT cameraCollision = camera;
	if(cameraCollision._x >= COLLIDE_EXPAND)
		cameraCollision._x -= COLLIDE_EXPAND;
	else
		cameraCollision._x = 0;

	if(cameraCollision._w <= GL_MapW - COLLIDE_EXPAND)
		cameraCollision._w += COLLIDE_EXPAND;
	else
		cameraCollision._w = GL_MapW;

	if(cameraCollision._y >= COLLIDE_EXPAND)
		cameraCollision._y -= COLLIDE_EXPAND;
	else
		cameraCollision._y = 0;

	if(cameraCollision._h <= GL_MapH - COLLIDE_EXPAND)
		cameraCollision._h += COLLIDE_EXPAND;
	else
		cameraCollision._h = GL_MapH;
#pragma endregion

	vector<MyObject*>* listCollision = this->_rootNode->GetObj(camera);
	vector<MyObject*>* listUpdate1 = this->_rootNode->GetObj(camera);
	vector<MyObject*>* listUpdate = this->_rootNode->QueryObj(camera);
	mario->UpdateRealTimeCollision(time,listUpdate);
	if(mario->_State != DEAD)
		listUpdate1->push_back(mario);
	for (std::vector<MyObject*>::iterator i = listUpdate->begin(); 
		i != listUpdate->end(); ++i)
	{
	
		(*i)->Render();

		// insert again
		if((*i)->IsAlive())
		{
			this->Insert(*i);
		}
	}
}
