#include "pile.h"

bool Pile::canAddCard(const Card& card) const {
    if (cards.empty())
        return card.rank == Rank::KING;

    const Card* topCard = cards.back().get();

    if (!topCard->show)
        return false;

    return (card.isRed != topCard->isRed) &&
        (static_cast<int>(card.rank) == static_cast<int>(topCard->rank) - 1);
}

void Pile::addCard(std::unique_ptr<Card> card) {
    cards.push_back(std::move(card));
}

std::unique_ptr<Card> Pile::removeCard() {
    if (cards.empty())
        return nullptr;

    std::unique_ptr<Card> removedCard = std::move(cards.back());
    cards.pop_back();

    if (!cards.empty() && !cards.back()->show)
        cards.back()->show = true;

    return removedCard;
}

Card Pile::check() {
    if (cards.empty())
        return Card(Suit::CLUBS, Rank::ACE);

    return *cards.back();
}

void Pile::revealCard() {
    if (!cards.empty())
        cards.back()->show = true;
}

int Pile::getShownCards() {
    int count = 0;
    for (const auto& card : cards) {
        if (card->show)
            count++;
    }
    return count;
}

Card* Pile::getCard(size_t index) const {
    if (index >= cards.size())
        return nullptr;

    return cards[index].get();
}

void Pile::arrangeCards(Vector2 startPos, Vector2 offset) {
    for (size_t i = 0; i < cards.size(); i++) {
        Vector2 cardPos = {
            startPos.x + offset.x * i,
            startPos.y + offset.y * i
        };
        cards[i]->position = cardPos;
        cards[i]->depth = 50 + static_cast<int>(i);
    }
}