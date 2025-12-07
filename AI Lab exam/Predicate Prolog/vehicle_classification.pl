/* ================================
   Vehicle Classification in PROLOG
   ================================ */

%% ---------- BASIC FACTS ----------

% wheels(Vehicle, NumberOfWheels)
wheels(car1,      4).
wheels(car2,      4).
wheels(bike1,     2).
wheels(scooter1,  2).
wheels(bicycle1,  2).
wheels(truck1,    6).
wheels(bus1,      6).

% motorized(Vehicle)
motorized(car1).
motorized(car2).
motorized(bike1).
motorized(scooter1).
motorized(truck1).
motorized(bus1).
% bicycle1 is not motorized

% carries_people(Vehicle)
carries_people(car1).
carries_people(car2).
carries_people(bike1).
carries_people(scooter1).
carries_people(bus1).
carries_people(bicycle1).

% carries_goods(Vehicle)
carries_goods(truck1).

% public_transport(Vehicle)
public_transport(bus1).

% fuel_type(Vehicle, Type)  % Type = petrol | diesel | electric | human
fuel_type(car1,     petrol).
fuel_type(car2,     electric).
fuel_type(bike1,    petrol).
fuel_type(scooter1, petrol).
fuel_type(truck1,   diesel).
fuel_type(bus1,     diesel).
fuel_type(bicycle1, human).


%% ---------- GENERAL VEHICLE PREDICATE ----------

% vehicle(V) : V is a vehicle if it has wheels
vehicle(V) :-
    wheels(V, _).


%% ---------- CLASSIFICATION RULES ----------

% two_wheeler(V)
two_wheeler(V) :-
    vehicle(V),
    wheels(V, 2).

% four_wheeler(V)
four_wheeler(V) :-
    vehicle(V),
    wheels(V, 4).

% car(V)
car(V) :-
    vehicle(V),
    four_wheeler(V),
    motorized(V),
    carries_people(V).

% bike(V)
bike(V) :-
    vehicle(V),
    two_wheeler(V),
    motorized(V).

% bicycle(V)
bicycle(V) :-
    vehicle(V),
    two_wheeler(V),
    \+ motorized(V).

% truck(V)
truck(V) :-
    vehicle(V),
    carries_goods(V),
    motorized(V).

% bus(V)
bus(V) :-
    vehicle(V),
    public_transport(V),
    motorized(V).

% heavy_vehicle(V)
heavy_vehicle(V) :-
    truck(V).
heavy_vehicle(V) :-
    bus(V).

% light_vehicle(V)
light_vehicle(V) :-
    car(V).
light_vehicle(V) :-
    bike(V).
light_vehicle(V) :-
    bicycle(V).

% eco_friendly(V)
eco_friendly(V) :-
    fuel_type(V, electric).
eco_friendly(V) :-
    fuel_type(V, human).


/* ================================
   SAMPLE QUERIES (for you to try)
   ================================

?- vehicle(X).
?- two_wheeler(X).
?- car(X).
?- truck(X).
?- heavy_vehicle(X).
?- light_vehicle(X).
?- eco_friendly(X).
?- fuel_type(car2, F).

*/
