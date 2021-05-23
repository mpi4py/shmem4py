#!/bin/bash

PYTHON=$(command -v python)
COVERAGE="$PYTHON -m coverage"

$COVERAGE erase

tmpdir=$(mktemp -d)
trap "{ rm -rf $tmpdir; }" EXIT

$COVERAGE run -m shmem4py > /dev/null
cat <<EOF > $tmpdir/cover.py
import shmem4py.__main__
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import shmem4py
shmem4py.rc.initialize = False
from shmem4py import shmem
shmem.init()
shmem.finalize()
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import shmem4py
shmem4py.rc.initialize = False
from shmem4py import shmem
shmem.init_thread()
shmem.finalize()
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import shmem4py
shmem4py.rc.threads = False
from shmem4py import shmem
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import shmem4py
shmem4py.rc.thread_level = 'single'
from shmem4py import shmem
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import shmem4py
shmem4py.rc.finalize = False
from shmem4py import shmem
shmem.finalize()
EOF
$COVERAGE run $tmpdir/cover.py

$COVERAGE run -m unittest discover -qq -s test/
$COVERAGE combine
$COVERAGE report
