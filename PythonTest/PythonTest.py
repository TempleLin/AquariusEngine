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

libc.getTestObject.restype = ctypes.POINTER(ctypes.c_void_p)
y = libc.getTestObject()
libc.getTest.argtype = (ctypes.POINTER(ctypes.c_void_p))
print(libc.getTest(y))

libc.saveTests.argtype = [ctypes.POINTER(ctypes.POINTER(ctypes.c_void_p)), ctypes.c_int]
libc.saveTests.restype = ctypes.c_voidp

a = libc.getTestObject()
b = libc.getTestObject()
c = libc.getTestObject()

array_type = ctypes.POINTER(ctypes.c_void_p) * 3
d = array_type(*[a, b, c])
libc.saveTests(d, 3)
libc.printTests()


def function_for_callback():
    print("Function callback succeeded.")

libc.runFunctionPointer.argtype = ctypes._CFuncPtr
libc.runFunctionPointer.restype = ctypes.c_void_p

CallBackFUNCTYPE = ctypes.CFUNCTYPE(None)
callback_func = CallBackFUNCTYPE(function_for_callback)
libc.runFunctionPointer(callback_func)


array_type = ctypes.POINTER(ctypes.c_float)
print(array_type)
array_type = ctypes.c_float * 3
print(array_type)
array_type = ctypes.POINTER(ctypes.c_void_p)
print(array_type)
array_type = ctypes.POINTER(ctypes.c_voidp)
print(array_type)


# Do not try to delete array passed from Python list. Causes unknown bug.
#b = array_type(*[1.0, 2.0, 3.0, 4.0])
#libc.testDeletePyList.argtype = [ctypes.POINTER(ctypes.c_float), ctypes.c_int]
#libc.testDeletePyList(b, 4)
#if b:
#    print("List still exists")
#else:
#    print("List deleted")