r"""OS routines for Mac, NT, or Posix depending on what system we're on.

This exports:
  - all functions from posix, nt, os2, or ce, e.g. unlink, stat, etc.
  - os.path is either posixpath or ntpath
  - os.name is either 'posix', 'nt', 'os2' or 'ce'.
  - os.curdir is a string representing the current directory ('.' or ':')
  - os.pardir is a string representing the parent directory ('..' or '::')
  - os.sep is the (or a most common) pathname separator ('/' or ':' or '\\')
  - os.extsep is the extension separator (always '.')
  - os.altsep is the alternate pathname separator (None or '/')
  - os.pathsep is the component separator used in $PATH etc
  - os.linesep is the line separator in text files ('\r' or '\n' or '\r\n')
  - os.defpath is the default search path for executables
  - os.devnull is the file path of the null device ('/dev/null', etc.)

Programs that import and use 'os' stand a better chance of being
portable between different platforms.  Of course, they must then
only use functions that are defined by all platforms (e.g., unlink
and opendir), and leave all pathname manipulation to os.path
(e.g., split and join).
"""

#'

import sys, errno

_names = sys.builtin_module_names

# Note:  more names are added to __all__ later.
__all__ = ["altsep", "curdir", "pardir", "sep", "pathsep", "linesep",
           "defpath", "name", "path", "devnull",
           "SEEK_SET", "SEEK_CUR", "SEEK_END"]

def _get_exports_list(module):
    try:
        return list(module.__all__)
    except AttributeError:
        return [n for n in dir(module) if n[0] != '_']

if 'posix' in _names:
    name = 'posix'
    linesep = '\n'
    from posix import *
    try:
        from posix import _exit
    except ImportError:
        pass
    import posixpath as path

    import posix
    __all__.extend(_get_exports_list(posix))
    del posix

elif 'nt' in _names:
    name = 'nt'
    linesep = '\r\n'
    from nt import *
    try:
        from nt import _exit
    except ImportError:
        pass
    import ntpath as path

    import nt
    __all__.extend(_get_exports_list(nt))
    del nt

elif 'os2' in _names:
    name = 'os2'
    linesep = '\r\n'
    from os2 import *
    try:
        from os2 import _exit
    except ImportError:
        pass
    if sys.version.find('EMX GCC') == -1:
        import ntpath as path
    else:
        import os2emxpath as path
        from _emx_link import link

    import os2
    __all__.extend(_get_exports_list(os2))
    del os2

elif 'ce' in _names:
    name = 'ce'
    linesep = '\r\n'
    from ce import *
    try:
        from ce import _exit
    except ImportError:
        pass
    # We can use the standard Windows path.
    import ntpath as path

    import ce
    __all__.extend(_get_exports_list(ce))
    del ce

else:
    raise ImportError('no os specific module found')

sys.modules['os.path'] = path
from os.path import (curdir, pardir, sep, pathsep, defpath, extsep, altsep,
    devnull)

del _names

# Python uses fixed values for the SEEK_ constants; they are mapped
# to native constants if necessary in posixmodule.c
SEEK_SET = 0
SEEK_CUR = 1
SEEK_END = 2

#'

# Super directory utilities.
# (Inspired by Eric Raymond; the doc strings are mostly his)

def makedirs(name, mode=0o777):
    """makedirs(path [, mode=0o777])

    Super-mkdir; create a leaf directory and all intermediate ones.
    Works like mkdir, except that any intermediate path segment (not
    just the rightmost) will be created if it does not exist.  This is
    recursive.

    """
    head, tail = path.split(name)
    if not tail:
        head, tail = path.split(head)
    if head and tail and not path.exists(head):
        try:
            makedirs(head, mode)
        except OSError as e:
            # be happy if someone already created the path
            if e.errno != errno.EEXIST:
                raise
        if tail == curdir:           # xxx/newdir/. exists if xxx/newdir exists
            return
    mkdir(name, mode)

def removedirs(name):
    """removedirs(path)

    Super-rmdir; remove a leaf directory and all empty intermediate
    ones.  Works like rmdir except that, if the leaf directory is
    successfully removed, directories corresponding to rightmost path
    segments will be pruned away until either the whole path is
    consumed or an error occurs.  Errors during this latter phase are
    ignored -- they generally mean that a directory was not empty.

    """
    rmdir(name)
    head, tail = path.split(name)
    if not tail:
        head, tail = path.split(head)
    while head and tail:
        try:
            rmdir(head)
        except error:
            break
        head, tail = path.split(head)

