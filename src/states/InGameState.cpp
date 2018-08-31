
#include "InGameState.h"
#include <ARK2D/Core/+.h>
#include <ARK2D/UI/+.h>
#include <ARK2D/Util/CameraShake.h>
#include "../objects/Player.h"
#include "../objects/Enemy.h"
#include "../objects/Tile.h"
#include "../objects/MyParticle.h"
#include "../objects/Flower.h"
#include "../objects/Bomb.h"
#include "../objects/ArrowBox.h"
#include "../objects/Arrow.h"
#include "../objects/Buzzsaw.h"
//#include "../objects/Enemy.h"
#include "../DefaultGame.h"

InGameState::InGameState():
	GameState()
	{

}

unsigned int InGameState::id() {
	return StatesList::STATE_INGAME;
}

void InGameState::enter(GameContainer* container, StateBasedGame* game, GameState* from) {

}

void InGameState::leave(GameContainer* container, StateBasedGame* game, GameState* to) {

}

void InGameState::init(GameContainer* container, StateBasedGame* game) {
    DefaultGame* dg = DefaultGame::getInstance();

    m_paused = false;

	m_players = new Pool<Player*>(8);
	m_enemies = new Pool<Enemy*>(20);
    m_tiles = new Pool<Tile*>(60);
    m_bombs = new Pool<Bomb*>(5);
    m_arrowBoxes = new Pool<ArrowBox*>(5);
    m_arrows = new Pool<Arrow*>(5);
    m_buzzsaws = new Pool<Buzzsaw*>(6);
    
    m_particles = new Pool<MyParticle*>(60);

    m_flowers = new Pool<Flower*>(10);


    m_iconHand = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/icon-hand.png"));
    m_iconHand->setCenterOfRotation(m_iconHand->getWidth() * 0.5f, m_iconHand->getHeight() * 0.5f);

    m_iconGlove = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/icon-glove.png"));
    m_iconGlove->setCenterOfRotation(m_iconGlove->getWidth() * 0.5f, m_iconGlove->getHeight() * 0.5f);

    m_iconBomb = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/icon-bomb.png"));
    m_iconBomb->setCenterOfRotation(m_iconBomb->getWidth() * 0.5f, m_iconBomb->getHeight() * 0.5f);

    m_iconCalendar = dg->spritesheet->getSubImage(dg->desc->getItemByName("sprites/icon-day.png"));
    m_iconCalendar->setCenterOfRotation(m_iconCalendar->getWidth() * 0.5f, m_iconCalendar->getHeight() * 0.5f);

    m_cameraShake = new CameraShake(game, 4);
    // bombs fuse
    // bombs going off
    // player die

    start();
}

void InGameState::spawnBlood(float x, float y, float radius, int num) {
	MyParticle* part = NULL;

	for(int i = 0; i < num; i++) {
		float splashStrength = MathUtil::randBetweenf(30.0f, 60.0f); 
		float tx = x;
		float ty = y;
		MathUtil::moveAngle<float>(tx, ty, MathUtil::randBetweenf(0,360), MathUtil::randBetweenf(0.0f, radius));

		Image* frame = MyParticle::s_bloodSelection->at(MathUtil::randBetween(0, MyParticle::s_bloodSelection->size()));
		part = m_particles->get();
		part->reset();
		part->m_animation->reset();
		part->m_animation->addFrame(frame);
		part->m_type = MyParticle::TYPE_BLOOD;
		part->m_bounds->setLocationByCenter(tx, ty);
		MathUtil::moveAngle<float>(part->m_velocity, MathUtil::randBetweenf(0,360), splashStrength);
	}
}

void InGameState::reset() {
	worldStartX = 10;
    worldStartY = 10;
	worldWidth = 12;
	worldHeight = 7;
	worldTileSize = 10;

    m_players->reset();
    m_enemies->reset();
	m_tiles->reset();
	m_tilesLinear.clear();
	m_bombs->reset();
	m_particles->reset();
	m_flowers->reset();
	m_arrowBoxes->reset();
	m_arrows->reset();
	m_buzzsaws->reset();
	

    m_waveNumber = 0;

    m_waveProgressionByMovementCount = 0;
    m_waveProgressionByKillsCount = 0;

    m_timesCrossedCenterTotal = 0;
    m_timesCrossedCenterThisWave = 0;

    m_timesCrossedCenterVerticalTotal = 0;
    m_timesCrossedCenterVerticalThisWave = 0;

	m_deadTimer = 0.0f;
	m_deadDuration = 2.5f;

	m_flashTimer = 0.0f;
	m_flashDuration = 0.2f;

	m_bombExplodedFilterTimer = 0.0f;
	m_bombExplodedFilterDuration = 2.0f;

	m_waveIntroTimer = 0.0f;
	m_waveIntroDuration = 2.0f;
}

