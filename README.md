# Onitama

I was given the game Onitama for christmas and thought implementing some AI to play it would be fun.  

Everything in this repo is a totally recreational work in progress. 

I chose C++ because I want to focus on making Monte Carlo Tree Search (MCTS) agents [1] that are fast and memory efficient.

My original idea was to make an Alpha Zero AI for Onitama, but it seems likely that this is total overkill because its branching factor is relatively small. In random simulations Onitama's branching factor was consistently <20 from early to late game. In contrast, the branching factor of Go is about 250 and the branching factor of chess is about 35 [ref](https://en.wikipedia.org/wiki/Branching_factor).

At the moment, the only AI that is implemented is an upper confidence for trees (UCT) algorithm [2]. This is implemented in UCTAgent.h. 

The code also implements a gym (Gym.h) that can be used to pit different AI agents. Currently the UCT agent beats an agent making random moves every time (as one would hope).

# To Do

For whenever I get around to it, in no particular order:

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