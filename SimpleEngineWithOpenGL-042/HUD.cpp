#include "HUD.h"
#include "Assets.h"
#include "Game.h"
#include "ShipActor.h"

HUD::HUD():
	UIScreen(),
	font(Assets::getFont("Carlito"))
{
	crosshair = &Assets::getTexture("Crosshair");
	font = Assets::getFont("Carlito");
	HPCount = font.renderText("100",Color::green,30);
	HPLogo = &Assets::getTexture("HPLogo");
	HPBG = &Assets::getTexture("DialogBG");
}

HUD::~HUD()
{
}

void HUD::update(float dt)
{
	UIScreen::update(dt);
}

void HUD::draw(Shader& shader)
{
	drawTexture(shader, crosshair, Vector2::zero, 2.0f);


	const Vector2 radarPosition{ -390.0f, 275.0f };
	
	drawTexture(shader, HPBG, Vector2(radarPosition.x - 150, -radarPosition.y - 110));
	drawTexture(shader, HPCount, Vector2(radarPosition.x, -radarPosition.y-30));
	drawTexture(shader, HPLogo, Vector2(radarPosition.x-60, -radarPosition.y-30));
}

void HUD::updateHP(int hp)
{
	Vector3 ColorUsed = Color::green;
	if (hp <= 0) {
		ColorUsed = Color::red;
	}
	HPCount = font.renderText(std::to_string(hp),ColorUsed, 30);
}