void InGameState::start() {
	reset();
    
    m_player = m_players->get();
    m_player->reset();

	for (int y = 0; y < worldHeight; y++) {
		for (int x = 0; x < worldWidth; x++) {
			Tile* t = m_tiles->get();
			t->reset();
			t->gx = x;
			t->gy = y;
			t->m_bounds->setLocation(worldStartX + (x*worldTileSize), worldStartY + (y*worldTileSize));

			m_tilesLinear.push_back(t);
		}
	}

	Flower* flower = NULL;
	flower = m_flowers->get(); // tl
	flower->reset();
	flower->m_bounds->setLocationByCenter(worldStartX + 3 + (worldTileSize*0.5f), worldStartY + 3 + (worldTileSize*0.5f));
	getTileAt(0,0)->itemonit = true;
 
	flower = m_flowers->get(); // tr
	flower->reset();
	flower->m_bounds->setLocationByCenter(worldStartX - 3 + (worldWidth*worldTileSize)-(worldTileSize*0.5f), worldStartY + 3 + (worldTileSize*0.5f));
	getTileAt(worldWidth-1,0)->itemonit = true;

	flower = m_flowers->get(); // bl
	flower->reset();
	flower->m_bounds->setLocationByCenter(worldStartX + 3 + (worldTileSize*0.5f), worldStartY + (worldHeight*worldTileSize)-(worldTileSize*0.5f) - 5);
	getTileAt(0,worldHeight-1)->itemonit = true;

	flower = m_flowers->get(); // br
	flower->reset();
	flower->m_bounds->setLocationByCenter(worldStartX - 3 + (worldWidth*worldTileSize)-(worldTileSize*0.5f), worldStartY + (worldHeight*worldTileSize)-(worldTileSize*0.5f) - 5);
	getTileAt(worldWidth-1,worldHeight-1)->itemonit = true;



	startWave();

	
}
void InGameState::startWave() {
    DefaultGame* dg = DefaultGame::getInstance();
    InGameState* igs = dg->stateInGame;

    m_processingWave = true;

	// remove other/old advance tiles
	for(int i = 0; i < m_tilesLinear.size(); i++) {
		if (m_tilesLinear[i]->advance) { // gib it
			
			MyParticle* part = NULL;
			float diePower = MathUtil::randBetweenf(40, 60);
			part = igs->m_particles->get();
			part->reset();
			part->m_animation->reset();
			part->m_animation->addFrame(Tile::s_tileAdvanceGibPlus);
			part->m_type = MyParticle::TYPE_PLAYER_GIB;
			part->m_bounds->setLocationByCenter(m_tilesLinear[i]->m_bounds->getCenterX(), m_tilesLinear[i]->m_bounds->getCenterY());
			MathUtil::moveAngle<float>(part->m_velocity, -90 - 45 + MathUtil::randBetweenf(0,90), diePower);

			diePower = MathUtil::randBetweenf(40, 60);
			part = igs->m_particles->get();
			part->reset();
			part->m_animation->reset();
			part->m_animation->addFrame(Tile::s_tileAdvanceGibBG);
			part->m_type = MyParticle::TYPE_PLAYER_GIB;
			part->m_bounds->setLocationByCenter(m_tilesLinear[i]->m_bounds->getCenterX() - 2, m_tilesLinear[i]->m_bounds->getCenterY() - 2);
			MathUtil::moveAngle<float>(part->m_velocity, -90 - 45 + MathUtil::randBetweenf(0,90), diePower);

			diePower = MathUtil::randBetweenf(40, 60);
			part = igs->m_particles->get();
			part->reset();
			part->m_animation->reset();
			part->m_animation->addFrame(Tile::s_tileAdvanceGibBG);
			part->m_type = MyParticle::TYPE_PLAYER_GIB;
			part->m_bounds->setLocationByCenter(m_tilesLinear[i]->m_bounds->getCenterX() + 2, m_tilesLinear[i]->m_bounds->getCenterY() + 2);
			MathUtil::moveAngle<float>(part->m_velocity, -90 - 45 + MathUtil::randBetweenf(0,90), diePower);
		}
		m_tilesLinear[i]->advance = false;
	}

	

	// add enemies
	m_spawnEnemies.clear();
	
	// small butterflies
	int numSmallButterflies = std::min( (int) (m_waveNumber*0.5f) + m_waveProgressionByKillsCount, 4);
	for(int i = 0; i <= numSmallButterflies; i++) {
		SpawnEnemyEvent ev;
		ev.enemyType = Enemy::TYPE_BUTTERFLY_SMALL;
		ev.delay = 1.5f + (i * 1.0f);
		m_spawnEnemies.push_back(ev);
	}

	// large butterflies
	int numLargeButterflies = 0;
	if (m_waveNumber >= 5 && m_waveProgressionByKillsCount >= 3) { numLargeButterflies++; }
	for(int i = 0; i < numLargeButterflies; i++) {
		SpawnEnemyEvent ev;
		ev.enemyType = Enemy::TYPE_BUTTERFLY_LARGE;
		ev.delay = 1.5f + (i * 2.0f);
		m_spawnEnemies.push_back(ev);
	}

	// slugs
	int numSlugs = std::max(0, m_waveNumber - 5);
	for(int i = 0; i < numSlugs; i++) {
		SpawnEnemyEvent ev;
		ev.enemyType = Enemy::TYPE_SLUG;
		ev.delay = 2.0f + (i * 1.5f);
		m_spawnEnemies.push_back(ev);
	}
	

	if (m_timesCrossedCenterTotal >= 6 && getTileAt(5, 0)->solid) {
		getTileAt(5, 0)->removeSolid();
		getTileAt(6, 0)->removeSolid();
		getTileAt(5, worldHeight-1)->removeSolid();
		getTileAt(6, worldHeight-1)->removeSolid();
	}
	if (m_timesCrossedCenterTotal >= 15 && getTileAt(5, 1)->solid) {
		getTileAt(4, 0)->removeSolid();
		getTileAt(5, 1)->removeSolid();
		getTileAt(6, 1)->removeSolid();
		getTileAt(7, 0)->removeSolid();
		getTileAt(4, worldHeight-1)->removeSolid();
		getTileAt(5, worldHeight-2)->removeSolid();
		getTileAt(6, worldHeight-2)->removeSolid();
		getTileAt(7, worldHeight-1)->removeSolid();
	}
	if (m_timesCrossedCenterVerticalThisWave > 8 && getTileAt(0, 3)->solid) {
		getTileAt(0, 3)->removeSolid();
		getTileAt(worldWidth-1, 3)->removeSolid();
	}
	if (m_timesCrossedCenterVerticalThisWave > 16 && getTileAt(0, 2)->solid) {
		getTileAt(0, 2)->removeSolid();
		getTileAt(0, 4)->removeSolid();
		getTileAt(worldWidth-1, 2)->removeSolid();
		getTileAt(worldWidth-1, 3)->removeSolid();
	}

	// if time spent in middle. undo the taking off of the edges.

	// add advance tiles.
	int advanceTiles = std::min(m_waveProgressionByMovementCount, 5);
	for(int i = 0; i <= advanceTiles; i++) {
		Tile* tile = getRandomSolidTile();
		tile->m_introTimer = 0.001f;
		tile->advance = true;
	}
	if (m_waveProgressionByMovementCount == 3 || m_waveProgressionByMovementCount == 6)  {
		spawnArrowBox();
	}
	else if (m_waveProgressionByMovementCount == 5 || m_waveProgressionByMovementCount == 7)  {
		spawnBuzzsaw();
	}

	m_player->nextWave();

	m_waveIntroTimer = 0.01f;
	
	m_timeSpentInMiddleThisWave = 0.0f;
	m_timeSpentOnEdgeThisWave = 0.0f;
	m_timesCrossedCenterThisWave = 0;
    m_timesCrossedCenterIsOnLeftSide = (m_player->m_bounds->getCenterX() < ARK2D::getContainer()->getWidth()*0.5f);
    
    m_timesCrossedCenterVerticalThisWave = 0;
    m_timesCrossedCenterIsOnTopSide = (m_player->m_bounds->getCenterY() < getWorldCY());

    if (m_waveNumber > 0) { 
    	dg->m_sfxWaveUp->play();
    }

    if (m_waveNumber+1 == 10) {
    	dg->m_musicCurrent->stop();
    	dg->m_musicCurrent = dg->m_musicFast;
    }
    else if (m_waveNumber+1 == 5) {
    	dg->m_musicCurrent->stop();
    	dg->m_musicCurrent = dg->m_musicMedium;
    }
     else if (m_waveNumber+1 == 1) {
    	dg->m_musicCurrent->stop();
    	dg->m_musicCurrent = dg->m_musicSlow;
    }

    m_processingWave = false;
}
void InGameState::nextWave() {
	// gib any enemies that existed.
	PoolIterator<Enemy*> it_enemies = m_enemies->newiteratorref();
	while(it_enemies.hasNext()) {
		Enemy* e = it_enemies.next();
		e->die();
		e->killParticles(-90, 30, 10);
	}
	m_waveNumber++;
	startWave();
}

