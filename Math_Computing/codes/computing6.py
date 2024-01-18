import numpy as np

A = np.array([1, 1, 1])
B = np.array([2, 4, -5])
D = np.array([0, 2, 3])
e1 = np.array([1, 0, 0]) 

A_T_B_plus_D =(A.T@(B + D))      

numerator = (B.T@B) + 2 * (B.T@D) + (D.T@ D) - A_T_B_plus_D**2              

denominator = 2 * (((A.T @ e1)) * A_T_B_plus_D - (B.T@e1) - (e1.T@ D))    

lambda_value = numerator / denominator
print(lambda_value)
