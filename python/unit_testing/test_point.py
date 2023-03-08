import unittest
import math
from point import Point



class PointTest(unittest.TestCase):

    def test_init_with_numbers(self):
        p = Point(3, 8.5)
        self.assertEqual(p.x, 3)
        self.assertEqual(p.y, 8.5)

    def test_init_without_numbers(self):
        p = Point("g", 5)
        self.assertEqual(p.x, 0.0)
        self.assertEqual(p.y, 0.0)

    def test_distance_from_origin(self):
        p = Point(3, 4)
        self.assertEqual(p.distance_from_origin(), 5)

    def test_distance_from_origin_negative(self):
        p = Point(-3, -4)
        self.assertEqual(p.distance_from_origin(), 5)

    def test_distance_from_origin_float(self):
        p = Point(1.5, 2.5)
        self.assertEqual(p.distance_from_origin(), math.sqrt(1.5**2 + 2.5**2))

    def test_distance_from_origin_fail(self):
        p = Point(3, 4)
        self.assertEqual(p.distance_from_origin(), 4)

if __name__ == '__main__':
    unittest.main()