Tile* InGameState::getRandomSolidTile() {
	while (true) { 
		int randomX = MathUtil::randBetween(1, worldWidth-1);
		int randomY = MathUtil::randBetween(1, worldHeight-1);
		if (getTileAt(randomX, randomY)->solid) { // only place on solids
			return getTileAt(randomX, randomY);
		}
	}
}
Tile* InGameState::getTopOrBottomEmptySolidTile() {
	vector<Tile*> all;
	for(int i = 0; i < m_tilesLinear.size(); i++) {
		Tile* t = m_tilesLinear[i];
		if ((t->gy == 0 || t->gy == worldHeight-1) && t->solid && !t->itemonit) {
			all.push_back(t);
		}
	}
	if (all.size() > 0) {
		return all.at(MathUtil::randBetween(0, all.size()));
	}
	return NULL;
}
Tile* InGameState::getLeftOrRightEmptySolidTile() {
	vector<Tile*> all;
	for(int i = 0; i < m_tilesLinear.size(); i++) {
		Tile* t = m_tilesLinear[i];
		if ((t->gx == 0 || t->gx == worldWidth-1) && t->solid && !t->itemonit) {
			all.push_back(t);
		}
	}
	if (all.size() > 0) {
        return all.at(MathUtil::randBetween(0, all.size()));
	}
	return NULL;
}

