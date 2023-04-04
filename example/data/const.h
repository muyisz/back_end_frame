#pragma once

const char* DBEncoded = "SET NAMES GBK";
const char* CanNotFind = "can not find  data";
const char* GetUserByNameAndTypeFormat = "select * from user where id=%s and type=%d";
const char* CreateUserFormat = "insert into user(id,name,type,password) values('%s','%s', '%d', '%s')";
const char* CreateSubjectFormat = "insert into user(name,content,answer,knowledge_point,type) values('%s','%s', '%s', '%d','%d')";
const char* GetSubjectIdByNameAndContentFormat = "select * from subject where name=%s and content=%s";
const char* CreateProgramTestFormat= "insert into program_test(subject_id,example_in,example_out) values('%s','%s', '%s')";
const char* CreateProgramDataFormat = "insert into program_data(subject_id,data_in,data_out) values('%s','%s', '%s')";