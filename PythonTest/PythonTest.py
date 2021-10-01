import ctypes
import os

path = os.path.dirname(os.path.realpath(__file__))
libc = ctypes.cdll.LoadLibrary(os.path.join(path, "PythonWrapTest.dll"))

libc.addThreeNumbers.argtype = (ctypes.POINTER(ctypes.c_float))

num_numbers = 3
array_type = ctypes.c_float * num_numbers

x = array_type(*[1, 2, 3])
libc.addThreeNumbers(x)