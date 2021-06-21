from custom_metaclass import CustomMeta
import unittest
from unittest import TestCase

class TestCustomMeta(TestCase):
    def setUp(self):
        class A(metaclass = CustomMeta):
            x = 50

            def fun(arg):
                return arg * 2
        self.a = A()

    def test_1(self):
        with self.assertRaises(AttributeError):
            self.a.x

    def test_2(self):
        with self.assertRaises(AttributeError):
            self.a.fun

    def test_3(self):
        def fun():
            try:
                self.a.custom_x
            except:
                return 'some error'
            else:
                return 'no errors'
        self.assertEqual(fun(), 'no errors')

    def test_4(self):
        def fun():
            try:
                self.a.custom_fun
            except:
                return 'some error'
            else:
                return 'no errors'
        self.assertEqual(fun(), 'no errors')


unittest.main()
