#!/bin/bash
set -eu

PYTHON=$(command -v python)
OSHRUN=$(command -v oshrun)
COVERAGE="$OSHRUN -n 1 $PYTHON -m coverage"

$PYTHON -c "import shmem4py.api"

tmpdir=$(mktemp -d)
trap "{ rm -rf $tmpdir; }" EXIT

$COVERAGE erase

$COVERAGE run -m shmem4py > /dev/null
cat <<EOF > $tmpdir/cover.py
import shmem4py.__main__
EOF
$COVERAGE run $tmpdir/cover.py

cat <<EOF > $tmpdir/cover.py
import os
os.environ['SHMEM4PY_RC_THREAD_LEVEL'] = 'single'
os.environ['SHMEM4PY_RC_INITIALIZE'] = 'true'
os.environ['SHMEM4PY_RC_THREADS'] = 'false'
from shmem4py import rc
rc.initialize = True
rc.finalize = False
from shmem4py import shmem
shmem.finalize()
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
shmem4py.rc.finalize = True
from shmem4py import shmem
shmem.init_thread(shmem.THREAD_SINGLE)
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
shmem4py.rc.threads = True
shmem4py.rc.thread_level = 'single'
from shmem4py import shmem
EOF
$COVERAGE run $tmpdir/cover.py

$COVERAGE run -m unittest discover -q -s test/

$COVERAGE combine
$COVERAGE report
for action in $@; do
    $COVERAGE $action
done;
