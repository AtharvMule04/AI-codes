/* ---------- FACTS ---------- */

% gender
male(john).
male(peter).
male(rahul).
male(amit).

female(mary).
female(anu).
female(sita).
female(neha).

% parent(Parent, Child)
parent(john, rahul).
parent(mary, rahul).

parent(john, neha).
parent(mary, neha).

parent(peter, john).
parent(anu, john).

parent(peter, sita).
parent(anu, sita).

parent(sita, amit).

/* ---------- RULES ---------- */

% father(F, C) : F is father of C
father(F, C) :-
    male(F),
    parent(F, C).

% mother(M, C) : M is mother of C
mother(M, C) :-
    female(M),
    parent(M, C).

% sibling(X, Y) : X and Y are siblings (share a parent and are different)
sibling(X, Y) :-
    parent(P, X),
    parent(P, Y),
    X \= Y.

% brother(B, X) : B is brother of X
brother(B, X) :-
    male(B),
    sibling(B, X).

% sister(S, X) : S is sister of X
sister(S, X) :-
    female(S),
    sibling(S, X).

% grandparent(GP, GC) : GP is grandparent of GC
grandparent(GP, GC) :-
    parent(GP, P),
    parent(P, GC).

% grandfather(GF, GC) : GF is grandfather of GC
grandfather(GF, GC) :-
    male(GF),
    grandparent(GF, GC).

% grandmother(GM, GC) : GM is grandmother of GC
grandmother(GM, GC) :-
    female(GM),
    grandparent(GM, GC).

% ancestor(A, D) : A is ancestor of D (recursive definition)
ancestor(A, D) :-
    parent(A, D).
ancestor(A, D) :-
    parent(A, X),
    ancestor(A, X).
