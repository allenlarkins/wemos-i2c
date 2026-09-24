# Menu Navigation Roadmap

Tracking doc for this feature branch. Current `Menu` class (see `src/Menu.h`,
`src/Menu.cpp`) supports a fixed-capacity item list, a title, and
parent-pointer-based Back navigation, rendered as a simple highlighted list
that fits entirely on the 128x64 screen.

## Planned work

- **Scroll bar** - a visual indicator (e.g. a thin vertical bar on the right
  edge) showing scroll position/extent when a menu has more items than fit
  on screen at once.
- **Horizontal scrolling** - for item labels (or detail screens) too long to
  fit the 128px display width at the current text size, scroll/marquee the
  text horizontally instead of truncating it.

## Open questions

- How many items should be visible on screen at once before scrolling
  kicks in, given the current row height/layout constants in `Menu.cpp`?
- Should horizontal scrolling be automatic (marquee on a timer) or driven by
  encoder/button input while an item is highlighted?
