#pragma once
#include "UIScreen.h"

class HUD : public UIScreen
{
public:
	HUD();
	~HUD();

	void update(float dt) override;
	void draw(class Shader& shader) override;

	void updateHP(int hp);

protected:

	

	class Texture* crosshair;
	class Texture* HPLogo;
	class Texture* HPBG;
	class Texture* HPCount;
	class Font& font;
};

