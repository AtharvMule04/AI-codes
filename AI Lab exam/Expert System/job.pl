/* -------------------------------
   Simple Skillset - Job Matching
   Expert System in PROLOG
   ------------------------------- */

% skill facts
has_skill(alice, programming).
has_skill(alice, web_design).

has_skill(bob, accounting).
has_skill(bob, spreadsheets).

has_skill(charlie, communication).
has_skill(charlie, sales).

% job requirements
job_requires(software_developer, programming).
job_requires(web_designer,      web_design).
job_requires(accountant,        accounting).
job_requires(sales_executive,   sales).

% rule: a person is suitable for a job
% if they have the required skill
suitable_for(Person, Job) :-
    job_requires(Job, Skill),
    has_skill(Person, Skill).