Tile* InGameState::getTileAt(int x, int y) {
	return m_tilesLinear[(y*worldWidth) + x];
	// PoolIterator<Tile*> it = m_tiles->newiteratorref();
	// while(it.hasNext()) {
	// 	Tile* t = it.next();
	// 	if (t->gx == x && t->gy == y) {
	// 		return t;
	// 	}
	// }
	// ARK2D::getLog()->e("missing tile");
	// ARK2D::getLog()->e(StringUtil::append("gx:", x));
	// ARK2D::getLog()->e(StringUtil::append("gy:", y));
	// return NULL;
}
void InGameState::spawnButterflySmall() {
	Enemy* e = m_enemies->get();
	e->reset();
	e->m_type = Enemy::TYPE_BUTTERFLY_SMALL;
	e->m_animationIdle->addFrame(Enemy::s_enemyButterfly1);
	e->m_animationIdle->addFrame(Enemy::s_enemyButterfly2);
	e->m_animationIdle->addFrame(Enemy::s_enemyButterfly3);
	e->m_animationIdle->setFrameTime(0.1f);
	e->m_bounds->setLocationByCenter(
		MathUtil::randBetweenf(worldStartX+5, worldStartX + (worldTileSize * worldWidth) - 5),
		MathUtil::randBetweenf(worldStartY+5, worldStartY + (worldTileSize * worldHeight) - 5)
    );
}
void InGameState::spawnButterflyLarge() {
	Enemy* e = m_enemies->get();
	e->reset();
	e->m_type = Enemy::TYPE_BUTTERFLY_LARGE;
	e->m_animationIdle->addFrame(Enemy::s_enemyButterflyLarge1);
	e->m_animationIdle->addFrame(Enemy::s_enemyButterflyLarge2);
	e->m_animationIdle->addFrame(Enemy::s_enemyButterflyLarge3);
	e->m_animationIdle->setFrameTime(0.1f);
	e->m_bounds->setLocationByCenter(
		MathUtil::randBetweenf(worldStartX+5, worldStartX + (worldTileSize * worldWidth) - 5),
		MathUtil::randBetweenf(worldStartY+5, worldStartY + (worldTileSize * worldHeight) - 5)
    );
	e->m_radius = 5;
	e->m_bumpPower = 180.0f;
}
void InGameState::spawnSlug() {
	Enemy* e = m_enemies->get();
	e->reset();
	e->m_type = Enemy::TYPE_SLUG;
	e->m_animationIdle->addFrame(Enemy::s_enemySlug1);
	e->m_animationIdle->addFrame(Enemy::s_enemySlug2);
	e->m_animationIdle->setFrameTime(0.5f);
	
	Tile* tile = getRandomSolidTile();
	e->m_bounds->setLocationByCenter(tile->m_bounds->getCenterX(), tile->m_bounds->getCenterY());
	
	e->m_radius = 1.5f;
	e->m_bumpPower = 0.0f;
}
void InGameState::spawnArrowBox() {

	Tile* tile = getLeftOrRightEmptySolidTile();
	if (tile == NULL) { return; }



	ArrowBox* ab = m_arrowBoxes->get();
	ab->reset();

	//float r = MathUtil::randBetweenf(0.0f, 1.0f);
	// if (r < 0.5f) {
		ab->m_bounds->setLocationByCenter(
			tile->m_bounds->getCenterX(),
			tile->m_bounds->getMinY() + 8
			//MathUtil::randBetweenf(worldStartY+8, worldStartY + (worldTileSize * worldHeight) - 8)
		);
		ab->m_facingLeft = tile->gx > 0;

		tile->itemonit = true;
	// } else {
	// 	ab->m_bounds->setLocationByCenter(
	// 		tile->m_bounds->getCenterX(),
	// 		//MathUtil::randBetweenf(worldStartY+8, worldStartY + (worldTileSize * worldHeight) - 8)
	// 		tile->m_bounds->getMinY() + 8
	// 	);
	// 	ab->m_facingLeft = false;
	// }

	

}

