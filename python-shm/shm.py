#! /usr/bin/env python3
#
# Provide Python wrappers for SystemV shared-memory API
#
#   SPDX-FileCopyrightText: 2024 Adriaan de Groot <groot@kde.org>
#   SPDX-License-Identifier: BSD-2-Clause
#
#   Loads the relevant library and returns typed versions of
#   the SysV-shmem API as ctypes callable functions.
#
#   Also provides shmrm which is the counterpart to shmget,
#   that otherwise needs shmctl and some bit-twiddling to
#   do its work.
#
#   Each function returns -1 on failure, usually 0 on success
#   or a meaningful API value (e.g. shared memory segment id
#   or memory address).
"""
SystemV shared memory API
"""

__all__ = ["shmat", "shmdt", "shmget", "shmrm"]

import ctypes

lib = ctypes.cdll.LoadLibrary(None)

shmget = lib.shmget
shmget.argtypes = [ctypes.c_int, ctypes.c_size_t, ctypes.c_int]
shmget.restype = ctypes.c_int
shmget.__doc__ = """See shmget(2)"""

shmat = lib.shmat
shmat.argtypes = [ctypes.c_int, ctypes.c_void_p, ctypes.c_int]
shmat.restype = ctypes.c_void_p
shmat.__doc__ = """See shmat(2)"""

shmdt = lib.shmdt
shmdt.argtypes = [ctypes.c_void_p]
shmdt.restype = ctypes.c_int
shmdt.__doc__ = """See shmdt(2)"""

# Needed for the implementation of shmrm, but not exported as part of __all__
shmctl = lib.shmctl
shmctl.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_void_p]
shmctl.restype = ctypes.c_int
shmctl.__doc__ = """See shmctl(2)"""


def shmrm(shmid : int) -> int:
    """
    Marks the @p shmid shared memory segment for removal.
    Returns 0 on success.
    """
    buffer = ctypes.create_string_buffer(1024) # assume this is larger than sizeof(shmid_ds)
    rc = shmctl(shmid, 2, buffer) # IPC_STAT
    if rc < 0:
        return rc
    rc = shmctl(shmid, 0, buffer)
    return rc

