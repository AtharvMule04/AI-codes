/* -------------------------
   Simple Family Tree Expert
   ------------------------- */

% basic facts
male(john).
male(rahul).
male(amit).

female(mary).
female(neha).
female(sita).

% parent(Parent, Child)
parent(john, rahul).
parent(mary, rahul).

parent(john, neha).
parent(mary, neha).

parent(rahul, amit).
parent(sita, amit).

/* ------- rules (expert logic) ------- */

% father(F, C) : F is father of C
father(F, C) :-
    male(F),
    parent(F, C).

% mother(M, C) : M is mother of C
mother(M, C) :-
    female(M),
    parent(M, C).

% sibling(X, Y) : X and Y have at least one common parent and are different
sibling(X, Y) :-
    parent(P, X),
    parent(P, Y),
    X \= Y.

% brother(B, X)
brother(B, X) :-
    male(B),
    sibling(B, X).

% sister(S, X)
sister(S, X) :-
    female(S),
    sibling(S, X).

% grandparent(GP, GC)
grandparent(GP, GC) :-
    parent(GP, P),
    parent(P, GC).
