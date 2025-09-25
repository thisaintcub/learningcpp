#pragma once
#include "card.h"
#include <vector>
#include <random>
#include <memory>

class Deck {
public:
    Deck();

    void initialize();
    void shuffle();
    std::unique_ptr<Card> draw();
    bool isEmpty() const { return cards.empty(); }
    size_t size() const { return cards.size(); }

private:
    std::vector<std::unique_ptr<Card>> cards;
    std::mt19937 rng;
};