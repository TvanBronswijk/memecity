# Code Review Guidelines

While reviewing code, ask yourself the following questions:

* Am I able to understand the code easily?
* Is the code written following the coding standards/guidelines?
* Is the same code duplicated more than twice?
* Can I unit test / debug the code easily to find the root cause?
* Is this function or class too big? If yes, is the function or class having too many responsibilities?

## Naming Violations

When a PR includes a naming violation, comment on the corresponding line. Example:

```cpp
  const int mY-var;
```
> Please rename `mY-var` to `my_var`.

---

When a PR includes multiple consistent naming violations, comment on the first violation. Example:

```cpp
  const int meme_variable;
```
> Please remove the `meme_` prefix from all variables. 
```cpp
  const char* meme_string;
  const int[1] meme_array;
```

## Best Practices

Sometimes, while code can be correct, it can be harder to read, or simply not be best practice in the language at hand. This
might not require a merge-blocking comment, but it's always nice to keep code conforming to the best practices available.
Example:

```cpp
  void do(int i);
```
> Please use `const` on parameters where possible.

## Other

Sometimes, an issue with a PR is too entrenched in the code that it requires the entire PR to be refactored. In that case,
comment on the PR itself. Write down your reasons for questioning the PR, and any possible solutions you've come up with.
Usually this can lead to longer discussions, sometimes with multiple parties. Never forget to be civil to eachother, even
if it's from behind a keyboard!

