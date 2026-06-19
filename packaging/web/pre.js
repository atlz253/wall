var Module = typeof Module !== 'undefined' ? Module : {};

Module.preRun = Module.preRun || [];
Module.preRun.push(function() {
  Module.addRunDependency('wall-idbfs');

  try {
    FS.mkdir('/wall');
  } catch (err) {
    if (!err || err.errno !== 20) {
      throw err;
    }
  }

  FS.mount(IDBFS, {}, '/wall');
  Module.wallStorageMounted = true;
  FS.syncfs(true, function(err) {
    if (err) {
      console.error('Failed to load persistent storage:', err);
    }
    Module.removeRunDependency('wall-idbfs');
  });
});
