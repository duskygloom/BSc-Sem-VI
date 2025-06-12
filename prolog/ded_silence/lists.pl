head([H | _], H).

tail([X], X) :- !.
tail([_ | T], X) :- tail(T, X).

prepend([], X, [X]) :- !.
prepend(L, X, [X | L]).

append([], X, [X]) :- !.
append([H | T], X, [H | L]) :- append(T, X, L).

join(L, [], L) :- !.
join(L, [H | Rest], Result) :- append(L, H, R), join(R, Rest, Result).

contains([X | _], X) :- !.
contains([_ | Rest], X) :- contains(Rest, X).

index([X | _], X, 0) :- !.
index([_ | Rest], X, Index) :- index(Rest, X, I), Index is I+1.

