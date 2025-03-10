-- Step 1: Create the students table
CREATE TABLE students (
    student_id NUMBER PRIMARY KEY,
    student_name VARCHAR2(100),
    mark NUMBER
);

-- Step 2: Insert sample data
INSERT INTO students (student_id, student_name, mark) VALUES (1, 'John Doe', 35);
INSERT INTO students (student_id, student_name, mark) VALUES (2, 'Jane Smith', 45);
INSERT INTO students (student_id, student_name, mark) VALUES (3, 'Alice Johnson', 50);
INSERT INTO students (student_id, student_name, mark) VALUES (4, 'Bob Brown', 30);
INSERT INTO students (student_id, student_name, mark) VALUES (5, 'Charlie Davis', 40);

-- Step 3: PL/SQL block to calculate average and print results
DECLARE
    total_marks NUMBER := 0;
    student_count NUMBER := 0;
    average_mark NUMBER;
    current_date DATE := SYSDATE;
    day_of_week VARCHAR2(20);
BEGIN
    -- Calculate total marks and count of students
    SELECT SUM(mark), COUNT(*)
    INTO total_marks, student_count
    FROM students;

    -- Calculate average mark
    IF student_count > 0 THEN
        average_mark := total_marks / student_count;
    ELSE
        average_mark := 0;
    END IF;

    -- Print the average mark
    DBMS_OUTPUT.PUT_LINE('Average Mark of the Class: ' || average_mark);

    -- Check if the average is less than 40
    IF average_mark < 40 THEN
        DBMS_OUTPUT.PUT_LINE('Need improvement');
    END IF;

    -- Print today's date and day of the week
    DBMS_OUTPUT.PUT_LINE('Today''s Date: ' || TO_CHAR(current_date, 'DD-MON-YYYY'));
    DBMS_OUTPUT.PUT_LINE('Day of the Week: ' || TO_CHAR(current_date, 'DAY'));
END;
/

-------------------------------------------------------------------------------



-- Step 1: Create the customer table
CREATE TABLE customer (
    customer_id NUMBER PRIMARY KEY,
    customer_name VARCHAR2(100),
    account_balance NUMBER
);

-- Step 2: Insert sample data
INSERT INTO customer (customer_id, customer_name, account_balance) VALUES (1, 'John Doe', 60000);
INSERT INTO customer (customer_id, customer_name, account_balance) VALUES (2, 'Jane Smith', 45000);
INSERT INTO customer (customer_id, customer_name, account_balance) VALUES (3, 'Alice Johnson', 8000);
INSERT INTO customer (customer_id, customer_name, account_balance) VALUES (4, 'Bob Brown', 12000);
INSERT INTO customer (customer_id, customer_name, account_balance) VALUES (5, 'Charlie Davis', 3000);

-- Step 3: Create the function dc
CREATE OR REPLACE FUNCTION dc(account_balance IN NUMBER) 
RETURN VARCHAR2 
IS
    customer_category VARCHAR2(20);
BEGIN
    IF account_balance > 50000 THEN
        customer_category := 'Platinum';
    ELSIF account_balance > 10000 THEN
        customer_category := 'Gold';
    ELSE
        customer_category := 'Silver';
    END IF;

    RETURN customer_category;
END;
/

-- Step 4: Query to retrieve customer details with category
SELECT 
    customer_id,
    customer_name,
    account_balance,
    dc(account_balance) AS customer_category
FROM 
    customer;



------------------------------------------------------------------




CREATE TABLE students (
    roll_number NUMBER PRIMARY KEY,
    student_name VARCHAR2(100),
    s1 NUMBER,
    s2 NUMBER
);

INSERT INTO students (roll_number, student_name, s1, s2) VALUES (1, 'John Doe', 7, 8);
INSERT INTO students (roll_number, student_name, s1, s2) VALUES (2, 'Jane Smith', 6, 7);
INSERT INTO students (roll_number, student_name, s1, s2) VALUES (3, 'Alice Johnson', 9, 5);
INSERT INTO students (roll_number, student_name, s1, s2) VALUES (4, 'Bob Brown', 8, 9);
INSERT INTO students (roll_number, student_name, s1, s2) VALUES (5, 'Charlie Davis', 4, 5);


DECLARE
    -- Step 1: Declare the cursor
    CURSOR honours_cursor IS
        SELECT roll_number, student_name, s1, s2
        FROM students
        WHERE (s1 + s2) > 12
        ORDER BY roll_number;

    -- Variables to store cursor data
    v_roll_number students.roll_number%TYPE;
    v_student_name students.student_name%TYPE;
    v_s1 students.s1%TYPE;
    v_s2 students.s2%TYPE;
    v_highest_grade NUMBER;
BEGIN
    -- Step 2: Open the cursor
    OPEN honours_cursor;

    -- Step 3: Fetch data from the cursor
    LOOP
        FETCH honours_cursor INTO v_roll_number, v_student_name, v_s1, v_s2;
        EXIT WHEN honours_cursor%NOTFOUND; -- Exit the loop when no more rows are found

        -- Calculate the highest grade
        v_highest_grade := GREATEST(v_s1, v_s2);

        -- Display the details of honours students and their highest grade
        DBMS_OUTPUT.PUT_LINE('Roll Number: ' || v_roll_number || 
                             ', Name: ' || v_student_name || 
                             ', Highest Grade: ' || v_highest_grade);
    END LOOP;

    -- Step 4: Close the cursor
    CLOSE honours_cursor;
