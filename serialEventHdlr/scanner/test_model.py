#! /usr/bin/python
import unittest
import scanner  

class Observer:
    def __init__(self):
        self.reset()
        self.nbr_of_calls = 0
        self.has_been_called = False

    def update(self):
        self.nbr_of_calls += 1
        self.has_been_called = True

    def reset(self):
        self.nbr_of_calls = 0
        self.has_been_called = False

class TestModel(unittest.TestCase):
    
    def setUp(self):
        self.model = scanner.Model(None)

    def test_init(self):
        self.assertEqual(self.model._mode, scanner.ScannerMode.NOT_HOMED)
        self.assertEqual(self.model.vertical_pos, 0)
        self.assertEqual(self.model.horizontal_pos, 0)

    def test_notify_observers(self):
        o = Observer()
        self.model.attatch(o)

        self.assertFalse(o.has_been_called)
        self.model.notify()
        self.assertTrue(o.has_been_called)

        
    def test_set_scanner_mode(self):
        o = Observer()
        self.model.attatch(o)

        self.assertFalse(o.has_been_called)
        self.model.set_scanner_mode(scanner.ScannerMode.INACTIVE)

        self.assertEqual(self.model._mode, scanner.ScannerMode.INACTIVE)
        self.assertTrue(o.has_been_called)

    def test_set_vertical_pos(self):
        o = Observer()
        self.model.attatch(o)

        self.assertFalse(o.has_been_called)
        self.model.set_vertical_pos(111.11)

        self.assertAlmostEqual(self.model.vertical_pos, 111.11)
        self.assertTrue(o.has_been_called)
    
    def test_set_horizontal_pos(self):
        o = Observer()
        self.model.attatch(o)

        self.assertFalse(o.has_been_called)
        self.model.set_horizontal_pos(222.22)

        self.assertAlmostEqual(self.model.horizontal_pos, 222.22)
        self.assertTrue(o.has_been_called)    
    
if __name__ == '__main__':
   unittest.main()