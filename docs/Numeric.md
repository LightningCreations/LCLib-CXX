# Numeric Named Requirement

*Numeric* is a Named Requirement in LCLib-C++.

For a Type T to satisfy *Numeric*, it must satisfy be *trivially copyable*, and Given:
* `t`, `s`, which are both expressions of type `T` and are not implementation-defined `NaN` values if such values exist
* `r` an lvalue of type `T`
* `cr` an lvalue of type `const T` or `T`
* `z`, a zero-initialized value of type `T`
* `i`, the value of type `T` which is equivalent to `T{1}`
* `U` a type which satisfies *Numeric*, and all values of type `T` can be represented as a value of type `U`
* `K` a type which satisfies *Numeric*, and all values of type `K` can be represented as a value of type `T`
* `c` an integral constant expression which can exactly be represented as a value of type `T`
* `k`, `u`, values of types `K` and `U` respectively

The following expressions are well formed, and have the following results:
<table>
    <tr>
        <th>Expression</th>
        <th>Type</th>
        <th>Value</th>
        <th>Preconditions</th>
    </tr>
    <tr>
        <th>T{}</th>
        <th>T</th>
        <th>z</th>
    </tr>
    <tr>
        <th>T{t}</th>
        <th>T</th>
        <th>Equivalent to t</th>
    </tr>
    <tr>
        <th>T{c}</th>
        <th>T</th>
        <th>Equivalent to t if the value of the object referred to by c is equivalent to t</th>
    </tr>
    <tr>
        <th>T{k}</th>
        <th>T</th>
        <th>The value of T which strictly represents the value of k</th>
        <th>This expression is only required to be well-formed if K is an arithmetic type. Otherwise it is implementation-defined when it is well-formed</th>
    </tr>
    <tr>
        <th>T(u)</th>
        <th>T</th>
        <th>The value of T which strictly represents the value of l, if s can be represented as a value of T, otherwise an unspecified value</th>
        <th>This expression is only required to be well-formed if U is an arithmetic type. Otherwise it is implementation-defined when it is well-formed</th>
    </tr>
    <tr>
        <th>T{c}</th>
        <th>T</th>
        <th>The value of T which strictly represents the value of c. For all such c, T{c}==T{c}</th>
    </tr>
    <tr>
        <th>T{0}</th>
        <th>T</th>
        <th>Equivalent to z</th>
    </tr>
    <tr>
        <th>T{1}</th>
        <th>T</th>
        <th>Equivalent to i</th>
    </tr>
    <tr>
        <th>s==t</th>
        <th>bool</th>
        <th>true if and only if s and t are equivalent</th>
    </tr>
    <tr>
        <th>t==t</th>
        <th>bool</th>
        <th>true</th>
    </tr>
    <tr>
        <th>t==T{t}</th>
        <th>bool</th>
        <th>true</th>
    </tr>
</table>
