SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

CREATE SCHEMA IF NOT EXISTS `yodownet` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci ;

USE `yodownet`;

CREATE  TABLE IF NOT EXISTS `yodownet`.`urls` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `url` VARCHAR(250) NOT NULL ,
  `name` VARCHAR(101) NULL DEFAULT NULL ,
  `mimetype` VARCHAR(10) NULL DEFAULT NULL ,
  `size` INT(11) NULL DEFAULT NULL ,
  `is_done` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `hash` VARCHAR(40) NULL DEFAULT NULL ,
  `created_at` TIMESTAMP NOT NULL DEFAULT NOW() ,
  `done_at` TIMESTAMP NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE  TABLE IF NOT EXISTS `yodownet`.`tags` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `name` VARCHAR(25) NOT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE  TABLE IF NOT EXISTS `yodownet`.`taged_items` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `tag_id` INT(11) NOT NULL ,
  `object_id` INT(11) NOT NULL ,
  `object_type` VARCHAR(25) NOT NULL ,
  `created_at` TIMESTAMP NOT NULL DEFAULT NOW() ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_taged_items_tag_id` (`tag_id` ASC) ,
  CONSTRAINT `fk_taged_items_tag_id`
    FOREIGN KEY (`tag_id` )
    REFERENCES `yodownet`.`tags` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE  TABLE IF NOT EXISTS `yodownet`.`downloaders` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `executable` VARCHAR(15) NOT NULL ,
  `resume_arg` VARCHAR(10) NULL DEFAULT NULL ,
  `is_support_resume` VARCHAR(45) NULL DEFAULT NULL ,
  `is_default` TINYINT(1) NOT NULL DEFAULT FALSE ,
  `created_at` TIMESTAMP NOT NULL DEFAULT NOW() ,
  `updated_at` TIMESTAMP NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;

CREATE  TABLE IF NOT EXISTS `yodownet`.`downloader_args` (
  `id` INT(11) NOT NULL AUTO_INCREMENT ,
  `downloader_id` INT(11) NOT NULL ,
  `name` VARCHAR(15) NOT NULL ,
  `value` VARCHAR(15) NULL DEFAULT NULL ,
  `is_enable` TINYINT(1) NOT NULL DEFAULT TRUE ,
  `created_at` TIMESTAMP NOT NULL DEFAULT NOW() ,
  `updated_at` TIMESTAMP NULL DEFAULT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_downloader_args_downloader_id` (`downloader_id` ASC) ,
  CONSTRAINT `fk_downloader_args_downloader_id`
    FOREIGN KEY (`downloader_id` )
    REFERENCES `yodownet`.`downloaders` (`id` )
    ON DELETE CASCADE
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_general_ci;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
