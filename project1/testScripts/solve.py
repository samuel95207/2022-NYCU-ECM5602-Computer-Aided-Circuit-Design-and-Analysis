import numpy as np
import scipy.linalg

A = np.loadtxt("../outputs/output_mnaMatrix_1.txt")
B = np.loadtxt("../outputs/output_rhs_1.txt")
solution = np.linalg.solve(A, B)
# P, L, U = scipy.linalg.lu(A)

print(solution)
