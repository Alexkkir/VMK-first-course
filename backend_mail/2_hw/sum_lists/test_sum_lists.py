from sum_lists import MyList
import unittest
from unittest import TestCase

class TestOnlyMyLists(TestCase):
    def setUp(self):
        self.mylist_1 = MyList([5, 1, 3, 7])
        self.mylist_2 = MyList([1, 2, 7])
        self.list_1 = [5, 1, 3, 7]
        self.list_2 = [1, 2, 7]

    def test_1(self):
        self.assertEqual(self.mylist_1 + self.mylist_2, MyList([6, 3, 10, 7]))

    def test_2(self):
        self.assertEqual(self.mylist_1 - self.mylist_2, MyList([4, -1, -4, 7]))

class TestMyListsAsLeftOperand(TestCase):
    def setUp(self):
        self.mylist_1 = MyList([5, 1, 3, 7])
        self.mylist_2 = MyList([1, 2, 7])
        self.list_1 = [5, 1, 3, 7]
        self.list_2 = [1, 2, 7]

    def test_3(self):
        self.assertEqual(self.mylist_1 + self.list_2, MyList([6, 3, 10, 7]))

    def test_4(self):
        self.assertEqual(self.mylist_1 - self.list_2, MyList([4, -1, -4, 7]))

class TestMyListsAsRightOperand(TestCase):
    def setUp(self):
        self.mylist_1 = MyList([5, 1, 3, 7])
        self.mylist_2 = MyList([1, 2, 7])
        self.list_1 = [5, 1, 3, 7]
        self.list_2 = [1, 2, 7]

    def test_5(self):
        self.assertEqual(self.list_1 + self.mylist_2, MyList([6, 3, 10, 7]))

    def test_6(self):
        self.assertEqual(self.list_1 - self.mylist_2, MyList([4, -1, -4, 7]))

if __name__ == '__main__':
    unittest.main()
