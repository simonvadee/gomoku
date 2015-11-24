#!/usr/bin/env python3.4

from setuptools import setup, find_packages

def install():
    return setup(name = "gomoku",
                 version = "0.1",
                 packages = find_packages(),
                 install_requires=["numpy"]
    )

if __name__ == "__main__":
    install()
