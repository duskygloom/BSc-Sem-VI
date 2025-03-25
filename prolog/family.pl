/* parent(parent, child)
 */
parent(pam, bob).
parent(tom, bob).
parent(tom, liz).
parent(bob, ann).
parent(bob, pat).
parent(pat, jin).

/* gender(person)
 */
male(tom).
male(bob).
male(jin).
female(pam).
female(liz).
female(ann).
female(pat).

/* rules
 */
father(X, Y)		:- parent(X, Y), male(X).
mother(X, Y)		:- parent(X, Y), female(X).

child(X, Y)			:- parent(Y, X).
son(X, Y)			:- child(X, Y), male(X).
daughter(X, Y)		:- child(X, Y), female(X).

grandparent(X, Y)	:- parent(Z, Y), parent(X, Z).
grandfather(X, Y)	:- grandparent(X, Y), male(X).
grandmother(X, Y)	:- grandparent(X, Y), female(X).

sibling(X, Y)		:- parent(Z, X), parent(Z, Y), X \== Y.
brother(X, Y)		:- sibling(X, Y), male(X).
sister(X, Y)		:- sibling(X, Y), female(X).

uncle(X, Y)			:- parent(Z, Y), brother(X, Z).
aunt(X, Y)			:- parent(Z, Y), sister(X, Z).

/* These are kinda like and operation.
 * Can we do or and not operations?
 */
cousin(X, Y)		:- parent(Z, Y), sibling(A, Z), child(X, A).

