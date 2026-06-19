#include "storage.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace storage
{
void init()
{
#ifdef __EMSCRIPTEN__
  EM_ASM({
    if (!Module.wallStorageMounted) {
      try {
        FS.mkdir('/wall');
      } catch (err) {
        if (err && err.errno !== 20) {
          throw err;
        }
      }
      FS.mount(IDBFS, {}, '/wall');
      Module.wallStorageMounted = true;
      FS.syncfs(true, function(err) {
        if (err) {
          console.error('Failed to load persistent storage:', err);
        }
      });
    }
  });
#endif
}

void sync()
{
#ifdef __EMSCRIPTEN__
  EM_ASM({
    FS.syncfs(false, function(err) {
      if (err) {
        console.error('Failed to save persistent storage:', err);
      }
    });
  });
#endif
}

const char *recordsPath()
{
#ifdef __EMSCRIPTEN__
  return "/wall/records.bin";
#else
  return "records.bin";
#endif
}

const char *recordsTempPath()
{
#ifdef __EMSCRIPTEN__
  return "/wall/_tmp";
#else
  return "_tmp";
#endif
}
}
