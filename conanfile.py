#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile
from conan.tools.gnu import MakeToolchain


class ProgrammingKataConan(ConanFile):
    name = "progamming-kata"
    version = "0.1"
    settings = "os", "arch", "compiler", "build_type"
    generators = "cmake"
    exports_sources = "*"
    requires = ["boost/1.75.0", "glew/2.2.0"]

    def generate(self):
        tc = MakeToolchain(self)
        tc.generate()

    def build(self):
        pass

    def package(self):
        pass
