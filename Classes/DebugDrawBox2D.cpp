#include "DebugDrawBox2D.h"
#include "Singleton.h"

#pragma execution_character_set("utf-8")


bool DebugDrawBox2D::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	_world = Singleton::getInstance()->getWorld();
	GLESDebugDraw* debugDraw = new GLESDebugDraw(Singleton::PTM_RATIO);
	_world->SetDebugDraw(debugDraw);

	uint32 flags = 0;
	//flags += b2Draw::e_shapeBit;
	//flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_pairBit;
	//flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);

    return true;
}

void DebugDrawBox2D::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Layer::draw(renderer, transform, flags);

	_customCmd.init(_globalZOrder, transform, flags);
	_customCmd.func = CC_CALLBACK_0(DebugDrawBox2D::onDraw, this, transform, flags);
	renderer->addCommand(&_customCmd);
}

void DebugDrawBox2D::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	_world->DrawDebugData();
	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
