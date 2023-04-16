OpenSHMEM
=========

.. currentmodule:: shmem4py.shmem


Version and Vendor Query
------------------------

.. autosummary::
   info_get_version
   info_get_name

.. autofunction:: info_get_version
.. autofunction:: info_get_name


Library Setup and Exit
----------------------

.. autosummary::
   init
   finalize
   global_exit
   init_thread
   query_thread
   THREAD

.. autofunction:: init
.. autofunction:: finalize
.. autofunction:: global_exit
.. autofunction:: init_thread
.. autofunction:: query_thread

.. autoclass::    THREAD


Accessibility Queries
---------------------

.. autosummary::
   my_pe
   n_pes
   pe_accessible
   addr_accessible
   ptr

.. autofunction:: my_pe
.. autofunction:: n_pes
.. autofunction:: pe_accessible
.. autofunction:: addr_accessible
.. autofunction:: ptr


Memory Management
-----------------

.. autosummary::
   alloc
   free
   fromalloc
   new_array
   del_array
   array
   empty
   zeros
   ones
   full
   MALLOC


.. autofunction:: alloc
.. autofunction:: free
.. autofunction:: fromalloc
.. autofunction:: new_array
.. autofunction:: del_array
.. autofunction:: array
.. autofunction:: empty
.. autofunction:: zeros
.. autofunction:: ones
.. autofunction:: full

.. autoclass:: MALLOC

Team Management
---------------
.. autosummary::
   Team
   Team.destroy
   Team.split_strided
   Team.get_config
   Team.my_pe
   Team.n_pes
   Team.translate_pe
   Team.create_ctx
   Team.sync

.. autoclass:: Team

   .. automethod:: destroy
   .. automethod:: split_strided
   .. automethod:: get_config
   .. automethod:: my_pe
   .. automethod:: n_pes
   .. automethod:: translate_pe
   .. automethod:: create_ctx
   .. automethod:: sync

Communication Management
------------------------

.. autosummary::
   Ctx
   Ctx.create
   Ctx.destroy
   Ctx.get_team
   Ctx.fence
   Ctx.quiet
   CTX

.. autoclass:: Ctx

   .. automethod:: create
   .. automethod:: destroy
   .. automethod:: get_team
   .. automethod:: fence
   .. automethod:: quiet

.. autoclass:: CTX

Remote Memory Access
--------------------

.. autosummary::
   put
   get
   iput
   iget
   put_nbi
   get_nbi

.. autofunction:: put
.. autofunction:: get
.. autofunction:: iput
.. autofunction:: iget
.. autofunction:: put_nbi
.. autofunction:: get_nbi


Atomic Memory Operations
------------------------

.. autosummary::
   atomic_op
   atomic_fetch_op
   atomic_fetch_op_nbi
   AMO

.. autosummary::
   atomic_set
   atomic_inc
   atomic_add
   atomic_and
   atomic_or
   atomic_xor
   atomic_fetch
   atomic_swap
   atomic_compare_swap
   atomic_fetch_inc
   atomic_fetch_add
   atomic_fetch_and
   atomic_fetch_or
   atomic_fetch_xor

   atomic_fetch_nbi
   atomic_swap_nbi
   atomic_compare_swap_nbi
   atomic_fetch_inc_nbi
   atomic_fetch_add_nbi
   atomic_fetch_and_nbi
   atomic_fetch_or_nbi
   atomic_fetch_xor_nbi

.. autofunction:: atomic_op
.. autofunction:: atomic_fetch_op
.. autofunction:: atomic_fetch_op_nbi
.. autoclass::    AMO

.. autofunction:: atomic_set
.. autofunction:: atomic_inc
.. autofunction:: atomic_add
.. autofunction:: atomic_and
.. autofunction:: atomic_or
.. autofunction:: atomic_xor
.. autofunction:: atomic_fetch
.. autofunction:: atomic_swap
.. autofunction:: atomic_compare_swap
.. autofunction:: atomic_fetch_inc
.. autofunction:: atomic_fetch_add
.. autofunction:: atomic_fetch_and
.. autofunction:: atomic_fetch_or
.. autofunction:: atomic_fetch_xor

