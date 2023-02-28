import unittest
import mod

class ModTest(unittest.TestCase):

  def testEvenNumber(self):
      self.assertTrue(mod.is_even(2))
      self.assertFalse(mod.is_even(1))

  def testZeroCase(self):
      self.assertTrue(mod.is_even(0))

  def testArgumentMustBeNumber(self):
      self.assertRaises(TypeError, mod.is_even, "str")

if __name__ == "__main__":
  unittest.main()
