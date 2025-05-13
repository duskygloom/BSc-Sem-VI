head([H | _], H).

tail([_ | Rest], T) :- tail(Rest, T), !.
tail([T], T).

prefix(P, List, [P | List]).

suffix(S, [], [S]).
suffix(S, [H | Rest], [H | Suffixed]) :- suffix(S, Rest, Suffixed).

member(M, [_ | Rest]) :- member(M, Rest), !.
member(M, [M | _]).

append(M, [], [M]).
append(M, [H | Rest], [H | Appended]) :- append(M, Rest, Appended).

prepend(M, List, [M | List]).

memberAt(I, [_ | List], M) :- I > 0, Inew is I-1, memberAt(Inew, List, M), !.
memberAt(0, [M | _], M).

concat(L1, [H | Rest], L3) :- append(H, L1, L4), concat(L4, Rest, L3), !.
concat(L1, [], L1).

delMember(M, [H | Rest], [H | Deleted]) :- delMember(M, Rest, Deleted), !.
delMember(M, [M | Rest], Rest).
delMember(_, [], []).

reverse([], []).
reverse([H | Rest], Rev) :- reverse(Rest, Rev2), concat(Rev2, [H], Rev).

revert(List, Rev) :- revAccum(List, [], Rev).

revAccum([H | Rest], Accum, Rev) :- revAccum(Rest, [H | Accum], Rev), !.
revAccum([], Accum, Accum).

