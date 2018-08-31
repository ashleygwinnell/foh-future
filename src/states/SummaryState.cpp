
#include "SummaryState.h"
#include "../DefaultGame.h"
#include "../objects/Player.h"
#include "../objects/Tile.h"

#include <ARK2D/Core/State/Transition/FadeToColourTransition.h>
#include <ARK2D/Core/State/Transition/FadeFromColourTransition.h>


SummaryState::SummaryState():
    GameState() {

}

unsigned int SummaryState::id() {
	return StatesList::STATE_SUMMARY;
}

void SummaryState::enter(GameContainer* container, StateBasedGame* game, GameState* from) { 
	DefaultGame* dg = DefaultGame::getInstance();
	if (!dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->play(); 
	}
	if (dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->setLowpass(true); 
		dg->m_musicCurrent->setLowpassFrequency(500.0f);
	}
}
void SummaryState::leave(GameContainer* container, StateBasedGame* game, GameState* to) { 
	
}

void SummaryState::init(GameContainer* container, StateBasedGame* game) {
	DefaultGame* dg = DefaultGame::getInstance();
	ending = dg->spritesheet->getSubImage(dg->desc->getItemByName("ending.png"));
}

void SummaryState::update(GameContainer* container, StateBasedGame* game, GameTimer* timer) {
	
	DefaultGame* dg = DefaultGame::getInstance();
	Input* in = ARK2D::getInput();

	if (!dg->m_musicCurrent->isPlaying()) { 
		dg->m_musicCurrent->play(); 
		dg->m_musicCurrent->setLowpass(true); 
	}
	dg->m_musicCurrent->setLowpassFrequency(500.0f);

	if (in->isKeyPressed(Input::KEY_ENTER) ||
        in->isGamepadButtonPressed(Gamepad::BUTTON_START) ||
        in->isGamepadButtonPressed(Gamepad::BUTTON_A) || 
        (container->isTouchMode() && in->isKeyPressed(Input::MOUSE_BUTTON_LEFT))
        ) {
		dg->enterState(dg->stateMenu,
			new FadeToColourTransition(0.25f, new Color(*Tile::s_bgColor)),
			new FadeFromColourTransition(0.25f, new Color(*Tile::s_bgColor))
		);
	}
}  

void SummaryState::render(GameContainer* container, StateBasedGame* game, Renderer* r) {
	//r->drawString("Summary State", 20, 20, Renderer::ALIGN_LEFT, Renderer::ALIGN_TOP);
	DefaultGame* dg = DefaultGame::getInstance();
	MenuState* menu = dg->stateMenu;

	r->setDrawColor(Color::white);

	float rotation = dg->juiceRotation(5.0f, dg->m_bgRotateTimer, 3.0f);
	//menu->background->draw(0,0,container->getWidth(),container->getHeight());

	menu->background->setRotation(rotation);
	menu->background->drawCenteredScaled(container->getWidth()*0.5f,container->getHeight()*0.5f, 0.7f, 0.7f);

	ending->draw(0,0,container->getWidth(),container->getHeight());

	int reason = dg->stateInGame->m_player->m_dieReason;
	if (reason == Player::DIE_FALL) {
		r->drawString("YOU FELL TO YOUR DEMISE", container->getWidth()*0.5f, 70, 0, 0, 0.0, 1.0f);	
		r->drawString(StringUtil::append("ON DAY ", dg->stateInGame->m_waveNumber+1), container->getWidth()*0.5f, 80, 0, 0, 0.0, 1.0f);
	}
	else if (reason == Player::DIE_BOMB) {
		r->drawString("YOU EXPLODED", container->getWidth()*0.5f, 70, 0, 0, 0.0, 1.0f);	
		r->drawString(StringUtil::append("ON DAY ", dg->stateInGame->m_waveNumber+1), container->getWidth()*0.5f, 80, 0, 0, 0.0, 1.0f);
	}
	else if (reason == Player::DIE_ARROW) {
		r->drawString("SHOT THROUGH THE HEART", container->getWidth()*0.5f, 70, 0, 0, 0.0, 1.0f);	
		r->drawString(StringUtil::append("ON DAY ", dg->stateInGame->m_waveNumber+1), container->getWidth()*0.5f, 80, 0, 0, 0.0, 1.0f);
	}
	else if (reason == Player::DIE_BUZZSAW) {
		r->drawString("YOU BECAME MINCE MEAT", container->getWidth()*0.5f, 70, 0, 0, 0.0, 1.0f);	
		r->drawString(StringUtil::append("ON DAY ", dg->stateInGame->m_waveNumber+1), container->getWidth()*0.5f, 80, 0, 0, 0.0, 1.0f);
	}
	
	

}

SummaryState::~SummaryState() {

}

