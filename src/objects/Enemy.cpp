/*
 * Enemy.cpp
 *
 *  Created on: 29 Jan 2011
 *      Author: Ashley
 */

#include "Enemy.h"
#include "Player.h"
#include "MyParticle.h"
#include "../DefaultGame.h"

#include "EightWayMovementComponent.h"
#include <ARK2D/Core/+.h>
#include <ARK2D/Audio/Sound.h>

Image* Enemy::s_enemyButterfly1 = NULL;
Image* Enemy::s_enemyButterfly2 = NULL;
Image* Enemy::s_enemyButterfly3 = NULL;
Image* Enemy::s_enemyButterflyGibLeft = NULL;
Image* Enemy::s_enemyButterflyGibMiddle = NULL;
Image* Enemy::s_enemyButterflyGibRight = NULL;

Image* Enemy::s_enemyButterflyLarge1 = NULL;
Image* Enemy::s_enemyButterflyLarge2 = NULL;
Image* Enemy::s_enemyButterflyLarge3 = NULL;
Image* Enemy::s_enemyButterflyLargeGibTopLeft = NULL;
Image* Enemy::s_enemyButterflyLargeGibBottomLeft = NULL;
Image* Enemy::s_enemyButterflyLargeGibMiddle = NULL;
Image* Enemy::s_enemyButterflyLargeGibTopRight = NULL;
Image* Enemy::s_enemyButterflyLargeGibBottomRight = NULL;

Image* Enemy::s_enemySlug1 = NULL;
Image* Enemy::s_enemySlug2 = NULL;
Image* Enemy::s_enemySlugGib1 = NULL;
Image* Enemy::s_enemySlugGib2 = NULL;
Image* Enemy::s_enemySlugGib3 = NULL;

