
#ifndef ARK2D_DEFAULTGAME_H_
#define ARK2D_DEFAULTGAME_H_

#include <ARK2D/Audio/Sound.h>
#include <ARK2D/Audio/SoundStore.h>
#include <ARK2D/Core/Graphics/Image.h>
#include <ARK2D/Core/Graphics/SpriteSheetDescription.h>
#include <ARK2D/Core/Graphics/Shaders/HSVShader.h>
#include <ARK2D/Core/State/StateBasedGame.h>
#include <ARK2D/Core/Tween/Easing.h>

#include "states/BlankState.h"
#include "states/InGameState.h"
#include "states/InstructionsState.h"
#include "states/MenuState.h"
#include "states/SplashState.h"
#include "states/SummaryState.h"

#include "util/FMOD.h" 

class StatesList {
	public:
		static const unsigned int STATE_BLANK = 0;
		static const unsigned int STATE_LOADING = 1;
		static const unsigned int STATE_SPLASH = 2;
		static const unsigned int STATE_MENU = 3;
		static const unsigned int STATE_INSTRUCTIONS = 4;
		static const unsigned int STATE_INGAME = 5;
		static const unsigned int STATE_SUMMARY = 6;
};

class DefaultGame : public StateBasedGame {
	public:

		BlankState* stateBlank = NULL;
		SplashState* stateSplash = NULL;
		MenuState* stateMenu = NULL;
		InstructionsState* stateInstructions = NULL;
		InGameState* stateInGame = NULL;
		SummaryState* stateSummary = NULL;

		Image* spritesheet = NULL;
		SpriteSheetDescription* desc = NULL;

		ArkFMOD* m_fmod;
		ArkFMODSound* m_musicSlow;
		ArkFMODSound* m_musicMedium;
		ArkFMODSound* m_musicFast;
		ArkFMODSound* m_musicCurrent;
		ArkFMODSound* m_sfxSelect;
		ArkFMODSound* m_sfxPlayerDie;
		ArkFMODSound* m_sfxButterflySmallDie;
		ArkFMODSound* m_sfxPunchCharge;
		ArkFMODSound* m_sfxPunchGo;
		ArkFMODSound* m_sfxBomb;
		ArkFMODSound* m_sfxBombPlace;
		ArkFMODSound* m_sfxBombFuse;
		ArkFMODSound* m_sfxTileAdvance;
		ArkFMODSound* m_sfxArrowFire;
		ArkFMODSound* m_sfxWaveUp;

		//Sound* m_music = NULL;
		Sound* m_sfxJump = NULL;

		HSVShader* m_hsvShader = NULL;

		float m_bgRotateTimer;

		DefaultGame(string title);
		virtual void initStates(GameContainer* container);
		virtual void update(GameContainer* container, GameTimer* timer);
		virtual void render(GameContainer* container, Renderer* r);
		virtual void render();
		virtual void resize(GameContainer* container, int width, int height);

		virtual void pause();
		
		virtual ~DefaultGame();

		float juiceRotation(float maxRotation, float timer, float duration) {
			float rotation = 0.0f;
			float segment = duration / 4.0f;
			if (timer <= segment) {
				rotation = Easing::ease(Easing::QUADRATIC_OUT, timer, 0.0f, maxRotation, segment);
			} else if (timer <= 2*segment) {
				rotation = Easing::ease(Easing::QUADRATIC_IN, timer-segment, maxRotation, maxRotation*-1, segment);
			} else if (timer <= 3*segment) {
				rotation = Easing::ease(Easing::QUADRATIC_OUT, timer-(2*segment), 0.0f, maxRotation*-1, segment);
			} else {
				rotation = Easing::ease(Easing::QUADRATIC_IN, timer-(3*segment), maxRotation*-1, maxRotation, segment);
			}
			return rotation;
		}
		float juiceScale(float maxScale, float timer, float duration) {
			float scale = 0.0f;
			float segment = duration / 4.0f;
			if (timer <= segment) {
				scale = Easing::ease(Easing::QUADRATIC_OUT, timer, 1.0f, maxScale, segment);
			} else if (timer <= 2*segment) {
				scale = Easing::ease(Easing::QUADRATIC_IN, timer-segment, 1.0f+ maxScale, maxScale*-1, segment);
			} else if (timer <= 3*segment) {
				scale = Easing::ease(Easing::QUADRATIC_OUT, timer-(2*segment), 1.0f, maxScale*-1, segment);
			} else {
				scale = Easing::ease(Easing::QUADRATIC_IN, timer-(3*segment), 1.0f - maxScale, maxScale, segment);
			}
			return scale;
		}

		static DefaultGame* getInstance();
};

#endif /* ARK2D_DEFAULTGAME_H_ */
