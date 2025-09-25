#include "deck.h"
#include <algorithm>
#include <chrono>

Deck::Deck() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
}

void Deck::initialize() {
    cards.clear();

    Suit suits[] = { Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES };

    for (Suit suit : suits) {
        for (int rankInt = 1; rankInt <= 13; rankInt++) {
            Rank rank = static_cast<Rank>(rankInt);
            cards.push_back(std::make_unique<Card>(suit, rank));
        }
    }
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

std::unique_ptr<Card> Deck::draw() {
    if (cards.empty()) {
        return nullptr;
    }

    std::unique_ptr<Card> drawnCard = std::move(cards.back());
    cards.pop_back();
    return drawnCard;
}