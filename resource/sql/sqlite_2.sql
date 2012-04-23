------------------------------------------------------------------------------------------
-- sqlite_1.sql is part of yoDownet
-- Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
-- subject to terms and condition provided in COPYING
------------------------------------------------------------------------------------------
BEGIN TRANSACTION;
ALTER TABLE urls RENAME TO tmp_urls;
CREATE TABLE IF NOT EXISTS "urls" ("id" INTEGER PRIMARY KEY  AUTOINCREMENT,"url" TEXT,"save_path" TEXT,"filename" VARCHAR,"status" INTEGER,"progress" INTEGER,"remaining_time" VARCHAR(75) DEFAULT "n/a","speed" VARCHAR(75),"created_at" TIMESTAMP NOT NULL  DEFAULT CURRENT_TIMESTAMP,"downloaded_at" TIMESTAMP);
INSERT INTO urls(id, url, save_path, filename, progress, remaining_time, speed, created_at) SELECT id, url, save_path, filename, progress, remaining_time, speed, created_at FROM tmp_urls;
DROP TABLE tmp_urls;
COMMIT;
