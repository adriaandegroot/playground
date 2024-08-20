#! /usr/bin/env python3
#
#   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
# A reader- and writer- of shared memory, example using
# ctypes and direct use of the SystemV-shared-memory API.

import ctypes
import sys

from shm import *

usage = """shm.py - manipulate shared memory segments

shm.py -c           Create a shared memory segment and print its id
shm.py -d <id>      Remove a shared memory segment (like ipcrm -m <id>)
shm.py -w <id> <s>  Write the string <s> to the shared memory segment
shm.py -r <id>      Read the shared memory and print its contents
"""


def create() -> int:
    shmid = shmget(0, 1024, 0o644)
    if shmid < 0:
        print("could not create shared memory segment", file=sys.stderr)
        sys.exit(1)
    print(shmid)
    return 0


def destroy(shmid : int):
    rc = shmrm(shmid)
    if rc < 0:
        print(f"could not destroy shared memory segment {shmid}", file=sys.stderr)
    return 0


def read(shmid : int):
    addr = shmat(shmid, ctypes.c_void_p(None), 0)
    error_return = ctypes.c_void_p(-1).value
    if addr == error_return:
        print(f"could not attach to shared memory segment {shmid}", file=sys.stderr)
        return 1

    iaddr = ctypes.cast(addr, ctypes.POINTER(ctypes.c_int))
    length = iaddr[0]

    s = ctypes.create_string_buffer(length)
    caddr = ctypes.cast(addr, ctypes.POINTER(ctypes.c_char))
    for i in range(length):
        s[i] = caddr[4+i]

    print(length, ctypes.string_at(s).decode("utf-8"))

    return shmdt(addr)


def write(shmid : int, v : str):
    addr = shmat(shmid, ctypes.c_void_p(None), 0)
    error_return = ctypes.c_void_p(-1).value
    if addr == error_return:
        print(f"could not attach to shared memory segment {shmid}", file=sys.stderr)
        return 1

    iaddr = ctypes.cast(addr, ctypes.POINTER(ctypes.c_int))
    caddr = ctypes.cast(addr, ctypes.POINTER(ctypes.c_char))

    ustring = v.encode("utf-8")
    iaddr[0] = len(ustring)
    for i in range(len(ustring)):
        caddr[4+i] = ustring[i]
    caddr[4+len(ustring)] = 0

    return shmdt(addr)


if __name__ == "__main__":
    if len(sys.argv) < 2 or sys.argv[1] == "-h":
        print(usage)
        sys.exit(0)

    if sys.argv[1] == "-c":
        if len(sys.argv) != 2:
            print(usage)
            sys.exit(1)
        sys.exit(create())

    if sys.argv[1] == "-d":
        if len(sys.argv) != 3:
            print(usage)
            sys.exit(1)
        sys.exit(destroy(int(sys.argv[2])))

    if sys.argv[1] == "-r":
        if len(sys.argv) != 3:
            print(usage)
            sys.exit(1)
        sys.exit(read(int(sys.argv[2])))

    if sys.argv[1] == "-w":
        if len(sys.argv) != 4:
            print(usage)
            sys.exit(1)
        sys.exit(write(int(sys.argv[2]), sys.argv[3]))

    print(usage)
    sys.exit(1)
