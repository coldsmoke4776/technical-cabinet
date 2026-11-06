# Vectors And Iterators

## The Problem Shape

A single named object is easy to act on directly:

```cpp
enemy.applyDamage(5);
```

That stops scaling once several objects represent the same kind of thing. In Terminal Velocity, Wurm and Hydra belonged in one enemy roster:

```cpp
std::vector<Combatant> enemies{
    {"Wurm", 50},
    {"Hydra", 40},
};
```

The vector owns both `Combatant` objects by value. The remaining problem is selection: attack the enemy named Hydra, not merely whatever happens to occupy index `1` today.

## Indexes Answer "Where?", Not "Which One?"

This works only because I already know the current order:

```cpp
enemies[1].applyDamage(5);
```

It says “damage the second element.” It does not say “damage Hydra.” Inserting, erasing, sorting, or otherwise changing the roster can make the same index identify a different object.

`at()` adds bounds checking:

```cpp
enemies.at(1).applyDamage(5);
```

That protects against an invalid position, but it still does not protect identity. `at(1)` can prove that a second element exists; it cannot prove that the second element is Hydra.

## Searching By Meaning With `std::find_if`

`std::find_if` examines the half-open range from `begin()` up to, but not including, `end()`:

```cpp
auto found = std::find_if(
    enemies.begin(),
    enemies.end(),
    [&targetName](const Combatant& enemy) {
        return enemy.name == targetName;
    }
);
```

The lambda is the predicate: it receives each enemy and answers `true` or `false`. `find_if` stops at the first `true` result.

The pieces have separate jobs:

- `[&targetName]` lets the lambda read the outer search string by reference.
- `const Combatant& enemy` aliases each existing vector element without copying or mutating it during comparison.
- `enemy.name == targetName` is the actual matching condition.

Capturing `targetName` by value would also work when the lambda only needs a snapshot. Capturing by reference means the lambda reads the existing outer string. Neither capture creates or searches for another `Combatant`; the string is only a query.

## What `find_if` Returns

`find_if` returns an iterator, not a numeric index and not a copied object.

For this mutable vector, the full type is:

```cpp
std::vector<Combatant>::iterator
```

`auto` lets the compiler infer that exact type at compile time:

```cpp
auto found = std::find_if(/* ... */);
```

The iterator identifies an element in the vector. Once it is known to be valid, pointer-like syntax reaches that existing object:

```cpp
found->applyDamage(5);
```

This is equivalent to:

```cpp
(*found).applyDamage(5);
```

No copied `Combatant` is being damaged.

## `end()` Is A Sentinel, Not An Element

When no element satisfies the predicate, `find_if` returns the end iterator:

```cpp
found == enemies.end()
```

`end()` represents the position one past the final element. It is valid for comparison, but it does not identify an object and must never be dereferenced.

The guard therefore comes before every use of `*found` or `found->`:

```cpp
if (found != enemies.end()) {
    found->applyDamage(5);
} else {
    std::cout << "Target not found\n";
}
```

The guard must cover every dereference. Moving `printCombatant(*found)` below the entire `if`/`else` does not make it safe: the missing branch still reaches that later statement.

Two experiments made the undefined behavior visible in different ways. One unguarded missing lookup triggered an AddressSanitizer heap-buffer-overflow in the vector's right redzone. Another ordinary build happened to print an empty name and zero values. Neither behavior is promised; undefined behavior may appear plausible, crash, corrupt memory, or change when the build changes.

## Iterator Invalidation

An iterator is useful only while the vector operation that produced it remains valid.

Vector elements normally live in one contiguous buffer. When an operation such as `reserve()` or `push_back()` causes reallocation, the vector obtains a new buffer and moves or copies its elements there. Pointers, references, and iterators into the old buffer then dangle.

Terminal Velocity forced a reallocation and observed the element address change while its values survived in the new buffer. Dereferencing a pointer retained from the old buffer produced an AddressSanitizer heap-use-after-free report.

The practical rule is:

> Do not retain a vector element's pointer, reference, or iterator across an operation that may reallocate. Perform the mutation first, then obtain a fresh handle.

An index itself does not point into the old buffer, so it can survive reallocation when order remains unchanged. It still does not provide stable identity across insertion, erasure, sorting, or reordering.

## Boundaries

The guarded lookup example proves exact, case-sensitive selection of the first matching name in the current vector.

It does not provide:

- unique identity when duplicate names exist;
- case-insensitive or partial matching;
- stable handles across vector mutation;
- input validation or a complete combat system.

If two enemies are named Hydra, `find_if` selects the first one because that is its contract.

[`guarded-lookup.cpp`](guarded-lookup.cpp) isolates the found and missing paths. Its output is verified by [`guarded-lookup.expected.txt`](guarded-lookup.expected.txt).

Related: [References and pointers](../references-pointers/notes.md) and [Arrays, strings, and loops](../arrays-strings-loops/notes.md)