END;
/



----------------------------------------------------------------



CREATE TABLE unitcharge (
    min_unit NUMBER,
    max_unit NUMBER,
    charge_per_unit NUMBER
);

INSERT INTO unitcharge (min_unit, max_unit, charge_per_unit) VALUES (1, 100, 5);
INSERT INTO unitcharge (min_unit, max_unit, charge_per_unit) VALUES (101, 300, 7.5);
INSERT INTO unitcharge (min_unit, max_unit, charge_per_unit) VALUES (301, 500, 15);
INSERT INTO unitcharge (min_unit, max_unit, charge_per_unit) VALUES (501, NULL, 22.5);

DECLARE
    -- Variables for input
    v_consumer_number NUMBER := &consumer_number; -- Accept consumer number
    v_present_reading NUMBER := &present_reading; -- Accept present reading
    v_past_reading NUMBER := &past_reading; -- Accept past reading

    -- Variables for calculation
    v_units_consumed NUMBER;
    v_charge_per_unit NUMBER;
    v_total_bill NUMBER := 0;

    -- Cursor to fetch unit charges
    CURSOR unit_charge_cursor IS
        SELECT min_unit, max_unit, charge_per_unit
        FROM unitcharge
        ORDER BY min_unit;
BEGIN
    -- Step 1: Calculate units consumed
    v_units_consumed := v_present_reading - v_past_reading;

    -- Step 2: Fetch unit charges using a cursor
    FOR charge_rec IN unit_charge_cursor LOOP
        -- Check if units consumed fall within the current range
        IF (charge_rec.max_unit IS NULL AND v_units_consumed >= charge_rec.min_unit) OR
           (v_units_consumed BETWEEN charge_rec.min_unit AND charge_rec.max_unit) THEN
            v_charge_per_unit := charge_rec.charge_per_unit;
            EXIT; -- Exit the loop once the correct range is found
        END IF;
    END LOOP;

    -- Step 3: Calculate total bill
    v_total_bill := v_units_consumed * v_charge_per_unit;

    -- Step 4: Display the bill details
    DBMS_OUTPUT.PUT_LINE('Consumer Number: ' || v_consumer_number);
    DBMS_OUTPUT.PUT_LINE('Units Consumed: ' || v_units_consumed);
    DBMS_OUTPUT.PUT_LINE('Charge Per Unit: ' || v_charge_per_unit);
    DBMS_OUTPUT.PUT_LINE('Total Bill: ' || v_total_bill);
END;
/



--------------------------------------------------------------------


CREATE TABLE accounts (
    account_number NUMBER PRIMARY KEY,
    balance NUMBER
);

INSERT INTO accounts (account_number, balance) VALUES (101, 1000);
INSERT INTO accounts (account_number, balance) VALUES (102, 600);
INSERT INTO accounts (account_number, balance) VALUES (103, 400);

DECLARE
    -- Variables
    v_account_number NUMBER := &account_number; -- Accept account number
    v_balance NUMBER;
    v_choice NUMBER;
    v_amount NUMBER := 200; -- Amount to debit
    v_min_balance NUMBER := 500; -- Minimum balance required
BEGIN
    -- Fetch the current balance for the given account number
    SELECT balance INTO v_balance
    FROM accounts
    WHERE account_number = v_account_number;

    -- Display menu
    DBMS_OUTPUT.PUT_LINE('1. Debit');
    DBMS_OUTPUT.PUT_LINE('2. Credit');
    DBMS_OUTPUT.PUT_LINE('3. Show Balance');
    DBMS_OUTPUT.PUT_LINE('Enter your choice (1/2/3): ');
    v_choice := &choice; -- Accept user choice

    -- Perform operation based on user choice
    CASE v_choice
        WHEN 1 THEN
            -- Debit operation
            IF v_balance - v_amount >= v_min_balance THEN
                UPDATE accounts
                SET balance = balance - v_amount
                WHERE account_number = v_account_number;
                DBMS_OUTPUT.PUT_LINE('Amount ' || v_amount || ' debited successfully.');
            ELSE
                DBMS_OUTPUT.PUT_LINE('Insufficient balance. Minimum balance of ' || v_min_balance || ' must be maintained.');
            END IF;

        WHEN 2 THEN
            -- Credit operation
            DBMS_OUTPUT.PUT_LINE('Enter the amount to credit: ');
            UPDATE accounts
            SET balance = balance + v_amount
            WHERE account_number = v_account_number;
            DBMS_OUTPUT.PUT_LINE('Amount ' || v_amount || ' credited successfully.');

        WHEN 3 THEN
            -- Show balance
            DBMS_OUTPUT.PUT_LINE('Current Balance: ' || v_balance);

        ELSE
            DBMS_OUTPUT.PUT_LINE('Invalid choice.');
    END CASE;

    -- Commit the transaction
    COMMIT;
END;
/