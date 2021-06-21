from tic_tac_toe import TicTacGame
import unittest
from unittest import TestCase
from unittest.mock import patch
import sys
import io

# class TestShowBoard(TestCase):
#     def setUp(self):
#         self.game = TicTacGame()
#
#     def test_1(self):
#         self.game.board = [['empty', 'empty', 'empty'], ['empty', 'empty', 'empty'], ['empty', 'empty', 'empty']]
#         line = "Board:\n- - - \n- - - \n- - - \n"
#         self.assertEqual(self.game.show_board(), line)


class TestValidateInput(TestCase):
    def setUp(self):
        self.game = TicTacGame()
        self.game.board = [['empty', 'empty', 'empty'],
                           ['zero', 'empty', 'empty'],
                           ['zero', 'cross', 'empty']]
        # self.game.board =  [['zero', 'zero', 'zero'], \
        #                     ['zero', 'zero', 'zero'], \
        #                     ['zero', 'cross', 'zero']]

    def test_1(self):
        self.assertEqual(self.game.validate_input('1 1', check_is_empty=True), True)
        # asserTru

    def test_2(self):
        self.assertEqual(self.game.validate_input('3 1', check_is_empty=True), False)

    def test_3(self):
        self.assertEqual(self.game.validate_input('1, 1', check_is_empty=True), False)

    def test_4(self):
        self.assertEqual(self.game.validate_input('1 1 1', check_is_empty=True), False)

    def test_5(self):
        self.assertEqual(self.game.validate_input('1 4', check_is_empty=True), False)


class TestCheckWinner(TestCase):
    def setUp(self):
        self.game = TicTacGame()

    def test_1(self):
        self.game.board = [['empty', 'empty', 'empty'],
                           ['zero', 'zero', 'zero'],
                           ['zero', 'cross', 'empty']]
        self.assertEqual(self.game.check_winner(), True)

    def test_2(self):
        self.game.board = [['cross', 'empty', 'empty'],
                           ['zero', 'cross', 'zero'],
                           ['zero', 'cross', 'cross']]
        self.assertEqual(self.game.check_winner(), True)

    def test_3(self):
        self.game.board = [['cross', 'empty', 'empty'],
                           ['zero', 'empty', 'zero'],
                           ['zero', 'cross', 'cross']]
        self.assertEqual(self.game.check_winner(), False)


class TestStartGame(TestCase, object):
    def setUp(self):
        self.game = TicTacGame()

    @patch('sys.stdout', new_callable=io.StringIO)
    @patch('builtins.input', side_effect=['1 1', '1 3', '2 1', '2 3', '3 1'])
    def test_1(self, mock_in, mock_out):
        self.game.start_game()
        self.assertEqual(self.game._winner, 'cross')
        self.assertEqual(self.game._num_of_steps, 5)

    @patch('sys.stdout', new_callable=io.StringIO)
    @patch('builtins.input', side_effect=['1 1', '1 3', '2 2', '2 3', '3 2', '3 3'])
    def test_2(self, mock_in, mock_out):
        self.game.start_game()
        self.assertEqual(self.game._winner, 'zero')
        self.assertEqual(self.game._num_of_steps, 6)


if __name__ == '__main__':
    unittest.main()

# https://spicyseashells.com/article/python-mock-stdin-stderr-stdout
