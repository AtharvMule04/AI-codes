/* ================================
   Bird Classification in PROLOG
   ================================ */

%% ---------- BASIC PROPERTIES (FACTS) ----------

% has_feathers(Animal).
has_feathers(sparrow).
has_feathers(eagle).
has_feathers(duck).
has_feathers(penguin).
has_feathers(ostrich).

% lays_eggs(Animal).
lays_eggs(sparrow).
lays_eggs(eagle).
lays_eggs(duck).
lays_eggs(penguin).
lays_eggs(ostrich).

% swims(Animal).
swims(duck).
swims(penguin).

% flies_well(Animal).
flies_well(sparrow).
flies_well(eagle).

% long_legs(Animal).
long_legs(ostrich).

% long_neck(Animal).
long_neck(ostrich).

% black_and_white(Animal).
black_and_white(penguin).


%% ---------- GENERAL CLASSIFICATION RULES ----------

% bird(X) :- X is a bird if it has feathers and lays eggs.
bird(X) :-
    has_feathers(X),
    lays_eggs(X).

% By default, a bird can fly if it is not abnormal.
can_fly(X) :-
    bird(X),
    \+ abnormal_bird(X).   % \+ means "not provable"

% Conditions when a bird is abnormal (cannot fly):
abnormal_bird(X) :- penguin(X).
abnormal_bird(X) :- ostrich(X).

% Specific bird types (categories)

% penguin(X): X is a penguin if it is a bird, black & white and swims, and cannot fly.
penguin(X) :-
    bird(X),
    black_and_white(X),
    swims(X),
    \+ can_fly(X).

% water_bird(X): X is a water bird if it is a bird and swims.
water_bird(X) :-
    bird(X),
    swims(X).

% flightless_bird(X): bird that cannot fly.
flightless_bird(X) :-
    bird(X),
    \+ can_fly(X).

% ostrich(X): long legs + long neck + bird + cannot fly.
ostrich(X) :-
    bird(X),
    long_legs(X),
    long_neck(X),
    \+ can_fly(X).

% raptor(X): bird of prey (example: eagle)
raptor(X) :-
    bird(X),
    flies_well(X).


%% ---------- NAMED INDIVIDUALS (TYPES) ----------

penguin(penguin).   % 'penguin' is of type penguin
ostrich(ostrich).   % 'ostrich' is of type ostrich


/* ================================
   SAMPLE QUERIES TO TRY
   ================================

?- bird(sparrow).
?- bird(penguin).

?- can_fly(sparrow).
?- can_fly(penguin).
?- can_fly(ostrich).

?- water_bird(duck).
?- flightless_bird(X).
?- penguin(X).
?- ostrich(X).
?- raptor(X).

*/
