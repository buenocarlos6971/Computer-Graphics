-- This sql is the base create of the avoke databse. Ot addsa ll the tables and forign keys to the tables
--Written by Lauren Paredes


CREATE TABLE "session" (
  "sid" varchar NOT NULL COLLATE "default",
	"sess" json NOT NULL,
	"expire" timestamp(6) NOT NULL
)
WITH (OIDS=FALSE);

ALTER TABLE "session" ADD CONSTRAINT "session_pkey" PRIMARY KEY ("sid") NOT DEFERRABLE INITIALLY IMMEDIATE;

CREATE INDEX "IDX_session_expire" ON "session" ("expire");

CREATE TABLE Users (
    UserID SERIAL PRIMARY KEY,
    first_name varchar  NOT NULL ,
    last_name varchar  NOT NULL ,
    passW text  NOT NULL ,
    Email text  NOT NULL,
    Search_ID INT,
    Bio text,
    img_src VARCHAR(200)
);


CREATE TABLE User_Search_History(
    Search_ID SERIAL PRIMARY KEY,
    SongNameByUser text NOT NULL,
    UserID int,
    SearchTime DATE NOT NULL
);


CREATE TABLE Songs(
    SongID SERIAL PRIMARY KEY,
    Song_Name text NOT NULL,
    song_author text  NOT NULL, 
    genre CHAR(4) NOT NULL,
    Search_ID int
  
);


ALTER TABLE Songs
ADD FOREIGN KEY (Search_ID) REFERENCES User_Search_History(Search_ID);


ALTER TABLE User_Search_History
ADD FOREIGN KEY (USERID) REFERENCES Users(UserID);

ALTER TABLE users ADD FOREIGN KEY (Search_ID)REFERENCES User_Search_History(Search_ID);
