-- Group A6 - ICS 2206: Database Systems

-- Members:
-- SCT211-0848/2018	Jany Muong
-- SCT211-0504/2021	Gatmach Yuol Nyuon
-- SCT211-0081/2022	IRKE KONZOLO
-- SCT211-0085/2022	Douglas Kimani Kitavi
-- SCT211-0011/2022	Mike Kevin Mugambi
-- SCT211-0079/2022	Joram Kireki


-- this script populates all created relations;
-- run this SQL script(as root user with no MySQL root password)
-- in command-line like this - Ubuntu/Linux:
--          cat db_populate_db.sql.sql | sudo mysql


USE group_a6_db_systems;

-- Insert data into the student table
INSERT INTO student (name, year_of_study) VALUES
('Jany Muong', 2018),
('Gatmach Yuol Nyuon', 2021),
('IRKE KONZOLO', 2022),
('Douglas Kimani Kitavi', 2022),
('Mike Kevin Mugambi', 2022),
('Joram Kireki', 2022);

-- Insert data into the course table
INSERT INTO course (designation, title, description, year, classroom) VALUES
('CSC101', 'Introduction to Computer Science', 'An introductory course covering basic concepts of computer science.', 1, 'Room 101'),
('CSC201', 'Data Structures and Algorithms', 'Advanced course focusing on data structures and algorithms.', 2, 'Room 202'),
('CSC301', 'Database Management Systems', 'In-depth study of database systems and management techniques.', 3, 'Room 303');

-- Insert data into the instructor table
INSERT INTO instructor (name, dept_affiliation, office_room, phone_ext, email) VALUES
('John Doe', 'Computer Science', 'Office 101', '123-456-7890', 'johndoe@example.com'),
('Jane Smith', 'Computer Engineering', 'Office 202', '234-567-8901', 'janesmith@example.com');

-- Insert data into the ta (teaching assistant) table
INSERT INTO ta (name, dept_affiliation, office_room, phone_ext, email) VALUES
('Emily Johnson', 'Computer Science', 'Office 303', '345-678-9012', 'emilyjohnson@example.com'),
('David Brown', 'Computer Engineering', 'Office 404', '456-789-0123', 'davidbrown@example.com');

-- Insert data into the la (lab assistant) table
INSERT INTO la (name, dept_affiliation, office_room, phone_ext, email) VALUES
('Jessica Williams', 'Computer Science', 'Office 505', '567-890-1234', 'jessicawilliams@example.com'),
('Michael Davis', 'Computer Engineering', 'Office 606', '678-901-2345', 'michaeldavis@example.com');

-- Insert data into the lab_section table
INSERT INTO lab_section (designation, la_id) VALUES
(1, 1),
(2, 2),
(3, 1);

-- Insert data into the tutorial_section table
INSERT INTO tutorial_section (designation, ta_id) VALUES
(1, 1),
(2, 2),
(3, 1);

-- Insert data into the prerequisite table
INSERT INTO prerequisite (course_id, prerequisite_id) VALUES
(2, 1),
(3, 2);

-- Insert data into the anti_requisite table
INSERT INTO anti_requisite (course_id, antirequisite_id) VALUES
(1, 3),
(2, 1);

-- Insert data into the course_enrollment table
INSERT INTO course_enrollment (student_id, course_id) VALUES
(1, 1),
(2, 1),
(3, 2),
(4, 2),
(5, 3),
(6, 3);

