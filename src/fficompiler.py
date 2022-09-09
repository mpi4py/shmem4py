import os
import shlex
import shutil


class fficompiler:

    from cffi import ffiplatform

    def __init__(self, cc, ld=None):
        self.cc = cc
        self.ld = ld if ld else cc
        self.ffi_compile = self.ffiplatform.compile

    def __enter__(self):
        self.ffiplatform.compile = self.compile

    def __exit__(self, *args):
        self.ffiplatform.compile = self.ffi_compile

    @staticmethod
    def search(envvar, fallback=None):
        cmd = os.environ.get(envvar)
        if cmd:
            return cmd
        if fallback:
            if isinstance(fallback, str):
                fallback = fallback.split(os.pathsep)
            for cmd in fallback:
                if shutil.which(cmd):
                    return cmd
        return None

    def configure(self, compiler):
        def fix_command(command, cmd):
            if not cmd:
                return
            cmd = shlex.split(cmd)
            exe = shutil.which(cmd[0])
            if not exe:
                return
            command[0] = exe
            command += cmd[1:]

        fix_command(compiler.compiler_so, self.cc)
        fix_command(compiler.linker_so, self.ld)

    def compile(self, *args, **kargs):
        from distutils.command import build_ext
        customize_compiler_orig = build_ext.customize_compiler

        def customize_compiler(compiler):
            customize_compiler_orig(compiler)
            self.configure(compiler)

        build_ext.customize_compiler = customize_compiler
        try:
            return self.ffi_compile(*args, **kargs)
        finally:
            build_ext.customize_compiler = customize_compiler_orig
