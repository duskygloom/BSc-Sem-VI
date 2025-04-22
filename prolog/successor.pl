/* Check whether a number is even or not. */
even(0).
even(s(s(N))) :- even(N).

/* Check whether a number is odd or not. */
odd(s(0)).
odd(s(s(N))) :- odd(N).

/* Find whether a number is divisible by 3 or not. */
divisibleByThree(0).
divisibleByThree(s(s(s(X)))) :- divisibleByThree(X).

isNatural(0).
isNatural(s(X)) :- isNatural(X).

isLessEqual(0, Y) :- isNatural(Y).
isLessEqual(s(X), s(Y)) :- isLessEqual(X, Y).

plus(X, 0, X).
plus(s(X), Y, s(Z)) :- plus(X, Y, Z).

