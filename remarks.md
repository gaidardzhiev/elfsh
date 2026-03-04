### ELFSH
Elfsh is a minimalistic compiler that compiles shell scripts into standalone `ELF64` executables for `Linux` on the `x86_64` architecture. It translates shell command lines into machine code, embeds them in an `ELF` binary, and handles process control and system calls natively without relying on an external shell or interpreter.Everything lives in one global `G g` so macros can spray opcodes without lugging pointers around.

### Shell subset
The source language is intentionally tiny. Anything outside the rules below is rejected with a parse error or left uninterpreted.

- Words: plain or double-quoted (no single quotes, no backslash escapes).
- Separators: whitespace, `;` and newlines end commands; `#` to end-of-line is a comment.
- Control: `cmd1 && cmd2`, `cmd1 || cmd2` honored with short-circuit using the captured exit status.
- Pipelines: only two-stage `a | b` supported; more stages are rejected by structure limits.
- No redirections, no builtins (cd/echo/exit), no variable expansion. Paths are tried literal or prefixed with `/bin/`.

### How ELF generation works
- Parsing builds a short array of commands/pipelines (`Sc/En/Pl/St/SV`), each argv captured in the shared string pool; offsets become absolute by adding `BB`.
- Emitters (`A/D/S/X/B2/B3/B4/SC`) append raw machine code into `g.c.b`. Helper `FK` wraps `clone` plus the child/parent split; `z()` extracts and stores the WEXITSTATUS in memory at `UO`.
- `ex()` inlines argv/env layout: writes argv pointers (and trailing NULL) into the RW segment, then issues `execve`. On failure it exits(1) silently.
- `h()` wires a single pipe, forks twice via `clone`, sets up dup2/close, runs left then right command, closes pipe ends, waits for the last child, records status.
- `el()` copies code+strings into a fresh buffer, writes a minimal ELF64 header and two PHDRs (RX text at 0x400000+0xB0, RW data at 0x600000 with 4 KiB align), then chmods the output to 0755.

### Obfuscation techniques
- Identifier diet: typedefs to single letters, globals for context; removed struct offset table, now store raw string offsets.
- Inlined helpers: argv builder folded into `ex`; status macros reuse shared address `UO`; printf path assembled with `sprintf` to avoid `snprintf` bloat.
- Opcode macros favor short B2/B3/B4 chains; `FK` macro eliminates repeated clone child-check boilerplate.
- Buffers trimmed (code+data slab 8 KiB; BO starts at 768); arrays capped (32 args, 4 pipeline stages, 16 commands).
- Headers compacted: preprocessor lines isolated but code densely packed; no comments in C; minimal whitespace.

### Testing
- Verify with `make clobber`, `make`, and `./try.sh` or manually.
