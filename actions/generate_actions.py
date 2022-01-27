import pandas as pd

DECK = {'MONKEY': '0000001010000000101000000',
        'MANTIS': '0000001010000000010000000',
        'FROG':   '0000000010000010100000000',
        'HORSE':  '0000000100000100010000000',
        'CRANE':  '0000000100000000101000000',
        'COBRA':  '0000001000000100100000000',
        'CRAB':   '0000000100100010000000000',
        'RABBIT': '0000001000100000001000000',
        'ROOSTR': '0000001000010100001000000',
        'GOOSE':  '0000000010010100100000000',
        'OX':     '0000000100010000010000000',
        'DRAGON': '0000010001000000101000000',
        'BOAR':   '0000000100010100000000000',
        'ELEPHT': '0000001010010100000000000',
        'EEL':    '0000000010010000001000000',
        'TIGER':  '0010000000000000010000000'}

columns = ['Player', 'piece_bit', 'Card'] + list(range(25))

valid_actions = []

# Tabulate valid red player moves
for card_index, (card, bit_string) in enumerate(DECK.items()):
    for piece_bit in range(25):
        valid_move_bits = []
        for move_bit in range(25):
            i = (piece_bit // 5) + (move_bit // 5)
            j = (piece_bit % 5) + (move_bit % 5)
            if bit_string[::-1][move_bit] == '1' and 2 <= i and i < 7 and 2 <= j and j < 7:
                valid_move_bits.append(1)
            else:
                valid_move_bits.append(0)
        valid_actions.append([0, piece_bit, card_index] + valid_move_bits)

# Tabulate valid blue player moves
for card_index, (card, bit_string) in enumerate(DECK.items()):
    for piece_bit in range(25):
        valid_move_bits = []
        for move_bit in range(25):
            i = (piece_bit // 5) - (move_bit // 5)
            j = (piece_bit % 5) - (move_bit % 5)
            if bit_string[::-1][move_bit] == '1' and -2 <= i and i < 3 and -2 <= j and j < 3:
                valid_move_bits.append(1)
            else:
                valid_move_bits.append(0)
        valid_actions.append([1, piece_bit, card_index] + valid_move_bits)

df = pd.DataFrame(data=valid_actions, columns=columns)
df.to_csv('valid_actions.csv')
