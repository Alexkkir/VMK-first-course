# %% codecell
class TicTacGame():
    def __init__(self):
        board = []
        board_line = []
        for j in range(3):
            board_line.append('empty')
        for i in range(3):
            board.append(board_line.copy())

        self.board = [['empty', 'empty', 'empty'],
                      ['empty', 'empty', 'empty'],
                      ['empty', 'empty', 'empty']]
        # self.board = board
        self._winner = None
        self._num_of_steps = 0

    def _symbol(self, name):
        return {'empty': '-', 'cross': 'X', 'zero': 'O'}[name]

    def show_board(self):
        print('Board:')
        for i in range(3):
            for j in range(3):
                print(f"{self._symbol(self.board[i][j])}  ", end='')
            print()

    def validate_input(self, line, check_is_empty=False):
        try:
            i, j = [int(x) for x in line.split()]
        except BaseException:
            return False
            # x.isdigit()
            # try validate_input
            # except ValidationError as err:
            #   print err.msg
        else:
            # print(2)
            i -= 1
            j -= 1
            if check_is_empty:
                return 0 <= i < 3 and 0 <= j < 3 and self.board[i][j] == 'empty'
                # else:
            return 0 <= i < 3 and 0 <= j < 3

    def start_game(self):
        print(
            'Make step in such format: [i] [j] where i, j are coordinates of position in 2d array')
        player = 'cross'

        print()
        self.show_board()
        print()

        while True:
            # print(f'Step of "{self._symbol(player)}" player:', end='\t')
            line = input(f'Step of "{self._symbol(player)}" player:', end='\t')

            if self.validate_input(line, check_is_empty=True):
                i, j = [int(x) for x in line.split()]
                i -= 1
                j -= 1
                self.board[i][j] = player
                self._num_of_steps += 1
                self.show_board()
                print()

                if self.check_winner() == True:
                    self._winner = player
                    print(f'Player with "{self._symbol(player)}" has won. Game over')
                    break

                change_pl = {'cross': 'zero', 'zero': 'cross'}
                player = change_pl[player]
            else:
                print(f'Wrong input format. Player with "{self._symbol(player)}", try again')
                print()
                self.show_board()
                print()
                continue

    def check_winner(self):
        # print("====")
        def item(self, i, j):
            # print(f"={i + 1} {j + 1}=")
            if self.validate_input(f"{i + 1} {j + 1}", check_is_empty=False) is False:
                return 'empty'
            else:
                return self.board[i][j]

        def win_line(self, i, j):
            conditions = [[0, 1], [1, 1], [1, 0], [1, -1]]
            for cond in conditions:
                i_bias = cond[0]
                j_bias = cond[1]
                # print('i j', )
                # print(item(self, i + i_bias, j + j_bias), item(self, i, j), item(self, i - i_bias, j - j_bias))
                if item(self, i + i_bias, j + j_bias) == item(self, i, j) == item(self, i - i_bias, j - j_bias) != 'empty':
                    # print('biases: ', i_bias, j_bias)
                    # print(item(self, 0, -1))
                    return True
            return False

        for i in range(3):
            for j in range(3):
                if win_line(self, i, j) is True:
                    # print("i, j: ", i, j)
                    return True
        return False


# game = TicTacGame()
# game.start_game()
