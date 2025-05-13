/*
	In unary form, we represent a number using a recursive form.
	0 = 0
	1 = s(0)
	2 = s(s(0))
	and so on...
*/

isUnary(0).
isUnary(s(X)) :- isUnary(X).

plus(X, s(Y), Z) :- plus(s(X), Y, Z), !.
plus(X, 0, X).

minus(s(X), s(Y), Z) :- minus(X, Y, Z), !.
minus(X, 0, X).

factorial(N, F) :- N > 0, N1 is N - 1,
				   factorial(N1, F1), F is N * F1, !.
factorial(0, 1).

fibonacci(N, F) :- N >= 0, N1 is N - 1, N2 is N - 2,
				   fibonacci(N1, F1), fibonacci(N2, F2),
				   F is F1 + F2, !.
fibonacci(0, 0).
fibonacci(1, 1).

