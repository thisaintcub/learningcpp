#pragma once

#include "../../core/object/object.h"
#include "carddata.h"
#include <raylib.h>
#include <string>
#include <unordered_map>

class Card : public Object {
public:
	Vector2 position = { 0, 0 };
	Vector2 size = { 85.5f, 118.5f };

	bool isDragging = false;

	Card(Suit s, Rank r);

	Suit suit;
	Rank rank;
	bool show = false;
	bool isRed = false;

	void update(float deltaTime) override;
	void draw() override;

	bool isMouseOver() const;
	Rectangle getBounds() const;

private:
	std::string getSuitString() const;
};