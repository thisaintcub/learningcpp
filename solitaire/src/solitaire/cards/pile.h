#pragma once

#include "card.h"
#include <vector>
#include <memory>

class Pile {
public:
	Pile() = default;

	bool canAddCard(const Card& card) const;
	void addCard(std::unique_ptr<Card> card);
	std::unique_ptr<Card> removeCard();
	Card check();

	size_t size() { return cards.size(); }
	bool isEmpty() { return cards.empty(); }

	void revealCard();
	int getShownCards();

	Card* getCard(size_t index) const;
	void arrangeCards(Vector2 startPos, Vector2 offset = { 0, 20 });

	const std::vector<std::unique_ptr<Card>>& getAllCards() const { return cards; }
private:
	std::vector<std::unique_ptr<Card>> cards;
};