Enemy::Enemy():
	Object()
	{

	DefaultGame* dg = DefaultGame::getInstance();

	if (s_enemyButterfly1 == NULL) {
		// small fly
		s_enemyButterfly1 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-1.png"));
		s_enemyButterfly1->setCenterOfRotation(s_enemyButterfly1->getWidth()*0.5f, s_enemyButterfly1->getHeight()*0.5f);

		s_enemyButterfly2 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-2.png"));
		s_enemyButterfly2->setCenterOfRotation(s_enemyButterfly2->getWidth()*0.5f, s_enemyButterfly2->getHeight()*0.5f);

		s_enemyButterfly3 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-3.png"));
		s_enemyButterfly3->setCenterOfRotation(s_enemyButterfly3->getWidth()*0.5f, s_enemyButterfly3->getHeight()*0.5f);

		s_enemyButterflyGibLeft = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-gib-left.png"));
		s_enemyButterflyGibLeft->setCenterOfRotation(s_enemyButterflyGibLeft->getWidth()*0.5f, s_enemyButterflyGibLeft->getHeight()*0.5f);

		s_enemyButterflyGibMiddle = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-gib-middle.png"));
		s_enemyButterflyGibMiddle->setCenterOfRotation(s_enemyButterflyGibMiddle->getWidth()*0.5f, s_enemyButterflyGibMiddle->getHeight()*0.5f);

		s_enemyButterflyGibRight = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-gib-right.png"));
		s_enemyButterflyGibRight->setCenterOfRotation(s_enemyButterflyGibRight->getWidth()*0.5f, s_enemyButterflyGibRight->getHeight()*0.5f);

		// large fly.
		s_enemyButterflyLarge1 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-1.png"));
		s_enemyButterflyLarge1->setCenterOfRotation(s_enemyButterflyLarge1->getWidth()*0.5f, s_enemyButterflyLarge1->getHeight()*0.5f);
		
		s_enemyButterflyLarge2 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-2.png"));
		s_enemyButterflyLarge2->setCenterOfRotation(s_enemyButterflyLarge2->getWidth()*0.5f, s_enemyButterflyLarge2->getHeight()*0.5f);
		
		s_enemyButterflyLarge3 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-3.png"));
		s_enemyButterflyLarge3->setCenterOfRotation(s_enemyButterflyLarge3->getWidth()*0.5f, s_enemyButterflyLarge3->getHeight()*0.5f);
		
		s_enemyButterflyLargeGibTopLeft = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-gib-tl.png"));
		s_enemyButterflyLargeGibTopLeft->setCenterOfRotation(s_enemyButterflyLargeGibTopLeft->getWidth()*0.5f, s_enemyButterflyLargeGibTopLeft->getHeight()*0.5f);
		
		s_enemyButterflyLargeGibBottomLeft = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-gib-bl.png"));
		s_enemyButterflyLargeGibBottomLeft->setCenterOfRotation(s_enemyButterflyLargeGibBottomLeft->getWidth()*0.5f, s_enemyButterflyLargeGibBottomLeft->getHeight()*0.5f);
		
		s_enemyButterflyLargeGibMiddle = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-gib-middle.png"));
		s_enemyButterflyLargeGibMiddle->setCenterOfRotation(s_enemyButterflyLargeGibMiddle->getWidth()*0.5f, s_enemyButterflyLargeGibMiddle->getHeight()*0.5f);
		
		s_enemyButterflyLargeGibTopRight = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-gib-tr.png"));
		s_enemyButterflyLargeGibTopRight->setCenterOfRotation(s_enemyButterflyLargeGibTopRight->getWidth()*0.5f, s_enemyButterflyLargeGibTopRight->getHeight()*0.5f);
		
		s_enemyButterflyLargeGibBottomRight = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/butterfly-large-gib-br.png"));
		s_enemyButterflyLargeGibBottomRight->setCenterOfRotation(s_enemyButterflyLargeGibBottomRight->getWidth()*0.5f, s_enemyButterflyLargeGibBottomRight->getHeight()*0.5f);

		// sluggg
		s_enemySlug1 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/slug-1.png"));
		s_enemySlug1->setCenterOfRotation(s_enemySlug1->getWidth()*0.5f, s_enemySlug1->getHeight()*0.5f);

		s_enemySlug2 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/slug-2.png"));
		s_enemySlug2->setCenterOfRotation(s_enemySlug2->getWidth()*0.5f, s_enemySlug2->getHeight()*0.5f);

		s_enemySlugGib1 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/slug-gib-1.png"));
		s_enemySlugGib1->setCenterOfRotation(s_enemySlugGib1->getWidth()*0.5f, s_enemySlugGib1->getHeight()*0.5f);

		s_enemySlugGib2 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/slug-gib-2.png"));
		s_enemySlugGib2->setCenterOfRotation(s_enemySlugGib2->getWidth()*0.5f, s_enemySlugGib2->getHeight()*0.5f);

		s_enemySlugGib3 = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/slug-gib-3.png"));
		s_enemySlugGib3->setCenterOfRotation(s_enemySlugGib3->getWidth()*0.5f, s_enemySlugGib3->getHeight()*0.5f);
	}

    m_bounds = new ARK::Core::Geometry::Rectangle(0, 0, 7, 7);
	m_bounds->setLocationByCenter(64, 32);

	m_velocity->set(0, 0);
	m_velocityMax->set(200, 200);
	m_acceleration->set(400, 400);

	m_animationIdle = new Animation();
	m_animationIdle->setFrameTime(0.5f);

	m_moving = false;
	m_facingLeft = false;
	m_facingUp = false;

	m_type = TYPE_BUTTERFLY_SMALL;

	reset();
}

void Enemy::reset() {
	//m_movement->reset();
	m_radius = 3;
	m_targetAngleOffset = -40.0f + MathUtil::randBetweenf(0.0f, 80.0f);

	m_animationIdle->clear();

	m_butterflySmallFlapTimer = -0.2f;
	m_butterflySmallFlapDuration = 0.3f;

	m_introTimer = 0.01f;
	m_introDuration = 0.5f;

	m_bumpPower = 100.0f;
	
}

