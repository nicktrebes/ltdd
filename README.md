# ltdd
Lua Test Driven Development

## ltdd Lua API

`ltdd.assertThat(actual, constraint)` behaves according to this table:

| Constraint | Passes if actual value/expression... |
| ---------- | ------------------------------------ |
| `ltdd.isTrue` | evaluates to `true` |
| `ltdd.isFalse` | evaluates to `false` |
| `ltdd.isNil` | evaluates to `nil` |
| `ltdd.isNotNil` | evaluates to anything other than `nil` |
| `ltdd.isEqualTo(value)` | `== value` |
| `ltdd.isNotEqualTo(value)` | `~= value` |
| `ltdd.isGreaterThan(value)` | `> value` |
| `ltdd.isLessThan(value)` | `< value` |
| `ltdd.isOfType(value)` | `type(actual) == value` |

`ltdd.assertThrows(fn, [msg, [...]])` protected calls `fn` with any given extra arguments.
The assertion fails when `fn` fails to raise an error.
If not nil, `msg` will be compared with any raised error.
In this case, the assertion will fail if `msg` is not equal to the raised error.

`ltdd.createSuite(name)` returns a test suite object with name `name`.
Its `__index` metavalue is `ltdd` and its `__newindex` metamethod adds tests to a table in its metatable.
The test suite can be run by invoking its `__call` metamethod.
If provided, string arguments to this function will be used to select specific tests to run instead of the whole suite.
