import pandas as pd

df = pd.read_csv('valid_actions.csv')

start = """//
//  ValidActions.h
//
//  Created by Jeremy Lane
//
//  Generate map that returns a list of valid actions for a given state.

#ifndef ValidActions_h
#define ValidActions_h

#include <map>
#include <list>


// Define a map such that:
// VALID_ACTIONS.at(400 * player + 25 * card + piece_bit)
// returns a std::list of valid move bits.

const std::map<int, std::list<int>> VALID_ACTIONS {
"""

end="""};

#endif /* ValidActions_h */
"""

with open("ValidActions.h", "w") as f:
    print(start, file=f)

    for index, row in df.iterrows():

        move_bits = []
        for i in range(25):
            if row[str(i)] == 1:
                move_bits.append(str(i))

        move_string = '  {' + str(index) + ', std::list<int>{' + ', '.join(move_bits) + '}},'
        print(move_string, file=f)

    print(end, file=f)