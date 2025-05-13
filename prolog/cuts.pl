f(X, 0) :- X < 3.
f(X, 2) :- X >= 3, X < 6.
f(X, 4) :- X >= 6.

fcut(X, 0) :- X < 3, !.
fcut(X, 2) :- X < 6, !.
fcut(_, 4).

/* Maximum of two numbers. */
max(X, Y, X) :- X >= Y.
max(X, Y, Y) :- Y >= X.

/* Maximum of two numbers using cuts. */
maxcut(X, Y, X) :- X >= Y, !.
maxcut(_, Y, Y).

/* Member function. */
member(X, [X | _]).
member(X, [_ | Rest]) :- member(X, Rest).

membercut(X, [X | _]) :- !.
membercut(X, [_ | Rest]) :- membercut(X, Rest).

efface(_, [], []).
efface(X, [X | L], L) :- !.
efface(X, [Y | L], [Y | L1]) :- efface(X, L, L1).
