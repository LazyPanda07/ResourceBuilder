import argparse
import os
import sys
import unittest

from ctypes import *


class Tests(unittest.TestCase):
    def test_resource(self):
        handle = cdll.LoadLibrary(f"{os.curdir}/{shared_library_name}")

        get_resource = handle.c_getResource

        get_resource.restype = POINTER(c_ubyte)
        get_resource.argtypes = [c_char_p, POINTER(c_size_t)]

        name_ptr = c_char_p(b"default.jpg")
        size_ptr = pointer(c_size_t())

        data_ptr = get_resource(name_ptr, size_ptr)

        data = bytearray(size_ptr.contents.value)

        for i in range(len(data)):
            data[i] = data_ptr[i]

        self.assertEqual(size_ptr.contents.value, 217204)


def get_extension():
    return ".dll" if os.name == "nt" else ".so"


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        "test",
        f"python test.py --application_folder_path --shell_script_name",
        "Test resource_builder"
    )

    parser.add_argument("--application_folder_path", required=True)
    parser.add_argument("--shell_script_name", required=True)

    args = parser.parse_args()

    application_folder_path = args.application_folder_path
    shared_library_name = f"default{get_extension()}"

    os.system(f"cd \"{application_folder_path}\" && \"{args.shell_script_name}\"")

    os.replace(f"{application_folder_path}/{shared_library_name}", f"{os.curdir}/{shared_library_name}")

    unittest.main(argv=[sys.argv[0]])
