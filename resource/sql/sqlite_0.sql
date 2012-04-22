------------------------------------------------------------------------------------------
-- sqlite_0.sql is part of yoDownet
-- Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>
-- subject to terms and condition provided in COPYING
------------------------------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS "urls" (
"id" INTEGER PRIMARY KEY  AUTOINCREMENT,
"url" TEXT,
"save_path" TEXT,
"status" INTEGER,
"progress" INTEGER,
"remaining_time" VARCHAR(75) DEFAULT "n/a",
"speed" VARCHAR(75),
"created_at" TIMESTAMP NOT NULL  DEFAULT CURRENT_TIMESTAMP,
"updated_at" TIMESTAMP
);
