/*
 * Flower.h
 *
 *  Created on: 29 Jan 2011
 *      Author: Ashley
 */

#ifndef FLOWER_H_
#define FLOWER_H_

#include "../ARK.h"
#include "Object.h"

class Flower : public Object {
	public:
		static Image* s_frame1;
		static Image* s_frame2;
		static Image* s_frame3;
		
	public:
		Animation* m_animationIdle;

	public:
		Flower();
		virtual void reset();
		virtual void explode();
		virtual void update(GameContainer* container, GameTimer* timer);
		virtual void render(GameContainer* container, Renderer* r);
		virtual void collision(Object* other);
		virtual ~Flower();
};

#endif /* FLOWER_H_ */
