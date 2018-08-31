
#include "MenuState.h"
#include "../DefaultGame.h"
#include "../objects/Tile.h"
#include <ARK2D/Core/State/Transition/FadeToColourTransition.h>
#include <ARK2D/Core/State/Transition/FadeFromColourTransition.h>
#include <ARK2D/Core/Controls/Accelerometer.h>

MenuState::MenuState():
	GameState() {

}

unsigned int MenuState::id() {
	return StatesList::STATE_MENU;
}

void MenuState::enter(GameContainer* container, StateBasedGame* game, GameState* from) {
	DefaultGame* dg = DefaultGame::getInstance();

	if (!dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->play(); 
	}
	if (dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->setLowpass(true); 
		dg->m_musicCurrent->setLowpassFrequency(500.0f);
	}
}

void MenuState::leave(GameContainer* container, StateBasedGame* game, GameState* to) {
	DefaultGame* dg = DefaultGame::getInstance();
	if (dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->setLowpass(true); 
		dg->m_musicCurrent->setLowpassFrequency(22100.0f);
	}
}

void MenuState::init(GameContainer* container, StateBasedGame* game) {
	DefaultGame* dg = DefaultGame::getInstance();
	m_selectedIndex = 0;

	background = dg->spritesheet->getSubImage(dg->desc->getItemByName("background.png"));
	background->setCenterOfRotation(background->getWidth()*0.5f, background->getHeight()*0.5f);

	logo = dg->spritesheet->getSubImage(dg->desc->getItemByName("menu.png"));
	logo->setCenterOfRotation(logo->getWidth()*0.5f, logo->getHeight()*0.5f);
}

void MenuState::update(GameContainer* container, StateBasedGame* game, GameTimer* timer) {
	DefaultGame* dg = DefaultGame::getInstance();
	Input* i = ARK2D::getInput();

	/*if (i->isKeyPressed(Input::KEY_W) ||
		i->isKeyPressed(Input::KEY_UP) ||
		i->isGamepadButtonPressed(Gamepad::DPAD_UP)) {
		m_selectedIndex--;
		if (m_selectedIndex < MENU_BEGIN) {
			m_selectedIndex = MENU_END;
		}
	}
	if (i->isKeyPressed(Input::KEY_S) ||
		i->isKeyPressed(Input::KEY_DOWN) ||
		i->isGamepadButtonPressed(Gamepad::DPAD_DOWN)) {
		m_selectedIndex++;
		if (m_selectedIndex > MENU_END) {
			m_selectedIndex = MENU_BEGIN;
		}
	}*/


	if (!dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->play(); 
		dg->m_musicCurrent->setLowpass(true); 
	}
	dg->m_musicCurrent->setLowpassFrequency(500.0f);
	//if (dg->m_musicMedium->isPlaying()) { dg->m_musicMedium->stop(); }
	//if (dg->m_musicFast->isPlaying()) { dg->m_musicFast->stop(); }

	auto playEvent = [this, dg] {
		dg->m_sfxSelect->play();

		dg->stateInGame->reset();
		dg->stateInGame->start();
		dg->enterState(dg->stateInGame, 
			new FadeToColourTransition(0.25f, new Color(*Tile::s_bgColor)),
			new FadeFromColourTransition(0.25f, new Color(*Tile::s_bgColor))
		);
	};

	if (i->isKeyPressed(Input::KEY_ENTER) ||
		i->isGamepadButtonPressed(Gamepad::BUTTON_START) ||
		i->isGamepadButtonPressed(Gamepad::BUTTON_A) ||
		(container->isTouchMode() && i->isKeyPressed(Input::MOUSE_BUTTON_LEFT))
		) {
		if (m_selectedIndex == MENU_PLAY) {
			playEvent();
		}
		else if (m_selectedIndex == MENU_INSTRUCTIONS) {
			game->enterState(dg->stateInstructions);
		}
		else if (m_selectedIndex == MENU_EXIT) {
			container->close();
		}
	}
}

void MenuState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {
	DefaultGame* dg = DefaultGame::getInstance();
	InGameState* igs = dg->stateInGame;
	//r->drawString("Menu", 20, 20, Renderer::ALIGN_LEFT, Renderer::ALIGN_TOP);

	r->setDrawColor(Color::white);


	float rotation = dg->juiceRotation(5.0f, dg->m_bgRotateTimer, 3.0f);

	background->setRotation(rotation);
	background->drawCenteredScaled(container->getWidth()*0.5f,container->getHeight()*0.5f, 0.7f, 0.7f);
	logo->draw(0,0,container->getWidth(),container->getHeight());

	// Accelerometer* acc = Accelerometer::getInstance();
	// if (container->isTouchMode() && acc->isEnabled()) {
	// 	r->drawString( StringUtil::appendf("x: ", acc->acceleration()->x), 10, 10);
	// 	r->drawString( StringUtil::appendf("y: ", acc->acceleration()->y), 10, 20);
	// 	r->drawString( StringUtil::appendf("z: ", acc->acceleration()->z), 10, 30);
	// }

	


	/*return; 
	r->setDrawColor(Color::white);

	int rooty = 320;
	int wid = (signed int) container->getWidth();

	if (m_selectedIndex == MENU_PLAY) {
		r->getFont()->drawStringCenteredAt("< Play >", wid/2, rooty);
	}
	else {
		r->getFont()->drawStringCenteredAt("Play", wid/2, rooty);
	}

	if (m_selectedIndex == MENU_INSTRUCTIONS) {
		r->getFont()->drawStringCenteredAt("< Instructions >", wid/2, rooty+40);
	}
	else {
		r->getFont()->drawStringCenteredAt("Instructions", wid/2, rooty+40);
	}

	if (m_selectedIndex == MENU_EXIT) {
		r->getFont()->drawStringCenteredAt("< Exit >", wid/2, rooty+80);
	}
	else {
		r->getFont()->drawStringCenteredAt("Exit", wid/2, rooty+80);
	}*/
}

MenuState::~MenuState() {

}
