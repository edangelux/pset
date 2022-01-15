SELECT * FROM "interviews" WHERE transcript LIKE "%bakery%";
--La consulta nos dice que el robo fue a las 10:15am, hay tres testigos que mecionan a la panaderia
SELECT * FROM "interviews" WHERE transcript LIKE "%bakery%";
--tenemos 5 resultados investigaremos a raymond es un testimonio mas solido
--Con esta persona tenemos dos datos importantes, hizo una llamada de menos de un min y salio en el primer vuelo del 29
SELECT * FROM "phone_calls" WHERE duration < 60 AND day = 28 AND month = 7;
--También hay muchos resultados, no sé como descubir quien lo hizo
--Si nos vamos a la tabla airports podemos ver que fiftyville tiene id = 8, nos será util para buscar los vuelos
SELECT * FROM "flights" WHERE day = 29 AND month = 7 AND origin_airport_id = 8 ORDER BY hour;
--Con esta consulta sabemos a donde escapó el ladrón, tomó el primer vuelo así que el id del destino es 4 y el id de vuelo es 36;
SELECT * FROM "airports" WHERE id = 4;
--El ladrón escapó a "New York City" segun la consulta
SELECT * FROM "passengers" WHERE flight_id = 36;
--Aún siguen existiendo 8 posibles sospechosos que tomaron ese vuelo

--investigamos sobre que un caso el ladron salio revisamos el parqueo
--Teniendo el dueño de cada placa puedo buscar si ese mismo dueño fue a sacar dinero al atm el día 28
SELECT name FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND transaction_type = "withdraw")

--se repite 2 veces bruce
--Teniendo el dueño de cada placa puedo buscar si ese mismo dueño fue a sacar dinero al atm el día 28
SELECT name FROM people
JOIN bank_accounts
ON bank_accounts.person_id = people.id
WHERE account_number in (SELECT account_number FROM atm_transactions
WHERE month = 7 AND day = 28 AND transaction_type = "withdraw")

--se repite 3 veces bruce
