import unittest
import test_sum_lists

testCases = []

testCases.append(test_sum_lists.TestOnlyMyLists)
testCases.append(test_sum_lists.TestMyListsAsLeftOperand)
testCases.append(test_sum_lists.TestMyListsAsRightOperand)

testLoad = unittest.TestLoader()

suites = []
for tc in testCases:
    suites.append(testLoad.loadTestsFromTestCase(tc))

res_suite = unittest.TestSuite(suites )

runner = unittest.TextTestRunner(verbosity=2)
runner.run(res_suite)
