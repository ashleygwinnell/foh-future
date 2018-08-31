
#include "DefaultGame.h"

DefaultGame::DefaultGame(string title):
	StateBasedGame(title) {

}

void DefaultGame::initStates(GameContainer* container) {

	m_fmod = new ArkFMOD();
	m_fmod->init();

	m_musicSlow = new ArkFMODSound(m_fmod, "music/slow.ogg");
	m_musicMedium = new ArkFMODSound(m_fmod, "music/medium.ogg");
	m_musicFast = new ArkFMODSound(m_fmod, "music/fast.ogg");
	m_musicCurrent = m_musicSlow;

	//m_musicSlow->play();

	m_sfxSelect = new ArkFMODSound(m_fmod, "sfx/select.wav");
	m_sfxPlayerDie = new ArkFMODSound(m_fmod, "sfx/player_die.wav");
	m_sfxButterflySmallDie = new ArkFMODSound(m_fmod, "sfx/butterfly_small_die.wav");
	m_sfxPunchCharge = new ArkFMODSound(m_fmod, "sfx/punch_charge.wav");
	m_sfxPunchGo = new ArkFMODSound(m_fmod, "sfx/punch_go.wav");
	m_sfxBomb = new ArkFMODSound(m_fmod, "sfx/bomb.wav");
	m_sfxBombPlace = new ArkFMODSound(m_fmod, "sfx/bomb_place.wav");
	m_sfxBombFuse = new ArkFMODSound(m_fmod, "sfx/bomb_fuse.wav");
	m_sfxTileAdvance = new ArkFMODSound(m_fmod, "sfx/tile_advance.wav");
	m_sfxArrowFire = new ArkFMODSound(m_fmod, "sfx/arrow_fire.wav");
	m_sfxWaveUp = new ArkFMODSound(m_fmod, "sfx/next_wave.wav");

	spritesheet = Resource::get("all.png")->asImage();
	desc = Resource::get("all.spritesheetdescription")->asSpriteSheetDescription();

	stateBlank = new BlankState();
	stateSplash = new SplashState();
	stateMenu = new MenuState();
	stateInstructions = new InstructionsState();
	stateInGame = new InGameState();
	stateSummary = new SummaryState();

	//m_hsvShader = new HSVShader();
	//m_hsvShader->load();

	addState(stateBlank);
	addState(stateSplash);
	addState(stateMenu);
	addState(stateInstructions);
	addState(stateInGame);
	addState(stateSummary);

	enterState(stateMenu);

	m_bgRotateTimer = 0.0f;

	#ifdef ARK2D_EMSCRIPTEN_JS
		container->setSize(140*5, 100*5);
	#else 
		container->setSize(140*6, 100*6);
	#endif
}

void DefaultGame::pause() {
	StateBasedGame::pause();
	//if (m_music != NULL) { m_music->pause(); }
}

void DefaultGame::update(GameContainer* container, GameTimer* timer) {
	StateBasedGame::update(container, timer);

	Input* i = ARK2D::getInput();
	if (i->isGamepadButtonPressed(Gamepad::BUTTON_ACTIVATE) || i->isKeyPressed(Input::KEY_F)) {
		container->setFullscreen(!container->isFullscreen());

		//container->setSize(140*6, 100*6);
		//container->resizeWindowToFitViewport();
		
	}

	m_bgRotateTimer += timer->getDelta();
	if (m_bgRotateTimer >= 3.0f) {
		m_bgRotateTimer -= 3.0f;
	}

	//if (stateLoading->m_doneLoading) {
		if (i->isKeyPressed(Input::KEY_M)) {
			float newVol = (SoundStore::getInstance()->getVolumeByGroupId(0)==1.0f)?0.0f:1.0f;
			//SoundStore::getInstance()->setVolumeByGroupId(0, newVol);
		}
		 
		m_fmod->update(); 
		if (m_musicSlow != NULL && m_musicMedium != NULL && m_musicFast != NULL) {
			//if (!m_music->isPlaying()) {
				//m_music->play();
			//}
			// if (getCurrentState() != stateInGame) {
			// 	if (m_musicSlow->isPlaying()) {
			// 		m_musicSlow->setLowpass(true); 
			// 		m_musicSlow->setLowpassFrequency(500.0f);
			// 	} 
			// } else {
			// 	if (m_musicSlow->isPlaying()) {
			// 		m_musicSlow->setLowpass(true); 
			// 		m_musicSlow->setLowpassFrequency(22100.0f);
			// 	}
			// }
			// 	if (m_musicSlow->isPlaying()) m_musicSlow->setLowpass(true); 
			// 	if (m_musicMedium->isPlaying()) m_musicMedium->setLowpass(true);	
			// 	if (m_musicFast->isPlaying()) m_musicFast->setLowpass(true);	
			// 	if (m_musicSlow->isPlaying()) m_musicSlow->setLowpassFrequency(500.0f);
			// 	if (m_musicMedium->isPlaying()) m_musicMedium->setLowpassFrequency(500.0f);
			// 	if (m_musicFast->isPlaying()) m_musicFast->setLowpassFrequency(500.0f);
			// } else { 
			// 	if (m_musicSlow->isPlaying()) m_musicSlow->setLowpass(true);
			// 	if (m_musicMedium->isPlaying()) m_musicMedium->setLowpass(true);
			// 	if (m_musicFast->isPlaying()) m_musicFast->setLowpass(true);
			// 	if (m_musicSlow->isPlaying()) m_musicSlow->setLowpassFrequency(22100.0f);
			// 	if (m_musicMedium->isPlaying()) m_musicMedium->setLowpassFrequency(22100.0f);
			// 	if (m_musicFast->isPlaying()) m_musicFast->setLowpassFrequency(22100.0f);
			// }
		}
	//}
}

void DefaultGame::render(GameContainer* container, Renderer* r) {
	StateBasedGame::render(container, r);
}
void DefaultGame::render() {
    GameContainer* container = ARK2D::getContainer();
	Renderer* r = ARK2D::getRenderer();
	r->setScissorBoxColors(Color("#002503"), Color("#002503"), Color("#002503"), Color("#002503"));
	r->setDrawColor("#002503", 1.0f);
	r->fillRect(0, 0, container->getWidth(), container->getHeight());

	r->setDrawColor(Color::white);
	StateBasedGame::render();
}

void DefaultGame::resize(GameContainer* container, int width, int height) {
	StateBasedGame::resize(container, width, height);
}

DefaultGame* DefaultGame::getInstance() {
    return dynamic_cast<DefaultGame*>(ARK2D::getGame());
}

DefaultGame::~DefaultGame() {

}
