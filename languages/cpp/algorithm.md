# &lt;algorithm&gt;

Unlike a container, a function from `<algorithm>` owns no data of its own. It operates on a range described by a pair of iterators, conventionally named `first` and `last`, where `last` points one past the final element, mirroring `end()` from [iterator.md](iterator.md). What a given function can do, and how fast, is bounded by which iterator category that range actually provides.

Every function below assumes this header and namespace are already in scope:

```cpp
#include <algorithm>
using namespace std;
```

## Predicates and lambdas

Several functions below, `count_if`, `find_if`, and `sort`'s optional comparator, take a callable instead of a fixed value, so the condition can be arbitrary logic rather than a hardcoded comparison. The usual way to write one inline is a lambda:

```cpp
[](int x) { return x % 2 == 0; }
```

Reading left to right, `[]` is the capture clause, controlling which outside variables the body is allowed to see, empty means none. `(int x)` is the parameter list, exactly like an ordinary function's, this is what the algorithm passes each element into. `{ return x % 2 == 0; }` is the body, also exactly like an ordinary function's, and for a predicate it must return `bool`.

Capturing outside variables works like this:

| Capture | Meaning |
|---|---|
| `[]` | no outside variables visible |
| `[x]` | a copy of `x`, fixed at the moment the lambda is created |
| `[&x]` | a reference to `x`, sees later changes to it |
| `[=]` | a copy of every outside variable the body actually uses |
| `[&]` | a reference to every outside variable the body actually uses |

```cpp
int threshold = 10;
int n = count_if(v.begin(), v.end(), [threshold](int x) { return x > threshold; });
```

`count_if` and `find_if` expect a unary predicate, one element in, `bool` out. `sort`'s comparator is a different shape, a binary predicate, two elements in, `bool` out, meaning "should the first argument come before the second," which is why `greater<int>()` and a two-parameter lambda both fit where `sort`'s third argument goes but a one-parameter lambda would not.

## 1. sort

`sort` rearranges a range into ascending order in place, using introsort, a hybrid that runs quicksort but falls back to heapsort if the recursion goes too deep, which is what guarantees O(n log n) even in the worst case rather than quicksort's usual O(n^2) worst case.

```cpp
sort(v.begin(), v.end());                                     // ascending
sort(v.begin(), v.end(), greater<int>());                     // descending
sort(v.begin(), v.end(), [](int a, int b) { return a > b; }); // custom comparator
```

Because it needs to jump to arbitrary positions to partition the range, `sort` requires random access iterators, which is why it compiles against `vector`, `deque`, and plain arrays, but not `list`, `map`, `set`, or either hash-based container.

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `sort(first, last)` | `void` | O(n log n) | random access |
| `sort(first, last, cmp)` | `void` | O(n log n) | random access |

## 2. reverse

`reverse` flips a range end for end in place, swapping the first element with the last, the second with the second-to-last, and so on toward the middle.

```cpp
reverse(v.begin(), v.end());
```

Swapping from both ends toward the middle only needs to step forward from one side and backward from the other, so bidirectional iterators are enough, no random access jumps required. That is enough for `vector`, `deque`, and `list`, but a `map`'s value type pairs a `const` key with its value, which cannot be swapped, so reversing a `map` in place is not meaningful.

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `reverse(first, last)` | `void` | O(n) | bidirectional |

## 3. binary_search, lower_bound, upper_bound

All three assume the range is already sorted, and search it the way a manual binary search would, repeatedly comparing against the middle element and discarding the half that cannot contain the answer.

```cpp
bool found = binary_search(v.begin(), v.end(), 5); // true or false

auto lo = lower_bound(v.begin(), v.end(), 5);                   // first element not less than 5
vector<int>::iterator lo2 = lower_bound(v.begin(), v.end(), 5); // same thing, spelled out

if (lo != v.end()) {
    // dereference to read the element lo points to
    int value = *lo;
}
```

The number of comparisons is always O(log n), but reaching the middle of the remaining range costs O(1) with random access iterators and O(k) with only forward iterators, since a forward iterator has to be advanced one step at a time to get there. On a `vector`, all three run in true O(log n). On a `map`, whose own `find`/`lower_bound` member functions walk the tree directly, calling the free-function version from `<algorithm>` instead would degrade to O(n log n) overall, which is exactly why `map` provides its own `lower_bound` and `upper_bound` as member functions.

| Function | Returns | Complexity |
|---|---|---|
| `binary_search(first, last, x)` | `bool` | O(log n) on random access, O(n) otherwise |
| `lower_bound(first, last, x)` | iterator | O(log n) on random access, O(n) otherwise |
| `upper_bound(first, last, x)` | iterator | O(log n) on random access, O(n) otherwise |

