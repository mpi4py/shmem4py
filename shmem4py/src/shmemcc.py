class shmemcompiler:

    from cffi import ffiplatform

    def __init__(self, cc, ld=None):
        self.cc = cc
        self.ld = ld if ld else cc
        self.ffi_compile = self.ffiplatform.compile

    def __enter__(self):
        self.ffiplatform.compile = self.compile

    def __exit__(self, *args):
        self.ffiplatform.compile = self.ffi_compile

    def configure(self, compiler):
        try:
            from shlex import split as shlex_split
        except ImportError:
            from distutils.util import split_quoted as shlex_split
        try:
            from shutil import which as shutil_which
        except ImportError:
            from distutils.spawn import find_executable as shutil_which

        def fix_command(command, cmd):
            if not cmd:
                return
            cmd = shlex_split(cmd)
            exe = shutil_which(cmd[0])
            if not exe:
                return
            command[0] = exe
            command += cmd[1:]

        fix_command(compiler.compiler_so, self.cc)
        fix_command(compiler.linker_so, self.ld)

    def compile(self, *args, **kargs):
        from setuptools.command import build_ext
        customize_compiler_orig = build_ext.customize_compiler

        def customize_compiler(compiler):
            customize_compiler_orig(compiler)
            self.configure(compiler)

        build_ext.customize_compiler = customize_compiler
        try:
            return self.ffi_compile(*args, **kargs)
        finally:
            build_ext.customize_compiler = customize_compiler_orig
