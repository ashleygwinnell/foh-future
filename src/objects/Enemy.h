/*
 * Enemy.h
 *
 *  Created on: 29 Jan 2011
 *      Author: Ashley
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "../ARK.h"
#include "Object.h"

class Enemy : public Object {
	public:
		static Image* s_enemyButterfly1;
		static Image* s_enemyButterfly2;
		static Image* s_enemyButterfly3;
		static Image* s_enemyButterflyGibLeft;
		static Image* s_enemyButterflyGibMiddle;
		static Image* s_enemyButterflyGibRight;

		static Image* s_enemyButterflyLarge1;
		static Image* s_enemyButterflyLarge2;
		static Image* s_enemyButterflyLarge3;
		static Image* s_enemyButterflyLargeGibTopLeft;
		static Image* s_enemyButterflyLargeGibBottomLeft;
		static Image* s_enemyButterflyLargeGibMiddle;
		static Image* s_enemyButterflyLargeGibTopRight;
		static Image* s_enemyButterflyLargeGibBottomRight;

		static Image* s_enemySlug1;
		static Image* s_enemySlug2;
		static Image* s_enemySlugGib1;
		static Image* s_enemySlugGib2;
		static Image* s_enemySlugGib3;
		
	public:
		Animation* m_animationIdle;
		
		bool m_moving;
		bool m_facingLeft;
		bool m_facingUp;

		int m_type;
		static const unsigned int TYPE_BUTTERFLY_SMALL = 0;
		static const unsigned int TYPE_BUTTERFLY_LARGE = 1;
		static const unsigned int TYPE_SLUG = 2;
		
		float m_targetAngleOffset;
		float m_butterflySmallFlapTimer;
		float m_butterflySmallFlapDuration;

		float m_introTimer;
		float m_introDuration;

		float m_bumpPower;

	public:
		Enemy();
		virtual void reset();
		void die();
		void killParticles(float startAngle, float power, float powerSpread);
		void checkPlayerCollisions(bool firstPass, bool movePlayer);
		void checkEnemyCollisions();
		virtual void update(GameContainer* container, GameTimer* timer);
		virtual void render(GameContainer* container, Renderer* r);
		virtual void collision(Object* other);
		virtual ~Enemy();
};

#endif /* ENEMY_H_ */
