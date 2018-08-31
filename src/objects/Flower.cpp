/*
 * Flower.cpp
 *
 *  Created on: 29 Jan 2011
 *      Author: Ashley
 */

#include "Flower.h"
#include "../DefaultGame.h"

#include "EightWayMovementComponent.h"
#include <ARK2D/Core/+.h>
#include <ARK2D/Audio/Sound.h>

Image* Flower::s_frame1 = NULL;
Image* Flower::s_frame2 = NULL;
Image* Flower::s_frame3 = NULL;

Flower::Flower():
	Object()
	{

	DefaultGame* dg = DefaultGame::getInstance();

	if (s_frame1 == NULL) {
		s_frame1 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/flowers-1.png"));
		s_frame1->setCenterOfRotation(s_frame1->getWidth()/2, s_frame1->getHeight());

		s_frame2 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/flowers-2.png"));
		s_frame2->setCenterOfRotation(s_frame2->getWidth()/2, s_frame2->getHeight());

		s_frame3 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/flowers-3.png"));
		s_frame3->setCenterOfRotation(s_frame3->getWidth()/2, s_frame3->getHeight());
	}

    m_bounds = new ARK::Core::Geometry::Rectangle(0, 0, 7, 7);
	m_bounds->setLocationByCenter(64, 32);

	m_velocity->set(0, 0);
	m_velocityMax->set(0, 0);
	m_acceleration->set(0, 0);

	m_animationIdle = new Animation();
	m_animationIdle->addImage(s_frame1);
	m_animationIdle->addImage(s_frame2);
	m_animationIdle->addImage(s_frame3);
	m_animationIdle->setFrameTime(1.0f);

	reset();
}

void Flower::reset() {
	m_animationIdle->setTime(MathUtil::randBetween(0.0f, 1.0f));
}

void Flower::explode() {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	ARK2D::getLog()->e("Flower explode");


}

void Flower::update(GameContainer* container, GameTimer* timer) {
	Object::update(container, timer);

	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	m_bounds->asRectangle()->setLocationByCenter(
		m_bounds->getCenterX() + (m_velocity->getX() * timer->getDelta()),
		m_bounds->getCenterY() + (m_velocity->getY() * timer->getDelta())
	);

	m_animationIdle->update(timer);

}
void Flower::collision(Object* other) {

}



void Flower::render(GameContainer* container, Renderer* r)
{
	InGameState* igs = DefaultGame::getInstance()->stateInGame;
	r->setDrawColor(Color::white);

	Object::render(container, r);

	Image* img = m_animationIdle->getCurrentFrame();
	img->drawCentered(m_bounds->getCenterX(), m_bounds->getCenterY());

	//r->setDrawColor(Color::white);
	//r->drawRect(m_bounds->getMinX(), m_bounds->getMinY(), m_bounds->getWidth(), m_bounds->getHeight());
}

Flower::~Flower() {

}
