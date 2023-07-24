#ifndef UTILS_RELATION_H
#define UTILS_RELATION_H

#include <odb/core.hxx>
#include <string>
#include <odb/mysql/database.hxx>
#include <odb/database.hxx>
#include <memory>

std::shared_ptr<odb::database> getDB();

#endif