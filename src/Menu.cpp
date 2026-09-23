#include "Menu.h"

namespace {

// Menu layout constants
constexpr int16_t MENU_TITLE_Y                  = 0;
constexpr int16_t MENU_DIVIDER_Y                = 11;
constexpr int16_t MENU_ITEM_FIRST_Y             = 18;
constexpr int16_t MENU_ITEM_ROW_HEIGHT          = 14;
constexpr int16_t MENU_ITEM_HIGHLIGHT_HEIGHT    = 12;
constexpr int16_t MENU_ITEM_HIGHLIGHT_PAD_TOP   = 2;
constexpr int16_t MENU_MARKER_X                 = 4;
constexpr int16_t MENU_LABEL_X                  = 16;

} // namespace

Menu::Menu(const char *title, MenuItem *items, uint8_t itemCount, Menu *parent)
    : title_(title), items_(items), itemCount_(itemCount), parent_(parent) {}

void Menu::selectNext() {
  selectedIndex_ = (selectedIndex_ + 1) % itemCount_;
}

void Menu::selectPrevious() {
  selectedIndex_ = (selectedIndex_ + itemCount_ - 1) % itemCount_;
}

Menu *Menu::selectedSubmenu() const {
  return items_[selectedIndex_].submenu;
}

void Menu::draw(Adafruit_SH1106G &display) const {
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(0, MENU_TITLE_Y);
  display.println(title_);
  display.drawFastHLine(0, MENU_DIVIDER_Y, display.width(), SH110X_WHITE);

  for (uint8_t i = 0; i < itemCount_; ++i) {
    const int16_t y = MENU_ITEM_FIRST_Y + (i * MENU_ITEM_ROW_HEIGHT);
    if (i == selectedIndex_) {
      display.fillRect(0, y - MENU_ITEM_HIGHLIGHT_PAD_TOP, display.width(),
                        MENU_ITEM_HIGHLIGHT_HEIGHT, SH110X_WHITE);
      display.setTextColor(SH110X_BLACK);
      display.setCursor(MENU_MARKER_X, y);
      display.print('>');
      display.setCursor(MENU_LABEL_X, y);
      display.print(items_[i].label);
      display.setTextColor(SH110X_WHITE);
    } else {
      display.setCursor(MENU_MARKER_X, y);
      display.print(' ');
      display.setCursor(MENU_LABEL_X, y);
      display.print(items_[i].label);
    }
  }
  display.display();
}

void Menu::drawSelection(Adafruit_SH1106G &display) const {
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("Selected:"));
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(items_[selectedIndex_].label);
  display.setTextSize(1);
  display.setCursor(0, 42);
  display.println(F("(termination node)"));
  display.setCursor(0, 56);
  display.println(F("Press BAR to return"));
  display.display();
}
