# 9.2 Statement Summary

Here is a summary of C++ statements:

## statement:

```
declaration
expressionopt ;
{ statement-listopt }
try { statement-listopt } handler-list
case constant-expression : statement
default : statement
break ;
continue ;
return expressionopt ;
goto identifier ;
identifier : statement
selection-statement
iteration-statement
```

## selection-statement:

```
if ( condition ) statement
if ( condition ) statement else statement
switch ( condition ) statement
```

## iteration-statement:

```
while ( condition ) statement
do statement while ( expression );
for ( for-init-statement conditionopt ; expressionopt ) statement
for ( for-init-declaration : expression ) statement
```

## statement-list:

```
statement statement-listopt
```

## condition:

```
expression
type-specifier declarator = expression
type-specifier declarator { expression }
```

## handler-list:

```
handler handler-listopt
```

## handler:

```
catch ( exception-declaration ){statement-listopt }
```

---

**Note:** A semicolon is by itself a statement, the empty statement.

**Section 9.2 - Statement Summary (Page 227)**

A (possibly empty) sequence of statements within "curly braces" (i.e., `{` and `}`) is called a **block** or a **compound statement**. A name declared in a block goes out of scope at the end of its block (§6.3.4).

A declaration is a statement and there is no assignment statement or procedure-call statement; assignments and function calls are expressions.

A `for-init-statement` must be either a declaration or an expression-statement. Note that both end with a semicolon.

A `for-init-declaration` must be the declaration of a single uninitialized variable.

The statements for handling exceptions, try-blocks, are described in §13.5

