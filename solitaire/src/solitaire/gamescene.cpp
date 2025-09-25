#include "gamescene.h"
#include "menuscene.h"
#include "../core/util/globals.h"
#include <iostream>

GameScene::GameScene() {
    bgColor = DARKGREEN;
}

void GameScene::create() {
    Scene::create();

    deck.initialize();
    deck.shuffle();

    dealCards();
    updateCardPositions();
}

void GameScene::update(float deltaTime) {
    Scene::update(deltaTime);

    handleCardInteraction();

    if (IsKeyPressed(KEY_ESCAPE))
        Globals::game->switchScene<MenuScene>();
}

void GameScene::draw() {
    Scene::draw();

    for (int i = 0; i < 7; i++) {
        if (tableau[i].isEmpty()) {
            Vector2 slotPos = {
                TABLEAU_START_X + i * PILE_SPACING,
                TABLEAU_START_Y
            };
        }
    }
}

void GameScene::dealCards() {
    for (int col = 0; col < 7; col++) {
        for (int row = 0; row <= col; row++) {
            auto card = deck.draw();
            if (card) {
                card->show = (row == col);

                card->position.x = TABLEAU_START_X + col * PILE_SPACING;
                card->position.y = TABLEAU_START_Y + row * CARD_STACK_OFFSET;

                Card* cardPtr = add(std::move(card));

                std::cout << "Dealt card to pile " << col << ", row " << row <<
                    " at position (" << cardPtr->position.x << ", " << cardPtr->position.y << ")" << std::endl;
            }
        }
    }
}

void GameScene::updateCardPositions() {
    std::cout << "Total cards in scene: " << findObjects<Card>().size() << std::endl;
}

void GameScene::handleCardInteraction() {
    Card* draggedCard = findDraggedCard();

    if (draggedCard && !IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        Pile* targetPile = findDropTarget(draggedCard);

        updateCardPositions();
    }
}

Card* GameScene::findDraggedCard() {
    auto cards = findObjects<Card>();
    for (Card* card : cards) {
        if (card->isDragging) {
            return card;
        }
    }
    return nullptr;
}

Pile* GameScene::findDropTarget(Card* draggedCard) {
    if (!draggedCard) return nullptr;

    Vector2 cardCenter = {
        draggedCard->position.x + CARD_WIDTH * 0.5f,
        draggedCard->position.y + CARD_HEIGHT * 0.5f
    };

    for (int i = 0; i < 7; i++) {
        Vector2 pilePos = {
            TABLEAU_START_X + i * PILE_SPACING,
            TABLEAU_START_Y
        };

        Rectangle pileArea = {
            pilePos.x,
            pilePos.y,
            CARD_WIDTH,
            CARD_HEIGHT + tableau[i].size() * CARD_STACK_OFFSET
        };

        if (CheckCollisionPointRec(cardCenter, pileArea))
            return &tableau[i];
    }

    return nullptr;
}