.. autofunction:: atomic_fetch_nbi
.. autofunction:: atomic_swap_nbi
.. autofunction:: atomic_compare_swap_nbi
.. autofunction:: atomic_fetch_inc_nbi
.. autofunction:: atomic_fetch_add_nbi
.. autofunction:: atomic_fetch_and_nbi
.. autofunction:: atomic_fetch_or_nbi
.. autofunction:: atomic_fetch_xor_nbi



Signaling Operations
--------------------

.. autosummary::
   new_signal
   del_signal
   signal_fetch
   put_signal
   put_signal_nbi
   SIGNAL

.. autofunction:: new_signal
.. autofunction:: del_signal
.. autofunction:: signal_fetch
.. autofunction:: put_signal
.. autofunction:: put_signal_nbi
.. autoclass::    SIGNAL


Collective Operations
---------------------

.. autosummary::
   barrier_all
   sync_all
   sync

   broadcast
   collect
   fcollect
   alltoall
   alltoalls

   reduce
   OP
   and_reduce
   or_reduce
   xor_reduce
   max_reduce
   min_reduce
   sum_reduce
   prod_reduce

.. autofunction:: barrier_all
.. autofunction:: sync_all

.. autofunction:: sync
.. autofunction:: broadcast
.. autofunction:: collect
.. autofunction:: fcollect
.. autofunction:: alltoall
.. autofunction:: alltoalls

.. autofunction:: reduce
.. autoclass::    OP
.. autofunction:: and_reduce
.. autofunction:: or_reduce
.. autofunction:: xor_reduce
.. autofunction:: max_reduce
.. autofunction:: min_reduce
.. autofunction:: sum_reduce
.. autofunction:: prod_reduce


Point-To-Point Synchronization
------------------------------

.. autosummary::
   wait_until
   wait_until_all
   wait_until_any
   wait_until_some
   wait_until_all_vector
   wait_until_any_vector
   wait_until_some_vector
   test
   test_all
   test_any
   test_some
   test_all_vector
   test_any_vector
   test_some_vector
   signal_wait_until
   CMP

.. autofunction:: wait_until
.. autofunction:: wait_until_all
.. autofunction:: wait_until_any
.. autofunction:: wait_until_some
.. autofunction:: wait_until_all_vector
.. autofunction:: wait_until_any_vector
.. autofunction:: wait_until_some_vector
.. autofunction:: test
.. autofunction:: test_all
.. autofunction:: test_any
.. autofunction:: test_some
.. autofunction:: test_all_vector
.. autofunction:: test_any_vector
.. autofunction:: test_some_vector
.. autofunction:: signal_wait_until
.. autoclass::    CMP


Memory Ordering
---------------

.. autosummary::
   fence
   quiet

.. autofunction:: fence
.. autofunction:: quiet


Distributed Locking
-------------------

.. autosummary::
   new_lock
   del_lock
   set_lock
   test_lock
   clear_lock

.. autofunction:: new_lock
.. autofunction:: del_lock
.. autofunction:: set_lock
.. autofunction:: test_lock
.. autofunction:: clear_lock

Distributed Locking (Object-Oriented)
-------------------------------------
.. autosummary::
   Lock
   Lock.destroy
   Lock.acquire
   Lock.release

.. autoclass:: Lock

   .. automethod:: destroy
   .. automethod:: acquire
   .. automethod:: release


Profiling Control
-----------------

.. autosummary::
   pcontrol

.. autofunction:: pcontrol


Typing Support
--------------

.. autodata:: Number
.. autodata:: SigAddr
.. autodata:: CtxHandle
.. autodata:: TeamHandle
.. autodata:: LockHandle

.. data:: ffi.CData

   See `ffi.CData <https://cffi.readthedocs.io/en/latest/ref.html#ffi-cdata-ffi-ctype>`_
