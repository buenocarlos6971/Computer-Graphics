-- Exported from QuickDBD: https://www.quickdatabasediagrams.com/
-- NOTE! If you have used non-SQL datatypes in your design, you will have to change these here.

-- Modify this code to update the DB schema diagram.
-- To reset the sample schema, replace everything with
-- two dots ('..' - without quotes).

CREATE TABLE `Users` (
    `ID` int  NOT NULL ,
    `first_name` varchar  NOT NULL ,
    `last_name` varchar  NOT NULL ,
    `password` string  NOT NULL ,
    `Email` string  NOT NULL ,
    PRIMARY KEY (
        `ID`
    )
);

CREATE TABLE `Posts` (
    `PostID` int  NOT NULL ,
    `ID` int  NOT NULL ,
    `post_title` string  NOT NULL ,
    `post_body` string  NOT NULL ,
    `post_brand` string  NOT NULL ,
    `post_date` datetime  NOT NULL, 
    `channelID` int NOT NULL,
    PRIMARY KEY (
        `PostID`
    )
);

-- Table documentation comment 1 (try the PDF/RTF export)
-- Table documentation comment 2


CREATE TABLE `Like`(
    `userLikeID` int NOT NULL,
    `PostID` INT NOT NULL,
    `ID` INT NOT NULL,
    `Liked` BOOLEAN,
    `Like_date` datetime NOT NULL,
    PRIMARY KEY (
        `userLikeID`
    )
);

CREATE TABLE `Channel`(
    `ChannelID` INT NOT NULL,
    `ID` int NOT NULL,
    `Channel_name` NVARCHAR(100) NOT NULL,
    PRIMARY KEY (
        `ChannelID`
    )
);

CREATE TABLE `Share`(
    `UserShareID` int NOT NULL,
    `PostID` int NOT NULL,
    `Caption` string NOT NULL,
    `Created` datetime NOT NULL,
    PRIMARY KEY (
        `UserShareID`
    )
);
CREATE TABLE `Comment`(
    `UserActivityID` int NOT NULL,
    `PostID` int NOT NULL,
    `commentID` int NOT NULL,
    `ID` int NOT NULL,
    `CreatedComment` datetime NOT NULL,
    PRIMARY KEY (
        `UserActivityID`
    )
);

CREATE TABLE `User_Search_History`(
    `Search_ID` int NOT NULL,
    `ID` int NOT NULL,
    `SongID` int NOT NULL,
    `SearchTime` datetime NOT NULL,
    PRIMARY KEY (
        `Search_ID`
    )

);

CREATE TABLE `Favorite`(
    `FavListID` int NOT NULL,
    `ID` int NOT NULL,
    `SongID` int NOT NULL,
    PRIMARY KEY (
        `FavListID`
    )
);
CREATE TABLE `Songs`(
    `SongID` INT NOT NULL,
    `Song_Name` string NOT NULL,
    `song_author` string  NOT NULL ,
    `song_mv` string  NOT NULL,
    PRIMARY KEY (
        `SongID`
    )
);

CREATE TABLE `Subscribe`(
    `SubscribeID` INT NOT NULL,
    `ChannelID` int NOT NULL,
    `ID` int NOT NULL,
    `is_subscribe` boolean,
    `subscribe_time` datetime NOT NULL,
    PRIMARY KEY(
        `SubscribeID`
    )
);


ALTER TABLE `Posts` ADD CONSTRAINT `fk_Posts_ID` FOREIGN KEY(`ID`)
REFERENCES `users` (`ID`);

ALTER TABLE `Post` ADD CONSTRAINT `fk_Post_PostID` FOREIGN KEY(`PostID`)
REFERENCES `Posts` (`PostID`);

ALTER TABLE `Favorite` ADD CONSTRAINT `fk_Favorite_ID` FOREIGN KEY(`ID`)
REFERENCES `users` (`ID`);

ALTER TABLE `Subscribe` ADD CONSTRAINT `subcribe_to_ch` FOREIGN KEY(`ChannelID`)
REFERENCES `Channel` (`ChannelID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_sub` FOREIGN KEY(`ID`)
REFERENCES `Subscribe` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_ch` FOREIGN KEY(`ID`)
REFERENCES `Channel` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_share` FOREIGN KEY(`ID`)
REFERENCES `Share` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_like` FOREIGN KEY(`ID`)
REFERENCES `Like` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `Users_to_comment` FOREIGN KEY(`ID`)
REFERENCES `Comment` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_searchH` FOREIGN KEY(`ID`)
REFERENCES `User_Search_History` (`ID`);
ALTER TABLE `Users` ADD CONSTRAINT `user_to_fav` FOREIGN KEY(`ID`)
REFERENCES `Favorite` (`ID`);
ALTER TABLE `Channel` ADD CONSTRAINT `chan_to_post` FOREIGN KEY(`ChannelID`)
REFERENCES `Post` (`ChannelID`);
ALTER TABLE `Share` ADD CONSTRAINT `share_to_post` FOREIGN KEY(`PostID`)
REFERENCES `Posts` (`PostID`);
ALTER TABLE `Like` ADD CONSTRAINT `like_to_post` FOREIGN KEY(`PostID`)
REFERENCES `Posts` (`PostID`);
ALTER TABLE `Comment` ADD CONSTRAINT `comm_to_post` FOREIGN KEY(`PostID`)
REFERENCES `Posts` (`PostID`);
ALTER TABLE `User_Search_History` ADD CONSTRAINT `hist_to_song` FOREIGN KEY(`SongID`)
REFERENCES `Songs` (`SongID`);
ALTER TABLE `Favorite` ADD CONSTRAINT `fav_to_song` FOREIGN KEY(`SongID`)
REFERENCES `Songs` (`songID`);
ALTER TABLE `Songs` ADD CONSTRAINT `song_to_post` FOREIGN KEY(`SongID`)
REFERENCES `Posts` (`SongID`);
