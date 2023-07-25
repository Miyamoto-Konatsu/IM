/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `relation`;

CREATE TABLE `relation` (
  `conversationKey_ownerId` VARCHAR(128) NOT NULL,
  `conversationKey_conversationId` VARCHAR(128) NOT NULL,
  `conversationType` TEXT NOT NULL,
  `groupId` TEXT NOT NULL,
  `toUserId` TEXT NOT NULL,
  `maxSeq` BIGINT UNSIGNED NOT NULL,
  `minSeq` BIGINT UNSIGNED NOT NULL,
  PRIMARY KEY (`conversationKey_ownerId`,
               `conversationKey_conversationId`))
 ENGINE=InnoDB;