void Enemy::die() {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	ARK2D::getLog()->e("enemy die");

	// if (igs->isDead()) { return; }

	// dg->m_sfxDie->play();
	// dg->m_saveFile->clearUnsaved();

//	igs->m_deadTimer = 0.001f;
	if (!isPendingRemoval() ) {
		if (!igs->m_processingWave) {
			dg->m_sfxButterflySmallDie->play();
		}
	}

	setPendingRemoval(true);


}

void Enemy::killParticles(float startAngle, float power, float powerSpread) {
	if (m_type == Enemy::TYPE_BUTTERFLY_SMALL) {
						
		DefaultGame* dg = DefaultGame::getInstance();
		InGameState* igs = dg->stateInGame;
		float diePower = 0.0f; 
		
		MyParticle* part = NULL;
		
		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyGibLeft);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() - 2, m_bounds->getCenterY());
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyGibRight);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() + 2, m_bounds->getCenterY());
		MathUtil::moveAngle<float>(part->m_velocity,startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyGibMiddle);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX(), m_bounds->getCenterY() - 2);
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

	}
	else if (m_type == Enemy::TYPE_BUTTERFLY_LARGE) {
						
		DefaultGame* dg = DefaultGame::getInstance();
		InGameState* igs = dg->stateInGame;
		float diePower = 0.0f; 
		
		MyParticle* part = NULL;
		
		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyLargeGibTopLeft);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() - 3, m_bounds->getCenterY() - 3);
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyLargeGibTopRight);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() + 3, m_bounds->getCenterY() - 3);
		MathUtil::moveAngle<float>(part->m_velocity,startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyLargeGibMiddle);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX(), m_bounds->getCenterY() - 2);
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyLargeGibBottomLeft);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() - 3, m_bounds->getCenterY() + 3);
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemyButterflyLargeGibBottomRight);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() + 3, m_bounds->getCenterY() + 3);
		MathUtil::moveAngle<float>(part->m_velocity,startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

	}
	if (m_type == Enemy::TYPE_SLUG) {
						
		DefaultGame* dg = DefaultGame::getInstance();
		InGameState* igs = dg->stateInGame;
		float diePower = 0.0f; 
		
		MyParticle* part = NULL;
		
		float faceOffset = (m_facingLeft)?-4:4;
		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemySlugGib1);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() + faceOffset, m_bounds->getCenterY());
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemySlugGib2);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() + 2, m_bounds->getCenterY());
		MathUtil::moveAngle<float>(part->m_velocity,startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		diePower = MathUtil::randBetween(power - powerSpread, power + powerSpread);
		part = igs->m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(Enemy::s_enemySlugGib3);
		part->m_type = MyParticle::TYPE_PLAYER_GIB;
		part->m_bounds->setLocationByCenter(m_bounds->getCenterX() - 2, m_bounds->getCenterY());
		MathUtil::moveAngle<float>(part->m_velocity, startAngle - 45 + MathUtil::randBetweenf(0,90), diePower);

		igs->spawnBlood(m_bounds->getCenterX(), m_bounds->getCenterY(), 1, 4);

	}
	

}

