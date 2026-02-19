IOCCC-style remarks for sh2elf.c (≈4.9 KB)

What it is
- A self-contained ELF-forge: parses a tiny shell subset and emits runnable x86-64 ELF binaries without /bin/sh or libcs at runtime. The C compiler is only needed to build the forger.
- Everything lives in one global `G g` so macros can spray opcodes without lugging pointers around. Strings, code, and runtime scratch share a single 8 KiB slab.

Shell subset (what scripts may do)
- Words: plain or double-quoted (no single quotes, no backslash escapes).
- Separators: whitespace, `;` and newlines end commands; `#` to end-of-line is a comment.
- Control: `cmd1 && cmd2`, `cmd1 || cmd2` honored with short-circuit using the captured exit status.
- Pipelines: only two-stage `a | b` supported; more stages are rejected by structure limits.
- No redirections, no builtins (cd/echo/exit), no variable expansion. Paths are tried literal or prefixed with `/bin/`.

How ELF generation works
- Parsing builds a short array of commands/pipelines (`Sc/En/Pl/St/SV`), each argv captured in the shared string pool; offsets become absolute by adding `BB`.
- Emitters (`A/D/S/X/B2/B3/B4/SC`) append raw machine code into `g.c.b`. Helper `FK` wraps `clone` plus the child/parent split; `z()` extracts and stores the WEXITSTATUS in memory at `UO`.
- `ex()` inlines argv/env layout: writes argv pointers (and trailing NULL) into the RW segment, then issues `execve`. On failure it exits(1) silently.
- `h()` wires a single pipe, forks twice via `clone`, sets up dup2/close, runs left then right command, closes pipe ends, waits for the last child, records status.
- `el()` copies code+strings into a fresh buffer, writes a minimal ELF64 header and two PHDRs (RX text at 0x400000+0xB0, RW data at 0x600000 with 4 KiB align), then chmods the output to 0755.

Obfuscation / size tricks
- Identifier diet: typedefs to single letters, globals for context; removed struct offset table, now store raw string offsets.
- Inlined helpers: argv builder folded into `ex`; status macros reuse shared address `UO`; printf path assembled with `sprintf` to avoid `snprintf` bloat.
- Opcode macros favor short B2/B3/B4 chains; `FK` macro eliminates repeated clone child-check boilerplate.
- Buffers trimmed (code+data slab 8 KiB; BO starts at 768); arrays capped (32 args, 4 pipeline stages, 16 commands).
- Headers compacted: preprocessor lines isolated but code densely packed; no comments in C; minimal whitespace.

Limits and assumptions
- x86_64 little-endian only; requires `clone`, `pipe`, `dup2`, `waitpid`, `execve`, `exit` syscalls.
- No redirections/builtins/expansion; pipeline length 2; argv length and string pool bounded by the fixed slab; command path max 63 chars.
- Status propagation relies on last child of pipeline; only the final exit code is stored/checked for `&&`/`||`.

Testing done (each minify round)
- `make -s`
- `./verify.sh` (Hello World, Pipeline, Logic) — all green at 4903 bytes.
