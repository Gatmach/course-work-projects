-- Group A6 - ICS 2206: Database Systems

-- Members:
-- SCT211-0848/2018 Jany Muong
-- SCT211-0504/2021 Gatmach Yuol Nyuon
-- SCT211-0081/2022 IRKE KONZOLO
-- SCT211-0085/2022	Douglas Kimani Kitavi
-- SCT211-0011/2022	Mike Kevin Mugambi
-- SCT211-0079/2022	Joram Kireki


-- run this SQL script(as root user with no MySQL root password)
-- in command-line like this - Ubuntu/Linux:
--          cat ics2206_grp_a6_db_system.sql | sudo mysql


-- create the database named group_a6_db_systems;
CREATE DATABASE group_a6_db_systems;
USE group_a6_db_systems;


-- create the student table for the STUDENT entity;
CREATE TABLE student (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    year_of_study INT
);

-- create the course table for the COURSE entity;
CREATE TABLE course (
    id INT AUTO_INCREMENT PRIMARY KEY,
    designation VARCHAR(100),
    title VARCHAR(100),
    description TEXT,
    year INT,
    classroom VARCHAR(100)
);

-- create the instructor table for INSTRUCTOR entity;
CREATE TABLE instructor (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    dept_affiliation VARCHAR(100),
    office_room VARCHAR(100),
    phone_ext VARCHAR(20),
    email VARCHAR(100)
);

-- create the ta (teaching assistant) table for TA entity;
CREATE TABLE ta (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    dept_affiliation VARCHAR(100),
    office_room VARCHAR(100),
    phone_ext VARCHAR(20),
    email VARCHAR(100)
);

-- create the la (lab assistant) table for the LA entity;
CREATE TABLE la (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100),
    dept_affiliation VARCHAR(100),
    office_room VARCHAR(100),
    phone_ext VARCHAR(20),
    email VARCHAR(100)
);

-- create the lab_section table for the LAB_SECTION entity;
CREATE TABLE lab_section (
    id INT AUTO_INCREMENT PRIMARY KEY,
    designation INT, -- references the course table
    la_id INT, -- references the la table
    FOREIGN KEY (designation) REFERENCES course(id),
    FOREIGN KEY (la_id) REFERENCES la(id)
);

-- create the tutorial_section table for the TUTORIAL_SECTION entity;
CREATE TABLE tutorial_section (
    id INT AUTO_INCREMENT PRIMARY KEY,
    designation INT, -- References the course table
    ta_id INT, -- References the ta table
    FOREIGN KEY (designation) REFERENCES course(id),
    FOREIGN KEY (ta_id) REFERENCES ta(id)
);

-- create the prerequisite table (associative entity) - many-to-many
CREATE TABLE prerequisite (
    course_id INT, -- References the course table
    prerequisite_id INT, -- references the course table(for previous course)
    PRIMARY KEY (course_id, prerequisite_id),
    FOREIGN KEY (course_id) REFERENCES course(id),
    FOREIGN KEY (prerequisite_id) REFERENCES course(id)
);

-- create the anti_requisite table (associative entity)
CREATE TABLE anti_requisite (
    course_id INT, -- references the course table
    antirequisite_id INT, -- references the course table(for parallel course)
    PRIMARY KEY (course_id, antirequisite_id),
    FOREIGN KEY (course_id) REFERENCES course(id),
    FOREIGN KEY (antirequisite_id) REFERENCES course(id)
);

-- create the course_enrollment table (associative entity for student-course relationship)
CREATE TABLE course_enrollment (
    student_id INT, -- references the student table
    course_id INT, -- references the course table
    PRIMARY KEY (student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES student(id),
    FOREIGN KEY (course_id) REFERENCES course(id)
);
