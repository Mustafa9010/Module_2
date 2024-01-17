import sys
import numpy as np
sys.path.insert(0, '/Documents/module two/Math_computing/CoordGeo')

A = np.array([1, 1, 1])
B = np.array([2, 4, -5])
D = np.array([0, 2, 3])
e_1 = np.array([1, 0, 0])
A_T_B_plus_D = np.dot(A.T, B + D)
numerator = np.dot(B, B) + 2 * np.dot(B, D) + np.dot(D, D) - A_T_B_plus_D**2
denominator = 2 * ((np.dot(A, e_1)) * A_T_B_plus_D - np.dot(B, e_1) - np.dot(e_1, D))
lambda_value = numerator / denominator
print(lambda_value)

