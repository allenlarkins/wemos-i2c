#pragma once

#include <Adafruit_SH110X.h>

class Menu;

// A single row in a Menu. `submenu` is nullptr for a terminating (leaf) item.
struct MenuItem {
  const char *label;
  Menu *submenu;
};

// A reusable, instantiable menu screen: a title plus a fixed-capacity list
// of items. Selecting an item either navigates into its submenu (if any)
// or shows a terminating info screen. `parent` lets Back navigate up.
class Menu {
public:
  Menu(const char *title, MenuItem *items, uint8_t itemCount, Menu *parent = nullptr);

  void draw(Adafruit_SH1106G &display) const;
  void drawSelection(Adafruit_SH1106G &display) const;

  void selectNext();
  void selectPrevious();

  Menu *selectedSubmenu() const;
  Menu *parent() const { return parent_; }

private:
  const char *title_;
  MenuItem *items_;
  uint8_t itemCount_;
  uint8_t selectedIndex_ = 0;
  Menu *parent_;
};