void Enemy::checkPlayerCollisions(bool firstPass, bool movePlayer) {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	// move towards player
	float angle = MathUtil::anglef(
		m_bounds->getCenterX(), 
		m_bounds->getCenterY(), 
		igs->m_player->m_bounds->getCenterX(),
		igs->m_player->m_bounds->getCenterY()
	);
	float distance = MathUtil::distance(
		m_bounds->getCenterX(), 
		m_bounds->getCenterY(), 
		igs->m_player->m_bounds->getCenterX(),
		igs->m_player->m_bounds->getCenterY()
                                        ) - igs->m_player->m_radius - m_radius + 1.0f;
    float speed = std::max(std::min(distance, 60.0f),20.0f);
    //if (m_type == TYPE_BUTTERFLY_LARGE) {
    	//speed = std::max(std::min(distance, 100.0f),30.0f);
    //}
	
    m_velocity->set(0.0f, 0.0f);
	MathUtil::moveAngle<float>(m_velocity, angle - 10 + MathUtil::randBetweenf(0.0f, 20.0f) + m_targetAngleOffset, speed);
	m_velocity->restrictMax(m_velocityMax);

	float result[2];
	bool collides = Shape<float>::collision_circleCircleVec(
		&result[0],
		m_bounds->getCenterX(), m_bounds->getCenterY(), m_radius,
		igs->m_player->m_bounds->getCenterX(), igs->m_player->m_bounds->getCenterY(), igs->m_player->m_radius
	);
	if (collides) {
		if (movePlayer) { // push player
			float newLocX = m_bounds->getCenterX();
			float newLocY = m_bounds->getCenterY();
			MathUtil::moveAngle<float>(newLocX, newLocY, angle, igs->m_player->m_radius + m_radius+0.1f);
			igs->m_player->m_bounds->setLocationByCenter(newLocX,newLocY);

			igs->m_player->m_velocity->set(0.0f, 0.0f);
			MathUtil::moveAngle<float>(igs->m_player->m_velocity, angle, m_bumpPower);
			//m_velocity->set(0.0f, 0.0f);

			if (firstPass) {
				PoolIterator<Enemy*> it = igs->m_enemies->newiteratorref();
				while(it.hasNext()) {
					Enemy* e = it.next();
					if (e == this) { continue; }
					e->checkPlayerCollisions(false, false);
				}
			}

		} else { // push enemy back
			float newLocX = igs->m_player->m_bounds->getCenterX();
			float newLocY = igs->m_player->m_bounds->getCenterY();
			MathUtil::moveAngle<float>(newLocX, newLocY, angle-180, igs->m_player->m_radius + m_radius);
			m_bounds->setLocationByCenter(newLocX,newLocY);
		}
	}
}
void Enemy::checkEnemyCollisions() {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	// if collides with other enemies, move them out of the way too.
    float result[2];
	while (true) { 
		bool didCollide = false;
		PoolIterator<Enemy*> it = igs->m_enemies->newiteratorref();
		while(it.hasNext()) {
			Enemy* e = it.next();
			if (e == this) { continue; }
			bool collides = Shape<float>::collision_circleCircleVec(
				&result[0],
				m_bounds->getCenterX(), m_bounds->getCenterY(), m_radius,
				e->m_bounds->getCenterX(), e->m_bounds->getCenterY(), e->m_radius
			);
			if (collides) {
				float angle = MathUtil::anglef(
					m_bounds->getCenterX(), 
					m_bounds->getCenterY(), 
					e->m_bounds->getCenterX(),
					e->m_bounds->getCenterY()
				);
				float newLocX = m_bounds->getCenterX();
				float newLocY = m_bounds->getCenterY();
				MathUtil::moveAngle<float>(newLocX, newLocY, angle, e->m_radius + m_radius + 0.02f);
				e->m_bounds->setLocationByCenter(newLocX, newLocY);
				m_velocity->set(0.0f, 0.0f);
				e->m_velocity->set(0.0f, 0.0f);
				didCollide = true;

				m_targetAngleOffset = -40.0f + MathUtil::randBetweenf(0.0f, 80.0f);
				e->m_targetAngleOffset = -40.0f + MathUtil::randBetweenf(0.0f, 80.0f);
			}
		}
		if (!didCollide) {
			break;
		}
	}
}

