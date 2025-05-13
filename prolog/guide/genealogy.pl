/*** FACTS ***/

man(adam).
man(peter).
man(paul).

woman(marry).
woman(eve).

parent(adam, peter). /* adam is the parent of peter */
parent(eve, peter).
parent(adam, paul).
parent(marry, paul).


/*** RULES ***/

father(F, C) :- parent(F, C), man(F).
mother(M, C) :- parent(M, C), woman(M).

isFather(F) :- father(F, _).
isMother(M) :- mother(M, _).

son(S, P) :- parent(P, S), man(S).
daughter(D, P) :- parent(P, D), woman(D).

sibling(A, B) :- parent(P, A), parent(P, B), A \= B.

human(H) :- man(H).
human(H) :- woman(H).

ancestor(A, X) :- parent(A, X).
ancestor(A, X) :- parent(A, P), ancestor(P, X).
descendant(D, X) :- ancestor(X, D).

