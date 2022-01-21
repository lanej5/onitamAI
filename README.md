# Onitama

Onitama is a chess variant. One of its interesting features is that legal moves are given on cards. Each player can only make moves based on the cards in their hand and cards are exchanged after each turn. This adds an extra challenge when looking several turns ahead because the moves that will be available will depend on which cards are played. [More details](https://www.chessvariants.com/rules/onitama).

I was given Onitama for christmas and thought that implementing some AI to play it would be fun.  I chose C++ because I want to focus on making Monte Carlo Tree Search (MCTS) agents [1] that are fast and memory efficient.

My original idea was to implement an Alpha Zero AI for Onitama. However, this is probably overkill because Onitama's branching factor is relatively small. In random simulations Onitama's branching factor was consistently <20 from early to late game. In contrast, the branching factor of Go is about 250 and the branching factor of chess is about 35 [[ref](https://en.wikipedia.org/wiki/Branching_factor)].

An agent using the upper confidence for trees (UCT) algorithm [2] is implemented in UCTAgent.h. 

A gym that can be used to pit different AI agents is implemented in Gym.h. Currently the UCT agent beats an agent making random moves every time (as one would hope).

Everything in this repo is a totally recreational work in progress. As such, I don't plan to maintain it. That being said, if you have some helpful or interesting thoughts, please feel free to open an issue and share your thoughts.

# To Do

For whenever I get around to it, in no particular order:

- Add some code to gather data for some tasty analysis
- Implement a polymorphic Node class that can be used by different AI Agents
- Continue speeding up the code (especially `get_valid_actions` in `Actions.h` which is called quite a bit)
- Implement full tree search for comparison sake
- Implement a few other MCTS algorithms and use the gym to compare them and tune their hyperparameters
- Implement time/memory resource constraints
- Implement an Alpha Zero variant (this might be totally unnecessary for Onitama which has a fairly low branching factor, but it would be fun to do and realistic to train with limited resources)
- Dockerize everything
- Clean up the C++

# References

Although I've certainly encountered Monte Carlo methods before, I've not worked with MCTS. I found this survey brief and sufficiently informative to code from:

[1] Browne et al. A Survey of Monte Carlo Tree Search Methods. 2012.

The original goal was to implement an Alpha Zero AI. Whether I end up doing that remains to be seen. In any case, one can read about it in their paper (which is really incredible):

[2] Silver et al. Mastering the game of Go without human knowledge. 2017.