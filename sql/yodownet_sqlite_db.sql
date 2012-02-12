
-- yodownet_sqlite_db.sql is part of yoDownet

-- Copyright 2011, 2012 Alireza Savand <alireza.savand@gmail.com>

-- yoDownet is free software; you can redistribute it and/or modify
-- it under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 3 of the License, or
-- (at your option) any later version.

-- yoDownet is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU General Public License for more details.

-- You should have received a copy of the GNU General Public License
-- along with this program; if not, If not, see <http://www.gnu.org/licenses/>.

CREATE TABLE IF NOT EXISTS "uris" (
"id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL ,
"uri" TEXT,
"save_path" TEXT,
"status" VARCHAR(25),
"progress" INTEGER,
"remaining_time" VARCHAR(75) DEFAULT "n/a",
"flag" VARCHAR(15) DEFAULT "init",
"created_at" TIMESTAMP NOT NULL  DEFAULT CURRENT_TIMESTAMP,
"updated_at" TIMESTAMP
);
