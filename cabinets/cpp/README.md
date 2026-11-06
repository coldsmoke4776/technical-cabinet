# C++ Reference Cabinet

A living collection of concepts I have studied, working fragments I can reuse, and explanations written in the language that made each mechanism click for me.

This is organized for lookup rather than as a course. Open the drawer for the thing you need, refresh the mental model, and start from code that has already been compiled.

## Verify the examples

```bash
make verify
```

This rebuilds the current examples with C++20 and strict warnings. When an example has a matching `<example>.expected.txt`, verification also runs it and compares its output.

Fresh builds go into the ignored `build/` directory. Historical Apple-Silicon binaries from the original folder are retained under [`artifacts/macos-arm64`](artifacts/macos-arm64/README.md), but fresh verification is the reliable proof that current source still compiles.

## Concept drawers

| Drawer | What is inside | Notes | Example |
| --- | --- | --- | --- |
| [Basic structure](concepts/basic-structure/notes.md) | Source files, `main`, libraries, compiler toolchain, ODR | In progress | Verified |
| [Variables](concepts/variables/notes.md) | Initialization, state, conditionals, `printf` formats | In progress | Verified |
| [Types](concepts/types/notes.md) | Built-in types, operators, `size_t`, `void` | In progress | Verified |
| [Arrays, strings, and loops](concepts/arrays-strings-loops/notes.md) | Arrays, iteration, sizes, string literals | In progress | Verified |
| [User-defined types](concepts/user-defined-types/notes.md) | Enums, structs, unions | In progress | Verified |
| [Functions](concepts/functions/notes.md) | Reserved drawer | Placeholder | Draft |
| [References and pointers](concepts/references-pointers/notes.md) | Copies, aliases, raw pointers, dynamic lifetime, ASan evidence, unique ownership | In progress | Verified |
| [Classes](concepts/classes/notes.md) | Encapsulation, access, constructors, initialization, destruction, RAII | In progress | Verified |
| [File input](concepts/file-input/notes.md) | Command-line paths, file streams, incremental line processing, exact substring counting | In progress | Verified |
| [Maps](concepts/maps/notes.md) | Key-value state, associative counting, scope, ordered iteration, evidence boundaries | In progress | Verified |
| [Vectors and iterators](concepts/vectors-iterators/notes.md) | Vector ownership, identity-based lookup, iterator guards, invalidation, ASan evidence | In progress | Verified |

“Verified” means the current example compiles under `make verify`. It does not mean every sentence in the accompanying learning notes has received a publication-level technical review.

## Snippet drawers

- [`snippets/experiments`](snippets/experiments) — larger standalone experiments
- [`snippets/project-start`](snippets/project-start) — a blank-page planning template that separates design ownership from reference work
- [`snippets/rng`](snippets/rng) — a reusable C random-number helper
- [`snippets/raylib-3d`](snippets/raylib-3d) — a Raylib experiment, verified only when Raylib is installed

## Adding something learned elsewhere

New material should come from real work rather than copied conversation logs:

1. identify the reusable concept;
2. place it in the existing drawer or create a clearly named new one;
3. explain the mechanism in concise personal notes;
4. extract the smallest representative example;
5. compile it and, where practical, verify its output;
6. review the diff before retaining it here.
