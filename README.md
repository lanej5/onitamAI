# Onitama

Onitama is a chess variant. One of its interesting features is that legal moves change from turn to turn. Moves are given on cards. Each player can only make moves based on the cards in their hand and cards are exchanged after each turn. This adds an extra challenge for human players when looking several turns ahead because the moves that will be available will depend on which cards are played (by both players). [More details](https://www.chessvariants.com/rules/onitama).

I was given Onitama for christmas and thought that implementing some AI to play it would be fun.  I chose C++ because I wanted to brush up on my C++ skills. In the process I learned some things about modern C++ that definitely weren't in my undergrad CS classes (e.g., smart pointers!).

An agent using the upper confidence for trees (UCT) algorithm [2] is implemented in UCTAgent.h. A gym that can be used to pit different AI agents is implemented in Gym.h.

Everything in this repo is a totally recreational work in progress. As such, I don't plan to maintain it. That being said, if you have some helpful or interesting thoughts, please feel free to open an issue and share your thoughts.

# To Do

For whenever I get around to it, in no particular order:

- Implement a few other MCTS algorithms and use the gym to compare them and tune their hyperparameters
- Implement time/memory resource constraints
- Implement an Alpha Zero variant
- Parallelize the MCTS algorithm?

# References

Although I've certainly encountered Monte Carlo methods before, I've not worked with MCTS. I found this survey brief and sufficiently informative to code from:

[1] Browne et al. A Survey of Monte Carlo Tree Search Methods. 2012.

The original goal was to implement an Alpha Zero AI. Whether I end up doing that remains to be seen. In any case, one can read about it in their paper (which is really incredible):

[2] Silver et al. Mastering the game of Go without human knowledge. 2017.
