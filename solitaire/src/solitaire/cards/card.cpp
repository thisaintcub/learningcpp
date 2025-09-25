#include "card.h"
#include <iostream>

static std::unordered_map<std::string, Texture2D> cardTextures;
static Texture2D cardBackTexture;
static Texture2D cardSlotTexture;
static bool texturesLoaded = false;

void LoadCardTextures() {
    if (texturesLoaded) return;

    cardSlotTexture = LoadTexture("res/img/cards/card_slot.png");

    cardBackTexture = LoadTexture("res/img/cards/card_backs/card_back_1.png");

    const char* suits[] = { "clubs", "diamonds", "hearts", "spades" };

    for (int suitIdx = 0; suitIdx < 4; suitIdx++) {
        for (int rank = 1; rank <= 13; rank++) {
            std::string filename = "res/img/cards/card_faces/" +
                std::to_string(rank) + "_of_" + suits[suitIdx] + ".png";
            std::string key = (std::string)suits[suitIdx] + "_" + std::to_string(rank);

            cardTextures[key] = LoadTexture(filename.c_str());
        }
    }

    texturesLoaded = true;
}

Card::Card(Suit s, Rank r) : suit(s), rank(r) {
    LoadCardTextures();
    depth = 50;

    isRed = (suit == Suit::HEARTS || suit == Suit::DIAMONDS);
}

void Card::update(float deltaTime) {
    if (!active) return;
    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isMouseOver() && !isDragging)
        isDragging = true;

    if (isDragging) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            position = mousePos;
            position.x -= size.x * 0.5f;
            position.y -= size.y * 0.5f;
        } else
            isDragging = false;
    }
}

void Card::draw() {
    if (!visible) return;

    Rectangle destRect = { position.x, position.y, size.x, size.y };

    if (show) {
        std::string key = getSuitString() + "_" + std::to_string(static_cast<int>(rank));

        DrawTexturePro(cardTextures[key],
            { 0, 0, (float)cardTextures[key].width, (float)cardTextures[key].height },
            destRect, { 0, 0 }, 0.0f, WHITE);
    } else {
        DrawTexturePro(cardBackTexture,
            { 0, 0, (float)cardBackTexture.width, (float)cardBackTexture.height },
            destRect, { 0, 0 }, 0.0f, WHITE);
    }

    if (isDragging)
        DrawRectangleLinesEx(destRect, 3, YELLOW);
}

bool Card::isMouseOver() const {
    Vector2 mousePos = GetMousePosition();
    return CheckCollisionPointRec(mousePos, getBounds());
}

Rectangle Card::getBounds() const {
    return { position.x, position.y, size.x, size.y };
}

std::string Card::getSuitString() const {
    switch (suit) {
        case Suit::CLUBS: return "clubs";
        case Suit::DIAMONDS: return "diamonds";
        case Suit::HEARTS: return "hearts";
        case Suit::SPADES: return "spades";
        default: return "clubs";
    }
}