void InGameState::spawnBuzzsaw() {
	Tile* tile = getTopOrBottomEmptySolidTile();
	if (tile == NULL) { return; }

	Buzzsaw* ab = m_buzzsaws->get();
	ab->reset();

	ab->m_bounds->setLocationByCenter(
		tile->m_bounds->getCenterX(),
		tile->m_bounds->getCenterY() - 3
		//MathUtil::randBetweenf(worldStartY+8, worldStartY + (worldTileSize * worldHeight) - 8)
	);
	tile->itemonit = true;
	// float r = MathUtil::randBetweenf(0.0f, 1.0f);
	// if (r < 0.5f) {
	// 	ab->m_bounds->setLocationByCenter(
	// 		worldStartX + (worldTileSize * worldWidth) - 10,
	// 		MathUtil::randBetweenf(worldStartY+8, worldStartY + (worldTileSize * worldHeight) - 8)
	// 	);
	// } else {
	// 	ab->m_bounds->setLocationByCenter(
	// 		worldStartX + 10,
	// 		MathUtil::randBetweenf(worldStartY+8, worldStartY + (worldTileSize * worldHeight) - 8)
	// 	);
	// }

}

void InGameState::spawnEnemy(int type) {
	if (type == Enemy::TYPE_BUTTERFLY_SMALL) {
		spawnButterflySmall();
	} else if (type == Enemy::TYPE_BUTTERFLY_LARGE) {
		spawnButterflyLarge();
	} else if (type == Enemy::TYPE_SLUG) {
		spawnSlug();
	}
}