def renames(old, new):
    """renames(old, new)

    Super-rename; create directories as necessary and delete any left
    empty.  Works like rename, except creation of any intermediate
    directories needed to make the new pathname good is attempted
    first.  After the rename, directories corresponding to rightmost
    path segments of the old name will be pruned way until either the
    whole path is consumed or a nonempty directory is found.

    Note: this function can fail with the new directory structure made
    if you lack permissions needed to unlink the leaf directory or
    file.

    """
    head, tail = path.split(new)
    if head and tail and not path.exists(head):
        makedirs(head)
    rename(old, new)
    head, tail = path.split(old)
    if head and tail:
        try:
            removedirs(head)
        except error:
            pass

__all__.extend(["makedirs", "removedirs", "renames"])

def walk(top, topdown=True, onerror=None, followlinks=False):
    """Directory tree generator.

    For each directory in the directory tree rooted at top (including top
    itself, but excluding '.' and '..'), yields a 3-tuple

        dirpath, dirnames, filenames

    dirpath is a string, the path to the directory.  dirnames is a list of
    the names of the subdirectories in dirpath (excluding '.' and '..').
    filenames is a list of the names of the non-directory files in dirpath.
    Note that the names in the lists are just names, with no path components.
    To get a full path (which begins with top) to a file or directory in
    dirpath, do os.path.join(dirpath, name).

    If optional arg 'topdown' is true or not specified, the triple for a
    directory is generated before the triples for any of its subdirectories
    (directories are generated top down).  If topdown is false, the triple
    for a directory is generated after the triples for all of its
    subdirectories (directories are generated bottom up).

    When topdown is true, the caller can modify the dirnames list in-place
    (e.g., via del or slice assignment), and walk will only recurse into the
    subdirectories whose names remain in dirnames; this can be used to prune
    the search, or to impose a specific order of visiting.  Modifying
    dirnames when topdown is false is ineffective, since the directories in
    dirnames have already been generated by the time dirnames itself is
    generated.

    By default errors from the os.listdir() call are ignored.  If
    optional arg 'onerror' is specified, it should be a function; it
    will be called with one argument, an os.error instance.  It can
    report the error to continue with the walk, or raise the exception
    to abort the walk.  Note that the filename is available as the
    filename attribute of the exception object.

    By default, os.walk does not follow symbolic links to subdirectories on
    systems that support them.  In order to get this functionality, set the
    optional argument 'followlinks' to true.

    Caution:  if you pass a relative pathname for top, don't change the
    current working directory between resumptions of walk.  walk never
    changes the current directory, and assumes that the client doesn't
    either.

    Example:

    import os
    from os.path import join, getsize
    for root, dirs, files in os.walk('python/Lib/email'):
        print(root, "consumes", end="")
        print(sum([getsize(join(root, name)) for name in files]), end="")
        print("bytes in", len(files), "non-directory files")
        if 'CVS' in dirs:
            dirs.remove('CVS')  # don't visit CVS directories
    """

    from os.path import join, isdir, islink

    # We may not have read permission for top, in which case we can't
    # get a list of the files the directory contains.  os.walk
    # always suppressed the exception then, rather than blow up for a
    # minor reason when (say) a thousand readable directories are still
    # left to visit.  That logic is copied here.
    try:
        # Note that listdir and error are globals in this module due
        # to earlier import-*.
        names = listdir(top)
    except error as err:
        if onerror is not None:
            onerror(err)
        return

    dirs, nondirs = [], []
    for name in names:
        if isdir(join(top, name)):
            dirs.append(name)
        else:
            nondirs.append(name)

    if topdown:
        yield top, dirs, nondirs
    for name in dirs:
        path = join(top, name)
        if followlinks or not islink(path):
            for x in walk(path, topdown, onerror, followlinks):
                yield x
    if not topdown:
        yield top, dirs, nondirs

__all__.append("walk")

# Make sure os.environ exists, at least
try:
    environ
except NameError:
    environ = {}

def execl(file, *args):
    """execl(file, *args)

    Execute the executable file with argument list args, replacing the
    current process. """
    execv(file, args)

def execle(file, *args):
    """execle(file, *args, env)

    Execute the executable file with argument list args and
    environment env, replacing the current process. """
    env = args[-1]
    execve(file, args[:-1], env)

def execlp(file, *args):
    """execlp(file, *args)

    Execute the executable file (which is searched for along $PATH)
    with argument list args, replacing the current process. """
    execvp(file, args)

def execlpe(file, *args):
    """execlpe(file, *args, env)

    Execute the executable file (which is searched for along $PATH)
    with argument list args and environment env, replacing the current
    process. """
    env = args[-1]
    execvpe(file, args[:-1], env)

def execvp(file, args):
    """execvp(file, args)

    Execute the executable file (which is searched for along $PATH)
    with argument list args, replacing the current process.
    args may be a list or tuple of strings. """
    _execvpe(file, args)

