primes([2, 3, 5, 7, 11, 13]).
fibonacci([0, 1, 1, 2, 3, 5]).

/* Check if the list is double header. */
doubleHeader([X | [X | _]]).

/* Check if the list does not have two elements. */
notDoubleTone([]).
notDoubleTone([_]).
notDoubleTone([_ | [_ | [_ | _]]]).

/* Check whether two lists are of equal length. */
equalLength([], []).
equalLength([_ | Rest1], [_ | Rest2]) :- equalLength(Rest1, Rest2).

/* Find the last element of a list. */
lastElement(X, [X]).
lastElement(X, [_ | Rest]) :- lastElement(X, Rest).

firstElement(X, [X]).
firstElement(X, [X | _]).

/* Check for consecutive elements in the list. */
nextTo(X, Y, [X | [Y | _]]).
nextTo(X, Y, [_ | Rest]) :- nextTo(X, Y, Rest).

/* Add an element to the start of a list. */
pushLeft(X, Y, [X | Y]).

pushRight(X, [], [X]).
pushRight(X, [Y | Rest1], [Y | Rest2]) :- pushRight(X, Rest1, Rest2).

/* Check if an element exists in a list. */
exists(X, [X | _]).
exists(X, [_ | Rest]) :- exists(X, Rest).

/* Concatenate two lists. */
concat([], A, A).
concat([X | Rest1], A, [X | Rest2]) :- concat(Rest1, A, Rest2).

/* lastElement function using concat */

/* nextTo using concat */
 nextToConcat(A, B, L) :- concat([A], [B], [A | B]).

/* exists function using concat */

/* Reverse a list. */

/* Check whether a list is palindrome. */