void InGameState::update(GameContainer* container, StateBasedGame* game, GameTimer* timer) {
	DefaultGame* dg = DefaultGame::getInstance();
	Input* in = ARK2D::getInput();

	if (in->isKeyPressed(Input::KEY_ENTER) || 
		in->isGamepadButtonPressed(Gamepad::BUTTON_START)) {
		dg->m_sfxSelect->play();
		m_paused = !m_paused;
	}
	if (m_paused) { return; }

	if (in->isKeyPressed(Input::KEY_ESCAPE) ||
		in->isKeyPressed(Input::KEY_BACKSPACE) ||
		in->isGamepadButtonPressed(Gamepad::BUTTON_BACK)) {
		game->enterState(dg->stateMenu);
	}

	// if (in->isKeyPressed(Input::KEY_B)) {
	// 	spawnButterflySmall();
	// }
	// if (in->isKeyPressed(Input::KEY_N)) {
	// 	spawnButterflyLarge();
	// }
	// if (in->isKeyPressed(Input::KEY_J)) {
	// 	spawnSlug();
	// }
	// if (in->isKeyPressed(Input::KEY_M)) {
	// 	spawnArrowBox();
	// }
	// if (in->isKeyPressed(Input::KEY_V)) {
	// 	spawnBuzzsaw();
	// }

	if (!dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->play(); 
	}

	if (m_waveIntroTimer > 0.0f) {
		m_waveIntroTimer += timer->getDelta();
		if (m_waveIntroTimer >= m_waveIntroDuration) {
			m_waveIntroTimer = 0.0f;
		}
	}

	for(int i = 0; i < m_spawnEnemies.size(); i++){
		SpawnEnemyEvent* ev = &m_spawnEnemies.at(i);
		ev->delay -= timer->getDelta();
		if (ev->delay < 0.0f) {
			spawnEnemy(ev->enemyType);
			m_spawnEnemies.erase(m_spawnEnemies.begin() + i);
			break;		
		}
	}
	


	m_cameraShake->update(container, timer);


	m_player->update(container, timer);
	m_tiles->updateAll(container, timer);
	m_buzzsaws->updateAll(container, timer);
	m_enemies->updateAll(container, timer);
	m_particles->updateAll(container, timer);
	m_flowers->updateAll(container, timer);
	m_bombs->updateAll(container, timer);
	m_arrowBoxes->updateAll(container, timer);
	m_arrows->updateAll(container, timer);

	m_enemies->pruneAll();
	m_particles->pruneAll();
	m_bombs->pruneAll();


	PoolIterator<ArrowBox*> it_arrowBoxes = m_arrowBoxes->newiteratorref();
	while(it_arrowBoxes.hasNext()) {
		ArrowBox* ab = it_arrowBoxes.next();
		Vector2<float> ret = Shape<float>::collision_rectangleRectangleVec(
			m_player->m_bounds->getMinX(), m_player->m_bounds->getMinY(), 
			m_player->m_bounds->getWidth(), m_player->m_bounds->getHeight(),
			ab->m_bounds->getMinX(), ab->m_bounds->getMinY(), 
			ab->m_bounds->getWidth(), ab->m_bounds->getHeight()
		);
		if (ret.length() > 0) {
			m_player->m_bounds->setLocationByCenter(
				m_player->m_bounds->getCenterX() + ret.getX(),
				m_player->m_bounds->getCenterY() + ret.getY()
			);
		}
	}
	PoolIterator<Arrow*> it_arrows = m_arrows->newiteratorref();
	while(it_arrows.hasNext()) {
		Arrow* a = it_arrows.next();
		if (a->m_bounds->collides(m_player->m_bounds)) {
			m_player->die();
			if (m_player->m_dieReason == Player::DIE_NULL) { 
				m_player->m_dieReason = Player::DIE_ARROW;
			}
		}
	}

	// Make sure player is colliding with at least one tile.
	bool isCollidingWithTile = false;
	PoolIterator<Tile*> it_tiles = m_tiles->newiteratorref();
	while(it_tiles.hasNext()){
		Tile* t = it_tiles.next();
		if (t->solid && t->m_bounds->collides(m_player->m_bounds)) {
			isCollidingWithTile = true;
			break;
		}
	}
	if (!isCollidingWithTile) {
		m_player->die();
		if (m_player->m_dieReason == Player::DIE_NULL) { 
			m_player->m_dieReason = Player::DIE_FALL;
		}
	}

	if (m_flashTimer > 0.0f) {
		m_flashTimer += timer->getDelta();
		if (m_flashTimer >= m_flashDuration) {
			m_flashTimer = 0.0f;
		}
	}

	if (m_bombExplodedFilterTimer > 0.0f) {
		//dg->m_musicCurrent->setHighpass(true);
        
  //      float freq = Easing::easebetween(Easing::LINEAR, m_bombExplodedFilterTimer, 500.0©©©©f, 21100.0f, m_bombExplodedFilterDuration);
//		dg->m_musicCurrent->setHighpassFrequency(freq);

		m_bombExplodedFilterTimer += timer->getDelta();
		if (m_bombExplodedFilterTimer >= m_bombExplodedFilterDuration) {
			//m_bombExplodedFilterTimer = 0.0f;
			//dg->m_musicCurrent->setHighpass(false);
		}
	}

	if (m_deadTimer > 0.0f) {
		m_deadTimer += timer->getDelta();
		if (m_deadTimer >= m_deadDuration) {
			FadeToColourTransition* ftc = new FadeToColourTransition(0.25f, new Color(*Tile::s_bgColor));
			//ftc->setUpdatingStates(true, false);
			game->enterState(
				dg->stateSummary, 
				ftc, 
				new FadeFromColourTransition(0.25f, new Color(*Tile::s_bgColor))
			);
		}
	}

	// Check collisions with 'advance' tiles.
	it_tiles = m_tiles->newiteratorref();
	int countAdvances = 0;
	while(it_tiles.hasNext()){
		Tile* t = it_tiles.next();
		if (t->advance) {
			if (t->m_bounds->collides(m_player->m_bounds) && t->m_introTimer == 0.0f) {
				t->advance = false;

				dg->m_sfxTileAdvance->play();

				MyParticle* particle = m_particles->get();
				particle->reset();
				particle->m_animation->addFrame(Tile::s_tileAdvance);
				particle->m_type = MyParticle::TYPE_TILE_ADVANCE;
				particle->m_bounds->setLocationByCenter(t->m_bounds->getCenterX(), t->m_bounds->getCenterY());
				particle->m_duration = 1.0f;
			}
			if (t->advance) {
				countAdvances++;
			}
		}
		if (t->m_bounds->collides(m_player->m_bounds)) {

			if (t->isEdgeTile()) {
				m_timeSpentOnEdgeThisWave += timer->getDelta();
			} else { 
				m_timeSpentInMiddleThisWave += timer->getDelta();
			}


			bool doAdd = true;
			for (int i = 0; i < m_player->m_tilesTouched.size(); i++) {
				if (m_player->m_tilesTouched[i] == t) {
					doAdd = false;
				}
			}
			if (doAdd) {
				m_player->m_tilesTouched.push_back(t);
			}
		}
	}
	
	//crossingtimes
	if (m_timesCrossedCenterIsOnLeftSide && m_player->m_bounds->getMinX() > container->getWidth()*0.5f) {
		m_timesCrossedCenterIsOnLeftSide = false;
		m_timesCrossedCenterThisWave++;
		m_timesCrossedCenterTotal++;
	} else if (!m_timesCrossedCenterIsOnLeftSide && m_player->m_bounds->getMaxX() < container->getWidth()*0.5f) {
		m_timesCrossedCenterIsOnLeftSide = true;
		m_timesCrossedCenterThisWave++;
		m_timesCrossedCenterTotal++;
	}

	//crossingtimes
	if (m_timesCrossedCenterIsOnTopSide && m_player->m_bounds->getMinY() > getWorldCY()) {
		m_timesCrossedCenterIsOnTopSide = false;
		m_timesCrossedCenterVerticalThisWave++;
		m_timesCrossedCenterVerticalTotal++;
	} else if (!m_timesCrossedCenterIsOnTopSide && m_player->m_bounds->getMaxY() < getWorldCY()) {
		m_timesCrossedCenterIsOnTopSide = true;
		m_timesCrossedCenterVerticalThisWave++;
		m_timesCrossedCenterVerticalTotal++;
	}

	if (countAdvances == 0 && m_player->m_alive) {
		m_waveProgressionByMovementCount++;
		nextWave();
		return;
	}

	// Count enemies - none = next wave.
	if (m_enemies->sizeActive() == 0 && m_spawnEnemies.size() == 0 && m_player->m_alive) {
		m_waveProgressionByKillsCount++;
		nextWave();
		return;
	}
}
float InGameState::getWorldCY() {
	return worldStartY + (worldHeight * worldTileSize * 0.5f);
}