void Enemy::update(GameContainer* container, GameTimer* timer) {
	Object::update(container, timer);

	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;

	if (m_introTimer > 0.0f) {
		m_introTimer += timer->getDelta();
		if (m_introTimer >= m_introDuration) {
			m_introTimer = 0.0f;
		}
	}

	// cool shield behavioiur
	// if (m_type == TYPE_BUTTERFLY_SMALL) {
	// 	// move towards player
	// 	float angle = MathUtil::anglef(
	// 		m_bounds->getCenterX(), 
	// 		m_bounds->getCenterY(), 
	// 		igs->m_player->m_bounds->getCenterX(),
	// 		igs->m_player->m_bounds->getCenterY()
	// 	);
	// 	MathUtil::moveAngle<float>(m_velocity, angle - 15 + MathUtil::randBetweenf(0.0f, 30.0f), 20.0f);
	// 	m_velocity->restrictMax(m_velocityMax);

	// 	if (m_bounds->collides(igs->m_player->m_bounds)) {
	// 		float dist = MathUtil::distance(
	// 			m_bounds->getCenterX(), 
	// 			m_bounds->getCenterY(), 
	// 			igs->m_player->m_bounds->getCenterX(),
	// 			igs->m_player->m_bounds->getCenterY()
	// 		);
	// 	}
	// }


	if (m_type == TYPE_BUTTERFLY_SMALL || m_type == TYPE_BUTTERFLY_LARGE) {
		checkPlayerCollisions(true, true);
		checkEnemyCollisions();

		m_butterflySmallFlapTimer += timer->getDelta();
		if (m_butterflySmallFlapTimer >= m_butterflySmallFlapDuration) {
			m_butterflySmallFlapTimer = 0.0f;
		}
	}
	else if (m_type == TYPE_SLUG) {
		m_velocity->set(0.0f, 0.0f);
		float angle = MathUtil::anglef(
			m_bounds->getCenterX(), m_bounds->getCenterY(), 
			igs->m_player->m_bounds->getCenterX(), igs->m_player->m_bounds->getCenterY()
		);
		MathUtil::moveAngle<float>(m_velocity, angle, 10.0f);

		PoolIterator<Player*> it_players = igs->m_players->newiteratorref();
		while(it_players.hasNext()) {
			Player* p = it_players.next();
			if (p->m_bounds->collides(m_bounds)) {
				killParticles(90, 20, 10);
				die();
			}
		}
	}
    m_animationIdle->update(timer);

	m_bounds->asRectangle()->setLocationByCenter(
		m_bounds->getCenterX() + (m_velocity->getX() * timer->getDelta()),
		m_bounds->getCenterY() + (m_velocity->getY() * timer->getDelta())
	);

}
void Enemy::collision(Object* other) {

}



void Enemy::render(GameContainer* container, Renderer* r)
{
	InGameState* igs = DefaultGame::getInstance()->stateInGame;
	r->setDrawColor(Color::white);

	Object::render(container, r);

	float renderOffset = 0.0f;
	if (m_type == TYPE_BUTTERFLY_SMALL) {
		renderOffset = Easing::easebetweenback(Easing::QUADRATIC_OUT, Easing::QUADRATIC_IN, m_butterflySmallFlapTimer, 0.0f, -2.0f, m_butterflySmallFlapDuration);
	}
	else if (m_type == TYPE_BUTTERFLY_LARGE) {
		renderOffset = Easing::easebetweenback(Easing::QUADRATIC_OUT, Easing::QUADRATIC_IN, m_butterflySmallFlapTimer, 0.0f, -3.0f, m_butterflySmallFlapDuration);
	}

	float scaleX = 1.0f;
	float scaleY = 1.0f;
	if (m_introTimer > 0.0f) {
		scaleX = Easing::easebetween(Easing::QUADRATIC_OUT, m_introTimer, 0.0f, 1.0f, m_introDuration);
		scaleY = Easing::easebetween(Easing::QUADRATIC_OUT, m_introTimer, 0.0f, 1.0f, m_introDuration);
	}

	if (m_type == TYPE_SLUG) {
		if (igs->m_player->m_bounds->getCenterX() > m_bounds->getCenterX()) {
			scaleX *= -1.0f; 
		}
	}


	Image* img = m_animationIdle->getCurrentFrame();
	img->drawCenteredScaled(m_bounds->getCenterX(), m_bounds->getCenterY() + renderOffset, scaleX, scaleY);

	//r->setDrawColor(Color::white);
	//r->drawRect(m_bounds->getMinX(), m_bounds->getMinY(), m_bounds->getWidth(), m_bounds->getHeight());

	//r->setDrawColor(Color::yellow);
	//r->drawCircle(m_bounds->getCenterX(), m_bounds->getCenterY(), m_radius);
}

Enemy::~Enemy() {

}
