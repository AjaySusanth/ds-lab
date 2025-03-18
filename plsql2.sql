CREATE TABLE students (
    roll_number NUMBER PRIMARY KEY,
    name VARCHAR2(100),
    grd_s1 NUMBER,
    grd_s2 NUMBER
);

INSERT INTO students (roll_number, name, grd_s1, grd_s2) VALUES (1, 'John Doe', 85, 90);

CREATE OR REPLACE TRIGGER students_trigger
AFTER INSERT OR UPDATE OR DELETE ON students
FOR EACH ROW
BEGIN
    -- Handle INSERT operation
    IF INSERTING THEN
        DBMS_OUTPUT.PUT_LINE('Inserting ' || :NEW.name);
    END IF;

    -- Handle UPDATE operation
    IF UPDATING THEN
        -- Check if the name is updated
        IF :OLD.name != :NEW.name THEN
            DBMS_OUTPUT.PUT_LINE('Updated name to ' || :NEW.name);
        END IF;

        -- Check if roll_number, grd_s1, or grd_s2 is updated
        IF :OLD.roll_number != :NEW.roll_number OR
           :OLD.grd_s1 != :NEW.grd_s1 OR
           :OLD.grd_s2 != :NEW.grd_s2 THEN
            DBMS_OUTPUT.PUT_LINE('Inserting ' || :NEW.name);
        END IF;
    END IF;

    -- Handle DELETE operation
    IF DELETING THEN
        DBMS_OUTPUT.PUT_LINE('Deleting ' || :OLD.name);
    END IF;
END;
/
UPDATE students SET name = 'Jane Doe' WHERE roll_number = 1;

-- Update the student's grades
UPDATE students SET grd_s1 = 88 WHERE roll_number = 1;

-- Delete the student
DELETE FROM students WHERE roll_number = 1;


----------------------------------------------------------



CREATE TABLE Student (
    Sid NUMBER PRIMARY KEY,
    name VARCHAR2(100),
    Subj1 NUMBER,
    Subj2 NUMBER,
    Subj3 NUMBER,
    Total NUMBER,
    Avg NUMBER
);

CREATE OR REPLACE TRIGGER calculate_total_avg_trigger
BEFORE INSERT ON Student
FOR EACH ROW
BEGIN
    -- Calculate Total
    :NEW.Total := :NEW.Subj1 + :NEW.Subj2 + :NEW.Subj3;

    -- Calculate Average
    :NEW.Avg := :NEW.Total / 3;
END;
/

-- Insert a new student record
INSERT INTO Student (Sid, name, Subj1, Subj2, Subj3)
VALUES (1, 'John Doe', 85, 90, 78);

-- Query the table to verify the results
SELECT * FROM Student;