void InGameState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {

//	DefaultGame* dg = DefaultGame::getInstance();
	//dg->m_hsvShader->set(0.25f, 1.0f, 1.0f);
	//dg->m_hsvShader->start();

	// SHAKE IT
	r->pushMatrix();
	r->translate(m_cameraShake->getXOffset(), m_cameraShake->getYOffset());

	r->setDrawColor(Color::white);
	m_tiles->renderAll(container, r);
	m_flowers->renderAll(container, r);
	m_buzzsaws->renderAll(container, r);
	m_arrows->renderAll(container, r);
	m_arrowBoxes->renderAll(container, r);
	m_bombs->renderAll(container, r);
	m_particles->renderAll(container, r);
	m_enemies->renderAll(container, r);
	m_player->render(container, r);

	// STOP SHAKING IT
	r->popMatrix();

	// ui
	float rightSideIcons = container->getWidth() - 35;
	r->setDrawColor(Color::white);
	m_iconHand->drawCenteredScaled(rightSideIcons + 10, container->getHeight() - 10, 1.5f, 1.5f);
	if (m_player->m_currentWeapon == Player::WEAPON_GLOVE) {
		m_iconGlove->drawCenteredScaled(rightSideIcons + 23, container->getHeight() - 9, 1.5f, 1.5f);
	} else if (m_player->m_currentWeapon == Player::WEAPON_BOMB) {
		m_iconBomb->drawCenteredScaled(rightSideIcons + 23, container->getHeight() - 9.5, 1.5f, 1.5f);
	}

	m_iconCalendar->drawCenteredScaled(14, container->getHeight() - 10, 1.5, 1.5f);
	r->drawString(StringUtil::append("",m_waveNumber+1), 26, container->getHeight()-11, Renderer::ALIGN_LEFT, Renderer::ALIGN_CENTER, 0.0f, 1.4f);
	
	if (m_flashTimer > 0.0f) {
		float alpha = Easing::easebetween(Easing::QUADRATIC_IN, m_flashTimer, 1.0f, 0.0f, m_flashDuration);
		r->setDrawColorf(1.0f, 1.0f, 1.0f, alpha);
		r->fillRect(0,0,container->getWidth(), container->getHeight());
	}

	if (m_waveIntroTimer > 0.0f) {
		float textRotation = 0.0f;
		float textScale = 1.0f;
		if (m_waveIntroTimer < m_waveIntroDuration * 0.25f) {
			textRotation = Easing::easebetween(Easing::QUADRATIC_IN_OUT, m_waveIntroTimer, 0.0f, 720, m_waveIntroDuration * 0.25f);
			textScale = Easing::easebetween(Easing::QUADRATIC_IN_OUT, m_waveIntroTimer, 0.0f, 1, m_waveIntroDuration * 0.25f);
		} else if (m_waveIntroTimer > m_waveIntroDuration * 0.75f) {
			textRotation = Easing::easebetween(Easing::QUADRATIC_IN_OUT, m_waveIntroTimer - (m_waveIntroDuration * 0.75f), 720.0f, 720*2, m_waveIntroDuration * 0.25f);
			textScale = Easing::easebetween(Easing::QUADRATIC_IN_OUT, m_waveIntroTimer - (m_waveIntroDuration * 0.75f), 1.0f, 0, m_waveIntroDuration * 0.25f);
		}

		float worldCenterY = worldStartY + (worldHeight*worldTileSize*0.5f);

		r->drawString("DAY", 								container->getWidth()*0.5f, worldCenterY-(container->getHeight()*0.1f), Renderer::ALIGN_CENTER, Renderer::ALIGN_CENTER, textRotation, 1.5f*textScale);
		r->drawString(StringUtil::append("",m_waveNumber+1), container->getWidth()*0.5f, worldCenterY+(container->getHeight()*0.05f), Renderer::ALIGN_CENTER, Renderer::ALIGN_CENTER, textRotation, 2.0f*textScale);
	}

	//r->drawString(StringUtil::append("",m_timesCrossedCenterTotal), container->getWidth()*0.7f, container->getHeight()-9, Renderer::ALIGN_CENTER, Renderer::ALIGN_CENTER, 0.0f, 1.0f);
	//r->drawString(StringUtil::append("",m_timesCrossedCenterVerticalTotal), container->getWidth()*0.8f, container->getHeight()-9, Renderer::ALIGN_CENTER, Renderer::ALIGN_CENTER, 0.0f, 1.0f);

	//dg->m_hsvShader->stop();

}

InGameState::~InGameState() {

}

