#ifndef STORAGE_HPP
#define STORAGE_HPP

namespace storage
{
void init();
void sync();
const char *recordsPath();
const char *recordsTempPath();
}

#endif
