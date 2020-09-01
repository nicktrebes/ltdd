# ltdd
Lua Test Driven Development

## ltdd Lua API

`ltdd.assert_that(actual, constraint)` behaves according to this table:

| Constraint | Passes if actual value/expression... |
| ---------- | ------------------------------------ |
| `ltdd.is_true` | evaluates to `true` |
| `ltdd.is_false` | evaluates to `false` |
| `ltdd.is_nil` | evaluates to `nil` |
| `ltdd.is_not_nil` | evaluates to anything other than `nil` |
| `ltdd.is_equal_to(value)` | `== value` |
| `ltdd.is_not_equal_to(value)` | `~= value` |
| `ltdd.is_greater_than(value)` | `> value` |
| `ltdd.is_less_than(value)` | `< value` |
| `ltdd.is_of_type(value)` | `type(actual) == value` |
