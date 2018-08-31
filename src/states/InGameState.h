
#ifndef ARK2D_DEFAULTGAME_INGAMESTATE_H_
#define ARK2D_DEFAULTGAME_INGAMESTATE_H_

#include <ARK2D/Core/State/GameState.h>

class DefaultGame;

class Object;
class BlankObject;
class Player;
class Pickup;
class Explosion;
class Tile;
class Enemy;
class MyParticle;
class Flower;
class Bomb;
class ArrowBox;
class Arrow;
class Buzzsaw;

class SpawnEnemyEvent {
	public:
		int enemyType;
		float delay;
};

class InGameState : public GameState {
	public:

		Pool<Player*>* m_players; // width 7
		Pool<Enemy*>* m_enemies;
		Pool<MyParticle*>* m_particles;
		Pool<Flower*>* m_flowers;
		Pool<Bomb*>* m_bombs;
		Pool<ArrowBox*>* m_arrowBoxes;
		Pool<Arrow*>* m_arrows;
		Pool<Buzzsaw*>* m_buzzsaws;

		Player* m_player;

		Pool<Tile*>* m_tiles;
		vector<Tile*> m_tilesLinear;

		int worldStartX;
		int worldStartY;
		int worldWidth;
		int worldHeight;
		int worldTileSize;

		Image* m_iconHand;
		Image* m_iconGlove;
		Image* m_iconBomb;
		Image* m_iconCalendar;

		int m_waveNumber;
		int m_waveProgressionByMovementCount;
		int m_waveProgressionByKillsCount;

		vector<SpawnEnemyEvent> m_spawnEnemies;

		float m_deadTimer;
		float m_deadDuration;

		float m_flashTimer;
		float m_flashDuration;

		float m_bombExplodedFilterTimer;
		float m_bombExplodedFilterDuration;

		CameraShake* m_cameraShake;

		float m_waveIntroTimer;
		float m_waveIntroDuration;

		float m_timeSpentInMiddleThisWave;
		float m_timeSpentOnEdgeThisWave;
		
		int m_timesCrossedCenterThisWave;
		int m_timesCrossedCenterTotal;
		bool m_timesCrossedCenterIsOnLeftSide;

		int m_timesCrossedCenterVerticalThisWave;
		int m_timesCrossedCenterVerticalTotal;
		bool m_timesCrossedCenterIsOnTopSide;

		bool m_processingWave;

		bool m_paused;

		InGameState();
		void enter(GameContainer* container, StateBasedGame* game, GameState* from);
		void leave(GameContainer* container, StateBasedGame* game, GameState* to);

		Tile* getTileAt(int x, int y);

		unsigned int id();
		void reset();
		void start();
		void startWave();
		void nextWave();
		void spawnEnemy(int type);
		void spawnButterflySmall();
		void spawnButterflyLarge();
		void spawnSlug();
		void spawnArrowBox();
		void spawnBuzzsaw();
		float getWorldCY();
		Tile* getRandomSolidTile();
		Tile* getTopOrBottomEmptySolidTile();
		Tile* getLeftOrRightEmptySolidTile();
		void spawnBlood(float x, float y, float radius, int num);
		void init(GameContainer* container, StateBasedGame* game);
		void update(GameContainer* container, StateBasedGame* game, GameTimer* timer);
		void render(GameContainer* container, StateBasedGame* game, Renderer* r);

		virtual ~InGameState();
};

#endif /* ARK2D_DEFAULTGAME_INGAMESTATE_H_ */
