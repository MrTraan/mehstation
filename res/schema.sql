BEGIN TRANSACTION;
CREATE TABLE "system" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL,
	`command`	TEXT NOT NULL
);
CREATE TABLE `executable` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`name`	TEXT NOT NULL,
	`filepath`	TEXT NOT NULL
);
COMMIT;