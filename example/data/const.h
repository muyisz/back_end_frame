#pragma once

const char* DBEncoded = "SET NAMES GBK";
const char* CanNotFind = "can not find  data";
const char* GetUserByNameAndTypeFomat = "select * from user where id=%s and type=%d";
const char* CreateUserFomat = "insert into user(id,name,type,password) values('%s','%s', '%d', '%s')";