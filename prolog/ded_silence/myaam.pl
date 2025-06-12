member([X | _], X) :- !.
member([_ | Rest], X) :- member(Rest, X).

concat([], L, L) :- !.
concat([H | Rest], L, [H | Result]) :- concat(Rest, L, Result).

% member function using concat
member2([X | _], X) :- !.
member2(L, X) :- concat(_, [X | _], L).

join([], L, L) :- !.
join([H | Rest], L, [H | Result]) :- join(Rest, L, Result).

delete([], _, []) :- !.
delete([X | Rest], X, Rest) :- !.
delete([H | Rest], X, [H | Result]) :- delete(Rest, X, Result).

deleteAll([], _, []) :- !.
deleteAll([X | Rest], X, Result) :- deleteAll(Rest, X, Result), !.
deleteAll([H | Rest], X, [H | Result]) :- deleteAll(Rest, X, Result).

last([X], X) :- !.
last([_ | Rest], X) :- last(Rest, X).

% last element using concat
last2([X], X) :- !.
last2(L, X) :- concat(_, [X], L).

reverse([], []) :- !.
reverse([X], [X]) :- !.
reverse([H | Rest], Result) :- reverse(Rest, P), concat(P, [H], Result).

palindrome(X) :- reverse(X, X).

odd([_]) :- !.
odd([_ | Rest]) :- even(Rest).

even([]) :- !.
even([_ | Rest]) :- odd(Rest).

prefix(_, []) :- !.
prefix([H | Rest1], [H | Rest2]) :- prefix(Rest1, Rest2).

suffix(L, L) :- !.
suffix([_ | Rest], L) :- suffix(Rest, L).

sublist(L, S) :- prefix(L, S), !.
sublist([_ | Rest], S) :- sublist(Rest, S).

doubleHeader([X, X | _]).

doubleTone([_, _]).
notDoubleTone(L) :- \+ doubleTone(L).

sameLength([], []) :- !.
sameLength([_ | Rest1], [_ | Rest2]) :- sameLength(Rest1, Rest2).

unary(0) :- !.
unary(s(X)) :- whole(X).

unaryEven(0) :- !.
unaryEven(s(X)) :- unaryOdd(X).

unaryOdd(s(0)) :- !.
unaryOdd(s(X)) :- unaryEven(X).

multiple3(0) :- !.
multiple3(s(s(s(X)))) :- multiple3(X).

f(X, 0) :- X<3, !.
f(X, 2) :- X<6, !.
f(_, 4).

max(X, Y, X) :- X>Y, !.
max(_, Y, Y).

gcd(X, X, X) :- !.
gcd(X, Y, D) :- Y>X, X1 is Y-X, gcd(X1, X, D), !.
gcd(X, Y, D) :- gcd(Y, X, D).

ackerman(0, N, R) :- N>0, R is N+1, !.
ackerman(M, 0, R) :- M>0, M1 is M-1, ackerman(M1, 1, R), !.
ackerman(M, N, R) :- M>0, N>0, M1 is M-1, N1 is N-1,
					 ackerman(M, N1, R1), ackerman(M1, R1, R).

% monkey banana problem
% state(hpos, vpos, bpos, has)
has(state(_, _, _, has)) :- !.
has(S1) :- move(S1, _, S2), has(S2).

move(state(middle, box, middle, hasnot),
	 grasp,
	 state(middle, box, middle, has)) :- !.

move(state(middle, floor, middle, H),
	 climb,
	 state(middle, box, middle, H)) :- !.

move(state(P1, floor, P1, H),
     push(P1, P2),
	 state(P2, floor, P2, H)) :- !.

move(state(P1, floor, B, H),
     walk(P1, P2),
     state(P2, floor, B, H)).


 subset2(L, [H | R]) :- .

intersection([], L, []) :- !.
intersection([H | R], L, [H | R2]) :- member(L, H), !, intersection(Rest, L, R2).
intersection([H | Rest], L, I) :- intersection(Rest, L, I).
