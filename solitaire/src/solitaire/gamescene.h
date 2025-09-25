#pragma once
#include "../core/scene/scene.h"
#include "cards/deck.h"
#include "cards/pile.h"
#include <array>

class GameScene : public Scene {
public:
    GameScene();

    void create() override;
    void update(float deltaTime) override;
    void draw() override;

private:
    Deck deck;
    std::array<Pile, 7> tableau;

    static constexpr float CARD_WIDTH = 85.5f;
    static constexpr float CARD_HEIGHT = 118.5f;
    static constexpr float PILE_SPACING = 100.0f;
    static constexpr float TABLEAU_START_X = 290.0f;
    static constexpr float TABLEAU_START_Y = 150.0f;
    static constexpr float CARD_STACK_OFFSET = 20.0f;

    void dealCards();
    void updateCardPositions();
    void handleCardInteraction();
    Card* findDraggedCard();
    Pile* findDropTarget(Card* draggedCard);
};