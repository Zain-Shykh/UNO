# C++ Console UNO Game

A fully functional, 2-player digital version of the classic UNO card game, built as a terminal-based application using C++.

##  Features
- **Full Standard Deck:** Includes all 108 cards (Numbered, Skip, Reverse, Draw Two, Wild, and Wild Draw Four).
- **Turn-Based Gameplay:** Smooth 2-player mechanics with real-time hand updates.
- **Action Card Logic:** Fully implemented special card effects (e.g., Reverse acts as a Skip in 2-player mode).
- **UNO Call System:** Penalizes players with +2 cards if they forget to call "UNO" before playing their second-to-last card.
- **Game History:** Automatically logs wins, scores, and turn counts to a text file.
- **Interactive UI:** Colorful console interface with clear prompts and card displays.

## Technical Details
- **Data Structure:** The deck is represented using a **2D Array** where rows indicate colors and columns represent card types.
- **Randomization:** Includes a custom shuffling algorithm to ensure a unique deck for every game.
- **Validation:** Strict enforcement of UNO matching rules (color or type).
- **File I/O:** Saves and loads historical player statistics.
