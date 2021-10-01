import ctypes
import os
import platform

path = os.path.dirname(os.path.realpath(__file__))
if(platform.system() == 'Windows'):
    libc = ctypes.cdll.LoadLibrary(os.path.join(path, "PythonWrapTest.dll"))
elif(platform.system() == 'Linux'):
    pass
elif(platform.system() == 'Darwin'):
    pass
else:
    pass

libc.addThreeNumbers.argtype = (ctypes.POINTER(ctypes.c_float))

num_numbers = 3
array_type = ctypes.c_float * num_numbers

x = array_type(*[1, 2, 3])
libc.addThreeNumbers(x)