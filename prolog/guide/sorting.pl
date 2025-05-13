/* Insertion sort */

insertionSort(List, Sorted) :- sortAccum(List, Sorted, []).

sortAccum([], Accum, Accum) :- !.
sortAccum([H | Rest], Sorted, Accum) :- insert(H, Accum, Accum1), sortAccum(Rest, Sorted, Accum1), !.

insert(M, [], [M]) :- !.
insert(M, [N | Rest], [M, N | Rest]) :- M =< N, !.
insert(M, [N | Rest], [N | Later]) :- insert(M, Rest, Later), !.


/* Selection sort */

selectionSort([], []) :- !.
selectionSort(List, [M | Sorted]) :- min(List, M), delete(M, List, Deleted), selectionSort(Deleted, Sorted), !.

% min([H | Rest], M) :- H < M, min(Rest, H), !.
% min([_ | Rest], M) :- min(Rest, H), !.
min([M], M) :- !.
min([H | Rest], M) :- min(Rest, M1), M1 < H, M is M1, !.
min([H | _], H) :- !.

delete(M, [M | Rest], Rest) :- !.
delete(M, [N | Rest], [N | Deleted]) :- M \= N, delete(M, Rest, Deleted), !.


/* Merge sort */

mergeSort([], []) :- !.
mergeSort([M], [M]) :- !.
% TODO

