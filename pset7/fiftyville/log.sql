-- Keep a log of any SQL queries you execute as you solve the mystery.
-- All you know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

-- See all the possible suspects
SELECT * FROM people

-- See crime reports from day of theft
SELECT * FROM crime_scene_reports WHERE day = 28 AND month = 7

-- | 2020 | 7 | 28 |
-- Chamberlin Street | Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

-- See the mentioned interviews on the crime report
SELECT * FROM interviews WHERE day = 28 AND month = 7

-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Thief got in a car by the courthouse from 10:15 to 10:25
-- Thief withdrew money at the ATM on Fifer Street early in the morning
-- Thief called someone as he left for less than a minute and told them to buy plane tickets on earliest flight out of Fiftyville 29/07

-- Checking what the first flight off headed to
SELECT * FROM flights WHERE day = 29 AND month = 7 ORDER BY hour ASC
SELECT * FROM airports

-- Earliest flight is LONDON, airport ID 4 flight 36

-- Checking courthouse security logs for exits and the persons name
SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = 28 AND month = 7 AND hour = 10 AND minute >= 15 AND minute < 25

/* Patrick
Ernest
Amber
Danielle
Roger
Elizabeth
Russell
Evelyn
*/

-- Checking transaction from the mentioned atm and the persons name
SELECT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = 28 AND month = 7 AND transaction_type = "withdraw" AND atm_location = "Fifer Street"

/*Ernest
Russell
Roy
Bobby
Elizabeth
Danielle
Madison
Victoria
*/

-- Checking calls made after the theft that lasted less than 60s and the persons name
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = 28 AND month = 7 AND duration < 60

/*Roger
Evelyn
Ernest
Evelyn
Madison
Russell
Kimberly
Bobby
Victoria
*/

-- Russell and Ernest are the only ones that show up in all 3 listings

-- Checking who will be flying to London on the 29th
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = 36

-- Ernest is the guilty individual
-- Checking who he called
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE month = 7 AND day = 28 AND caller = (SELECT phone_number FROM people WHERE name = "Ernest" )  AND duration < 60 )

-- Berthold is the accomplice