def execvpe(file, args, env):
    """execvpe(file, args, env)

    Execute the executable file (which is searched for along $PATH)
    with argument list args and environment env , replacing the
    current process.
    args may be a list or tuple of strings. """
    _execvpe(file, args, env)

__all__.extend(["execl","execle","execlp","execlpe","execvp","execvpe"])

def _execvpe(file, args, env=None):
    if env is not None:
        func = execve
        argrest = (args, env)
    else:
        func = execv
        argrest = (args,)
        env = environ

    head, tail = path.split(file)
    if head:
        func(file, *argrest)
        return
    if 'PATH' in env:
        envpath = env['PATH']
    else:
        envpath = defpath
    PATH = envpath.split(pathsep)
    last_exc = saved_exc = None
    saved_tb = None
    for dir in PATH:
        fullname = path.join(dir, file)
        try:
            func(fullname, *argrest)
        except error as e:
            last_exc = e
            tb = sys.exc_info()[2]
            if (e.errno != errno.ENOENT and e.errno != errno.ENOTDIR
                and saved_exc is None):
                saved_exc = e
                saved_tb = tb
    if saved_exc:
        raise saved_exc.with_traceback(saved_tb)
    raise last_exc.with_traceback(tb)


# Change environ to automatically call putenv(), unsetenv if they exist.
from _abcoll import MutableMapping  # Can't use collections (bootstrap)

class _Environ(MutableMapping):
    def __init__(self, environ, keymap, putenv, unsetenv):
        self.keymap = keymap
        self.putenv = putenv
        self.unsetenv = unsetenv
        self.data = data = {}
        for key, value in environ.items():
            data[keymap(key)] = str(value)

    def __getitem__(self, key):
        return self.data[self.keymap(key)]

    def __setitem__(self, key, value):
        value = str(value)
        self.putenv(key, value)
        self.data[self.keymap(key)] = value

    def __delitem__(self, key):
        self.unsetenv(key)
        del self.data[self.keymap(key)]

    def __iter__(self):
        for key in self.data:
            yield key

    def __len__(self):
        return len(self.data)

    def __repr__(self):
        return 'environ({!r})'.format(self.data)

    def copy(self):
        return dict(self)

    def setdefault(self, key, value):
        if key not in self:
            self[key] = value
        return self[key]

try:
    _putenv = putenv
except NameError:
    _putenv = lambda key, value: None
else:
    __all__.append("putenv")

try:
    _unsetenv = unsetenv
except NameError:
    _unsetenv = lambda key: _putenv(key, "")
else:
    __all__.append("unsetenv")

if name in ('os2', 'nt'): # Where Env Var Names Must Be UPPERCASE
    _keymap = lambda key: str(key.upper())
else:  # Where Env Var Names Can Be Mixed Case
    _keymap = lambda key: str(key)

environ = _Environ(environ, _keymap, _putenv, _unsetenv)


def getenv(key, default=None):
    """Get an environment variable, return None if it doesn't exist.
    The optional second argument can specify an alternate default."""
    return environ.get(key, default)
__all__.append("getenv")

def _exists(name):
    return name in globals()

# Supply spawn*() (probably only for Unix)
if _exists("fork") and not _exists("spawnv") and _exists("execv"):

    P_WAIT = 0
    P_NOWAIT = P_NOWAITO = 1

    # XXX Should we support P_DETACH?  I suppose it could fork()**2
    # and close the std I/O streams.  Also, P_OVERLAY is the same
    # as execv*()?

    def _spawnvef(mode, file, args, env, func):
        # Internal helper; func is the exec*() function to use
        pid = fork()
        if not pid:
            # Child
            try:
                if env is None:
                    func(file, args)
                else:
                    func(file, args, env)
            except:
                _exit(127)
        else:
            # Parent
            if mode == P_NOWAIT:
                return pid # Caller is responsible for waiting!
            while 1:
                wpid, sts = waitpid(pid, 0)
                if WIFSTOPPED(sts):
                    continue
                elif WIFSIGNALED(sts):
                    return -WTERMSIG(sts)
                elif WIFEXITED(sts):
                    return WEXITSTATUS(sts)
                else:
                    raise error("Not stopped, signaled or exited???")

    def spawnv(mode, file, args):
        """spawnv(mode, file, args) -> integer

Execute file with arguments from args in a subprocess.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return _spawnvef(mode, file, args, None, execv)

    def spawnve(mode, file, args, env):
        """spawnve(mode, file, args, env) -> integer

Execute file with arguments from args in a subprocess with the
specified environment.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return _spawnvef(mode, file, args, env, execve)

    # Note: spawnvp[e] is't currently supported on Windows

    def spawnvp(mode, file, args):
        """spawnvp(mode, file, args) -> integer

Execute file (which is looked for along $PATH) with arguments from
args in a subprocess.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return _spawnvef(mode, file, args, None, execvp)

    def spawnvpe(mode, file, args, env):
        """spawnvpe(mode, file, args, env) -> integer

