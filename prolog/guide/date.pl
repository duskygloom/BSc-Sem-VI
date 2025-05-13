/* Date data structure */

/* Date constructor */
createDate(D, M, Y, date(Y, M, D)).

/* Date getters */
getDay(date(_, _, D), D).
getMonth(date(_, M, _), M).
getYear(date(Y, _, _), Y).

/* Date setters */
setDay(D, date(Y, M, _), date(Y, M, D)).
setMonth(M, date(Y, _, D), date(Y, M, D)).
setYear(Y, date(_, M, D), date(Y, M, D)).

nextYear(date(Y, M, D), date(Next, M, D)) :- Next is Y+1.
prevYear(date(Y, M, D), date(Prev, M, D)) :- Prev is Y-1.

correctDate(date(_, M, _)) :- M <= 12, M >= 0.
correctDate(date(_, M, D)) :- M = 1, D <= 31.
correctDate(date(_, M, D)) :- M = 2, D <= 29.
correctDate(date(_, M, D)) :- M = 3, D <= 31.

tomorrow(date(Y, M, D), date(Y, M, D)).



