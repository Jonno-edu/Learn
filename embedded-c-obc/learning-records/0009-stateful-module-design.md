# Stateful module design

The user completed the stateful flight-phase module exercise and practiced the caller-owned context pattern: initialize explicit module state, pass the same context through repeated update calls, keep memory out of hidden globals, and let tests replay sample sequences through the public API. Future lessons can assume the user understands why a module can remember facts between calls without owning its own loop.

Keep reinforcing that a later scheduler or FreeRTOS task is just the caller around this ordinary C module. The module should not secretly allocate state, block, sleep, or mutate file-scope state unless that ownership is deliberate and documented.
