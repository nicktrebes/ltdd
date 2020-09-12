# ltdd
Lua Test Driven Development

## ltdd Lua API

`ltdd.assertEqual(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isEqualTo(value))`

`ltdd.assertFalse(actual)` is equivalent to `ltdd.assertThat(actual, ltdd.isFalse)`

`ltdd.assertGreaterThan(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isGreaterThan(value))`

`ltdd.assertLessThan(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isLessThan(value))`

`ltdd.assertNil(actual)` is equivalent to `ltdd.assertThat(actual, ltdd.isNil)`

`ltdd.assertNotEqual(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isNotEqualTo(value))`

`ltdd.assertNotNil(actual)` is equivalent to `ltdd.assertThat(actual, ltdd.isNotNil)`

`ltdd.assertTablesEqual(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isEqualToTable(value))`

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
| `ltdd.isEqualToTable(value)` | all key/value pairs are the same for `actual` and `value` |

`ltdd.assertThrows(fn, [msg, [...]])` protected calls `fn` with any given extra arguments.
The assertion fails when `fn` fails to raise an error.
If not nil, `msg` will be compared with any raised error.
In this case, the assertion will fail if `msg` is not equal to the raised error.

`ltdd.assertTrue(actual)` is equivalent to `ltdd.assertThat(actual, ltdd.isTrue)`

`ltdd.assertType(actual, value)` is equivalent to `ltdd.assertThat(actual, ltdd.isOfType(value))`

`ltdd.createMock(name)` returns a mock object with name `name`.
If `mock.return_value` is a table, calling `mock(...)` repeatedly will cycle through that table, returning one value per call.
If `mock.return_value` is anything else, calling `mock(...)` repeatedly will return `mock.return_value` each call.
The arguments given to `mock(...)` are stored in the mock object's `calls` metavalue table.
`mock:assertCalledWith(...)` will fail if `mock(...)` was never previously called with the same arguments.

`ltdd.createSuite(name)` returns a test suite object with name `name`.
Its `__index` metavalue is `ltdd` and its `__newindex` metamethod adds tests to a table in its metatable.
The test suite can be run by invoking its `__call` metamethod.
If provided, string arguments to this function will be used to select specific tests to run instead of the whole suite.