Execute file (which is looked for along $PATH) with arguments from
args in a subprocess with the supplied environment.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return _spawnvef(mode, file, args, env, execvpe)

if _exists("spawnv"):
    # These aren't supplied by the basic Windows code
    # but can be easily implemented in Python

    def spawnl(mode, file, *args):
        """spawnl(mode, file, *args) -> integer

Execute file with arguments from args in a subprocess.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return spawnv(mode, file, args)

    def spawnle(mode, file, *args):
        """spawnle(mode, file, *args, env) -> integer

Execute file with arguments from args in a subprocess with the
supplied environment.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        env = args[-1]
        return spawnve(mode, file, args[:-1], env)


    __all__.extend(["spawnv", "spawnve", "spawnl", "spawnle",])


if _exists("spawnvp"):
    # At the moment, Windows doesn't implement spawnvp[e],
    # so it won't have spawnlp[e] either.
    def spawnlp(mode, file, *args):
        """spawnlp(mode, file, *args) -> integer

Execute file (which is looked for along $PATH) with arguments from
args in a subprocess with the supplied environment.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        return spawnvp(mode, file, args)

    def spawnlpe(mode, file, *args):
        """spawnlpe(mode, file, *args, env) -> integer

Execute file (which is looked for along $PATH) with arguments from
args in a subprocess with the supplied environment.
If mode == P_NOWAIT return the pid of the process.
If mode == P_WAIT return the process's exit code if it exits normally;
otherwise return -SIG, where SIG is the signal that killed it. """
        env = args[-1]
        return spawnvpe(mode, file, args[:-1], env)


    __all__.extend(["spawnvp", "spawnvpe", "spawnlp", "spawnlpe",])

import copyreg as _copyreg

def _make_stat_result(tup, dict):
    return stat_result(tup, dict)

def _pickle_stat_result(sr):
    (type, args) = sr.__reduce__()
    return (_make_stat_result, args)

try:
    _copyreg.pickle(stat_result, _pickle_stat_result, _make_stat_result)
except NameError: # stat_result may not exist
    pass

def _make_statvfs_result(tup, dict):
    return statvfs_result(tup, dict)

def _pickle_statvfs_result(sr):
    (type, args) = sr.__reduce__()
    return (_make_statvfs_result, args)

try:
    _copyreg.pickle(statvfs_result, _pickle_statvfs_result,
                     _make_statvfs_result)
except NameError: # statvfs_result may not exist
    pass

if not _exists("urandom"):
    def urandom(n):
        """urandom(n) -> str

        Return a string of n random bytes suitable for cryptographic use.

        """
        try:
            _urandomfd = open("/dev/urandom", O_RDONLY)
        except (OSError, IOError):
            raise NotImplementedError("/dev/urandom (or equivalent) not found")
        bs = b""
        while len(bs) < n:
            bs += read(_urandomfd, n - len(bs))
        close(_urandomfd)
        return bs

# Supply os.popen()
def popen(cmd, mode="r", buffering=None):
    if not isinstance(cmd, str):
        raise TypeError("invalid cmd type (%s, expected string)" % type(cmd))
    if mode not in ("r", "w"):
        raise ValueError("invalid mode %r" % mode)
    import subprocess, io
    if mode == "r":
        proc = subprocess.Popen(cmd,
                                shell=True,
                                stdout=subprocess.PIPE,
                                bufsize=buffering)
        return _wrap_close(io.TextIOWrapper(proc.stdout), proc)
    else:
        proc = subprocess.Popen(cmd,
                                shell=True,
                                stdin=subprocess.PIPE,
                                bufsize=buffering)
        return _wrap_close(io.TextIOWrapper(proc.stdin), proc)

# Helper for popen() -- a proxy for a file whose close waits for the process
class _wrap_close:
    def __init__(self, stream, proc):
        self._stream = stream
        self._proc = proc
    def close(self):
        self._stream.close()
        returncode = self._proc.wait()
        if returncode == 0:
            return None
        if name == 'nt':
            return returncode
        else:
            return returncode << 8  # Shift left to match old behavior
    def __enter__(self):
        return self
    def __exit__(self, *args):
        self.close()
    def __getattr__(self, name):
        return getattr(self._stream, name)
    def __iter__(self):
        return iter(self._stream)

# Supply os.fdopen()
def fdopen(fd, *args, **kwargs):
    if not isinstance(fd, int):
        raise TypeError("invalid fd type (%s, expected integer)" % type(fd))
    import io
    return io.open(fd, *args, **kwargs)