## 4. min, max, min_element, max_element

`min` and `max` compare two values directly and are O(1). `min_element` and `max_element` instead scan a whole range to find the smallest or largest element, so they need nothing more than a forward iterator, one pass, no jumping around required.

```cpp
int a = min(3, 7);       // 3
int b = max(3, 7);       // 7

auto it = min_element(v.begin(), v.end()); // iterator to the smallest element
auto jt = max_element(v.begin(), v.end()); // iterator to the largest element
```

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `min(a, b)` / `max(a, b)` | value | O(1) | (values, not a range) |
| `min_element(first, last)` / `max_element(first, last)` | iterator | O(n) | forward |

## 5. count, count_if

`count` walks the range once and tallies how many elements compare equal to a given value. `count_if` does the same but with a predicate function instead of a fixed value, so the condition can be arbitrary.

```cpp
// how many equal 5
int n = count(v.begin(), v.end(), 5);

// how many are even
int m = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }); 
```

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `count(first, last, x)` | `size_t` | O(n) | input |
| `count_if(first, last, pred)` | `size_t` | O(n) | input |

## 6. find, find_if

`find` scans linearly for the first element equal to a value, and `find_if` does the same with a predicate. Both return `last` when nothing matches, the exact sentinel convention `end()` establishes for containers themselves.

```cpp
auto it = find(v.begin(), v.end(), 5);
if (it != v.end()) { /* found at *it */ }

auto jt = find_if(v.begin(), v.end(), [](int x) { return x > 100; });
```

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `find(first, last, x)` | iterator | O(n) | input |
| `find_if(first, last, pred)` | iterator | O(n) | input |

## 7. unique

`unique` collapses consecutive runs of equal elements down to one, shifting the surviving elements to the front of the range and returning an iterator to the new logical end. It does not shrink the container, and it only removes duplicates that are already adjacent, so it is almost always called on a range that has just been sorted.

```cpp
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end()); // erase-remove idiom
```

The trailing `erase` call is necessary because `unique` cannot resize `v` itself, an iterator has no way to shrink the container behind it, so the leftover tail past the new logical end still has to be erased explicitly.

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `unique(first, last)` | iterator | O(n) | forward |

## 8. next_permutation

`next_permutation` rearranges a range in place into the lexicographically next arrangement of its elements, and reports whether such an arrangement existed by returning `false` once the range was already at its highest permutation, wrapping it back around to the lowest (fully sorted ascending) in that case.

```cpp
sort(v.begin(), v.end()); // start from the lowest permutation
do {
    // use v here
} while (next_permutation(v.begin(), v.end()));
```

Each call is amortized O(n) across a full cycle through all permutations, since most calls only need to swap a small suffix, while a full traversal of every permutation costs O(n!) calls overall.

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `next_permutation(first, last)` | `bool` | O(n) amortized per call | bidirectional |

## 9. fill, swap

`fill` assigns the same value to every element in a range, one pass, no comparisons needed. `swap` exchanges two values, and for containers it does not swap element by element at all, it swaps the internal pointers/state (the buffer pointer and size for a `vector`, the root pointer for a `map`), so swapping two whole containers is O(1) regardless of how many elements they hold.

```cpp
fill(v.begin(), v.end(), 0); // zero out every element

vector<int> a = {1, 2, 3};
vector<int> b = {4, 5, 6};
swap(a, b); // a and b trade contents in O(1), not O(n)
```

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `fill(first, last, x)` | `void` | O(n) | forward |
| `swap(a, b)` | `void` | O(1) for containers, O(1) for scalars | (values, not a range) |

# &lt;numeric&gt;

Everything in `<algorithm>` only ever compares or rearranges elements, using `operator<` or `operator==`, which is why it works on strings, custom structs, anything comparable, without expecting arithmetic. `<numeric>` exists as its own header because its functions fold elements together with arithmetic instead, `operator+` by default, a stronger requirement than comparison alone, and that requirement is exactly the line the standard draws between the two headers. `accumulate` sits on the arithmetic side of that line.

## 1. accumulate

`accumulate` folds a range down to a single value by repeatedly applying an operation, addition by default, starting from a given initial value.

```cpp
#include <numeric>
using namespace std;

int sum = accumulate(v.begin(), v.end(), 0);                        // sum, starting from 0
int product = accumulate(v.begin(), v.end(), 1, multiplies<int>()); // product instead
```

| Function | Returns | Complexity | Requires |
|---|---|---|---|
| `accumulate(first, last, init)` | value | O(n) | input |
| `accumulate(first, last, init, op)` | value | O(n) | input |
