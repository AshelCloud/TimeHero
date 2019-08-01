#pragma once

#include "cocos2d.h"
#include "Box2d/Box2D.h"
#include "GLES-Render.h"

using namespace cocos2d;

class DebugDrawBox2D : public cocos2d::Layer
{
public:
	virtual bool init();

    CREATE_FUNC(DebugDrawBox2D);

	b2World* _world;

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

	cocos2d::CustomCommand _customCmd;
};
